/*
 * working.h
 *
 *  Created on: Dec 8, 2022
 *      Author: murat
 */

#ifndef INC_WORKING_H_
#define INC_WORKING_H_

#include "main.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;

typedef enum
{
    NO_PROCESS,
    BUTTON1,
    BUTTON2,
    GO_POSE
} process ;

void buttonLedRun(void);
void goForward(void);
void goBackward(void);
void stop(void);

#endif /* INC_WORKING_H_ */
