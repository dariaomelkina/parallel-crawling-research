#include <unistd.h>
#include <sys/epoll.h>
#include <iostream>

#include "EpollCrawler.h"

///


//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <errno.h>
//#include <sys/socket.h>
//#include <resolv.h>
//#include <arpa/inet.h>
//
//#define PORT 22
//#define SERVER "127.0.0.1"
//#define MAXBUF 1024
//#define MAX_EPOLL_EVENTS 64
//
//int main() {
//  int sockfd;
//  struct sockaddr_in dest;
//  char buffer[MAXBUF];
//  struct epoll_event events[MAX_EPOLL_EVENTS];
//  int i, num_ready;
//
//  /*---Open socket for streaming---*/
//  if ( (sockfd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0)) < 0 ) {
//    perror("Socket");
//    exit(errno);
//  }
//
//  /*---Add socket to epoll---*/
//  int epfd = epoll_create(1);
//  struct epoll_event event;
//  event.events = EPOLLIN; // Cann append "|EPOLLOUT" for write events as well
//  event.data.fd = sockfd;
//  epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
//
//  /*---Initialize server address/port struct---*/
//  bzero(&dest, sizeof(dest));
//  dest.sin_family = AF_INET;
//  dest.sin_port = htons(PORT);
//  if ( inet_pton(AF_INET, SERVER, &dest.sin_addr.s_addr) == 0 ) {
//    perror(SERVER);
//    exit(errno);
//  }
//
//  /*---Connect to server---*/
//  if ( connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) != 0 ) {
//    if(errno != EINPROGRESS) {
//      perror("Connect ");
//      exit(errno);
//    }
//  }
//
//  /*---Wait for socket connect to complete---*/
//  num_ready = epoll_wait(epfd, events, MAX_EPOLL_EVENTS, 1000/*timeout*/);
//  for(i = 0; i < num_ready; i++) {
//    if(events[i].events & EPOLLIN) {
//      printf("Socket %d connected\n", events[i].data.fd);
//    }
//  }
//
//  /*---Wait for data---*/
//  num_ready = epoll_wait(epfd, events, MAX_EPOLL_EVENTS, 1000/*timeout*/);
//  for(i = 0; i < num_ready; i++) {
//    if(events[i].events & EPOLLIN) {
//      printf("Socket %d got some data\n", events[i].data.fd);
//      bzero(buffer, MAXBUF);
//      recv(sockfd, buffer, sizeof(buffer), 0);
//      printf("Received: %s", buffer);
//    }
//  }
//
//  close(sockfd);
//  return 0;
//}

///

void* EpollCrawler::parsing_thread(void* args) {
  std::queue<std::string> urls = *(std::queue<std::string>*)args;
  // Initialize epoll structures
  epoll_event event;
  epoll_event events[MAX_EVENTS];
  int epoll_fd = epoll_create1(0);

  if(epoll_fd == -1)
  {
    std::cerr << "Failed to create epoll file descriptor" << std::endl;
    exit(-1);
  }

  // Tell the kernel we are waiting for inputs
  event.events = EPOLLIN;
  event.data.fd = 0;

  bool running = true;
  size_t event_count;
  size_t total_urls = urls.size();
  size_t finished = 0;
  size_t events_waiting = 0;

  size_t bytes_read;
  char read_buffer[READ_SIZE + 1];
  while(finished != total_urls)
  {
    // If we are able to, open up a new socket and add it to the wait list
    if (events_waiting < MAX_EVENTS) {
      int sock = get_socket(urls.front());
      urls.pop();

      std::string response{};
      char buffer[RESPONSE_BUFFER_SIZE];

      while (true) {
        size_t char_read = read(sock, buffer, RESPONSE_BUFFER_SIZE);
        if (char_read == 0) {
          break;
        }
        response.append(buffer, char_read);
      }

      close(sock);
    }

    // wait and test whether the connections are ready and have transmitted some data
    event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
    for(size_t i = 0; i < event_count; i++)
    {
      std::cout << "Reading file descriptor " << events[i].data.fd << std::endl;
      bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
      std::cout << bytes_read << " bytes read.\n" << std::endl;
      read_buffer[bytes_read] = '\0';
    }
  }

  // TODO: parse the result on our own, without sending it to the main thread

  // once no urls are available anymore, finish working
  if(close(epoll_fd))
  {
    std::cerr << "Failed to close epoll file descriptor" << std::endl;
    exit(-1);
  }

  exit(0);
}

EpollCrawler::EpollCrawler(size_t max_workers) : AbstractCrawler(max_workers) {}

void EpollCrawler::process_queue() {

  // split the available workload between several threads
  std::vector<pthread_t> threads;
  threads.reserve(max_workers);
  size_t queue_len = input_queue.size();

  for (size_t i = 0; i < max_workers - 1; ++i) {
    std::queue<std::string> urls;
    for (size_t j = 0; j < queue_len / max_workers; j++) {
      urls.emplace(input_queue.front());
      input_queue.pop();
    }
    pthread_create(&threads[i], nullptr, EpollCrawler::parsing_thread, (void *) &urls);
  }

  void *retval;
  // waiting for all workers to finish
  for (size_t i = 0; i < max_workers; i++) {
    pthread_join(threads[i], &retval);
    // add thread error handling
    std::cout << retval << std::endl;
  }
}