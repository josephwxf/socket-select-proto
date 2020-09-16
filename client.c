#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#include "fb_msg.h"
#include "fb_rpc.h"
#include "comm.pb-c.h"
#include "init.pb-c.h"

#define PRINTK(fmt, ...)                           \
	do                                             \
	{                                              \
		if (1)                                     \
		{                                          \
			printf("[%s,%d]", __FILE__, __LINE__); \
			printf(fmt, ##__VA_ARGS__);            \
			printf("\n");                          \
		}                                          \
	} while (0)

double epoch_double()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec * 1.0) / 1000000.0;
}

typedef struct
{
	char *build_release;
	char *build_user;
	char *build_host;
	char *build_date;
	char *build_datestamp;
	char *build_tree;
	char *build_arch;
	char *build_os;
} im_version_t;

int im_kernel_version(im_version_t *ver)
{
	int rv, size = 0;
	uint8_t *buff = NULL;
	im_request_t *req = NULL;
	im_result_t *res = NULL;
	Fberhome__ImVerReq *ImVerRes = NULL;

	req = calloc(1, IM_REQ_HDR_OFFSET);
	if (!req)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	req->length = 0;
	req->cmd = IM_KERNEL_VER;
	rv = rpc_send_and_recv(req, &res);
	if (rv != MSG_OK)
	{
		goto END;
	}
	ImVerRes = fberhome__im_ver_req__unpack(NULL, res->length, res->content);
	if (ImVerRes)
	{
		if (ImVerRes->build_arch && ver->build_arch)
		{
			strcpy(ver->build_arch, ImVerRes->build_arch);
		}
		if (ImVerRes->build_date && ver->build_date)
		{
			strcpy(ver->build_date, ImVerRes->build_date);
		}
		fberhome__im_ver_req__free_unpacked(ImVerRes, NULL);
	}

	PRINTK("%s,%s", ver->build_arch, ver->build_date);
END:
	if (req)
		free(req);
	if (res)
		free(res);
	if (buff)
		free(buff);
	return rv;
}

int im_debug_of(int off)
{
	int rv = 0, size = 0;
	uint8_t *buff = NULL;
	im_request_t *req = NULL;
	im_result_t *res = NULL;
	Fberhome__ImDbgReq ImDbgReq = FBERHOME__IM_DBG_REQ__INIT;
	ImDbgReq.enable = 1;

	size = fberhome__im_dbg_req__get_packed_size(&ImDbgReq);
	buff = malloc(size);
	if (!buff)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	fberhome__im_dbg_req__pack(&ImDbgReq, buff);

	req = calloc(1, IM_REQ_HDR_OFFSET + size);
	if (!req)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	req->length = size;
	req->cmd = IM_DEBUG_OF;
	memcpy(req->content, buff, size);

	rv = rpc_send_and_recv(req, &res);
END:
	if (req)
		free(req);
	if (res)
		free(res);
	if (buff)
		free(buff);

	return rv;
}

int main(int argc, char **argv)
{
	int rv;
	rv = rpc_create_handle();
	if (rv != MSG_OK)
		return 0;

	im_version_t knl_ver;
	knl_ver.build_release = calloc(1, 256);
	knl_ver.build_user = calloc(1, 256);
	knl_ver.build_host = calloc(1, 256);
	knl_ver.build_date = calloc(1, 256);
	knl_ver.build_datestamp = calloc(1, 256);
	knl_ver.build_tree = calloc(1, 256);
	knl_ver.build_arch = calloc(1, 256);
	knl_ver.build_os = calloc(1, 256);
	rv = im_kernel_version(&knl_ver);

	rv = im_debug_of(1);

	return 0;
}
