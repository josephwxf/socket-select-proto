/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: comm.proto */

#ifndef PROTOBUF_C_comm_2eproto__INCLUDED
#define PROTOBUF_C_comm_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1002001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Fberhome__ImPbmp Fberhome__ImPbmp;
typedef struct _Fberhome__FbInitReq Fberhome__FbInitReq;
typedef struct _Fberhome__ImDbgReq Fberhome__ImDbgReq;


/* --- enums --- */


/* --- messages --- */

struct  _Fberhome__ImPbmp
{
  ProtobufCMessage base;
  size_t n_pbmp;
  uint32_t *pbmp;
};
#define FBERHOME__IM_PBMP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&fberhome__im_pbmp__descriptor) \
    , 0,NULL }


struct  _Fberhome__FbInitReq
{
  ProtobufCMessage base;
  int32_t unit;
};
#define FBERHOME__FB_INIT_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&fberhome__fb_init_req__descriptor) \
    , 0 }


struct  _Fberhome__ImDbgReq
{
  ProtobufCMessage base;
  int32_t enable;
};
#define FBERHOME__IM_DBG_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&fberhome__im_dbg_req__descriptor) \
    , 0 }


/* Fberhome__ImPbmp methods */
void   fberhome__im_pbmp__init
                     (Fberhome__ImPbmp         *message);
size_t fberhome__im_pbmp__get_packed_size
                     (const Fberhome__ImPbmp   *message);
size_t fberhome__im_pbmp__pack
                     (const Fberhome__ImPbmp   *message,
                      uint8_t             *out);
size_t fberhome__im_pbmp__pack_to_buffer
                     (const Fberhome__ImPbmp   *message,
                      ProtobufCBuffer     *buffer);
Fberhome__ImPbmp *
       fberhome__im_pbmp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   fberhome__im_pbmp__free_unpacked
                     (Fberhome__ImPbmp *message,
                      ProtobufCAllocator *allocator);
/* Fberhome__FbInitReq methods */
void   fberhome__fb_init_req__init
                     (Fberhome__FbInitReq         *message);
size_t fberhome__fb_init_req__get_packed_size
                     (const Fberhome__FbInitReq   *message);
size_t fberhome__fb_init_req__pack
                     (const Fberhome__FbInitReq   *message,
                      uint8_t             *out);
size_t fberhome__fb_init_req__pack_to_buffer
                     (const Fberhome__FbInitReq   *message,
                      ProtobufCBuffer     *buffer);
Fberhome__FbInitReq *
       fberhome__fb_init_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   fberhome__fb_init_req__free_unpacked
                     (Fberhome__FbInitReq *message,
                      ProtobufCAllocator *allocator);
/* Fberhome__ImDbgReq methods */
void   fberhome__im_dbg_req__init
                     (Fberhome__ImDbgReq         *message);
size_t fberhome__im_dbg_req__get_packed_size
                     (const Fberhome__ImDbgReq   *message);
size_t fberhome__im_dbg_req__pack
                     (const Fberhome__ImDbgReq   *message,
                      uint8_t             *out);
size_t fberhome__im_dbg_req__pack_to_buffer
                     (const Fberhome__ImDbgReq   *message,
                      ProtobufCBuffer     *buffer);
Fberhome__ImDbgReq *
       fberhome__im_dbg_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   fberhome__im_dbg_req__free_unpacked
                     (Fberhome__ImDbgReq *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Fberhome__ImPbmp_Closure)
                 (const Fberhome__ImPbmp *message,
                  void *closure_data);
typedef void (*Fberhome__FbInitReq_Closure)
                 (const Fberhome__FbInitReq *message,
                  void *closure_data);
typedef void (*Fberhome__ImDbgReq_Closure)
                 (const Fberhome__ImDbgReq *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor fberhome__im_pbmp__descriptor;
extern const ProtobufCMessageDescriptor fberhome__fb_init_req__descriptor;
extern const ProtobufCMessageDescriptor fberhome__im_dbg_req__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_comm_2eproto__INCLUDED */
