// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wpr_simulation2:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef WPR_SIMULATION2__MSG__DETAIL__OBJECT__TRAITS_HPP_
#define WPR_SIMULATION2__MSG__DETAIL__OBJECT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wpr_simulation2/msg/detail/object__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace wpr_simulation2
{

namespace msg
{

inline void to_flow_style_yaml(
  const Object & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    if (msg.name.size() == 0) {
      out << "name: []";
    } else {
      out << "name: [";
      size_t pending_items = msg.name.size();
      for (auto item : msg.name) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: x
  {
    if (msg.x.size() == 0) {
      out << "x: []";
    } else {
      out << "x: [";
      size_t pending_items = msg.x.size();
      for (auto item : msg.x) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: y
  {
    if (msg.y.size() == 0) {
      out << "y: []";
    } else {
      out << "y: [";
      size_t pending_items = msg.y.size();
      for (auto item : msg.y) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: z
  {
    if (msg.z.size() == 0) {
      out << "z: []";
    } else {
      out << "z: [";
      size_t pending_items = msg.z.size();
      for (auto item : msg.z) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: probability
  {
    if (msg.probability.size() == 0) {
      out << "probability: []";
    } else {
      out << "probability: [";
      size_t pending_items = msg.probability.size();
      for (auto item : msg.probability) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Object & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.name.size() == 0) {
      out << "name: []\n";
    } else {
      out << "name:\n";
      for (auto item : msg.name) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.x.size() == 0) {
      out << "x: []\n";
    } else {
      out << "x:\n";
      for (auto item : msg.x) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.y.size() == 0) {
      out << "y: []\n";
    } else {
      out << "y:\n";
      for (auto item : msg.y) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.z.size() == 0) {
      out << "z: []\n";
    } else {
      out << "z:\n";
      for (auto item : msg.z) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: probability
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.probability.size() == 0) {
      out << "probability: []\n";
    } else {
      out << "probability:\n";
      for (auto item : msg.probability) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Object & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace wpr_simulation2

namespace rosidl_generator_traits
{

[[deprecated("use wpr_simulation2::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const wpr_simulation2::msg::Object & msg,
  std::ostream & out, size_t indentation = 0)
{
  wpr_simulation2::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wpr_simulation2::msg::to_yaml() instead")]]
inline std::string to_yaml(const wpr_simulation2::msg::Object & msg)
{
  return wpr_simulation2::msg::to_yaml(msg);
}

template<>
inline const char * data_type<wpr_simulation2::msg::Object>()
{
  return "wpr_simulation2::msg::Object";
}

template<>
inline const char * name<wpr_simulation2::msg::Object>()
{
  return "wpr_simulation2/msg/Object";
}

template<>
struct has_fixed_size<wpr_simulation2::msg::Object>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<wpr_simulation2::msg::Object>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<wpr_simulation2::msg::Object>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WPR_SIMULATION2__MSG__DETAIL__OBJECT__TRAITS_HPP_
