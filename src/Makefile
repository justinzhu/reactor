CXX=g++
CFLAGS=-g -Wall
PLAT=-DEPOLL
DEMULTIPLEX=epoll_demultiplexer.o
OBJS=$(DEMULTIPLEX) reactor.o reactor_impl.o listen_handle.o sock_handle.o
BIN=client server

.SUFFIXES:.cpp .o

.cpp.o:
	$(CXX) -c $< $(CFLAGS) $(PLAT)

all:$(BIN)

server:server.o $(OBJS)
	$(CXX) $^ -o $@

client:client.o
	$(CXX) $^ -o $@

clean:
	$(RM) *.o  $(BIN) core*
