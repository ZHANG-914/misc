#pragma once
#include "pid_para.h"
/*********************
*
*项目：森林火灾无人机
*创建时间：2021.7.18
*创建人：toeveryone_zxy
*版本:v1.0
*
* *********************/
#define DEG2RAD		0.017453293f	/* 度转弧度 π/180 */
#define RAD2DEG		57.29578f		/* 弧度转度 180/π */


void imuComputeRotationMatrix(void);
float invSqrt(float x);
void imuUpdate(Axis3f acc, Axis3f gyro, Attitude *attitude , float dt);
