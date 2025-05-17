cmake_minimum_required(VERSION 3.8)
project(cv_pkg)

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
add_executable(cv_image_node src/cv_image.cpp)
add_executable(cv_hsv_node src/cv_hsv.cpp)
add_executable(cv_follow_node src/cv_follow.cpp)
add_executable(cv_face_detect_node src/cv_face_detect.cpp)

# 链接依赖库
ament_target_dependencies(cv_image_node
  rclcpp
  sensor_msgs
  cv_bridge
)
target_link_libraries(cv_image_node ${OpenCV_LIBS})

ament_target_dependencies(cv_hsv_node
  rclcpp
  sensor_msgs
  cv_bridge
)
target_link_libraries(cv_hsv_node ${OpenCV_LIBS})

ament_target_dependencies(cv_follow_node
  rclcpp
  sensor_msgs
  cv_bridge
)
target_link_libraries(cv_follow_node ${OpenCV_LIBS})

ament_target_dependencies(cv_face_detect_node
  rclcpp
  sensor_msgs
  cv_bridge
  OpenCV
)
target_link_libraries(cv_face_detect_node ${OpenCV_LIBS})

# ament_target_dependencies(pc_data_node
#   rclcpp
#   sensor_msgs
#   pcl_conversions
#   pcl_ros
# )
# target_link_libraries(pc_data_node ${PCL_LIBRARIES})

# 安装规则
install(TARGETS
  cv_image_node
  cv_hsv_node
  cv_follow_node
  cv_face_detect_node
  DESTINATION lib/${PROJECT_NAME}
)

# 测试配置（可选）
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
