#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@file slam_launch.py
@brief 增强版SLAM建图启动文件
@author Danny Lee (20213041@cqu.edu.cn)
@version 2.1
@date 2025-05-20

@details 主要改进：
1. 优化消息队列配置防止数据丢失
2. 添加性能调节参数
3. 增强时间同步机制
4. 支持动态参数重配置
"""

import os
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    SetEnvironmentVariable,
    RegisterEventHandler,
    LogInfo
)
from launch.event_handlers import OnProcessStart
from launch.substitutions import (
    LaunchConfiguration,
    PathJoinSubstitution
)
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # ==================== 环境配置 ====================
    env_config = SetEnvironmentVariable(
        name='ROS_DOMAIN_ID',
        value='0'  # 防止多机干扰
    )

    # ==================== 参数声明 ====================
    config_dir = os.path.join(
        get_package_share_directory('wpr_simulation2'),
        'config'
    )
    
    declare_params = [
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='使用仿真时钟'),
        DeclareLaunchArgument(
            'base_frame',
            default_value='base_footprint',
            description='机器人基坐标系'),
        DeclareLaunchArgument(
            'slam_params_file',
            default_value=PathJoinSubstitution([
                config_dir, 'slam_config.yaml']),
            description='SLAM参数文件路径'),
        DeclareLaunchArgument(
            'scan_topic',
            default_value='/scan',
            description='激光雷达话题名')
    ]

    # ==================== SLAM节点 ====================
    slam_node = Node(
        package='slam_toolbox',
        executable='async_slam_toolbox_node',  # 改用异步模式
        name='slam_toolbox',
        output='screen',
        parameters=[
            LaunchConfiguration('slam_params_file'),
            {
                'use_sim_time': LaunchConfiguration('use_sim_time'),
                'base_frame': LaunchConfiguration('base_frame'),
                'odom_frame': 'odom',
                'map_frame': 'map',
                'max_laser_range': 8.0,  # 扩大检测范围
                'resolution': 0.05,
                'throttle_scans': 2,     # 降低处理频率
                'transform_publish_period': 0.05,  # 提高TF发布频率
                'queue_size': 50         # 增大处理队列
            }
        ],
        remappings=[
            ('/scan', LaunchConfiguration('scan_topic'))
        ],
        arguments=['--ros-args', '--log-level', 'WARN']  # 控制日志级别
    )

    # ==================== RViz2优化配置 ====================
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', PathJoinSubstitution([
            get_package_share_directory('wpr_simulation2'),
            'rviz', 'slam.rviz'])],
        parameters=[{
            'use_sim_time': LaunchConfiguration('use_sim_time'),
            # QoS优化配置
            'qos_overrides./scan.subscription.queue_size': 100,
            'qos_overrides./map.publisher.history': 'keep_last',
            'qos_overrides./map.publisher.depth': 10
        }],
        output='screen'
    )

    # ==================== 数据节流节点(可选) ====================
    throttle_node = Node(
        package='topic_tools',
        executable='throttle',
        name='scan_throttle',
        arguments=[
            'messages',
            LaunchConfiguration('scan_topic'),
            '10',  # 限制为10Hz
            'scan_throttled'
        ],
        parameters=[{
            'use_sim_time': LaunchConfiguration('use_sim_time')
        }]
    )

    # ==================== 启动后事件处理 ====================
    startup_info = RegisterEventHandler(
        OnProcessStart(
            target_action=slam_node,
            on_start=[
                LogInfo(msg='SLAM系统已启动，建议操作：\n'
                      '1. 使用2D Pose Estimate初始化地图\n'
                      '2. 通过2D Nav Goal设置目标点')
            ]
        )
    )

    # ==================== 构建启动描述 ====================
    ld = LaunchDescription([
        env_config,
        *declare_params,
        slam_node,
        rviz_node,
        # throttle_node,  # 按需启用
        startup_info
    ])

    return ld
写一个gitignore文件，忽略掉一些不必要的文件和目录