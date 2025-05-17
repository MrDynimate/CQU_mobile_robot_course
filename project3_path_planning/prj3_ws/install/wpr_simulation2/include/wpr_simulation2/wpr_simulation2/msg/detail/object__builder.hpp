// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wpr_simulation2:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef WPR_SIMULATION2__MSG__DETAIL__OBJECT__BUILDER_HPP_
#define WPR_SIMULATION2__MSG__DETAIL__OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wpr_simulation2/msg/detail/object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wpr_simulation2
{

namespace msg
{

namespace builder
{

class Init_Object_probability
{
public:
  explicit Init_Object_probability(::wpr_simulation2::msg::Object & msg)
  : msg_(msg)
  {}
  ::wpr_simulation2::msg::Object probability(::wpr_simulation2::msg::Object::_probability_type arg)
  {
    msg_.probability = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wpr_simulation2::msg::Object msg_;
};

class Init_Object_z
{
public:
  explicit Init_Object_z(::wpr_simulation2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_probability z(::wpr_simulation2::msg::Object::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_Object_probability(msg_);
  }

private:
  ::wpr_simulation2::msg::Object msg_;
};

class Init_Object_y
{
public:
  explicit Init_Object_y(::wpr_simulation2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_z y(::wpr_simulation2::msg::Object::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Object_z(msg_);
  }

private:
  ::wpr_simulation2::msg::Object msg_;
};

class Init_Object_x
{
public:
  explicit Init_Object_x(::wpr_simulation2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_y x(::wpr_simulation2::msg::Object::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Object_y(msg_);
  }

private:
  ::wpr_simulation2::msg::Object msg_;
};

class Init_Object_name
{
public:
  Init_Object_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object_x name(::wpr_simulation2::msg::Object::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Object_x(msg_);
  }

private:
  ::wpr_simulation2::msg::Object msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wpr_simulation2::msg::Object>()
{
  return wpr_simulation2::msg::builder::Init_Object_name();
}

}  // namespace wpr_simulation2

#endif  // WPR_SIMULATION2__MSG__DETAIL__OBJECT__BUILDER_HPP_
