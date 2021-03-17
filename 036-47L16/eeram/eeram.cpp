#include "eeram.hpp"

void EERAM::begin(uint8_t A2, uint8_t A1, i2c_inst_t *obj) {
	config.i2c_obj = obj;
	uint8_t mask = (A2 << 1) | (A1);
	mask <<= 1;
	config.sram_register = 0x50 | mask;
	config.control_register = 0x18 | mask;

	setAutoStore(true);
}

uint8_t EERAM::readControlRegister() {
	uint8_t buffer = 0x80;
	uint8_t adata = 0x00;  //status register
    i2c_write_blocking(config.i2c_obj, config.control_register, &adata, 1, false);
    i2c_read_blocking(config.i2c_obj, config.control_register, &buffer, 1, false);    
	return buffer;
}


bool EERAM::getAutoStore() {
	uint8_t buffer = readControlRegister();
	return buffer & 0x02;
}


void EERAM::setAutoStore(bool value)
{
	uint8_t buffer = readControlRegister();
	buffer = value ? buffer|0x02 : buffer&0xfd;
	uint8_t adata[2];
	adata[0] = 0; //status register
	adata[1] = buffer;
	i2c_write_blocking(config.i2c_obj, config.control_register, &adata[0], 2, false);
}

void EERAM::writeByte(uint16_t address, uint8_t value)
{
    uint8_t address_high = (address << 8) & 0x00ff;
    uint8_t address_low = address & 0x00ff;
    uint8_t adata[3];
    adata[0] = address_high;
    adata[1] = address_low;
    adata[2] = value;
 	i2c_write_blocking(config.i2c_obj, config.sram_register, &adata[0], 3, false);   
}

void EERAM::write(uint16_t address, uint8_t* values, uint16_t size)
{
    uint8_t address_high = (address << 8) & 0x00ff;
    uint8_t address_low = address & 0x00ff;
    uint8_t *adata = (uint8_t *) malloc((2+ size) * sizeof(uint16_t));
    adata[0] = address_high;
    adata[1] = address_low;
    memcpy(adata+2, values, size);
 	i2c_write_blocking(config.i2c_obj, config.sram_register, &adata[0], 2+size, false);   
 	free(adata);
}

uint8_t EERAM::readByte(uint16_t address)
{
    uint8_t address_high = (address << 8) & 0x00ff;
    uint8_t address_low = address & 0x00ff;
    uint8_t adata[2];
    adata[0] = address_high;
    adata[1] = address_low;
  	i2c_write_blocking(config.i2c_obj, config.sram_register, &adata[0], 2, false);   
  	uint8_t adata2;
	i2c_read_blocking(config.i2c_obj, config.sram_register, &adata2, 1, true); 
	return adata2;
}

void EERAM::read(uint16_t address, uint8_t * values, uint16_t size)
{
    uint8_t address_high = (address << 8) & 0x00ff;
    uint8_t address_low = address & 0x00ff;
    uint8_t adata[2];
    adata[0] = address_high;
    adata[1] = address_low;
  	i2c_write_blocking(config.i2c_obj, config.sram_register, &adata[0], 2, false);     
	i2c_read_blocking(config.i2c_obj, config.sram_register, values, size, true); 
}