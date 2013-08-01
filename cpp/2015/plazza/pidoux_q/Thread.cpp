#include <pthread.h>
#include <iostream>
#include "Thread.hh"

Thread::Thread(void *(*task)(void *))
{
  this->th = new pthread_t;
  this->task = task;
  this->stat = NOT_WORKING;
}


Thread::~Thread()
{
  delete th;
}


void	Thread::begin(void *arg)
{
  if (pthread_create(this->th, NULL, this->task, arg))
    std::cerr << "Cannot begin Thread." << std::endl;
  else
    this->stat = WIP;
}


void	*Thread::wait()
{
  void	*ret;

  pthread_join(*(this->th), &ret);
  this->stat = DEAD;
  return ret;
}
