#!/bin/sh
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/MyWorld.world" &
sleep 10
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/World/MyMap.yaml" &
sleep 10
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers  view_navigation.launch" &
sleep 10
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects"