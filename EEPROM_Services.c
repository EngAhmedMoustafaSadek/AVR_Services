
#include "StdTypes.h"
#include "EEPROM_Interface.h"
#include "Queue_EEPROM.h"
#include "EEPROM_Services_Interface.h"
#include "LCD_Interface.h"
#include "DIO_Interface.h"

static Queue_EEPROM_t EEPROM_Queue;
static EEPROM_Request_t REQUEST;
static volatile u8 writedata_flag=0;
static volatile u8 writedata_count=0;
static volatile u8 dequeue_flag=0;
static volatile u8 stop_flag=0;

void EEPROM_Services_Init(void)
{
	EQ_Queue_Init(&EEPROM_Queue,EPPROM_REQUEST_MAXNUM);
	REQUEST.address=0;
	REQUEST.data=0;
	REQUEST.data_size=1;
	EEPROM_InterruptSetCallBack(EEPROM_Interrupt_Func);
	EEPROM_InterruptEnable();
}

void EEPROM_Services_Runnable(void)
{
	EEPROMQueueStatus_t status;
	if (writedata_flag==1)
	{
		LCD_WriteNumber(writedata_count);
		EEPROM_Write(((REQUEST.address)+writedata_count),REQUEST.data[writedata_count]);
		writedata_flag=0;
	}
	if (dequeue_flag==1)
	{
		status=EQ_dequeue(&EEPROM_Queue,&REQUEST);
		dequeue_flag=0;
		if (status==Queue_Empty)
		{
			REQUEST.data_size=1;
			stop_flag=1;
		}
	}
	
}

EEPROMQueueStatus_t EEPROM_Services_WriteArray(u16 local_address,u8 *data,u8 s)
{
	EEPROM_InterruptEnable();
	stop_flag=0;
	EEPROMQueueStatus_t status;
	EEPROM_Request_t request;
	request.address=local_address;
	request.data_size=s;
	request.data=data;
	status=EQ_enqueue(&EEPROM_Queue,request);
	return status;
}

EEPROMQueueStatus_t EEPROM_Services_WriteString(u16 local_address,c8 *data)
{
}

static void EEPROM_Interrupt_Func(void)
{
	if (writedata_flag==0)
	{
		writedata_flag=1;
		
		if (writedata_count==REQUEST.data_size-1)
		{
			if (stop_flag==1)
			{
				EEPROM_InterruptDisable();
			}
			dequeue_flag=1;
			writedata_count=0;
		}
		else
		{
			writedata_count++;
		}
	}
}