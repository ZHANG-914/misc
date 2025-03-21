#ifndef PID_H
#define PID_H
#include "includes.h"
#include "filter.h"
#define MAIN_RATE  1000        //任务执行频率
#define MAIN_DT	   (1.0/MAIN_RATE)  //任务执行周期
#define	ANGLE_PID_RATE	250		//角度环频率
#define ANGLE_PID_DT	(1.0/ANGLE_PID_RATE)  //角度环周期
#define RATE_PID_RATE	500		//角速度环频率
#define RATE_PID_DT		(1.0/RATE_PID_RATE)	  //角速度环周期
#define GETSET_RATE		100		//遥控器获取频率
#define GETSET_DT	    (1.0/GETSET_RATE)
#define GETSEN_RATE		500
#define GETSEN_DT	    (1.0/GETSEN_RATE)
#define TIME_TODO(X,Y)	 ((Y%(MAIN_RATE/X))==0)
#define RP_RANGE		30   //角度范围+-ANGEL_RANGE
#define Y_RANGE		15   //角度范围+-ANGEL_RANGE
#define REMOTE2RP(X,Y)   (Y=((float)(X-1500)/500.0)*RP_RANGE)
#define REMOTE2Y(X,Y)   (Y=((float)(X-1500)/500.0)*Y_RANGE)
#define ATTITUDE_ESTIMAT_RATE	250//姿态解算速率
#define ATTITUDE_ESTIMAT_DT		(1.0/250)

/*角速度PID积分限幅（单位：deg/s）*/
#define PID_RATE_ROLL_INTEGRATION_LIMIT		200.0
#define PID_RATE_PITCH_INTEGRATION_LIMIT	200.0
#define PID_RATE_YAW_INTEGRATION_LIMIT		100.0

/*角速度PID输出限幅（单位：油门值）*/
#define PID_RATE_ROLL_OUTPUT_LIMIT			500.0
#define PID_RATE_PITCH_OUTPUT_LIMIT			500.0
#define PID_RATE_YAW_OUTPUT_LIMIT			300.0

/*角度PID输出限幅（单位：deg/s）*/
#define PID_ANGLE_ROLL_OUTPUT_LIMIT    		300.0
#define PID_ANGLE_PITCH_OUTPUT_LIMIT   		300.0
#define PID_ANGLE_YAW_OUTPUT_LIMIT     		150.0

//Z轴速度PID积分限幅（单位cm/s）
#define PID_VZ_INTEGRATION_LIMIT 			500.0
//Z轴速度PID输出限幅（单位油门值）
#define PID_VZ_OUTPUT_LIMIT					800.0

//XY轴速度PID积分限幅（单位cm/s）
#define PID_VXY_INTEGRATION_LIMIT			300.0
//XY轴速度PID输出限幅（单位deg）
#define PID_VXY_OUTPUT_LIMIT				30.0


//角速度PID D项低通截止频率（单位Hz）
#define PID_RATE_LPF_CUTOFF_FREQ			80.0
typedef struct   //定义记录每个方向pid各量的结构
{
	float desired;
	float error;
	float preerr;
	float kp;
	float ki;
	float kd;
	float dt;
	float integ;
	float deriv;
	biquadFilter_t dFilter;
}PID_type;

typedef	struct		//最终的混控设定值
{
	float yaw;
	float pitch;
	float roll;
	float throttle;
}control_t;

typedef struct		//期望的角度值
{
	float yaw;
	float pitch;
	float roll;
}desired_t;

typedef struct attitude //飞行器当前各方向角度值，用于角度环
{
	float pitch;
	float roll;
	float yaw;
} Attitude;

extern PID_type PID_angle_roll;
extern PID_type PID_angle_pitch;
extern PID_type PID_angle_yaw;
extern PID_type PID_rate_roll;
extern PID_type PID_rate_pitch;
extern PID_type PID_rate_yaw;

#define INLIMIT_RATE 50
#define INLIMIT_ANGLE 30
void pidinit(PID_type *pid,float dt,float cutoffFreq);
float anglePID(PID_type *pid,float state,float angledesired,float dt);
float ratePID(PID_type *pid,float state,float angledesired,float dt);
#endif
