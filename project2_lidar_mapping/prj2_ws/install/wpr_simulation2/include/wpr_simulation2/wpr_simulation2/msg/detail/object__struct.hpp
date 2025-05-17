// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wpr_simulation2:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef WPR_SIMULATION2__MSG__DETAIL__OBJECT__STRUCT_HPP_
#define WPR_SIMULATION2__MSG__DETAIL__OBJECT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__wpr_simulation2__msg__Object __attribute__((deprecated))
#else
# define DEPRECATED__wpr_simulation2__msg__Object __declspec(deprecated)
#endif

namespace wpr_simulation2
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Object_
{
  using Type = Object_<ContainerAllocator>;

  explicit Object_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit Object_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _name_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _name_type name;
  using _x_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _x_type x;
  using _y_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _y_type y;
  using _z_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _z_type z;
  using _probability_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _probability_type probability;

  // setters for named parameter idiom
  Type & set__name(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__x(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__z(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->z = _arg;
    return *this;
  }
  Type & set__probability(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->probability = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wpr_simulation2::msg::Object_<ContainerAllocator> *;
  using ConstRawPtr =
    const wpr_simulation2::msg::Object_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wpr_simulation2::msg::Object_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wpr_simulation2::msg::Object_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wpr_simulation2::msg::Object_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wpr_simulation2::msg::Object_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wpr_simulation2::msg::Object_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wpr_simulation2::msg::Object_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wpr_simulation2::msg::Object_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wpr_simulation2::msg::Object_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wpr_simulation2__msg__Object
    std::shared_ptr<wpr_simulation2::msg::Object_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wpr_simulation2__msg__Object
    std::shared_ptr<wpr_simulation2::msg::Object_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Object_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    if (this->probability != other.probability) {
      return false;
    }
    return true;
  }
  bool operator!=(const Object_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Object_

// alias to use template instance with default allocator
using Object =
  wpr_simulation2::msg::Object_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace wpr_simulation2

#endif  // WPR_SIMULATION2__MSG__DETAIL__OBJECT__STRUCT_HPP_
