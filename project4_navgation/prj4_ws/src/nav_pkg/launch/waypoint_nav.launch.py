"""
ROS 2 导航系统集成启动文件
功能: 启动完整的导航系统，包括:
    1. Nav2 导航堆栈
    2. RViz 可视化工具
    3. 航点编辑工具 (wp_edit_node)
    4. 航点导航服务 (wp_navi_server)
    
作者: Danny Lee
创建时间: 2025-5-18
最后修改: 2025-5-18
版本: V1.0
"""

import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # ====================== 包路径配置 ======================
    pkg_wpr_sim = get_package_share_directory('wpr_simulation2')
    pkg_wp_map = get_package_share_directory('wp_map_tools')
    pkg_nav2 = get_package_share_directory('nav2_bringup')

    # ====================== 文件路径配置 ======================
    # 导航相关文件
    map_file = os.path.join(pkg_wpr_sim, 'maps', 'map.yaml')
    nav_param_file = os.path.join(pkg_wpr_sim, 'config', 'nav2_params.yaml')
    
    # RViz 配置文件
    rviz_config = os.path.join(pkg_wp_map, 'rviz', 'navi.rviz')

    # ====================== 节点配置 ======================
    # Nav2 导航系统
    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_nav2, 'launch', 'bringup_launch.py')
        ),
        launch_arguments={
            'map': map_file,
            'use_sim_time': 'True',
            'params_file': nav_param_file
        }.items()
    )

    # RViz 可视化工具
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='navigation_rviz2',
        output='screen',
        arguments=['-d', rviz_config],
        parameters=[{'use_sim_time': True}]
    )

    # 航点编辑工具
    wp_edit_node = Node(
        package='wp_map_tools',
        executable='wp_edit_node',
        name='wp_edit_node',
        output='screen'
    )

    # 航点导航服务
    wp_navi_server = Node(
        package='wp_map_tools',
        executable='wp_navi_server',
        name='wp_navi_server',
        output='screen'
    )

    # ====================== 启动描述 ======================
    ld = LaunchDescription()
    
    ld.add_action(nav2_launch)
    ld.add_action(rviz_node)
    ld.add_action(wp_edit_node)
    ld.add_action(wp_navi_server)

    return ld