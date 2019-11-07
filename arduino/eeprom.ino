/**
 * This module provides all functions for accessing the EEPROM (read, write) of the arduino
 */
#include "main.h"

#include <EEPROM.h>

/*
 * write
 */
// write a 4 byte long to the eeprom at the specified address (until addr+3)
void eepromWriteLong(int p_address, long p_value) {
  if (p_address <= EEPROM.length() - 4) {
    byte b0 = ((p_value >> 0)  & 0xFF); // lowest byte
    byte b1 = ((p_value >> 8)  & 0xFF);
    byte b2 = ((p_value >> 16) & 0xFF);
    byte b3 = ((p_value >> 24) & 0xFF); // highest byte
    EEPROM.write(p_address + 0, b0);
    EEPROM.write(p_address + 1, b1);
    EEPROM.write(p_address + 2, b2);
    EEPROM.write(p_address + 3, b3);
  }
}

// write a 4 byte float to the eeprom at the specified address (until addr+3)
void eepromWriteFloat(int p_address, float p_value) {
  if (p_address <= EEPROM.length() - 4) {
    byte bytes[4];
    *(float*)(bytes) = p_value;
    EEPROM.write(p_address + 0, bytes[0]);
    EEPROM.write(p_address + 1, bytes[1]);
    EEPROM.write(p_address + 2, bytes[2]);
    EEPROM.write(p_address + 3, bytes[3]);
  }
}

/*
 * read
 */
// read a 4 byte long from the eeprom at the specified address (until addr+3)
unsigned long eepromReadLong(int p_address) {
  if (p_address <= EEPROM.length() - 4) {
    byte b0 = EEPROM.read(p_address + 0);
    byte b1 = EEPROM.read(p_address + 1);
    byte b2 = EEPROM.read(p_address + 2);
    byte b3 = EEPROM.read(p_address + 3);  
    return (
      ((b0 << 0) & 0xFF) + 
      (((int)b1 << 8) & 0xFF00) + 
      (((long)b2 << 16) & 0xFF0000) + 
      (((long)b3 << 24) & 0xFF000000)
    );
  }
  else return 0;
}

// read a 4 byte float from the eeprom at the specified address (until addr+3)
unsigned long eepromReadFloat(int p_address) {
  if (p_address <= EEPROM.length() - 4) {
    byte bytes[4];
    bytes[0] = EEPROM.read(p_address + 0);
    bytes[1] = EEPROM.read(p_address + 1);
    bytes[2] = EEPROM.read(p_address + 2);
    bytes[3] = EEPROM.read(p_address + 3);  
    return *(float*)(bytes);
  }
  else return 0;
}
