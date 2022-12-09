/*
 * button_state.c
 *
 *  Created on: Dec 8, 2022
 *      Author: murat
 */


#include "button_state.h"

bool buttonState()
{

		static uint32_t DEBOUNCE_MILLIS = 20 ;
		GPIO_PinState buttonstate = HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_0 ) == GPIO_PIN_SET ;
		uint32_t buttonstate_ts = HAL_GetTick() ;

		uint32_t now = HAL_GetTick() ;
		if( now - buttonstate_ts > DEBOUNCE_MILLIS )
		{
			if( buttonstate != HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_0 ) == GPIO_PIN_SET )
			{
				buttonstate = !buttonstate ;
				buttonstate_ts = now ;
			}
		}

	return buttonstate ;
}

eButtonEvent getButtonEvent()
{
    static const uint32_t DOUBLE_GAP_MILLIS_MAX = 250 ;
    static const uint32_t LONG_MILLIS_MIN = 800 ;
    static uint32_t button_down_ts = 0 ;
    static uint32_t button_up_ts = 0 ;
    static bool double_pending = false ;
    static bool long_press_pending = false ;
    static bool button_down = false ; ;

    eButtonEvent button_event = NO_PRESS ;
    uint32_t now = HAL_GetTick() ;

    // If state changed...
    if( button_down != buttonState() )
    {
        button_down = !button_down ;
        if( button_down )
        {
            // Timestamp button-down
            button_down_ts = now ;
        }
        else
        {
            // Timestamp button-up
            button_up_ts = now ;

            // If double decision pending...
            if( double_pending )
            {
                button_event = DOUBLE_PRESS ;
                double_pending = false ;
            }
            else
            {
                double_pending = true ;
            }

            // Cancel any long press pending
            long_press_pending = false ;
        }
    }

    // If button-up and double-press gap time expired, it was a single press
    if( !button_down && double_pending && now - button_up_ts > DOUBLE_GAP_MILLIS_MAX )
    {
        double_pending = false ;
        button_event = SINGLE_PRESS ;
    }
    // else if button-down for long-press...
    else if( !long_press_pending && button_down && now - button_down_ts > LONG_MILLIS_MIN )
    {
        button_event = LONG_PRESS ;
        long_press_pending = false ;
        double_pending = false ;

    }

    return button_event ;
}


bool buttonState2()
{
		static uint32_t DEBOUNCE_MILLIS = 20 ;
		GPIO_PinState buttonstate = HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_1 ) == GPIO_PIN_SET ;
		uint32_t buttonstate_ts = HAL_GetTick() ;

		uint32_t now = HAL_GetTick() ;
		if( now - buttonstate_ts > DEBOUNCE_MILLIS )
		{
			if( buttonstate != HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_1 ) == GPIO_PIN_SET )
			{
				buttonstate = !buttonstate ;
				buttonstate_ts = now ;
			}
		}

	return buttonstate ;
}

eButtonEvent getButtonEvent2()
{
    static const uint32_t DOUBLE_GAP_MILLIS_MAX = 250 ;
    static const uint32_t LONG_MILLIS_MIN = 800 ;
    static uint32_t button_down_ts = 0 ;
    static uint32_t button_up_ts = 0 ;
    static bool double_pending = false ;
    static bool long_press_pending = false ;
    static bool button_down = false ; ;

    eButtonEvent button_event = NO_PRESS ;
    uint32_t now = HAL_GetTick() ;

    // If state changed...
    if( button_down != buttonState2() )
    {
        button_down = !button_down ;
        if( button_down )
        {
            // Timestamp button-down
            button_down_ts = now ;
        }
        else
        {
            // Timestamp button-up
            button_up_ts = now ;

            // If double decision pending...
            if( double_pending )
            {
                button_event = DOUBLE_PRESS ;
                double_pending = false ;
            }
            else
            {
                double_pending = true ;
            }

            // Cancel any long press pending
            long_press_pending = false ;
        }
    }

    // If button-up and double-press gap time expired, it was a single press
    if( !button_down && double_pending && now - button_up_ts > DOUBLE_GAP_MILLIS_MAX )
    {
        double_pending = false ;
        button_event = SINGLE_PRESS ;
    }
    // else if button-down for long-press...
    else if( !long_press_pending && button_down && now - button_down_ts > LONG_MILLIS_MIN )
    {
        button_event = LONG_PRESS ;
        long_press_pending = false ;
        double_pending = false ;

    }

    return button_event ;
}
