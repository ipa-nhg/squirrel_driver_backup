#ifndef ROBOT_CONTROLLER_HPP
#define ROBOT_CONTROLLER_HPP
#include <iostream>
#include <vector>
#include <uibk_robot_driver/base_controller.hpp>
#include <uibk_robot_driver/arm_controller.hpp>
#include <uibk_robot_driver/tictoc.hpp>
#include <std_msgs/Bool.h>
#include <mutex>

#define DONTCARE nan("1")

class RobotController {

private:

    void skinCallback(const std_msgs::Bool &skinReply);

    TicToc skinTic;
    std::mutex skinMutex;
	
    bool receivedFirstSkinPacket;
	std::shared_ptr<BaseController> myBase;
	std::shared_ptr<Arm> myArm;
	std::shared_ptr<std::thread> myArmThread;
    bool baseExists, armExists;
	double controller_freq;
	ros::NodeHandle myNode;
    std::string portName;
    double protocolVersion;
    int baudRate;
    ros::Subscriber skinBumper;

public:

	RobotController(ros::NodeHandle& node, double controller_freq);
	void initBase();
	void initArm(std::vector<int> ids, std::vector<motor_controller::motor_type> types, std::vector< std::pair<double, double> > jointLimits);
	void moveAll(std::vector<double> targetStates);
	void ptpAll(std::vector<double> targetStates);
	void gotoAll(std::vector<double> targetStates);
	std::vector<double> getCurrentStates();


	// For arm
	double getArmFrequency();
	double getArmCycleTime();
	double getArmMaxStepPerCycle();
	int getDegOfFreedom();

	void shutdown();

};

#endif // ROBOT_CONTROLLER_HPP
