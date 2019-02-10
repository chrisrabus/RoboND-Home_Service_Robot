#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Int32.h>          //included for deriving state of robot

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  ros::Rate r(1000);
  ros::Publisher state_robot = n.advertise<std_msgs::Int32>("StateRobot", 3);
  std_msgs::Int32 RobState;
  
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  // set Publisher for robot state, and initialize robot state
  //ros::Duration(2.0).sleep();
  //ROS_INFO("Sending 0");
  RobState.data = 0; // 0 - robot is at start position
  state_robot.publish(RobState);
  
  //ros::Duration(2.0).sleep(); // wait 2 seconds before start running.
  
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 4.0;
  goal.target_pose.pose.position.y = 6.0;  
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending robot to pick up zone");
  ac.sendGoal(goal);
  //ROS_INFO("Sending 1");
  RobState.data = 1; // 1 - robot is moving to pick up zone
  state_robot.publish(RobState);
  
  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, the robot reached the pickup zone");
  	RobState.data = 2; // 2 - robot is at pick up zone
  	state_robot.publish(RobState);
  }
  else
    ROS_INFO("The base failed to move to the pick up zone for some reason");

/**************************
Second Goal Position
***************************/
  // Wait 5 sec at pick up zone
 ros::Duration(5.0).sleep();
 RobState.data = 3; // 3 - robot is moving to drop off zone
 state_robot.publish(RobState);
  
  move_base_msgs::MoveBaseGoal goal2;

  // set up the frame parameters
  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal2.target_pose.pose.position.x = -4.0;
  goal2.target_pose.pose.position.y = 6.0;  
  goal2.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending robot to drop off zone");
  ac.sendGoal(goal2);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the robot moved to the drop off zone");
    RobState.data = 4; // 4 - robot is at drop off zone
 	state_robot.publish(RobState);
  }
  else
    ROS_INFO("The base failed to move to the drop off zone for some reason");
  
  ros::Duration(5.0).sleep(); 
  
  return 0;
}