#include "Stopwatch.h"
#include "stm32f4xx_hal.h"

static void TIM8_Init( void );
extern void Error_Handler( void );

TIM_HandleTypeDef htim8;


void stopwatch_init( void ) {
    TIM8_Init();
}

void stopwatch_start( void ) {
  HAL_TIM_Base_Start(&htim8);
}

void stopwatch_stop( void ) {
  HAL_TIM_Base_Stop(&htim8);
}

void stopwatch_reset( void ) {
  __HAL_TIM_SET_COUNTER(&htim8, __HAL_TIM_GET_AUTORELOAD(&htim8));
}

int stopwatch_get_time( void ) {
  return __HAL_TIM_GET_COUNTER(&htim8);
}

static void TIM8_Init( void )
{

  __HAL_RCC_TIM8_CLK_ENABLE();


  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 10000;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 0xFFFF;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 100;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  if (HAL_TIM_SlaveConfigSynchro(&htim8, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}