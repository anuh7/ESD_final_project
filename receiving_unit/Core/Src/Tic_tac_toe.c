/*
 * Filename: Tic-tac-toe.c
 * Created on: Nov 25, 2022
 * Author: Shashank and Anuhya
 * Description: This C file contains the tic tac toe algorithm
 * Reference: None
 */

#include <IL9341_TFT_Drivers.h>
#include <ILI9341_TFT_API.h>
#include <SPI_DMA.h>
#include <UART.h>
#include <main.h>
#include <stdio.h>
#include <stdbool.h>

//Macros for the coordinates and lengths in graphic APIs
#define TEXT1_X 10
#define TEXT1_Y 120
#define TEXT2_X 50
#define TEXT2_Y 140
#define DELAY_2000MS 2000
#define BOTTOM_TEXT1_X 70
#define BOTTOM_TEXT1_Y 20
#define HLINE_X 20
#define HLINE_LEN 200
#define HLINE1_Y 126.7
#define HLINE2_Y 193.367
#define DELAY_100MS 100
#define VLINE1_X 86.7
#define VLINE2_X 153.4
#define VLINE_Y 60
#define VLINE_LEN 200
#define BOTTOM_TEXT2_X 30
#define BOTTOM_TEXT2_Y 280
#define BOTTOM_TEXT3_X 40
#define BOTTOM_TEXT3_Y 300
#define BOTTOM_TEXT4_X 70
#define BOTTOM_TEXT4_Y 280
#define X_LEN 50
#define CIRC_RAD 25
#define ROW1X_Y 68.35
#define COL1X_X 28.35
#define COL2X_X 95.02
#define COL3X_X 161.69
#define ROW2X_Y 138.02
#define ROW22X_Y 98.02
#define ROW3X_Y 201.69
#define ROW1O_Y 93.35
#define COL1O_X 53.35
#define COL2O_X 120.02
#define COL3O_X 186.69
#define ROW2O_Y 160.02
#define ROW3O_Y 226.72
#define DELAY_1000MS 1000
#define DIAG_Y 251.69
#define TEXT3_X 50
#define TEXT3_Y 160
#define TEXT4_X 70
#define DELAY_5000MS 5000

uint8_t RX_BUFFER[BUFFER_LEN] = {0};

//Variables for tic-tac-toe algorithm
char board[3][3]={"DDD","DDD","DDD"};
bool track_pos = false;
bool xflag=true,oflag=true;
int count=0;
bool pos_00 = false;
bool pos_01 = false;
bool pos_02 = false;
bool pos_10 = false;
bool pos_11 = false;
bool pos_12 = false;
bool pos_20 = false;
bool pos_21 = false;
bool pos_22 = false;

//For SPI in DMA mode
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

//For UART
UART_HandleTypeDef huart2;


/******************************GPIO initialization function**********************************
 * Parameter passed: None
 * Parameter returned: None
 *********************************************************************************************/
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10, GPIO_PIN_RESET);

	/*Configure GPIO pins : PB0 PB1 PB10 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


/******************************System Clock Configuration*************************************
 * Parameter passed: None
 * Parameter returned: None
 *********************************************************************************************/
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	//Configure the main internal regulator output voltage
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 72;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	// Initializes the CPU, AHB and APB buses clocks
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/****************************Fill the tic-tac-toe matrix with X and O************************
 * Parameter passed: None
 * Parameter returned: None
 *********************************************************************************************/
void fill_matrix(void)
{
	if(pos_00==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(COL1X_X, ROW1X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			xflag=false;
			oflag=true;
			count++;
			board[0][0]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL1O_X, ROW1O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			xflag=true;
			oflag=false;
			count++;
			board[0][0]='O';
		}
		track_pos=false;
		pos_00=false;
	}
	else if(pos_01==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(COL2X_X, ROW1X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			xflag=false;
			oflag=true;
			count++;
			board[0][1]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL2O_X , ROW1O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=true;
			oflag=false;
			board[0][1]='O';
		}
		track_pos=false;
		pos_01=false;
	}
	else if(pos_02==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(COL3X_X, ROW1X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=false;
			oflag=true;
			board[0][2]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL3O_X , ROW1O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=true;
			oflag=false;
			board[0][2]='O';
		}
		track_pos=false;
		pos_02=false;
	}
	else if(pos_10==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(COL1X_X, ROW2X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=false;
			oflag=true;
			board[1][0]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL1O_X, ROW2O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=true;
			oflag=false;
			board[1][0]='O';
		}
		track_pos=false;
		pos_10=false;
	}
	else if(pos_11==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(ROW22X_Y, ROW2X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=false;
			oflag=true;
			board[1][1]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL2O_X , ROW2O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=true;
			oflag=false;
			board[1][1]='O';
		}
		track_pos=false;
		pos_11=false;
	}
	else if(pos_12==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(COL3X_X, ROW2X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=false;
			oflag=true;
			board[1][2]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL3O_X, ROW2O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=true;
			oflag=false;
			board[1][2]='O';
		}
		track_pos=false;
		pos_12=false;
	}
	else if(pos_20==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(COL1X_X, ROW3X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=false;
			oflag=true;
			board[2][0]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL1O_X, ROW3O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=true;
			oflag=false;
			board[2][0]='O';
		}
		track_pos=false;
		pos_20=false;
	}
	else if(pos_21==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(COL2X_X, ROW3X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=false;
			oflag=true;
			board[2][1]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL2O_X, ROW3O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=true;
			oflag=false;
			board[2][1]='O';
		}
		track_pos=false;
		pos_21=false;
	}
	else if(pos_22==true)
	{
		if(RX_BUFFER[0]=='X' && xflag==true)
		{
			ILI9341_DrawX(COL3X_X, ROW3X_Y, X_LEN, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player O turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=false;
			oflag=true;
			board[2][2]='X';
		}
		else if (RX_BUFFER[0]=='O' && oflag==true)
		{
			ILI9341_DrawHollowCircle(COL3O_X, ROW3O_Y, CIRC_RAD, BLACK);
			HAL_Delay(DELAY_100MS);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Player X turn", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			count++;
			xflag=true;
			oflag=false;
			board[2][2]='O';
		}
		track_pos=false;
		pos_22=false;
	}
}

/***************************************Check Winner*****************************************
 * Parameter passed: None
 * Parameter returned: Character value which is same in either rows, columns or diagonals
 *********************************************************************************************/
char check_winner(void)
{
	//check if any of the rows have the same data
	for(int i=0;i<3;i++)
	{
		if(board[i][0]==board[i][1] && board[i][0]==board[i][2] && board[i][0]!='D')
		{
			if(i==0)
				ILI9341_DrawHLine(COL1X_X, ROW1O_Y, HLINE_LEN, BLACK);
			else if (i==1)
				ILI9341_DrawHLine(COL1X_X, ROW2O_Y, HLINE_LEN, BLACK);
			else if (i==2)
				ILI9341_DrawHLine(COL1X_X, ROW3O_Y, HLINE_LEN, BLACK);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Game over", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			HAL_Delay(DELAY_1000MS);
			return board[i][0];
		}
	}

	//check if any of the columns have the same data
	for(int i=0;i<3;i++)
	{
		if(board[0][i]==board[1][i] && board[0][i]==board[2][i] && board[0][i]!='D')
		{
			if(i==0)
				ILI9341_DrawVLine(COL1O_X, ROW1X_Y, VLINE_LEN, BLACK);
			else if (i==1)
				ILI9341_DrawVLine(COL2O_X, ROW1X_Y, VLINE_LEN, BLACK);
			else if (i==2)
				ILI9341_DrawVLine(COL3O_X, ROW1X_Y, VLINE_LEN, BLACK);
			ILI9341_Usermsg(WHITE);
			ILI9341_DrawText("Game over", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
			HAL_Delay(DELAY_1000MS);
			return board[0][i];
		}
	}

	//check if any of the diagonals have the same data
	if(board[0][0]==board[1][1] && board[0][0]==board[2][2] && board[0][0]!='D')
	{
		ILI9341_diag(COL1X_X, ROW1X_Y, VLINE_LEN, 1, BLACK);
		ILI9341_Usermsg(WHITE);
		ILI9341_DrawText("Game over", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
		HAL_Delay(DELAY_1000MS);
		return board[0][0];
	}
	if(board[0][2]==board[1][1] && board[0][2]==board[2][0] && board[0][2]!='D')
	{
		ILI9341_diag(COL1X_X, DIAG_Y, VLINE_LEN, 2, BLACK);
		ILI9341_Usermsg(WHITE);
		ILI9341_DrawText("Game over", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
		HAL_Delay(DELAY_1000MS);
		return board[0][2];
	}

	//check for draw
	if(count==9)
	{
		ILI9341_Usermsg(WHITE);
		ILI9341_DrawText("Game over", FONT4, BOTTOM_TEXT4_X, BOTTOM_TEXT4_Y, BLACK, WHITE);
		HAL_Delay(DELAY_1000MS);
		return 'T';
	}

	//Else return default value i.e. no action
	return 'D';
}


/******************************Display Winner on TFT*****************************************
 * Parameter passed: winner: The character returned by check_winner function
 * Parameter returned: true if winner is valid else false
 *********************************************************************************************/
bool display_winner(char winner)
{
	if(winner=='X')
	{
		ILI9341_FillScreen(WHITE);
		ILI9341_DrawText("Player X wins", FONT4, TEXT3_X, TEXT3_Y, BLACK, WHITE);
		HAL_Delay(DELAY_5000MS);
		return true;
	}
	if(winner=='O')
	{
		ILI9341_FillScreen(WHITE);
		ILI9341_DrawText("Player O wins", FONT4, TEXT3_X, TEXT3_Y, BLACK, WHITE);
		HAL_Delay(DELAY_5000MS);
		return true;
	}
	if(winner=='T')
	{
		ILI9341_FillScreen(WHITE);
		ILI9341_DrawText("Game Tied", FONT4, TEXT4_X, TEXT3_Y, BLACK, WHITE);
		HAL_Delay(DELAY_5000MS);
		return true;
	}
	if (winner=='D')
	{
		return false;
	}
	return false;
}

/******************************Restart the game*********************************************
 * Parameter passed: None
 * Parameter returned: None
 *********************************************************************************************/
void restart_game(void)
{
	//Reset all the variables
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			board[i][j]='D';
		}
	}
	track_pos = false;
	pos_00=false;
	pos_01 = false;
	pos_02 = false;
	pos_10 = false;
	pos_11 = false;
	pos_12 = false;
	pos_20 = false;
	pos_21 = false;
	pos_22 = false;
	count=0;
	xflag=true;
	oflag=true;
	ILI9341_FillScreen(WHITE);
	ILI9341_DrawText("Restarting the game", FONT4, 40, 160, BLACK, WHITE);
	HAL_Delay(DELAY_2000MS);
	ILI9341_FillScreen(WHITE);
	ILI9341_DrawText("Tic-Tac-Toe", FONT4, BOTTOM_TEXT1_X, BOTTOM_TEXT1_Y, BLACK, WHITE);
	//2 Horizontal lines
	ILI9341_DrawHLine(HLINE_X, HLINE1_Y, HLINE_LEN, BLACK);
	HAL_Delay(DELAY_100MS);
	ILI9341_DrawHLine(HLINE_X, HLINE2_Y, HLINE_LEN, BLACK);
	HAL_Delay(DELAY_100MS);
	//2 vertical lines
	ILI9341_DrawVLine(VLINE1_X, VLINE_Y, VLINE_LEN, BLACK);
	HAL_Delay(DELAY_100MS);
	ILI9341_DrawVLine(VLINE2_X, VLINE_Y, VLINE_LEN, BLACK);
	HAL_Delay(DELAY_100MS);
	ILI9341_DrawText("Any player can start", FONT4, BOTTOM_TEXT2_X, BOTTOM_TEXT2_Y, BLACK, WHITE);
}

/****************************************Main subroutine****************************************/
int main(void)
{
	bool player_winner;

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_SPI1_Init();
	MX_USART2_UART_Init();

	HAL_UART_Receive_IT(&huart2, RX_BUFFER, BUFFER_LEN); //Store data received in buffer

	//Initialize the TFT
	ILI9341_Init();

	//TFT screen initialization before starting the game
	ILI9341_FillScreen(WHITE);
	ILI9341_SetRotation(SCREEN_VERTICAL);
	ILI9341_DrawText("Starting Tic-tac-toe game", FONT4, TEXT1_X, TEXT1_Y, BLACK, WHITE);
	ILI9341_DrawText("Player X vs O", FONT4, TEXT2_X , TEXT2_Y, BLACK, WHITE);
	HAL_Delay(DELAY_2000MS);
	ILI9341_FillScreen(WHITE);
	ILI9341_DrawText("Tic-Tac-Toe", FONT4, BOTTOM_TEXT1_X, BOTTOM_TEXT1_Y, BLACK, WHITE);
	//2 Horizontal lines
	ILI9341_DrawHLine(HLINE_X, HLINE1_Y, HLINE_LEN, BLACK);
	HAL_Delay(DELAY_100MS);
	ILI9341_DrawHLine(HLINE_X, HLINE2_Y, HLINE_LEN, BLACK);
	HAL_Delay(DELAY_100MS);
	//2 vertical lines
	ILI9341_DrawVLine(VLINE1_X, VLINE_Y, VLINE_LEN, BLACK);
	HAL_Delay(DELAY_100MS);
	ILI9341_DrawVLine(VLINE2_X, VLINE_Y, VLINE_LEN, BLACK);
	HAL_Delay(DELAY_100MS);
	ILI9341_DrawText("Any player can start", FONT4, BOTTOM_TEXT2_X, BOTTOM_TEXT2_Y, BLACK, WHITE);

	/* Infinite loop */
	while (1)
	{
		//Check the buffer value for the command given by user
		if(RX_BUFFER[0]=='A' && track_pos==false && board[0][0]=='D')
		{
			pos_00=true;
			track_pos=true;
			ILI9341_DrawText("Position 1 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if(RX_BUFFER[0]=='B' && track_pos==false && board[0][1]=='D')
		{
			pos_01=true;
			track_pos=true;
			ILI9341_DrawText("Position 2 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if(RX_BUFFER[0]=='C' && track_pos==false && board[0][2]=='D')
		{
			pos_02=true;
			track_pos=true;
			ILI9341_DrawText("Position 3 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if(RX_BUFFER[0]=='D' && track_pos==false && board[1][0]=='D')
		{
			pos_10=true;
			track_pos=true;
			ILI9341_DrawText("Position 4 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if(RX_BUFFER[0]=='E' && track_pos==false && board[1][1]=='D')
		{
			pos_11=true;
			track_pos=true;
			ILI9341_DrawText("Position 5 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if(RX_BUFFER[0]=='F' && track_pos==false && board[1][2]=='D')
		{
			pos_12=true;
			track_pos=true;
			ILI9341_DrawText("Position 6 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if(RX_BUFFER[0]=='G' && track_pos==false && board[2][0]=='D')
		{
			pos_20=true;
			track_pos=true;
			ILI9341_DrawText("Position 7 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if(RX_BUFFER[0]=='H' && track_pos==false && board[2][1]=='D')
		{
			pos_21=true;
			track_pos=true;
			ILI9341_DrawText("Position 8 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if(RX_BUFFER[0]=='I' && track_pos==false && board[2][2]=='D')
		{
			pos_22=true;
			track_pos=true;
			ILI9341_DrawText("Position 9 selected", FONT4, BOTTOM_TEXT3_X, BOTTOM_TEXT3_Y, BLACK, WHITE);
		}
		else if (RX_BUFFER[0]=='X' || RX_BUFFER[0]=='O')
		{
			fill_matrix();
		}

		player_winner=display_winner(check_winner());
		if(player_winner==true)
			restart_game();
	}
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
