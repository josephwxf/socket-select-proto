/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: init.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "init.pb-c.h"
void   fberhome__test_req__init
                     (Fberhome__TestReq         *message)
{
  static Fberhome__TestReq init_value = FBERHOME__TEST_REQ__INIT;
  *message = init_value;
}
size_t fberhome__test_req__get_packed_size
                     (const Fberhome__TestReq *message)
{
  assert(message->base.descriptor == &fberhome__test_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t fberhome__test_req__pack
                     (const Fberhome__TestReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &fberhome__test_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t fberhome__test_req__pack_to_buffer
                     (const Fberhome__TestReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &fberhome__test_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Fberhome__TestReq *
       fberhome__test_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Fberhome__TestReq *)
     protobuf_c_message_unpack (&fberhome__test_req__descriptor,
                                allocator, len, data);
}
void   fberhome__test_req__free_unpacked
                     (Fberhome__TestReq *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &fberhome__test_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   fberhome__im_ver_req__init
                     (Fberhome__ImVerReq         *message)
{
  static Fberhome__ImVerReq init_value = FBERHOME__IM_VER_REQ__INIT;
  *message = init_value;
}
size_t fberhome__im_ver_req__get_packed_size
                     (const Fberhome__ImVerReq *message)
{
  assert(message->base.descriptor == &fberhome__im_ver_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t fberhome__im_ver_req__pack
                     (const Fberhome__ImVerReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &fberhome__im_ver_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t fberhome__im_ver_req__pack_to_buffer
                     (const Fberhome__ImVerReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &fberhome__im_ver_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Fberhome__ImVerReq *
       fberhome__im_ver_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Fberhome__ImVerReq *)
     protobuf_c_message_unpack (&fberhome__im_ver_req__descriptor,
                                allocator, len, data);
}
void   fberhome__im_ver_req__free_unpacked
                     (Fberhome__ImVerReq *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &fberhome__im_ver_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor fberhome__test_req__field_descriptors[1] =
{
  {
    "fe",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Fberhome__TestReq, fe),
    &fberhome__im_pbmp__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned fberhome__test_req__field_indices_by_name[] = {
  0,   /* field[0] = fe */
};
static const ProtobufCIntRange fberhome__test_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor fberhome__test_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Fberhome.testReq",
  "TestReq",
  "Fberhome__TestReq",
  "Fberhome",
  sizeof(Fberhome__TestReq),
  1,
  fberhome__test_req__field_descriptors,
  fberhome__test_req__field_indices_by_name,
  1,  fberhome__test_req__number_ranges,
  (ProtobufCMessageInit) fberhome__test_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor fberhome__im_ver_req__field_descriptors[5] =
{
  {
    "build_release",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Fberhome__ImVerReq, build_release),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "build_user",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Fberhome__ImVerReq, build_user),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "build_host",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Fberhome__ImVerReq, build_host),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "build_date",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Fberhome__ImVerReq, build_date),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "build_arch",
    5,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Fberhome__ImVerReq, build_arch),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned fberhome__im_ver_req__field_indices_by_name[] = {
  4,   /* field[4] = build_arch */
  3,   /* field[3] = build_date */
  2,   /* field[2] = build_host */
  0,   /* field[0] = build_release */
  1,   /* field[1] = build_user */
};
static const ProtobufCIntRange fberhome__im_ver_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor fberhome__im_ver_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Fberhome.ImVerReq",
  "ImVerReq",
  "Fberhome__ImVerReq",
  "Fberhome",
  sizeof(Fberhome__ImVerReq),
  5,
  fberhome__im_ver_req__field_descriptors,
  fberhome__im_ver_req__field_indices_by_name,
  1,  fberhome__im_ver_req__number_ranges,
  (ProtobufCMessageInit) fberhome__im_ver_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
