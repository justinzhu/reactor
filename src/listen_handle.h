#ifndef _REACTOR_LISTEN_HANDLE_H_
#define _REACTOR_LISTEN_HANDLE_H_

class ListenHandle : public EventHandler
{
  public:
    ListenHandle();
    virtual ~ListenHandle();

    virtual Handle get_handle() const { return listenfd; }
    virtual void handle_read();
    virtual void handle_write() {}
    virtual void handle_error(); 
	
	bool listenOn( int port );

  private:
	void setNonBlocking( int fd );	

  private:
    Handle listenfd;
};

#endif
