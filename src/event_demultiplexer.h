#ifndef _REACTOR_EVENTDEMULTIPLEXER_H_
#define _REACTOR_EVENTDEMULTIPLEXER_H_

class EventDemultiplexer
{
public:
    EventDemultiplexer() {}
    virtual ~EventDemultiplexer() {}
    virtual int wait_event( std::map<Handle, EventHandler *>&  handlers,
                           int timeout = 0) = 0;
    virtual int regist(EventHandler* handle, Event evt) = 0;
    virtual int remove(Handle handle) = 0;
};

#endif 
