/*
 * Copyright © 2011 Stéphane Raimbault <stephane.raimbault@gmail.com>
 *
 * License ISC, see LICENSE for more details.

 * This library implements the Modbus protocol.
 * http://libmodbus.org/
 *
 */

#ifndef Modbusino_h
#define Modbusino_h

#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#define MODBUS_BROADCAST_ADDRESS 0

/* Protocol exceptions */
#define MODBUS_EXCEPTION_ILLEGAL_FUNCTION     1
#define MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS 2
#define MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE   3
#define MODBUS_INFORMATIVE_NOT_FOR_US   4
#define MODBUS_INFORMATIVE_RX_TIMEOUT   5

class ModbusinoInterface {
public:
    virtual uint16_t getRegister(uint16_t address) = 0;
    virtual void setRegister(uint16_t address, uint16_t value) = 0;
};

class ModbusinoSlave {
public:
    ModbusinoSlave(uint8_t slave);
    void setup(long baud);

    int loop(uint16_t *tab_reg, uint16_t nb_reg);

    // Allow client to map registers in some switch statements. Useful when
    // querying SPI or I2C devices
    int loop(ModbusinoInterface *intf, uint16_t nb_reg);

private:
    int _slave;
};

#endif
