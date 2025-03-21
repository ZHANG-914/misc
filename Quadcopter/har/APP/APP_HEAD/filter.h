#pragma once

#include "stm32f4xx.h"
/*********************
*
*项目：森林火灾无人机
*创建时间：2021.7.18
*创建人：toeveryone_zxy
*版本:v1.0
*
* *********************/
typedef struct biquadFilter_s {
    float b0, b1, b2, a1, a2;
    float d1, d2;
} biquadFilter_t;

typedef enum {
    FILTER_LPF,
    FILTER_NOTCH
} biquadFilterType_e;

void biquadFilterInitLPF(biquadFilter_t *filter, u16 samplingFreq, u16 filterFreq);
void biquadFilterInit(biquadFilter_t *filter, u16 samplingFreq, u16 filterFreq, float Q, biquadFilterType_e filterType);
float biquadFilterApply(biquadFilter_t *filter, float input);
