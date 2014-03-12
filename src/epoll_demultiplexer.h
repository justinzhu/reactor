#ifndef _REACTOR_EPOLL_H_
#define _REACTOR_EPOLL_H_

class EpollDemultiplexer : public EventDemultiplexer
{
public:
    EpollDemultiplexer();
    virtual ~EpollDemultiplexer();

    virtual int wait_event( std::map<Handle, EventHandler *>&  handlers,
                           int timeout = 0) ;
    virtual int regist(Handle handle, Event evt) ;
    virtual int remove(Handle handle) ;

private:
    int max_fd;
    int epoll_fd;
};

#endif
