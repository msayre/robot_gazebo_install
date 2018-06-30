#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/String.h>
#include <rosgraph_msgs/Log.h>
#include <string>

using namespace std;

ros::Publisher pubHeading1, pubHeading2;
visualization_msgs::Marker textHeading1, textHeading2;
string clearing="Clearing costmap to unstuck robot";
string recovery="Rotate recovery behavior";
string aborting="Aborting because a valid plan";
string prevMsg="AUTOMATED\nOPERATION";

void rosoutCallback1(const rosgraph_msgs::Log::ConstPtr& msg) {
  //ROS_INFO("%s", msg->msg.c_str());
  textHeading1.header.frame_id = "/base_link";
  textHeading1.header.stamp = ros::Time::now();
  textHeading1.ns = "points";
  textHeading1.id = 1;
  textHeading1.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
  textHeading1.action = visualization_msgs::Marker::ADD;

  textHeading1.pose.position.x = 0.0;
  textHeading1.pose.position.y = 0.0;
  textHeading1.pose.position.z = 1.5;
  textHeading1.pose.orientation.x = 0.0;
  textHeading1.pose.orientation.y = 0.0;
  textHeading1.pose.orientation.z = 0.0;
  textHeading1.pose.orientation.w = 1.0;

if ((msg->msg.find(clearing) != std::string::npos) || (msg->msg.find(recovery) != std::string::npos)) {
    prevMsg = "PREDICTIVE ALARM:\n  ROBOT STUCK";
ROS_INFO("Cleared or recovery");
} else if (msg->msg.find(aborting) != std::string::npos) {
    prevMsg = "ALARM:\nROBOT PLANNING FAILED";
ROS_INFO("planning failed");
} 
  textHeading1.text = prevMsg;
  textHeading1.scale.x = 0.5;
  textHeading1.scale.y = 0.5;
  textHeading1.scale.z = 0.5;

  textHeading1.color.r = 1.0f;
  textHeading1.color.g = 0.0f;
  textHeading1.color.b = 0.0f;
  textHeading1.color.a = 1.0;

  pubHeading1.publish(textHeading1);
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "cog_visualization");

  ros::NodeHandle n("~");

  pubHeading1 = n.advertise<visualization_msgs::Marker>("/alert_marker", 10);

  ros::Subscriber subRosout = n.subscribe("/rosout_agg", 1000, rosoutCallback1);

  ros::spin();

  return 0;
}

