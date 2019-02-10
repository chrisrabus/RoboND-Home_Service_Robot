#!/bin/sh
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/MyWorld.world" &
sleep 5
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/World/MyMap.yaml" &
sleep 5
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; rosrun rviz rviz -d /home/workspace/catkin_ws/src/RvizConfig/navigation_with_markers.rviz" &
sleep 5
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; rosrun add_markers add_markers" &
sleep 5
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects"