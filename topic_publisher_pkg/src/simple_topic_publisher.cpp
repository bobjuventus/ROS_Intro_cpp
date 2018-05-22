#include <ros/ros.h>
//#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv) {

    ros::init(argc, argv, "topic_publisher");
    ros::NodeHandle nh;
    double linearx, angularz;
    
    nh.getParam("/topic_publisher/linear_x", linearx);
    nh.getParam("/topic_publisher/angular_z", angularz);

    
    //ros::Publisher pub = nh.advertise<std_msgs::Int32>("counter", 1000);
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    ros::Rate loop_rate(2);
    
    //std_msgs::Int32 count;
    //count.data = 0;
    geometry_msgs::Twist var;
    var.linear.x = linearx;
    var.angular.z = angularz;
    
    while (ros::ok())
    {
        pub.publish(var);
        ros::spinOnce();
        loop_rate.sleep();
        //++count.data;
    }
    
    return 0;
}