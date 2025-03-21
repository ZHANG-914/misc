#pragma once
#include"pid_para.h"
/*********************
*
*项目：森林火灾无人机
*创建时间：2021.7.18
*创建人：toeveryone_zxy
*版本:v1.0
*
* *********************/

#define INLIMIT_RATE 50
#define INLIMIT_ANGLE 30
void pidinit(PID_type *pid,float dt,float cutoffFreq);
float anglePID(PID_type *pid,float state,float angledesired,float dt);
float ratePID(PID_type *pid,float state,float angledesired,float dt);
