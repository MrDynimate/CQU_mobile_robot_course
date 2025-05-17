#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@file slam_launch.py
@author Danny Lee (20213041@cqu.edu.cn)
@brief SLAM建图启动文件
@version 1.0
@date 2025-5-18

@details 功能：
  1. 启动SLAM工具箱节点
  2. 加载预配置的RViz界面
  3. 支持参数动态配置

使用方式：
  ros2 launch wpr_simulation2 robocup_home.launch.py
"""

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # 参数声明
    use_sim_time = DeclareLaunchArgument(
        'use_sim_time',
        default_value='true',
        description='是否使用仿真时间'
    )
    
    base_frame = DeclareLaunchArgument(
        'base_frame',
        default_value='base_footprint',
        description='机器人基座坐标系'
    )

    # SLAM节点配置
    slam_params = {
        'use_sim_time': LaunchConfiguration('use_sim_time'),
        'base_frame': LaunchConfiguration('base_frame'),
        'odom_frame': 'odom',
        'map_frame': 'map',
        'max_laser_range': 6.0,  # 增加激光最大范围限制
        'resolution': 0.05,      # 地图分辨率
    }

    slam_node = Node(
        package='slam_toolbox',
        executable='sync_slam_toolbox_node',
        name='slam_toolbox',
        output='screen',
        parameters=[slam_params],
        remappings=[('/scan', '/lidar_scan')]  # 支持话题重映射
    )

    # RViz配置
    rviz_config_dir = os.path.join(
        get_package_share_directory('wpr_simulation2'),
        'rviz',
        'slam.rviz'
    )

    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', rviz_config_dir],
        parameters=[{'use_sim_time': LaunchConfiguration('use_sim_time')}]
    )

    # 构建启动描述
    ld = LaunchDescription()
    ld.add_action(use_sim_time)
    ld.add_action(base_frame)
    ld.add_action(slam_node)
    ld.add_action(rviz_node)

    return ld