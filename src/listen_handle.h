#ifndef _REACTOR_LISTEN_HANDLE_H_
#define _REACTOR_LISTEN_HANDLE_H_

class ListenHandle : public EventHandler
{
  public:
    ListenHandle( int fd );
    virtual ~ListenHandle();

    virtual Handle get_handle() const { return listen_fd; }
    virtual void handle_read();
    virtual void handle_write() {}
    virtual void handle_error(); 

  private:
    Handle listen_fd;
};

#endif
