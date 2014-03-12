#ifndef _REACTOR_IMPL_H_
#define _REACTPR_IMPL_H_

class ReactorImplementation
{
public:
    ReactorImplementation();
    ~ReactorImplementation();

    typedef std::map<Handle, EventHandler *>::iterator iterator;

    int regist(EventHandler* handler, Event evt);
    void remove(EventHandler* handler);
    void event_loop(int timeout = 0 );

private:
    EventDemultiplexer* demultiplexer;
    std::map<Handle, EventHandler *>  handlers;    
};

#endif
