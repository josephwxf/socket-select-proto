all:libpproto.so server client

OBJS:=comm.pb-c.o init.pb-c.o

CFLAGS:=-W -g

libpproto.so:$(OBJS)
	@echo [CC] $@
	gcc -shared -fPIC $(OBJS) -o $@
$(OBJS):%.o:%.c
	@echo [CC] $@
	gcc -fPIC $(CFLAGS) -o $@ -W -c $<
%.pb-c.c:%.proto
	protoc-c --c_out=$(@D) $<
	
.PHONY:all clean

server:server.c fbk_rpc.c fb_msg.h
	gcc $(CFLAGS) -rdynamic -Wl,-rpath=./ -o server server.c fbk_rpc.c  -L. -lrt -lpthread -lpproto -lprotobuf-c 

client:client.c fb_rpc.c fb_msg.h
	gcc $(CFLAGS) -rdynamic -Wl,-rpath=./ -o client client.c fb_rpc.c   -L. -lrt -lpthread -lpproto -lprotobuf-c 

clean:
	rm -rf server client *.o *.pb-c.c *.pb-c.h *.pb-c.o
