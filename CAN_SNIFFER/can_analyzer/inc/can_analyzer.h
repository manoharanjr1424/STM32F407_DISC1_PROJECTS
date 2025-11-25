/*
 * can_analyzer.h
 *
 *  Created on: Nov 22, 2025
 *      Author: mjayakumar
 */

#ifndef INC_CAN_ANALYZER_H_
#define INC_CAN_ANALYZER_H_

#include "main.h"

#define CAN_NODE_BROADCAST_ENABLE  1
#define CAN_NODE_BROADCAST_DISABLE 0

typedef enum
{
    STATUS_OK = 0,             // Operation successful
    STATUS_NULL_POINTER,       // Input pointer is NULL
    STATUS_INVALID_ADDRESS,    // Invalid memory address or out of allowed range
    STATUS_INVALID_PARAM,      // Function argument invalid
    STATUS_BUFFER_OVERFLOW,    // Buffer too small / write overflow
    STATUS_TIMEOUT,            // Operation timed out
    STATUS_BUSY,               // Peripheral or resource is busy
    STATUS_NOT_INITIALIZED,    // Module or driver not initialized
    STATUS_HW_ERROR,           // Hardware error occurred
    STATUS_COMM_ERROR,         // Communication error (CAN/I2C/UART/etc)
    STATUS_UNSUPPORTED,        // Operation not supported
    STATUS_FAILED,              // Generic failure
	STATUS_NODATA
} Status_t;


typedef enum {
	IDEAL = 0,
	TRANSMIT,
	RECEIVE
}state_t;

typedef struct {
	state_t current_state;
}state_handler_t;

typedef struct {
	CAN_HandleTypeDef *pcan;
	CAN_TxHeaderTypeDef *pcanTxheader;
	CAN_RxHeaderTypeDef *pcanRxheader;
	CAN_FilterTypeDef   *pcanconfig;
	uint32_t *pTxMailbox;
}can_handler_t;

typedef struct {
	state_handler_t state_handler;
	can_handler_t can;
	void 		*data;
	uint32_t 	len;
	uint16_t	identifier;
	uint8_t 	broadcast;
}can_analyzer_handle_t;



Status_t can_analyzer_init(can_analyzer_handle_t *);
Status_t can_analyzer_statemachine(can_analyzer_handle_t *);
Status_t can_analyzer_read(can_analyzer_handle_t *);
Status_t can_analyzer_write(can_analyzer_handle_t *);
Status_t can_analyzer_set_config(can_analyzer_handle_t *);

Status_t can_analyzer_read_state(can_analyzer_handle_t *);
Status_t can_analyzer_idle_state(can_analyzer_handle_t *);
Status_t can_analyzer_write_state(can_analyzer_handle_t *);
void printlog(char *);

#endif /* INC_CAN_ANALYZER_H_ */
