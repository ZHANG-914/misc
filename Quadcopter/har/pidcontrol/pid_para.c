#include"pid_para.h"

/*********************
*
*项目：森林火灾无人机
*创建时间：2021.7.18
*创建人：toeveryone_zxy
*版本:v1.0
*
* *********************/

 //本文件单独将PID系数拿出来，方便调参
 
PID_type PID_angle_roll=
{
	.kp=1.0,
	.ki=0.0,
	.kd=0.0,
};

//PID_type PID_angle_pitch=
//{
//	.kp=1.1,
//	.ki=0.0,
//	.kd=0.2,
//};

PID_type PID_angle_pitch=
{
	.kp=0.0,
	.ki=0.0,
	.kd=0.0,
};

PID_type PID_angle_yaw=
{
	.kp=0.0,
	.ki=0.0,
	.kd=0.0,
};

//PID_type PID_angle_yaw=
//{
//	.kp=1.1,
//	.ki=0.0,
//	.kd=0.2,
//};

PID_type PID_rate_roll=
{
	.kp=1.75,
	.ki=0.0,
	.kd=0.0,
};

//PID_type PID_rate_pitch=
//{
//	.kp=1.1,
//	.ki=0.0,
//	.kd=0.2,
//};
PID_type PID_rate_pitch=
{
	.kp=0.0,
	.ki=0.0,
	.kd=0.0,
};

PID_type PID_rate_yaw=
{
	.kp=0.0,
	.ki=0.0,
	.kd=0.0,
};


//PID_type PID_rate_yaw=   //初代角速度偏航PID
//{
//	.kp=1.0,
//	.ki=0.1,
//	.kd=0.2,
//};
