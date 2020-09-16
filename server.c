#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <execinfo.h>

#include "fb_msg.h"
#include "comm.pb-c.h"
#include "init.pb-c.h"

#define SERVERPATH "./serversockpath"

typedef int (*im_msg_process)(im_request_t *req, im_result_t **res);

static im_msg_process msg_process[IM_IOCTL_INDEX_MAX] = {NULL};

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

static int imk_msg_fill_dft_result(im_result_t **res, int rv)
{
	im_result_t *res_tmp = calloc(1, IM_REQ_HDR_OFFSET);
	res_tmp->length = 0;
	res_tmp->rv = rv;
	*res = res_tmp;
	return 0;
}

static int imk_msg_fill_result(im_result_t **res, int rv, uint8_t *buf, int len)
{
	im_result_t *res_tmp = calloc(1, IM_RES_HDR_OFFSET + len);
	memcpy(res_tmp->content, buf, len);
	res_tmp->length = len;
	res_tmp->rv = rv;
	*res = res_tmp;
	return 0;
}

int imk_msg_kern_ver_get(im_request_t *req, im_result_t **res)
{
	int rv = 0, size = 0;
	uint8_t *buff = NULL;
	Fberhome__ImVerReq ImVerRes = FBERHOME__IM_VER_REQ__INIT;

	ImVerRes.build_release = calloc(1, 256);
	if (!ImVerRes.build_release)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	strcpy(ImVerRes.build_release, "release");

	ImVerRes.build_user = calloc(1, 256);
	if (!ImVerRes.build_user)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	strcpy(ImVerRes.build_user, "user");

	ImVerRes.build_host = calloc(1, 256);
	if (!ImVerRes.build_host)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	strcpy(ImVerRes.build_host, "host");

	ImVerRes.build_date = calloc(1, 256);
	if (!ImVerRes.build_date)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	strcpy(ImVerRes.build_date, "2020");

	ImVerRes.build_arch = calloc(1, 256);
	if (!ImVerRes.build_arch)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	strcpy(ImVerRes.build_arch, "x86");

	size = fberhome__im_ver_req__get_packed_size(&ImVerRes);
	buff = calloc(1, size);
	if (!buff)
	{
		rv = MSG_ERR_MEM;
		goto END;
	}
	fberhome__im_ver_req__pack(&ImVerRes, buff);
END:
	imk_msg_fill_result(res, rv, buff, size);
	if (ImVerRes.build_release)
	{
		free(ImVerRes.build_release);
	}
	if (ImVerRes.build_user)
	{
		free(ImVerRes.build_user);
	}
	if (ImVerRes.build_host)
	{
		free(ImVerRes.build_host);
	}
	if (ImVerRes.build_date)
	{
		free(ImVerRes.build_date);
	}
	if (ImVerRes.build_arch)
	{
		free(ImVerRes.build_arch);
	}
	if (buff)
	{
		free(buff);
	}
}

int imk_msg_debug_of(im_request_t *req, im_result_t **res)
{
	int rv = 0;
	Fberhome__ImDbgReq *ImDbgReq = NULL;

	ImDbgReq = fberhome__im_dbg_req__unpack(NULL, req->length, req->content);
	if (!ImDbgReq)
	{
		rv = MSG_ERR_INNER;
		goto END;
	}
	PRINTK("imk_msg_debug_of enable=%d", ImDbgReq->enable);
END:
	imk_msg_fill_dft_result(res, rv);
	if (ImDbgReq)
	{
		fberhome__im_dbg_req__free_unpacked(ImDbgReq, NULL);
	}
	return rv;
}

int imk_rpc_send_result(int handle, im_result_t *res)
{
	int n = 0, r, len = res->length + IM_REQ_HDR_OFFSET;

	res->length = htonl(res->length);
	res->rv = htonl(res->rv);

	while (n < len)
	{
		r = write(handle, (uint8_t *)res + n, len - n);
		if (-1 == r)
		{
			if (EINTR == errno)
			{
				continue;
			}
			else
			{
				perror("socket write error.");
				close(handle);
				free((void *)res);
				return MSG_ERR_NET;
			}
		}
		n += r;
	}
	free((void *)res);
	return n;
}

int imk_rpc_recv_request(int handle, im_request_t *req)
{
	uint32_t n = 0, len;
	int r;

	while (1)
	{
		r = read(handle, (uint8_t *)req + n, MAX_BUF_LEN);
		if (-1 == r)
		{
			if (EINTR == errno)
			{
				continue;
			}
			else
			{
				perror("socket read error.");
				return 0;
			}
		}
		else if (0 == r)
		{
			return 0;
		}
		n += r;

		if (n >= IM_RES_HDR_OFFSET)
		{
			len = ntohl(req->length) + IM_RES_HDR_OFFSET;
			if (n >= len)
			{
				break;
			}
		}
	}
	req->length = ntohl(req->length);
	req->cmd = ntohl(req->cmd);
	return n;
}

int imk_rpc_msg_process(im_request_t *req, im_result_t **res)
{
	int rv = 0;
	int cmd = req->cmd;

	assert(cmd >= IM_KERNEL_VER && cmd < IM_IOCTL_INDEX_MAX);
	if (msg_process[cmd])
		rv = msg_process[cmd](req, res);
	return rv;
}

static void _rigister_msg_handler(void)
{
	msg_process[IM_KERNEL_VER] = imk_msg_kern_ver_get;
	msg_process[IM_DEBUG_OF] = imk_msg_debug_of;
}

static void _do_hand(int *clientfds, fd_set *prset, fd_set *pallset, int maxi)
{
	uint8_t buff[MAX_BUF_LEN] = {0};
	int n;
	im_request_t *req = (im_request_t *)buff;
	im_result_t *res = NULL;

	for (int i = 0; i <= maxi; i++)
	{
		if (clientfds[i] < 0)
			continue;

		if (FD_ISSET(clientfds[i], prset))
		{

			n = imk_rpc_recv_request(clientfds[i], req);
			if (0 == n) //pair close
			{
				close(clientfds[i]);
				FD_CLR(clientfds[i], pallset);
				clientfds[i] = -1;
				continue;
			}

			imk_rpc_msg_process(req, &res);

			imk_rpc_send_result(clientfds[i], res);
		}
	}
}

static void _do_select_handle(int listenfd)
{
	fd_set rset, allset;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	struct sockaddr_un cliaddr;
	int i, nready = -1, maxfd, maxi = -1, len = sizeof(cliaddr);
	int connfd;
	int clientfds[MAX_CONN_FD];
	for (i = 0; i < MAX_CONN_FD; i++)
	{
		clientfds[i] = -1;
	}

	maxfd = listenfd;
	while (1)
	{
		rset = allset;
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (-1 == nready)
		{
			if (EINTR == errno)
			{
				continue;
			}
			else
			{
				perror("select error.");
				exit(1);
			}
		}

		if (FD_ISSET(listenfd, &rset))
		{
			connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
			if (connfd == -1)
			{
				if (errno == EINTR)
				{
					continue;
				}
				else
				{
					perror("accept error");
					exit(1);
				}
			}

			for (i = 0; i < MAX_CONN_FD; i++)
			{
				if (clientfds[i] < 0)
				{
					clientfds[i] = connfd;
					break;
				}
			}

			if (i == MAX_CONN_FD)
			{
				perror("too many clients.");
				close(connfd);
				continue;
			}

			FD_SET(connfd, &allset);
			maxi = (i > maxi) ? i : maxi;
			maxfd = (connfd > maxfd) ? connfd : maxfd;

			if (--nready <= 0) // only listenfd is ready
				continue;
		}

		_do_hand(clientfds, &rset, &allset, maxi);
	}
}

static void _rpc_msg_thread(void *arg)
{
	unlink(SERVERPATH);

	//���� addr
	struct sockaddr_un addr;
	int len = sizeof(addr);
	bzero(&addr, len);

	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SERVERPATH);
	PRINTK("%s", SERVERPATH);

	//���� sock
	int listenfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		perror("socket create error.");
		exit(0);
	}

	//bind
	int ret = bind(listenfd, (struct sockaddr *)&addr, len);
	if (-1 == ret)
	{
		close(listenfd);
		perror("bind error.");
		exit(0);
	}

	//listen
	ret = listen(listenfd, 5);
	if (-1 == ret)
	{
		close(listenfd);
		perror("listen error.");
		exit(0);
	}

	_do_select_handle(listenfd);
}

void out_stack(char *sig);

void signal_exit(int dunno)
{
	char *signal_str = "";
	char dunno_str[10] = {0};
	sprintf(dunno_str, "%d", dunno);
	switch (dunno)
	{
	case 1:
		signal_str = "SIGHUP(1)";
		break;
	case 2:
		signal_str = "SIGINT(2:CTRL_C)"; //CTRL_C
		break;
	case 3:
		signal_str = "SIGQUIT(3)";
		break;
	case 6:
	{
		signal_str = "SIGABRT(6)";
		out_stack(signal_str);
	}
	break;
	case 9:
		signal_str = "SIGKILL(9)";
		break;
	case 15:
		signal_str = "SIGTERM(15 KILL)"; //kill
		break;
	case 11:
	{
		signal_str = "SIGSEGV(11)"; //SIGSEGV
		out_stack(signal_str);
	}
	break;
	default:
		signal_str = "OTHER";
		break;
	}
	PRINTK("%s", signal_str);
	exit(0);
}

static void output_addrline(char addr[])
{
	char cmd[256];
	char line[256];
	char addrline[32] = {
		0,
	};
	char *str1, *str2;
	FILE *file;

	str1 = strchr(addr, '[');
	str2 = strchr(addr, ']');
	if (str1 == NULL || str2 == NULL)
	{
		return;
	}
	memcpy(addrline, str1 + 1, str2 - str1);
	snprintf(cmd, sizeof(cmd), "addr2line -e /proc/%d/exe %s ", getpid(), addrline);
	file = popen(cmd, "r");
	if (NULL != fgets(line, 256, file))
	{
		printf("%s\n", line);
	}
	pclose(file);
}

void out_stack(char *sig)
{
	void *array[32];
	size_t size;
	char **strings;
	uint32_t i;

	printf("%s\n", sig);
	size = backtrace(array, 32);
	strings = backtrace_symbols(array, size);
	if (NULL == strings)
	{
		printf("backtrace_symbols\n");
		return;
	}

	for (i = 0; i < size; i++)
	{
		printf("%s", strings[i]);
		output_addrline(strings[i]);
	}

	free(strings);
}

static void _rigister_signal_hander()
{
	signal(SIGHUP, signal_exit);
	signal(SIGINT, signal_exit);
	signal(SIGQUIT, signal_exit);
	signal(SIGABRT, signal_exit);
	signal(SIGKILL, signal_exit);
	signal(SIGTERM, signal_exit);
	signal(SIGSEGV, signal_exit);
}

int main(int argc, char **argv)
{
	pthread_t tid;

	_rigister_signal_hander();

	_rigister_msg_handler();

	if (pthread_create(&tid, NULL, (void *)_rpc_msg_thread, NULL) != 0)
	{
		perror("pthread create error.");
		return 0;
	}
	pthread_join(tid, NULL);

	return 0;
}
