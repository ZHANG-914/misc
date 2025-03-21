#include"control.h"
#include"pid_para.h"
#include"pid.h"
#include"sys.h"
#include"imu.h"
#include"motor.h"
#include"usart.h"
#include <ucos_ii.h>
/*********************
*
*项目：森林火灾无人机
*创建时间：2021.7.18
*创建人：toeveryone_zxy
*版本:v1.0
*
* *********************/
desired_t angledesired;
desired_t ratedesired;
set_t	setpoint;
sensor_t sensordata;
Attitude  state;
control_t control;
extern u16 throttle;
extern OS_EVENT  *Timqry1;
extern OS_EVENT  *Timqry2;
extern OS_EVENT  *Timqry3;
extern OS_EVENT  *Timqry4;
extern OS_EVENT  *Timqry;
extern OS_EVENT	 *senqry;
extern u8 lock;
extern u16 measur[4];
void controlinit(control_t *c)
{
	pidinit(&PID_angle_roll,ANGLE_PID_DT,0);
	pidinit(&PID_angle_pitch,ANGLE_PID_DT,0);
	pidinit(&PID_angle_yaw,ANGLE_PID_DT,0);
	pidinit(&PID_rate_roll,RATE_PID_DT,PID_RATE_LPF_CUTOFF_FREQ);
	pidinit(&PID_rate_pitch,RATE_PID_DT,PID_RATE_LPF_CUTOFF_FREQ);
	pidinit(&PID_rate_yaw,RATE_PID_DT,PID_RATE_LPF_CUTOFF_FREQ);
	c->pitch=0;
	c->roll=0;
	c->throttle=1000;
	c->yaw=0;
}
void attitudecontrol(control_t *control,set_t *setpoint,Attitude *state,int time,sensor_t *sensor)
{
	if(TIME_TODO(ANGLE_PID_RATE,time)){
		//角度环
		//横滚角和俯仰角直接根据摇杆的状态进行期望值得设定
		angledesired.roll=setpoint->roll;		
		angledesired.pitch=setpoint->pitch;

		//偏航角叠加对应摇杆的状态，并且在1s秒转动摇杆对应的角度
		angledesired.yaw+=setpoint->yaw/ANGLE_PID_RATE;  
		if(angledesired.yaw>180.0f)
			angledesired.yaw-=360.0f;
		if(angledesired.yaw<-180.0f)
			angledesired.yaw+=360.0f;
	   //printf("  angledesired yaw:%f\n",angledesired.yaw);
		 //printf("  setpoint->yaw: %f\n",setpoint->yaw);
		 

		ratedesired.roll=anglePID(&PID_angle_roll,state->roll,angledesired.roll,ANGLE_PID_DT);
		ratedesired.pitch=anglePID(&PID_angle_pitch,state->pitch,angledesired.pitch,ANGLE_PID_DT);
		ratedesired.yaw=anglePID(&PID_angle_yaw,state->yaw,angledesired.yaw,ANGLE_PID_DT);
	}
	if(TIME_TODO(RATE_PID_RATE,time)){
		//角速度环
		control->roll=ratePID(&PID_rate_roll,sensor->gyro.x,ratedesired.roll,RATE_PID_DT);
		control->pitch=ratePID(&PID_rate_pitch,sensor->gyro.y,ratedesired.pitch,RATE_PID_DT);
		control->yaw=ratePID(&PID_rate_yaw,sensor->gyro.z,ratedesired.yaw,RATE_PID_DT);
	}
	control->throttle=setpoint->throttle;
}

void TASK_PID(void)
{
		int time;
		controlinit(&control);
		while(1){
			//获取遥控器信息
mag = READ_HMCALL(mag);
        mpu6050 = MPU6050_READ(mpu6050); //读取加速度、角速度、磁场强度
			//进行姿态解算
			if(TIME_TODO(ATTITUDE_ESTIMAT_RATE,time)){
				imuUpdate(sensordata.acc,sensordata.gyro,&state,ATTITUDE_ESTIMAT_DT);
//				float x=state.pitch;
//				state.pitch=state.roll;
//				state.roll=x;
			}
			if(!lock)attitudecontrol(&control,&setpoint,&state,time,&sensordata);
			MOTOR_control(&control);
			//
			time++;
			OSTimeDly(1);  //任务周期1ms
		}

}
