#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/JointState.h>

//generic C/C++ include
#include <string>
#include <sstream>
#include <ros/console.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "arm2r_tf_listener");

  ros::NodeHandle node;

  sensor_msgs::JointState jointstate_msg;
  jointstate_msg.header.stamp = ros::Time(0);
  jointstate_msg.name.push_back("joint_base_first");
  jointstate_msg.name.push_back("joint_first_second");
  //reset the messages
  // jointstate_msg.position.clear();
  // jointstate_msg.velocity.clear();
  // jointstate_msg.effort.clear();
  jointstate_msg.position.push_back(1);
  //jointstate_msg.position[0]=1;
  jointstate_msg.position.push_back(0.5); 
  //jointstate_msg.position[1]=0.5;
  ros::Publisher pub_datainfo_joints;
  pub_datainfo_joints=node.advertise<sensor_msgs::JointState>(node.resolveName("/calibrated/joint_states"), 10);

  tf::TransformListener listener;

  ros::Rate rate(10.0);
  while (node.ok()){
    pub_datainfo_joints.publish(jointstate_msg);
    tf::StampedTransform transform;
    try {
    //listener.waitForTransform("/second_link", "/base_link", ros::Time(0), ros::Duration(10.0) );
    listener.lookupTransform("/second_link", "/base_link", ros::Time(0), transform);
    ROS_INFO("Translation = %f,%f,%f", transform.getOrigin().x(),transform.getOrigin().y(),transform.getOrigin().z());
	} catch (tf::TransformException ex) {
    ROS_ERROR("%s",ex.what());
	}
    rate.sleep();
  }
  return 0;
};
