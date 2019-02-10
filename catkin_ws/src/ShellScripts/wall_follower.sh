#!/bin/sh
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/MyWorld.world" &
sleep 5
#xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=/home/workspace/catkin_ws/src/customized/custom_gmapping.launch.xml" &
sleep 5
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers  view_navigation.launch" &
sleep 5
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; rosrun wall_follower wall_follower"