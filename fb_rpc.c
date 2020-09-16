#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fb_msg.h"

#define SERVERPATH "./serversockpath" 

static pthread_mutex_t handle_mutex = PTHREAD_MUTEX_INITIALIZER;
#define handle_mutex_lock pthread_mutex_lock
#define handle_mutex_unlock pthread_mutex_unlock


static int g_handle = -1;

/******************************************************************************/
/*创建client端用于通信的handle
*******************************************************************************/
int rpc_create_handle()
{
	//定义addr
	struct sockaddr_un addr;
	int len = sizeof(addr);
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SERVERPATH);

	//创建 socket
	g_handle = socket(AF_UNIX, SOCK_STREAM, 0);
	if(g_handle < 0){
		return MSG_ERR_INNER;
	}
	
	//connect
	int ret = connect(g_handle, (struct sockaddr*)&addr, len);
	if(-1 == ret){
		return MSG_ERR_NET;
	}

	return 0;
}


void rpc_destory_handle()
{
	close(g_handle);
	g_handle =-1;
}

int rpc_send_request(im_request_t* req)
{
	int n = 0;
	int len = req->length + IM_REQ_HDR_OFFSET;

	req->length = htonl(req->length);
	req->cmd = htonl(req->cmd);

	while(n < len){		
		int r = write(g_handle, (uint8_t*)req+n, len-n);		
		if(-1 == r){
			if(EINTR == errno){
				continue;
			}else{
				rpc_destory_handle();
				perror("socket write error");
				return MSG_ERR_NET;
			}			
		}
		n += r;
	}
	return 0;	
}

int rpc_recv_result(im_result_t* res)
{
	uint32_t n = 0, len;
	int r;

	while(1){
		r = read(g_handle, (uint8_t*)res+n, MAX_BUF_LEN);
		if(-1 == r){
			if(EINTR == errno){
				continue;
			}else{
				perror("socket read error.");
				rpc_destory_handle();
				return MSG_ERR_NET;
			}
		}else if(0 == r){//pair close
			perror("pair close");
			rpc_destory_handle();
			return MSG_ERR_NET;
		}
		n += r;

		if(n >= IM_RES_HDR_OFFSET){
			len = ntohl(res->length)+IM_RES_HDR_OFFSET;
			if(n >= len){
				break;
			}
		}
	}	
	res->length = ntohl(res->length);
	res->rv = ntohl(res->rv);
	return 0;
}

int rpc_send_and_recv(im_request_t* req, im_result_t** res)
{
	im_result_t* res_t = calloc(1, MAX_BUF_LEN);
	*res = res_t;
	if(!res_t){
		return MSG_ERR_MEM;
	}
	
	handle_mutex_lock(&handle_mutex);
	int rv = rpc_send_request(req);	
	if(0 ==  rv){
		rv = rpc_recv_result(res_t);
		if(0 == rv){
			rv = res_t->rv;
		}
	}	
	handle_mutex_unlock(&handle_mutex);
	return rv;
}