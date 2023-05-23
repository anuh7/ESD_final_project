/*
 * Filename: UART.h
 * Created on: Nov 25, 2022
 * Author: Shashank and Anuhya
 * Description: This H file contains the UART interfacing functions
 * Reference: None
 */

#ifndef INC_UART_H_
#define INC_UART_H_

//Buffer length and buffer to store character received by bluetooth
#define BUFFER_LEN  1
extern uint8_t RX_BUFFER[BUFFER_LEN];

extern UART_HandleTypeDef huart2;

/*
 * UART2 Initialization for bluetooth
 * Parameter Passed: None
 * Parameter returned: None
 */
void MX_USART2_UART_Init(void);


/*
 * UART receive callback function
 * Parameter Passed: huart: The UART instance causing the interrupt
 * Parameter returned: None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* INC_UART_H_ */
