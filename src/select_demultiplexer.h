#ifndef _REACTOR_SELECT_H_
#define _REACTOR_SELECT_H_

class SelectDemultiplexer : public EventDemultiplexer
{
public:
    SelectDemultiplexer();
    virtual ~SelectDemultiplexer();

    virtual int wait_event( std::map<Handle, EventHandler *>&  handlers,
                           int timeout = 0) ;
    virtual int regist(Handle handle, Event evt) ;
    virtual int remove(Handle handle) ;

private:
    fd_set read_set;
    fd_set write_set;
    fd_set err_set;
};

#endif
