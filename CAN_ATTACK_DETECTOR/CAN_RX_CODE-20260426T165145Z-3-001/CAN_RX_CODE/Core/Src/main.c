	/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "string.h"
#include "Serial.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define DEVICEID              0x446

#define MAX_CAN_DATA_SIZE 8
#define MAX_DEVICE_COUNT  3



#define ENGINE_RPM_DEVICE_ID  0x0C0
#define TEMPERATURE_DEVICE_ID 0x0B0
#define THROTTLE_POSITION_ID  0x0D0


#define MAX_ENGINE_RPM        4000
#define MIN_ENGINE_RPM        1000
#define MAX_TEMPERATURE       150
#define MIN_TEMPERATURE       70
#define MAX_THROTTLE          60
#define MIN_THROTTLE          10

typedef struct {
  uint32_t CANDEVICEID;
  uint32_t MAXTHERSHOLD;
  uint32_t MINTHERSHOLD;
  uint8_t  CANDATA[MAX_CAN_DATA_SIZE];
}caninfo_t;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
UART_HandleTypeDef huart4;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN PV */


void CanNodeInit(caninfo_t *pvData);
void CAN_Packet_Decoder (CAN_RxHeaderTypeDef RxHeader,uint8_t *pvData);

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
/* USER CODE BEGIN PFP */
static void MX_UART4_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint8_t TxData[8];
uint8_t RxData[8];

uint32_t TxMailbox;

caninfo_t CANINFOS[MAX_DEVICE_COUNT];
caninfo_t PreviousCanPacket;

volatile static uint8_t CANRXSTATUS;


unsigned char Start[] = {"\r\n==========================================================\r\n"
						  "\r\n REAL-TIME INTRUSION DETECTION FOR AUTOMOTIVE CAN COMMUNICATION ON EMBEDDED PLATFORMS \r\n"
						  "\r\n ATTACK DEETECTOR \r\n"
					      "\r\n=========================================================\r\n"};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  CanNodeInit(CANINFOS);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_UART4_Init();
  HAL_CAN_Start(&hcan1);

  // Activate the notification
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
//  PrintLog((const char *)Start);
  printf(Start);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    if(CANRXSTATUS) {
      CANRXSTATUS = 0;
      CAN_Packet_Decoder(RxHeader,RxData);
    }
    /* USER CODE BEGIN 3 */
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6 ;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_11TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  CAN_FilterTypeDef canfilterconfig;

  canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
  canfilterconfig.FilterBank = 18;  // which filter bank to use from the assigned ones
  canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  canfilterconfig.FilterIdHigh = 0x0000;
  canfilterconfig.FilterIdLow = 0x0000;
  canfilterconfig.FilterMaskIdHigh = 0x0000;
  canfilterconfig.FilterMaskIdLow = 0x0000;
  canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
  canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
  canfilterconfig.SlaveStartFilterBank = 20;  // how many filters to assign to the CAN1 (master can)

  HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);


  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

static void MX_UART4_Init(void) {

	/* USER CODE BEGIN UART4_Init 0 */
	/* USER CODE END UART4_Init 0 */

	/* USER CODE BEGIN UART4_Init 1 */
	/* USER CODE END UART4_Init 1 */
	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart4) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN UART4_Init 2 */
	/* USER CODE END UART4_Init 2 */

}

void CanNodeInit(caninfo_t *pvData) {

  pvData[0].CANDEVICEID =   ENGINE_RPM_DEVICE_ID;
  pvData[1].CANDEVICEID =   TEMPERATURE_DEVICE_ID;
  pvData[2].CANDEVICEID =   THROTTLE_POSITION_ID;

  pvData[0].MAXTHERSHOLD =  MAX_ENGINE_RPM;
  pvData[1].MAXTHERSHOLD =  MAX_TEMPERATURE;
  pvData[2].MAXTHERSHOLD =  MAX_THROTTLE;

  pvData[0].MINTHERSHOLD =  MIN_ENGINE_RPM;
  pvData[1].MINTHERSHOLD =  MIN_TEMPERATURE;
  pvData[2].MINTHERSHOLD =  MIN_THROTTLE;

}



void CAN_Packet_Decoder (CAN_RxHeaderTypeDef rxHeader,uint8_t *pvData) {

  uint32_t Data = 0;


  if( (PreviousCanPacket.CANDEVICEID == rxHeader.StdId) && ((PreviousCanPacket.CANDATA[0] == pvData[0]) && (PreviousCanPacket.CANDATA[1] == pvData[1]))) {
	  printf("[SECURITY ALERT]:: Flooding/DOS Attack detected on the communication bus\n");

    return;
  } else if(PreviousCanPacket.CANDEVICEID == rxHeader.StdId) {
	  printf("[SECURITY ALERT]:: Replay Attack detected on the communication bus\n");
    return;
  }

  PreviousCanPacket.CANDEVICEID = rxHeader.StdId;


  switch(rxHeader.StdId) {
    case ENGINE_RPM_DEVICE_ID:
    Data |= pvData[0];
    Data |= (pvData[1] << 8);

    if((Data > MAX_ENGINE_RPM) || (Data < MIN_ENGINE_RPM)) {
      printf("[SECURITY ALERT]:: Spoofing Attack Invalid RPM %ld Data from the  Engine RPM CAN node\n",Data);
      return;
    } else {
      printf("CAR RPM %ld\n",Data);
    }
    break;
    case TEMPERATURE_DEVICE_ID:
    if((pvData[0] > MAX_TEMPERATURE) || (pvData[0] < MIN_TEMPERATURE)) {
      printf("[SECURITY ALERT]:: Spoofing Attack Invalid TEMPERATURE %d Data from the  Engine Temperature CAN node\n",pvData[0]);
      return;
    } else {
      printf("CAR TEMPERATURE %d \n",pvData[0]);
    }
    break;
    case THROTTLE_POSITION_ID:
    if((pvData[0] > MAX_THROTTLE) || (pvData[0] < MIN_THROTTLE)) {
      printf("[SECURITY ALERT]:: Spoofing Attack Invalid Throttle %d Data from the  Engine Throttle CAN node\n",pvData[0]);
      return;
    } else {
      printf("CAR THROTTLE %d\n",pvData[0]);
    }
    break;
    default:
    PreviousCanPacket.CANDEVICEID = 0x000;
    printf("[SECURITY ALERT]::  Unauthorized  CAN node detected on the communication bus\n");
    break;
  }
  PreviousCanPacket.CANDATA[0] = pvData[0];
  PreviousCanPacket.CANDATA[1] = pvData[1];

}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
  CANRXSTATUS = 1;

}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
