#include "pid.h"
#include "pid_para.h"
#include "usart.h"
#include "filter.h"
/*********************
*
*项目：森林火灾无人机
*创建时间：2021.7.18
*创建人：toeveryone_zxy
*版本:v1.0
*
* *********************/

static int x;
void pidinit(PID_type *pid, float dt, float cutoffFreq)
{
	pid->error = 0;
	pid->preerr = 0;
	pid->desired = 0;
	pid->dt = dt;
	biquadFilterInitLPF(&pid->dFilter, (1.0f / dt), cutoffFreq);
}
float anglePID(PID_type *pid, float state, float angledesired, float dt)
{
	float ans;
	pid->error = angledesired - state;
	//主要针对航向角，因为航向有可能无视极限继续转动，以顺时针转动为例，当由180到达负角度时，其实只正向转动了一点点，但是error却是大于180
	if (pid->error > 180.0f)
	{
		pid->error -= 360.0f;
	}
	else if (pid->error < -180.0)
	{
		pid->error += 360.0f;
	}
	pid->integ += pid->error * pid->dt;
	pid->deriv = (pid->error - pid->preerr) / pid->dt;
	pid->preerr = pid->error;
	//积分限幅
	if (pid->integ > INLIMIT_ANGLE)
	{
		pid->integ = INLIMIT_ANGLE;
	}
	else if (pid->integ < -INLIMIT_ANGLE)
	{
		pid->integ = -INLIMIT_ANGLE;
	}

	ans = pid->kp * pid->error + pid->ki * pid->integ + pid->kd * pid->deriv;
	return ans;
}

float ratePID(PID_type *pid, float state, float angledesired, float dt)
{
	float ans;
	pid->error = angledesired - state;
	pid->integ += pid->error * pid->dt;
	pid->deriv = (pid->error - pid->preerr) / pid->dt;
	x++;
	//	if(x%1000==0)printf("%d\n",x);
	//	mmtt=(pid->error-pid->preerr);

	//printf("%f\n",pid->error);

	//积分限幅
	if (pid->integ > INLIMIT_RATE)
	{
		pid->integ = INLIMIT_RATE;
	}
	else if (pid->integ < -INLIMIT_RATE)
	{
		pid->integ = -INLIMIT_RATE;
	}

	//微分滤波
	pid->deriv = biquadFilterApply(&pid->dFilter, pid->deriv);

	pid->preerr = pid->error;
	ans = pid->kp * pid->error + pid->ki * pid->integ + pid->kd * pid->deriv;
	return ans;
}
