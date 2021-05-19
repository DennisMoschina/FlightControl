#ifndef _BLE_RESOURCES_H
#define _BLE_RESOURCES_H

#include <NimBLEDevice.h>

const char* name = "Flight Controller";

const char* gainServiceUUID = "0000";

const char* gainPCharacteristicUUID = "1111";
const char* gainICharacteristicUUID = "2222";
const char* gainDCharacteristicUUID = "3333";

const char* relaxICharacteristicUUID = "4444";

uint32_t gainProperties = NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY;

#endif
