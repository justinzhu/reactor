#ifndef _REACTOR_SOCK_HANDLE_H_
#define _REACTOR_SOCK_HANDLE_H_

class SockHandle : public EventHandler
{
  public:
    SockHandle( Handle fd );
    virtual ~SockHandle();

    virtual Handle get_handle() const;
    virtual void handle_read();
    virtual void handle_write();
    virtual void handle_error();

  private:
    Handle sock_fd;
    char* buf;
    static const int MAX_SIZE = 1024;
};

#endif
