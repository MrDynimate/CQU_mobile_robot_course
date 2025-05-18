cmake_minimum_required(VERSION 3.8)
project(nav_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# 添加可执行文件
add_executable(waypoint_navigation src/waypoint_navigation.cpp)

# 链接依赖库
ament_target_dependencies(waypoint_navigation
  rclcpp
  std_msgs
)

# 安装规则
install(TARGETS
  waypoint_navigation                 # 导航航点数据处理节点
  RUNTIME DESTINATION lib/${PROJECT_NAME}  # 可执行文件安装目录
  COMPONENT runtime          # 组件分类(用于分组安装)
)

# 启动文件安装规则
install(
  DIRECTORY
    launch/                  # 启动文件目录
  DESTINATION 
    share/${PROJECT_NAME}/launch  # 标准ROS2启动文件路径
  PATTERN "*.py" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE  # 设置Python文件可执行权限
  PATTERN "*.launch.py" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
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
