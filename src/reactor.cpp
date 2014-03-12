#include <stdint.h>
#include <unistd.h>

#include <map>

#include "reactor.h"

Reactor Reactor::reactor;

Reactor& Reactor::get_instance()
{
    return reactor;
}

Reactor::Reactor()
{
    impl = new ReactorImplementation(); 
}

Reactor::~Reactor()
{
    if ( impl )
        delete impl;
}

int Reactor::regist( EventHandler* handle, Event evt )
{
    return impl->regist( handle, evt );
}

void Reactor::remove( EventHandler* handle )
{
    return impl->remove( handle );
}

void Reactor::event_loop( int timeout )
{
    impl->event_loop( timeout );
}


