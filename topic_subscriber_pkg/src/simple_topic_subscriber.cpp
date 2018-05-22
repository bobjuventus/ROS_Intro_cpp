#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/Odometry.h>

void counterCallback(const std_msgs::Int32::ConstPtr &msg)
{
  ROS_INFO("%d", (*msg).data);
}

void odomCallback(const nav_msgs::Odometry::ConstPtr &msg)
{
  ROS_INFO("%s", (*msg).header.frame_id.c_str());
  ros::Duration(0.5).sleep();
  ROS_INFO("%f", msg->twist.twist.linear.x);
  //ROS_INFO("%f", msg->pose.pose.position.x);
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "topic_subscriber");
    ros::NodeHandle nh;
    
    //ros::Subscriber sub = nh.subscribe("counter", 1000, counterCallback);
    ros::Subscriber sub = nh.subscribe("odom", 1000, odomCallback);
    
    ros::spin();
    
    return 0;
}