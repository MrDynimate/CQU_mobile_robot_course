cmake_minimum_required(VERSION 3.8)
project(lidar_pkg)

# 编译选项
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED) 
find_package(sensor_msgs REQUIRED) 
find_package(geometry_msgs REQUIRED)

# 添加可执行文件
add_executable(lidar_data src/lidar_data.cpp)
add_executable(lidar_behavior src/lidar_behavior.cpp)


# 链接依赖库
ament_target_dependencies(lidar_data
  rclcpp
  sensor_msgs
)
target_link_libraries(lidar_data ${OpenCV_LIBS})

ament_target_dependencies(lidar_behavior
  rclcpp
  sensor_msgs
  geometry_msgs
)
target_link_libraries(lidar_behavior ${OpenCV_LIBS})

# 安装规则
install(TARGETS
  lidar_data                 # LIDAR数据处理节点
  lidar_behavior             # LIDAR避障行为节点
  RUNTIME DESTINATION lib/${PROJECT_NAME}  # 可执行文件安装目录
  COMPONENT runtime          # 组件分类(用于分组安装)
)


# 测试配置
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
