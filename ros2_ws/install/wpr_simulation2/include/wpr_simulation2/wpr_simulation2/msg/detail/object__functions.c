// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from wpr_simulation2:msg/Object.idl
// generated code does not contain a copyright notice
#include "wpr_simulation2/msg/detail/object__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `x`
// Member `y`
// Member `z`
// Member `probability`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
wpr_simulation2__msg__Object__init(wpr_simulation2__msg__Object * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__Sequence__init(&msg->name, 0)) {
    wpr_simulation2__msg__Object__fini(msg);
    return false;
  }
  // x
  if (!rosidl_runtime_c__double__Sequence__init(&msg->x, 0)) {
    wpr_simulation2__msg__Object__fini(msg);
    return false;
  }
  // y
  if (!rosidl_runtime_c__double__Sequence__init(&msg->y, 0)) {
    wpr_simulation2__msg__Object__fini(msg);
    return false;
  }
  // z
  if (!rosidl_runtime_c__double__Sequence__init(&msg->z, 0)) {
    wpr_simulation2__msg__Object__fini(msg);
    return false;
  }
  // probability
  if (!rosidl_runtime_c__double__Sequence__init(&msg->probability, 0)) {
    wpr_simulation2__msg__Object__fini(msg);
    return false;
  }
  return true;
}

void
wpr_simulation2__msg__Object__fini(wpr_simulation2__msg__Object * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__Sequence__fini(&msg->name);
  // x
  rosidl_runtime_c__double__Sequence__fini(&msg->x);
  // y
  rosidl_runtime_c__double__Sequence__fini(&msg->y);
  // z
  rosidl_runtime_c__double__Sequence__fini(&msg->z);
  // probability
  rosidl_runtime_c__double__Sequence__fini(&msg->probability);
}

bool
wpr_simulation2__msg__Object__are_equal(const wpr_simulation2__msg__Object * lhs, const wpr_simulation2__msg__Object * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // x
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->x), &(rhs->x)))
  {
    return false;
  }
  // y
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->y), &(rhs->y)))
  {
    return false;
  }
  // z
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->z), &(rhs->z)))
  {
    return false;
  }
  // probability
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->probability), &(rhs->probability)))
  {
    return false;
  }
  return true;
}

bool
wpr_simulation2__msg__Object__copy(
  const wpr_simulation2__msg__Object * input,
  wpr_simulation2__msg__Object * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // x
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->x), &(output->x)))
  {
    return false;
  }
  // y
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->y), &(output->y)))
  {
    return false;
  }
  // z
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->z), &(output->z)))
  {
    return false;
  }
  // probability
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->probability), &(output->probability)))
  {
    return false;
  }
  return true;
}

wpr_simulation2__msg__Object *
wpr_simulation2__msg__Object__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wpr_simulation2__msg__Object * msg = (wpr_simulation2__msg__Object *)allocator.allocate(sizeof(wpr_simulation2__msg__Object), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wpr_simulation2__msg__Object));
  bool success = wpr_simulation2__msg__Object__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wpr_simulation2__msg__Object__destroy(wpr_simulation2__msg__Object * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wpr_simulation2__msg__Object__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wpr_simulation2__msg__Object__Sequence__init(wpr_simulation2__msg__Object__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wpr_simulation2__msg__Object * data = NULL;

  if (size) {
    data = (wpr_simulation2__msg__Object *)allocator.zero_allocate(size, sizeof(wpr_simulation2__msg__Object), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wpr_simulation2__msg__Object__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wpr_simulation2__msg__Object__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wpr_simulation2__msg__Object__Sequence__fini(wpr_simulation2__msg__Object__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wpr_simulation2__msg__Object__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wpr_simulation2__msg__Object__Sequence *
wpr_simulation2__msg__Object__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wpr_simulation2__msg__Object__Sequence * array = (wpr_simulation2__msg__Object__Sequence *)allocator.allocate(sizeof(wpr_simulation2__msg__Object__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wpr_simulation2__msg__Object__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wpr_simulation2__msg__Object__Sequence__destroy(wpr_simulation2__msg__Object__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wpr_simulation2__msg__Object__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wpr_simulation2__msg__Object__Sequence__are_equal(const wpr_simulation2__msg__Object__Sequence * lhs, const wpr_simulation2__msg__Object__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wpr_simulation2__msg__Object__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wpr_simulation2__msg__Object__Sequence__copy(
  const wpr_simulation2__msg__Object__Sequence * input,
  wpr_simulation2__msg__Object__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wpr_simulation2__msg__Object);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wpr_simulation2__msg__Object * data =
      (wpr_simulation2__msg__Object *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wpr_simulation2__msg__Object__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wpr_simulation2__msg__Object__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wpr_simulation2__msg__Object__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
