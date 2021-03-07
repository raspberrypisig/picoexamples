#include "47L16.h"

#define EERAM_SRAM_ADDRESS      0x50
#define EERAM_CONTROL_ADDRESS   0x18
#define EERAM_I2C_SPEED 100000
#define EERAM_SDA 21
#define EERAM_SCL 22

int8_t EERAM_SRAM_REGISTER;
int8_t EERAM_CONTROL_REGISTER;

typedef struct {
    int8_t eeram_sram_register;
    int8_t eeram_control_register;
} EERAMRegisters;

EERAMRegisters eeram_get_default_config(uint8_t A2, uint8_t A1) {
	uint8_t mask = (A2 << 1) | (A1);
	mask <<= 1;
    EERAMRegisters registers;
	registers.eeram_sram_register = 0x50 | mask;
	registers.eeram_control_register = 0x18 | mask;	
    return registers;
}

void eeram_begin(EERAMRegisters r) {
}

bool eeram_writeConfig(uint8_t val) {
  //uint8_t returnval;
  uint8_t adata[2];
  adata[0] = 0; //STATUS register
  adata[1] = val;
  i2c_write_blocking(i2c0, CONTROL_REGISTER, &adata, 2, false);
  //delay needed here
  /*
  i2c_read_blocking(i2c0, CONTROL_REGISTER, &returnval, 1, true);
  if (val == returnval) {
  	return true;
  }
  return false;
  */
}

void eeram_read(uint16_t address, uint8_t* values, uint16_t size) {

}

uint8_t eeram_read_byte(uint16_t address) {
	uint8_t adata[2];
    adata[0] = address >> 8;
    adata[1] = address & 0xFF;

	uint8_t val;

	i2c_write_blocking(i2c0, EERAM_SRAM_REGISTER, adata, 2, false);
	i2c_read_blocking(i2c0, EERAM_SRAM_REGISTER, &val, 1, false);

	return val;
}

void eeram_write(uint16_t address, uint8_t* values, uint16_t size) {
	uint8_t adata[3];
    adata[0] = address >> 8;
    adata[1] = address & 0xFF;
    adata[2] = *values;
	
	i2c_write_blocking(i2c0, EERAM_SRAM_REGISTER, adata, 3, false);
}

uint8_t eeram_write_byte(uint16_t address, uint8_t value) {
	uint8_t adata[3];
    adata[0] = address >> 8;
    adata[1] = address & 0xFF;
    adata[2] = value;
	
	i2c_write_blocking(i2c0, EERAM_SRAM_REGISTER, adata, 3, false);	
}

void eeram_setup_pico() {
    i2c_init(i2c0, EERAM_I2C_SPEED);
    gpio_set_function(EERAM_SDA, GPIO_FUNC_I2C);
    gpio_set_function(EERAM_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(EERAM_SDA);
    gpio_pull_up(EERAM_SCL);
}