#ifndef __FB_RPC_H__
#define __FB_RPC_H__
#ifdef __cplusplus
	extern "C"{
#endif

int rpc_create_handle();
void rpc_destory_handle();
int rpc_send_and_recv(im_request_t* req, im_result_t** res);

#ifdef __cplusplus
		}
#endif
#endif //__FB_RPC_H__