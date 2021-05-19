#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>

#include "EpollCrawler.h"

void *EpollCrawler::parsing_thread(void *args) {
  std::queue<std::string> urls = *(std::queue<std::string> *)args;
  // Initialize epoll structures
  epoll_event event;
  // Tell the kernel we are waiting for inputs
  event.events = EPOLLIN;

  epoll_event events[MAX_EVENTS];
  int epoll_fd = epoll_create1(0);

  if (epoll_fd == -1) {
    std::cerr << "Failed to create epoll file descriptor" << std::endl;
    exit(-1);
  }

  size_t event_count;
  size_t total_urls = urls.size();
  size_t finished = 0;
  size_t events_waiting = 0;

  size_t bytes_read;
  char read_buffer[READ_SIZE + 1];
  std::unordered_map<int, std::string> responses;
  while (finished != total_urls) {
    // If we are able to, open up a new socket and add it to the wait list
    if (events_waiting < MAX_EVENTS) {
      int socket = get_socket(urls.front());
      urls.pop();
      event.data.fd = socket;
      epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket, &event);
      ++events_waiting;
    }

    // Wait and test whether the connections are ready and have transmitted some
    // data
    event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
    for (size_t i = 0; i < event_count; i++) {
      std::cout << "Reading file descriptor " << events[i].data.fd << std::endl;
      bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
      if (bytes_read == 0) {
        std::cout << "Closing file descriptor " << events[i].data.fd << std::endl;
        // I think (?) we can consider this socket's fully read?
        // I have no idea how to understand whether we've read all of the
        // data, this 'if' will probably never get called due to how epoll
        // works
        ++finished;
        --events_waiting;
        close(events[i].data.fd);
        continue;
      }
      responses[events[i].data.fd].append(read_buffer, bytes_read);
    }
  }

  // TODO: parse the result on our own, without sending it to the main thread

  // Once no urls are available anymore, finish working
  if (close(epoll_fd)) {
    std::cerr << "Failed to close epoll file descriptor" << std::endl;
    exit(-1);
  }

  exit(0);
}

EpollCrawler::EpollCrawler(size_t max_workers) : AbstractCrawler(max_workers) {}

void EpollCrawler::process_queue() {

  // Split the available workload between several threads
  std::vector<pthread_t> threads;
  threads.reserve(max_workers);
  size_t queue_len = input_queue.size();

  for (size_t i = 0; i < max_workers - 1; ++i) {
    std::queue<std::string> urls;
    for (size_t j = 0; j < queue_len / max_workers; j++) {
      urls.emplace(input_queue.front());
      input_queue.pop_front();
    }
    pthread_create(&threads[i], nullptr, EpollCrawler::parsing_thread,
                   (void *)&urls);
  }
  std::queue<std::string> urls;
  while (!input_queue.empty()) {
    urls.emplace(input_queue.front());
    input_queue.pop_front();
  }
  pthread_create(&threads[max_workers - 1], nullptr,
                 EpollCrawler::parsing_thread, (void *)&urls);

  std::cout << "Created " << max_workers << " threads" << std::endl;

  void *retval;
  // Waiting for all workers to finish
  for (size_t i = 0; i < max_workers; i++) {
    pthread_join(threads[i], &retval);
    // TODO: add thread error handling
    std::cout << retval << std::endl;
  }
}