/*
 * button_state.h
 *
 *  Created on: Dec 8, 2022
 *      Author: murat
 */

#ifndef INC_BUTTON_STATE_H_
#define INC_BUTTON_STATE_H_

#include "main.h"

#include "stdbool.h"
#include "main.h"

typedef enum
{
    NO_PRESS,
    SINGLE_PRESS,
    LONG_PRESS,
    DOUBLE_PRESS
} eButtonEvent ;

bool buttonState(void);
eButtonEvent getButtonEvent(void);
bool buttonState2(void);
eButtonEvent getButtonEvent2(void);

#endif /* INC_BUTTON_STATE_H_ */
