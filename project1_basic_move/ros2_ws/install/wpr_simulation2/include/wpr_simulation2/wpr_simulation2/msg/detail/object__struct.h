// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wpr_simulation2:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef WPR_SIMULATION2__MSG__DETAIL__OBJECT__STRUCT_H_
#define WPR_SIMULATION2__MSG__DETAIL__OBJECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"
// Member 'x'
// Member 'y'
// Member 'z'
// Member 'probability'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/Object in the package wpr_simulation2.
typedef struct wpr_simulation2__msg__Object
{
  rosidl_runtime_c__String__Sequence name;
  rosidl_runtime_c__double__Sequence x;
  rosidl_runtime_c__double__Sequence y;
  rosidl_runtime_c__double__Sequence z;
  rosidl_runtime_c__double__Sequence probability;
} wpr_simulation2__msg__Object;

// Struct for a sequence of wpr_simulation2__msg__Object.
typedef struct wpr_simulation2__msg__Object__Sequence
{
  wpr_simulation2__msg__Object * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wpr_simulation2__msg__Object__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WPR_SIMULATION2__MSG__DETAIL__OBJECT__STRUCT_H_
