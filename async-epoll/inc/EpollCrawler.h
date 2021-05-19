#ifndef ASYNC_EPOLL_H
#define ASYNC_EPOLL_H

#include "pthread.h"

#include "AbstractCrawler.h"

#define RESPONSE_BUFFER_SIZE 512
#define MAX_EVENTS 25
#define READ_SIZE 1024*1024

class EpollCrawler : public AbstractCrawler {
protected:
  static void* parsing_thread(void* args);

public:
  explicit EpollCrawler(size_t max_workers);

  virtual void process_queue();
};

#endif
