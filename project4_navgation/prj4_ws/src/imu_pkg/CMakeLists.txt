cmake_minimum_required(VERSION 3.8)
project(imu_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED) 
find_package(sensor_msgs REQUIRED) 
find_package(tf2 REQUIRED)
find_package(geometry_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# 添加可执行文件
add_executable(imu_data src/imu_data.cpp)
add_executable(imu_behavior src/imu_behavior.cpp)

# 链接依赖库
ament_target_dependencies(imu_data
  rclcpp
  sensor_msgs
  tf2
)
target_link_libraries(imu_data ${OpenCV_LIBS})

ament_target_dependencies(imu_behavior
  rclcpp
  sensor_msgs
  tf2
  geometry_msgs
)
target_link_libraries(imu_behavior ${OpenCV_LIBS})

# 安装规则
install(TARGETS
  imu_data                 # IMU数据处理节点
  imu_behavior             # IMU避障行为节点
  RUNTIME DESTINATION lib/${PROJECT_NAME}  # 可执行文件安装目录
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()