"""
ROS 2 导航系统集成启动文件
功能: 启动Nav2导航系统、RViz可视化工具和相关配置
主要组件:
    1. Nav2 导航系统 (含地图服务和参数配置)
    2. RViz 可视化界面
作者: Danny Lee
创建时间: 2025-5-18
最后修改: 2025-5-18
版本: V1.1
"""

import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # 获取包路径 ==============================================================
    pkg_wpr_sim = get_package_share_directory('wpr_simulation2')
    pkg_nav2_bringup = get_package_share_directory('nav2_bringup')
    
    # 路径配置 ================================================================
    # 地图文件配置
    map_dir = os.path.join(pkg_wpr_sim, 'maps', 'map.yaml')
    
    # 导航参数配置
    nav_params = os.path.join(pkg_wpr_sim, 'config', 'nav2_params.yaml')
    
    # RViz 配置文件
    rviz_config = os.path.join(pkg_wpr_sim, 'rviz', 'navi.rviz')
    
    # Nav2 启动文件路径
    nav2_launch_dir = os.path.join(pkg_nav2_bringup, 'launch')

    # 节点配置 ================================================================
    # Nav2 导航系统启动配置
    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(nav2_launch_dir, 'bringup_launch.py')
        ),
        launch_arguments={
            'map': map_dir,
            'use_sim_time': 'True',    # 使用仿真时间
            'params_file': nav_params  # 导航参数文件
        }.items()
    )

    # RViz 可视化节点配置
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='navi_rviz2',
        output='screen',
        arguments=['-d', rviz_config],
        parameters=[{'use_sim_time': True}]
    )

    # 构建启动描述 ============================================================
    ld = LaunchDescription()
    
    # 添加节点
    ld.add_action(nav2_launch)
    ld.add_action(rviz_node)

    return ld