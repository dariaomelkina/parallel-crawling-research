#include "EpollCrawler.h"

void *EpollCrawler::parsing_thread(void *args) {
    auto params = (async_parsing_args_t *) args;

    pthread_barrier_wait(params->start_barrier_ptr);

    std::deque<std::string> *input_ptr = params->input_ptr;
    size_t max_events = params->max_requests;

    size_t current_index = params->threads_index;


    epoll_event read_event{};
    read_event.events = EPOLLIN;

    epoll_event connect_event{};
    connect_event.events = EPOLLOUT;


    auto events = new epoll_event[max_events];


    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        throw std::runtime_error("Failed to create epoll file descriptor");
    }

    std::unordered_map<int, html_getter_t *> responses;

    for (size_t i = 0; i < max_events; i++) {
        int sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
        if (sock < 0) {
            throw std::runtime_error("Can't create socket");
        }
        auto html_getter_ptr = new html_getter_t;
        html_getter_ptr->mode = SOCK_IDLE;
        html_getter_ptr->buffer = new char[MAX_SIZE];
        html_getter_ptr->index = 0;
        responses[sock] = html_getter_ptr;
    }

    size_t active_events = 0;

    for (auto&[sock, html_getter_ptr]: responses) {
        while (current_index < input_ptr->size()) {
            html_getter_ptr->parsed_url = parse_url((*input_ptr)[current_index]);
            current_index += params->threads_num;
            int res = connect_to_host(sock, html_getter_ptr->parsed_url);
            if (res < 0 && errno != EINPROGRESS) {
                std::cout << "Can't connect to host" << std::endl;
            } else {
                html_getter_ptr->mode = SOCK_CONNECTING;
                connect_event.data.fd = sock;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock, &connect_event);
                active_events++;
                break;
            }
        }
    }


    size_t bytes_read;


    while (current_index < input_ptr->size() || active_events != 0) {

        // Wait and test whether the connections are ready and have transmitted some
        // data
        size_t ready_events = epoll_wait(epoll_fd, events, max_events, -1);
        for (size_t i = 0; i < ready_events; i++) {
            int sock = events[i].data.fd;
            bool need_new = false;
            if (responses[sock]->mode == SOCK_CONNECTING) {
                if (send_request(sock, responses[sock]->parsed_url, ADDITIONAL_PARAMS)) {
                    read_event.data.fd = sock;
                    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, sock, &read_event);
                    responses[sock]->mode = SOCK_READING;
                    break;
                } else {
                    std::cout << "Can't send request in while loop" << std::endl;
                    need_new = true;
                }
            } else if (responses[sock]->mode == SOCK_READING) {
                bytes_read = read(
                        sock,
                        responses[sock]->buffer + responses[events[i].data.fd]->index,
                        MAX_SIZE - responses[sock]->index
                );
                responses[sock]->index += bytes_read;
                if (bytes_read == 0) {
                    need_new = true;
                    std::cout << responses[sock]->index << std::endl;
                    count_tags(responses[sock]->buffer, responses[sock]->index);
                }
            }

            if (!need_new) {
                continue;
            }

            active_events--;

            int new_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
            auto html_getter_ptr = new html_getter_t;
            html_getter_ptr->mode = SOCK_IDLE;
            html_getter_ptr->buffer = responses[sock]->buffer;
            html_getter_ptr->index = 0;

            responses[new_socket] = html_getter_ptr;

            delete responses[sock];
            responses.erase(sock);
            close(sock);


            while (current_index < input_ptr->size() && need_new) {
                responses[new_socket]->parsed_url = parse_url((*input_ptr)[current_index]);
                current_index += params->threads_num;

                int res = connect_to_host(new_socket, responses[new_socket]->parsed_url);
                if (res < 0 && errno != EINPROGRESS) {
                    std::cout << "Can't connect to host in while loop" << std::endl;
                } else {
                    responses[new_socket]->mode = SOCK_CONNECTING;
                    connect_event.data.fd = new_socket;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &connect_event);
                    active_events++;
                    need_new = false;
                }
            }

            if (need_new) {
                close(new_socket);
                delete[] responses[new_socket]->buffer;
                delete responses[new_socket];
                responses.erase(new_socket);
            }
        }
    }

    delete[] events;

    // Once no urls are available anymore, finish working
    if (close(epoll_fd)) {
        throw std::runtime_error("Failed to close epoll file descriptor");
    }

    delete params;

    return nullptr;
}

EpollCrawler::EpollCrawler(size_t max_workers, size_t max_requests) : AbstractCrawler(max_workers),
                                                                      _max_requests(max_requests) {}

void EpollCrawler::process_queue() {

    if (max_workers < 1) {
        throw std::runtime_error("There are no workers");
    }

    pthread_barrier_t start_barrier;
    pthread_barrier_init(&start_barrier, nullptr, max_workers);


    auto threads = new pthread_t[max_workers - 1];


    for (size_t i = 0; i < max_workers - 1; i++) {
        auto args = new async_parsing_args_t;
        args->input_ptr = &input_queue;
        args->threads_num = max_workers;
        args->threads_index = i;
        args->max_requests = _max_requests;
        args->start_barrier_ptr = &start_barrier;
        pthread_create(&threads[i], nullptr, EpollCrawler::parsing_thread, (void *) args);
    }

    auto main_args = new async_parsing_args_t;
    main_args->input_ptr = &input_queue;
    main_args->threads_num = max_workers;
    main_args->threads_index = max_workers - 1;
    main_args->max_requests = _max_requests;
    main_args->start_barrier_ptr = &start_barrier;

    EpollCrawler::parsing_thread((void *) main_args);


    for (size_t i = 0; i < max_workers - 1; i++) {
        pthread_join(threads[i], nullptr);
    }

    input_queue.clear();

    delete[] threads;
    pthread_barrier_destroy(&start_barrier);
}