#ifndef _REACTOR_EVENT_H_
#define _REACTOR_EVENT_H_

typedef unsigned int Event;
enum EventMask
{
    ReadEvent    = 0x01,
    WriteEvent   = 0x02,
    ErrorEvent   = 0x04,
    EventMask    = 0xff
};

#endif
