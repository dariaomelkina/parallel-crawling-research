#include "EpollCrawler.h"

void *EpollCrawler::parsing_thread(void *args) {
    auto params = (async_parsing_args_t*) args;
    std::deque<std::string> *input_ptr = params->input_ptr;
    size_t max_events = params->max_requests;

    // Initialize epoll structures
    epoll_event event{};

    // Tell the kernel we are waiting for inputs
    event.events = EPOLLIN;

    auto events = new epoll_event[max_events];
    std::unordered_map<size_t, std::pair<size_t, char*>> responses;
    int epoll_fd = epoll_create1(0);

    if (epoll_fd == -1) {
        throw std::runtime_error("Failed to create epoll file descriptor");
    }

    size_t event_count;
    size_t events_waiting = 0;
    size_t current_index = params->threads_index;

    for (size_t i = 0; i < max_events; i++) {
        if (current_index >= input_ptr->size()) {
            break;
        }
        int socket = get_socket((*input_ptr)[current_index]);
        current_index += params->threads_num;
        responses[socket] = std::make_pair(0, new char [MAX_SIZE]);
        event.data.fd = socket;
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket, &event);
        ++events_waiting;
    }


    size_t bytes_read;


    while (current_index < input_ptr->size() || events_waiting != 0) {

        // Wait and test whether the connections are ready and have transmitted some
        // data
        event_count = epoll_wait(epoll_fd, events, max_events, -1);
        for (size_t i = 0; i < event_count; i++) {
            bytes_read = read(
                    events[i].data.fd,
                    responses[events[i].data.fd].second + responses[events[i].data.fd].first,
                    MAX_SIZE
                    );
            responses[events[i].data.fd].first += bytes_read;
            if (bytes_read == 0) {
                --events_waiting;
                close(events[i].data.fd);
                size_t tags = count_tags(responses[events[i].data.fd].second, responses[events[i].data.fd].first);

                // starting a new connection
                if (current_index < input_ptr->size()) {
                    int socket = get_socket((*input_ptr)[current_index]);
                    current_index += params->threads_num;
                    responses[socket] = std::make_pair(0, new char [MAX_SIZE]);
                    event.data.fd = socket;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket, &event);
                    ++events_waiting;
                }
            }


        }
    }


    for (auto& resp: responses) {
        delete[] resp.second.second;
    }
    delete[] events;

    // Once no urls are available anymore, finish working
    if (close(epoll_fd)) {
        throw std::runtime_error("Failed to close epoll file descriptor");
    }

    return nullptr;
}

EpollCrawler::EpollCrawler(size_t max_workers, size_t max_requests) : AbstractCrawler(max_workers), _max_requests(max_requests){}

void EpollCrawler::process_queue() {

    if (max_workers < 1) {
        throw std::runtime_error("There are no workers");
    }

    auto threads = new pthread_t[max_workers - 1];


    for (size_t i = 0; i < max_workers - 1; i++) {
        auto args = new async_parsing_args_t;
        args->input_ptr = &input_queue;
        args->threads_num = max_workers;
        args->threads_index = i;
        args->max_requests = _max_requests;
        pthread_create(&threads[i], nullptr, EpollCrawler::parsing_thread, (void*) args);
    }

    auto main_args = new async_parsing_args_t;
    main_args->input_ptr = &input_queue;
    main_args->threads_num = max_workers;
    main_args->threads_index = max_workers - 1;
    main_args->max_requests = _max_requests;

    EpollCrawler::parsing_thread((void*) main_args);


    for (size_t i = 0; i < max_workers - 1; i++) {
        pthread_join(threads[i], nullptr);
    }

    input_queue.clear();

    delete[] threads;
}