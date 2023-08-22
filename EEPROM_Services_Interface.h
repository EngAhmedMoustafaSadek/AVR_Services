

#ifndef EEPROM_SERVICES_INTERFACE_H_
#define EEPROM_SERVICES_INTERFACE_H_





void EEPROM_Services_Init(void);

void EEPROM_Services_Runnable(void);

EEPROMQueueStatus_t EEPROM_Services_WriteArray(u16 local_address,u8 *data,u8 s);

EEPROMQueueStatus_t EEPROM_Services_WriteString(u16 local_address,c8 *data);

static void EEPROM_Interrupt_Func(void);

#endif /* EEPROM_SERVICES_INTERFACE_H_ */