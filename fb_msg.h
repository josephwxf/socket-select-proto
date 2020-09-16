#ifndef __IM_RPC_MSG_H__
#define __IM_RPC_MSG_H__
#ifdef __cplusplus
	extern "C" {
#endif

#include <stdint.h>


typedef struct{
	int length;
	int cmd;
	uint8_t content[0];
}im_request_t;
#define IM_REQ_HDR_OFFSET sizeof(im_request_t)

typedef struct{
	int length;
	int rv;
	uint8_t content[0];
}im_result_t;
#define IM_RES_HDR_OFFSET sizeof(im_request_t)

enum{
	MSG_OK = 0,
	MSG_ERR_PARAM,
	MSG_ERR_NET,
	MSG_ERR_MEM,
	MSG_ERR_INNER,
};

enum{
	IM_KERNEL_VER,
	IM_DEBUG_OF,
	IM_PORT_INIT,
	IM_PORT_CLEAR,
	IM_IOCTL_INDEX_MAX
};

#define MAX_BUF_LEN (1<<16)
#define MAX_CONN_FD 100

#define MSG_COMM (1<<1)
#define MSG_PORT (1<<2)
#define MSG_VLAN (1<<3)

#ifdef __cplusplus
		}
#endif
#endif//__IM_RPC_MSG_H__