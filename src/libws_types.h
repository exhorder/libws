
#ifndef __LIBWS_TYPES_H__
#define __LIBWS_TYPES_H__

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "libws_header.h"

typedef struct ws_s *ws_t;
typedef struct ws_base_s *ws_base_t;

#define WS_MAX_FRAME_SIZE 0x7FFFFFFFFFFFFFFF
#define WS_DEFAULT_CONNECT_TIMEOUT 60

typedef enum ws_state_e
{
	WS_STATE_DNS_LOOKUP,
	WS_STATE_CLOSING,
	WS_STATE_CLOSING_UNCLEANLY,
	WS_STATE_CLOSED_CLEANLY,
	WS_STATE_CLOSED_UNCLEANLY,
	WS_STATE_CONNECTING,
	WS_STATE_CONNECTED
} ws_state_t;

typedef enum ws_parse_state_e
{
	WS_PARSE_STATE_USER_ABORT = -2,
	WS_PARSE_STATE_ERROR = -1,
	WS_PARSE_STATE_SUCCESS = 0,
	WS_PARSE_STATE_NEED_MORE
} ws_parse_state_t;

#ifdef LIBWS_WITH_OPENSSL
typedef enum libws_ssl_state_e
{
	LIBWS_SSL_OFF,
	LIBWS_SSL_ON,
	LIBWS_SSL_SELFSIGNED
} libws_ssl_state_t;
#endif // LIBWS_WITH_OPENSSL

#define WS_RANDOM_PATH "/dev/urandom"

typedef void (*ws_msg_callback_f)(ws_t ws, char *msg, uint64_t len, int binary, void *arg);

typedef void (*ws_msg_begin_callback_f)(ws_t ws, void *arg);
typedef void (*ws_msg_frame_callback_f)(ws_t ws, char *payload, uint64_t len, void *arg);
typedef void (*ws_msg_end_callback_f)(ws_t ws, void *arg);

typedef void (*ws_msg_frame_begin_callback_f)(ws_t ws, void *arg);
typedef void (*ws_msg_frame_data_callback_f)(ws_t ws, char *payload, uint64_t len, void *arg);
typedef void (*ws_msg_frame_end_callback_f)(ws_t ws, void *arg);

typedef void (*ws_err_callback_f)(ws_t ws, int errcode, const char *errmsg, void *arg);
typedef void (*ws_close_callback_f)(ws_t ws, ws_close_status_t status, const char *reason, size_t reason_len, void *arg);
typedef void (*ws_connect_callback_f)(ws_t ws, void *arg);
typedef void (*ws_timeout_callback_f)(ws_t ws, struct timeval timeout, void *arg);
typedef void (*ws_no_copy_cleanup_f)(ws_t ws, const void *data, uint64_t datalen, void *extra);
typedef int (*ws_header_callback_f)(ws_t ws, const char *header_name, const char *header_val, void *arg);

typedef void *(*ws_malloc_replacement_f)(size_t bytes);
typedef void (*ws_free_replacement_f)(void *ptr);
typedef void *(*ws_realloc_replacement_f)(void *ptr, size_t bytes);

#endif // __LIBWS_TYPES_H__