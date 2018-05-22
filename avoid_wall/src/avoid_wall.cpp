#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>

struct avoid_wall{
    
        float min_range;
        float max_range;
        int size = 720;
        //std::vector<std::string> ranges;
        std::vector<float> ranges = std::vector<float>(size);
        float dist, ang;
        int min_pos;
        //float ranges[720];
        ros::NodeHandle nh;
        ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        ros::Subscriber sub = nh.subscribe("kobuki/laser/scan", 1000, &avoid_wall::callback, this);
        //float *ranges = float[size];
        //avoid_wall();
    public:
        //avoid_wall();
        
        void callback(const sensor_msgs::LaserScan::ConstPtr &msg);
        float distance();
        float angle();
    
};
/*
avoid_wall::avoid_wall(){
        std::vector<float> ranges(720, 42.0);

}
*/
void avoid_wall::callback(const sensor_msgs::LaserScan::ConstPtr &msg){
        min_range = msg->range_min;
        max_range = msg->range_max;
        size = (msg->ranges).size();
        //std::cout << size;
        //std::cout << msg->ranges[720];
        ranges.resize(size);
        
        //std::cout << ranges.size() << "\n";
    
        //std::vector<std::string>::const_iterator i
        for (int i = 0; i<size; i++)
        {
            //std::vector<std::string>::iterator it;
            //it  = ranges.begin() + i;
            //ranges.insert(i, msg->ranges[i].str());
            ranges[i] = msg->ranges[i];
            //std::cout << ranges[i] << " ";
            
        }
        
        //std::cout << typeid(ranges[1]) << "\n";
}


float avoid_wall::angle(){
        //float min_value = std::min_element( ranges.begin(), ranges.end() );
        //ros::Duration(0.5).sleep();
        //float min_value = 30.0;
        ang = 90.0;
        //int min_pos;
        float temp_dist = 30.0;
        float min_pos;
        
        for (int i=0; i<size; i++)
        {
            std::ostringstream ss;
            ss << ranges[i];
            if (ss.str() != "inf" && ranges[i] < temp_dist)
            {
                temp_dist = ranges[i];
                min_pos = float(i);
            }

        }
        
        if (min_pos >= 0 && min_pos <=720)
        {
            ang = min_pos/size*180;
        }
        //std::vector<float>::iterator it;
        //it = ranges.begin() + 1;       
        //std::cout<<*it<<" ";
        //std::cout << ranges[360] << " ";
        //std::cout << "min_range is :" << min_range << " and max_range is :" << max_range << " ";
        return ang;
}

float avoid_wall::distance(){
        //float min_value = std::min_element( ranges.begin(), ranges.end() );
        //ros::Duration(0.5).sleep();
        //float min_value = 30.0;
        dist = 30.0;
        
        
        for (int i=0; i<size; i++)
        {
            std::ostringstream ss;
            ss << ranges[i];
            if (ss.str() != "inf" && ranges[i] < dist)
            {
                //min_value = std::strtof((ranges[i]).c_str(),0);
                dist = ranges[i];
                //min_pos = i;
            }

        }
        
        //std::vector<float>::iterator it;
        //it = ranges.begin() + 1;       
        //std::cout<<*it<<" ";
        //std::cout << ranges[360] << " ";
        //std::cout << "min_range is :" << min_range << " and max_range is :" << max_range << " ";
        return dist;
}

int main(int argc, char** argv) {
    
    ros::init(argc, argv, "avoid_wall");
    
    float dist, angle;
    
    avoid_wall avoid;
    
    geometry_msgs::Twist vel;
    vel.linear.x = 0.5;
    vel.angular.z = 0.0;
    avoid.pub.publish(vel);
    
    ros::Rate loop_rate(2);
        
    while (ros::ok())
    {
        //std::cout << avoid.min_range << "\n";
        //ros::Duration(0.5).sleep();
        dist = avoid.distance();
        angle = avoid.angle();
        std::cout << "distance is " << dist << " and angle is " << angle << "\n";
        ros::Duration(0.5).sleep();
        
        if (dist < 2.0 && angle > 0.1 && angle < 70.0)
        {
          vel.linear.x = 0.0;
          vel.angular.z = 0.5;
          avoid.pub.publish(vel);
        }
        else if (dist < 2.0 and angle > 110 and angle < 180)
        {
          vel.linear.x = 0.0;
          vel.angular.z = -0.5;
          avoid.pub.publish(vel);
        }
        else if (dist < 2.0 and angle >= 70 and angle <= 90)
        {
          vel.linear.x = 0.5;
          vel.angular.z = 0.5;
          avoid.pub.publish(vel);
        }
        else if (dist < 2 and angle >= 90 and angle <= 110)
        {
          vel.linear.x = 0.5;
          vel.angular.z = -0.5;
          avoid.pub.publish(vel);
        }
        else
        {
          vel.linear.x = 0.5;
          vel.angular.z = 0.5;
          avoid.pub.publish(vel);
        }
        
        
        
        ros::spinOnce();
        loop_rate.sleep();
        //++count.data;
    }
    
    
    
    return 0;
}