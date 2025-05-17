// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from wpr_simulation2:msg/Object.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "wpr_simulation2/msg/detail/object__rosidl_typesupport_introspection_c.h"
#include "wpr_simulation2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "wpr_simulation2/msg/detail/object__functions.h"
#include "wpr_simulation2/msg/detail/object__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `x`
// Member `y`
// Member `z`
// Member `probability`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  wpr_simulation2__msg__Object__init(message_memory);
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_fini_function(void * message_memory)
{
  wpr_simulation2__msg__Object__fini(message_memory);
}

size_t wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__name(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__name(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__name(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__name(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__name(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__name(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__name(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__name(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__x(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__x(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__x(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__x(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__x(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__x(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__x(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__x(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__y(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__y(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__y(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__y(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__y(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__y(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__y(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__y(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__z(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__z(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__z(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__z(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__z(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__z(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__z(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__z(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__probability(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__probability(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__probability(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__probability(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__probability(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__probability(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__probability(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__probability(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_message_member_array[5] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wpr_simulation2__msg__Object, name),  // bytes offset in struct
    NULL,  // default value
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__name,  // size() function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__name,  // get_const(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__name,  // get(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__name,  // fetch(index, &value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__name,  // assign(index, value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__name  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wpr_simulation2__msg__Object, x),  // bytes offset in struct
    NULL,  // default value
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__x,  // size() function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__x,  // get_const(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__x,  // get(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__x,  // fetch(index, &value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__x,  // assign(index, value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__x  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wpr_simulation2__msg__Object, y),  // bytes offset in struct
    NULL,  // default value
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__y,  // size() function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__y,  // get_const(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__y,  // get(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__y,  // fetch(index, &value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__y,  // assign(index, value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__y  // resize(index) function pointer
  },
  {
    "z",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wpr_simulation2__msg__Object, z),  // bytes offset in struct
    NULL,  // default value
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__z,  // size() function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__z,  // get_const(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__z,  // get(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__z,  // fetch(index, &value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__z,  // assign(index, value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__z  // resize(index) function pointer
  },
  {
    "probability",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wpr_simulation2__msg__Object, probability),  // bytes offset in struct
    NULL,  // default value
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__size_function__Object__probability,  // size() function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_const_function__Object__probability,  // get_const(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__get_function__Object__probability,  // get(index) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__fetch_function__Object__probability,  // fetch(index, &value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__assign_function__Object__probability,  // assign(index, value) function pointer
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__resize_function__Object__probability  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_message_members = {
  "wpr_simulation2__msg",  // message namespace
  "Object",  // message name
  5,  // number of fields
  sizeof(wpr_simulation2__msg__Object),
  wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_message_member_array,  // message members
  wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_init_function,  // function to initialize message memory (memory has to be allocated)
  wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_message_type_support_handle = {
  0,
  &wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wpr_simulation2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wpr_simulation2, msg, Object)() {
  if (!wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_message_type_support_handle.typesupport_identifier) {
    wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &wpr_simulation2__msg__Object__rosidl_typesupport_introspection_c__Object_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
