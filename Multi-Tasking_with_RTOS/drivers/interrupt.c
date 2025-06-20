

#include <mcu.h>
#include <interrupt.h>

uint8_t NvicEnableInt(uint8_t IntNumber) {

	if( (IntNumber >=0) && (IntNumber < 32) ) {
		(*NVIC_ISER0) |= (1 << IntNumber);
	}
	else if( (IntNumber >= 32) && (IntNumber < 64) ) {
		(*NVIC_ISER1) |= (1 << (IntNumber%32));
	}else if( (IntNumber >= 64) && (IntNumber < 81) ) {
		(*NVIC_ISER2) |= (1 << (IntNumber%64));
	}

	return SUCCESS;
}

uint8_t NvicDisableInt(uint8_t IntNumber) {

	(*NVIC_ISER0) &= ~(1 << IntNumber);

	if( (IntNumber >=0) && (IntNumber < 32) ) {
		(*NVIC_ISER0) &= ~(1 << IntNumber);
	}
	else if( (IntNumber >= 32) && (IntNumber < 64) ) {
		(*NVIC_ISER1) &= ~(1 << (IntNumber%32));
	}else if( (IntNumber >= 64) && (IntNumber < 88) ) {
		(*NVIC_ISER2) &= ~(1 << (IntNumber%64));
	}
	return SUCCESS;
}


int8_t NvicGetPriority(uint8_t IntNumber) {
	return ( NVIC_IPR(IntNumber) & (0xF << (IntNumber % 4)));
}


int8_t  NvicSetPriority(uint8_t IntNumber, uint8_t preEmption, uint8_t subPriority) {

	uint8_t priority = ( ( preEmption << 4 ) | (subPriority) );
	priority &= 0xF0;
	NVIC_IPR(IntNumber) &= ~(0xF0 << (IntNumber % 4));
	NVIC_IPR(IntNumber) |= (priority << (IntNumber % 4));
	if( NVIC_IPR(IntNumber) & (priority << (IntNumber % 4))) {
		printf("Priority was Set properly\n");
		return 0;
	}
	return -1;
}

int8_t NvicSetPriorityGrouping(nvicPriorityGrouping priorityGrouping) {

	uint32_t currentData;
	uint8_t currentPriorityValue = (0x7 & priorityGrouping);

	currentData = AIRCR;
	currentData &= ~(0x7 << 8);
	currentData = ( (currentData & 0x0000FFFF) | (0x5FA << 16) | (currentPriorityValue << 8));
	AIRCR = currentData;
//	switch(priorityGrouping) {
//	case NVIC_PriorityGroup_0:
//		break;
//	case NVIC_PriorityGroup_1:
//		break;
//	case NVIC_PriorityGroup_2:
//		break;
//	case NVIC_PriorityGroup_3:
//		break;
//	case NVIC_PriorityGroup_4:
//		break;
//	}

	return -1;
}
