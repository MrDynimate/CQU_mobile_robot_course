cmake_minimum_required(VERSION 3.8)
project(pc_pkg)

# 编译选项
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_ros REQUIRED)

# 添加可执行文件
add_executable(pc_data src/pc_data.cpp)
add_executable(pc_objects src/pc_objects.cpp)
# 链接依赖库

ament_target_dependencies(pc_data
  rclcpp
  sensor_msgs
  pcl_conversions
  pcl_ros
)

ament_target_dependencies(pc_objects
  rclcpp
  sensor_msgs
  pcl_conversions
  pcl_ros
)

# 安装规则
install(TARGETS
  pc_data
  pc_objects
  DESTINATION lib/${PROJECT_NAME}
)

# 测试配置
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()