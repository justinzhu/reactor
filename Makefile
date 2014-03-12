epoll:
	cd src; $(MAKE) "PLAT=-D_USE_EPOLL" "DEMULTIPLEX=epoll_demultiplexer.o"

select:
	cd src; $(MAKE) "PLAT=-D_USE_SELECT" "DEMULTIPLEX=select_demultiplexer.o"

clean:
	cd src; $(MAKE) clean
