#include "main.h"
#include "DataGen.h"
#include "Stopwatch.h"
#include "stdlib.h"

#define DATA_SIZE 2000
#define SAMPLE_AMOUNT 10
#define PRINT_BUF_SIZE 50

UART_HandleTypeDef huart6;
TIM_HandleTypeDef tim6;

uint8_t arr[DATA_SIZE];
volatile int timeHAL[SAMPLE_AMOUNT];
volatile int timeBare[SAMPLE_AMOUNT];
char print_buf[PRINT_BUF_SIZE];

char HALStr[] = "\nHAL Measurements:\n";
char BareStr[] = "\nBare-Metal Measurements:\n";

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  GPIO_Init();
  USART6_UART_Init();
  stopwatch_init();

  if (!FillArray(arr, DATA_SIZE) == DG_Ok)
  {
    Error_Handler();
  }

  //  HAL
  for (int i = 0; i < SAMPLE_AMOUNT; i++)
  {
    stopwatch_start();
    HAL_UART_Transmit(&huart6, arr, DATA_SIZE, 10000);
    stopwatch_stop();
    timeHAL[i] = stopwatch_get_time();
    stopwatch_reset();
  }

  //  Bare-Metal
  for (int i = 0; i < SAMPLE_AMOUNT; i++)
  {
    stopwatch_start();

    for (int j = 0; j < DATA_SIZE; j++)
    {
      while (!(USART6->SR & 0x80))
        ;
      USART6->DR = arr[j];
    }

    stopwatch_stop();
    timeBare[i] = stopwatch_get_time();
    stopwatch_reset();
  }

  //  Transmit HAL measurements
  HAL_UART_Transmit(&huart6, HALStr, sizeof(HALStr), 10000);
  for (int i = 0; i < SAMPLE_AMOUNT; i++)
  {
    itoa(timeHAL[i], print_buf, 10);
    print_buf[PRINT_BUF_SIZE - 1] = '\n';

    HAL_UART_Transmit(&huart6, (uint8_t *)print_buf, PRINT_BUF_SIZE, 10000);
  }

  //  Transmit Bare-Metal measurements
  HAL_UART_Transmit(&huart6, BareStr, sizeof(BareStr), 10000);
  for (int i = 0; i < SAMPLE_AMOUNT; i++)
  {
    itoa(timeBare[i], print_buf, 10);
    print_buf[PRINT_BUF_SIZE - 1] = '\n';

    HAL_UART_Transmit(&huart6, (uint8_t *)print_buf, PRINT_BUF_SIZE, 10000);
  }

  /*
  int timee = 4;

  itoa(timee, print_buf, 10);

  HAL_UART_Transmit(&huart6, (uint8_t *)print_buf, 10, 10000);

  for (int i = 0; i < 10; i++)
  {
    stopwatch_start();
    HAL_Delay(100);
    stopwatch_stop();

    time[i] = stopwatch_get_time();

    stopwatch_reset();
  }

  for (int i = 0; i < SAMPLE_AMOUNT; i++)
  {
    itoa(time[i], print_buf, 10);
    print_buf[PRINT_BUF_SIZE - 1] = '\n';

    HAL_UART_Transmit(&huart6, (uint8_t *)print_buf, PRINT_BUF_SIZE, 10000);
  }
  */

  for (;;)
  {
  }
}

void USART6_UART_Init(void)
{
  __HAL_RCC_USART6_CLK_ENABLE();

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 38400;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
}

void GPIO_Init()
{
  __HAL_RCC_GPIOG_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);

  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ARDUINO_USART6_TX_Pin | USART6_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 6;
  RCC_OscInitStruct.PLL.PLLR = 6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV16;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  for (;;)
    ;
}
