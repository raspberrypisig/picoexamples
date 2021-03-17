
#ifndef __EERAM_47L16_H__
#define __EERAM_47L16_H__


#include "hardware/i2c.h"


#include "stdlib.h"
#include "string.h"


typedef struct {
	uint8_t sram_register;
	uint8_t control_register;
	i2c_inst_t *i2c_obj;
	uint32_t i2c_speed;
	uint sda;
	uint scl;
} EERAMConfig;


class EERAM {

  private:
     EERAMConfig config;
  public:
     EERAM();
	 void begin(uint8_t A2 = 0, uint8_t A1 = 0, i2c_inst_t *obj = NULL);
	 void write(uint16_t address, uint8_t* values, uint16_t size);
	 void writeByte(uint16_t address, uint8_t value);
	 void read(uint16_t address, uint8_t *values, uint16_t size);
	 uint8_t readByte(uint16_t address);
	 uint8_t readControlRegister();
	 bool getAutoStore();
	 void setAutoStore(bool value);
};



#endif