/*
#include "ros/ros.h"
#include "iri_wam_reproduce_trajectory/ExecTraj.h"
#include <ros/package.h>
//#include "gazebo_msgs/DeleteModel.h" 
// Import the service message used by the service /gazebo/delete_model

int main(int argc, char **argv)
{
  ros::init(argc, argv, "arm_client"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;
  
  // Create the connection to the service /gazebo/delete_model
  ros::ServiceClient arm_service_client = nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>("/execute_trajectory");
  iri_wam_reproduce_trajectory::ExecTraj srv; // Create an object of type DeleteModel
  // This ros::package::getPath works in the same way as $(find name_of_package) in the launch files.
  srv.request.file = ros::package::getPath("iri_wam_reproduce_trajectory") + "/config/get_food.txt";
  
  if (arm_service_client.call(srv)) // Send through the connection the name of the object to be deleted by the                                             // service
  {
    ROS_INFO("%s", "Service successfully called. Executing trajectory."); // Print the result given by the service called
  }
  else
  {
    ROS_ERROR("Failed to call service arm_service");
    return 1;
  }

  return 0;
}
*/

#include "ros/ros.h"
#include "iri_wam_reproduce_trajectory/ExecTraj.h"
#include <ros/package.h>
// Import rospackage

int main(int argc, char **argv)
{
  ros::init(argc, argv, "execute_trajectory_node");
  ros::NodeHandle nh;
  
  // Create the connection to the service /execute_trajectory
  ros::ServiceClient exec_traj_service = nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>("/execute_trajectory");
  iri_wam_reproduce_trajectory::ExecTraj trajectory; // Create an object of type ExecTraj
    
  // This ros::package::getPath works in the same way as $(find name_of_package) in the launch files.
  trajectory.request.file = ros::package::getPath("iri_wam_reproduce_trajectory") + "/config/get_food.txt";
  // Fill the variable file of this object with the desired value
  
  if (exec_traj_service.call(trajectory)) 
  {
    ROS_INFO("%s", "Service successfully called. Executing trajectory.");
  }
  else
  {
    ROS_ERROR("Failed to call service delete_model");
    return 1;
  }

  return 0;
}