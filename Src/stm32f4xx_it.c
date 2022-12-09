/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "tim.h"
#include "working.h"
#include "button_state.h"
#include "stdio.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */


int a;

uint32_t m = 0;


uint32_t encoder;
int16_t signedEncoder;
int16_t speed;
int16_t oldPos = 0;
int indx = 0;
int u;

int saved_position = 0;

int encoderPose = 0;

eButtonEvent button1;
eButtonEvent button2;

#define ONE_CYCLE 7100
#define GOAL_TOLERANCE 20
bool processEnable = true;
bool goingPose = false;
process currentOperation = NO_PROCESS;
int goalPose = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	indx = indx + 1;

	if(indx == 10){
		speed = (signedEncoder - oldPos)*100; // speed in clicks/sec
		oldPos = signedEncoder;
		encoderPose = encoderPose + speed*0.01;
		indx = 0;
	}

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  buttonLedRun();

  encoder = TIM4->CNT;
  signedEncoder = (int16_t)encoder;

  button1 = getButtonEvent();
  button2 = getButtonEvent2();

  if(button1 == NO_PRESS){
	  a = 1;
    }
  else if(button1 == SINGLE_PRESS){
	  // m = m + 1;
	  if(processEnable){
		  m = m + 1;
		  processEnable = false;
		  currentOperation = GO_POSE;
		  goalPose = saved_position;
	  }
  }
  else if(button1 == LONG_PRESS){
	  a = 3;
	  if(processEnable){
		  a = 6;
		  // goingPose = true;
		  processEnable = false;
		  currentOperation = BUTTON1;
		  goalPose = encoderPose + ONE_CYCLE;
	  }
    }
  else if(button1 == DOUBLE_PRESS){
	  a = 4;
	  if(processEnable){
		  a = 6;
		  // goingPose = true;
		  currentOperation = NO_PROCESS;
		  saved_position = encoderPose;
	  }
    }
  else{
	  a = 5;
  }


  if(button2 == NO_PRESS){
	  a = 1;
    }
  else if(button2 == SINGLE_PRESS){
	  // m = m + 1;
	  if(processEnable){
		  m = m + 1;
		  processEnable = false;
		  currentOperation = GO_POSE;
		  goalPose = saved_position;
	  }
  }
  else if(button2 == LONG_PRESS){
	  a = 3;
	  if(processEnable){
		  a = 6;
		  // goingPose = true;
		  processEnable = false;
		  currentOperation = BUTTON2;
		  goalPose = encoderPose - ONE_CYCLE;
	  }
    }
  else if(button2 == DOUBLE_PRESS){
	  a = 4;
	  if(processEnable){
		  a = 6;
		  // goingPose = true;
		  currentOperation = NO_PROCESS;
		  saved_position = encoderPose;
	  }
    }
  else{
	  a = 5;
  }

  if(!processEnable){
	  // algoritm, sonra fonksiyon haline getir.
	  u = abs(goalPose - encoderPose);
	  if(abs(goalPose - encoderPose) < GOAL_TOLERANCE){
		  stop();
		  processEnable = true;
		  goalPose = encoderPose;
		  currentOperation = NO_PROCESS;
	  }
	  else if(currentOperation == BUTTON1){
		  goForward();
	  }
	  else if(currentOperation == BUTTON2){
		  goBackward();
	  }
	  else if(currentOperation == GO_POSE){
		  if(goalPose - encoderPose > 0){
			  goForward();
		  }
		  else if(goalPose - encoderPose < 0){
			  goBackward();
		  }
		  else{
			  stop();
		  }
	  }
	  else{
		  stop();
	  }
  }

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
