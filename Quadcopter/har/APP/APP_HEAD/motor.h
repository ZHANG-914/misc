#ifndef MOTOR_H
#define MOTOR_H

//���벶��ʱ����TIM3��Ƶ��Ϊ 1MHz ,�� 1/1M ���������1��
//��һ�������ز����½��ز����ʱ��Ϊ x/1M �룬xΪ���β��������ֵ���
//��ң������������PWMƵ��Ϊ 54.27Hz ����һ��PWM����ʱ��Ϊ 1/54.27 ��
//�����ʱ�����ռ�ձ�ΪD���� D / 54.27 = x / 1M => x = 1000000D / 54.27
//����ΪPWM�����ʱ����TIM3��arrΪ20000��Ϊ�������ռ�ձȺ������һ�����������CCRxֵΪ 20000D
//���� x * PWM_IN_TO_OUT = 20000D => PWM_IN_TO_OUT = 20000D * 54.27 / 1000000D = 1.0854
#define PWM_IN_TO_OUT 1

void MOTOR_init(void);
void MOTOR_lock(void);
void MOTOR_max(void);
void MOTOR_CONTROL(void);
#endif
