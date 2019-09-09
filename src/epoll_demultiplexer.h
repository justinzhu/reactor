#ifndef _REACTOR_EPOLL_H_
#define _REACTOR_EPOLL_H_

#include <vector>
#include <sys/epoll.h>

class EpollDemultiplexer : public EventDemultiplexer
{
public:
    EpollDemultiplexer();
    virtual ~EpollDemultiplexer();

    virtual int wait_event( std::map<Handle, EventHandler *>&  handlers,
                           int timeout = 0) ;
    virtual int regist(EventHandler* handle, Event evt) ;
    virtual int remove(Handle handle) ;

private:
    static const int max_event;
    int epoll_fd;
    std::vector<struct epoll_event> evs; 
};

#endif
