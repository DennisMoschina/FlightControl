#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#define BLE_LOG "ble"

#include <NimBLEDevice.h>

#include <Bluetooth/BLEResources.h>

NimBLEServer* pServer;
NimBLEService* gainService;

NimBLECharacteristic* gainPCharacteristic;
NimBLECharacteristic* gainICharacteristic;
NimBLECharacteristic* gainDCharacteristic;
NimBLECharacteristic* relaxICharacteristic;
NimBLEAdvertising* pAdvertising;

boolean bleClientConnected = false;



void advertise() {
        pAdvertising = NimBLEDevice::getAdvertising();
        pAdvertising->addServiceUUID(gainServiceUUID);
        pAdvertising->start();
}

void setValue(NimBLECharacteristic* characteristic, const char* value, boolean notify) {
    characteristic->setValue(value);
    characteristic->notify(notify);
}


class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* server) {
        bleClientConnected = true;
        ESP_LOGI(BLE_LOG, "client connected");
    };
    void onDisconnect(BLEServer* server) {
        bleClientConnected = false;
        server -> startAdvertising();
        ESP_LOGI(BLE_LOG, "client disconnected");
    }
};

void startBluetooth() {
    NimBLEDevice::init(name);
    pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    gainService = pServer->createService(gainServiceUUID);

    gainPCharacteristic =
        gainService->createCharacteristic(gainPCharacteristicUUID,
                                            gainProperties);
    gainICharacteristic =
        gainService->createCharacteristic(gainICharacteristicUUID,
                                            gainProperties);
    gainDCharacteristic =
        gainService->createCharacteristic(gainDCharacteristicUUID,
                                            gainProperties);

    relaxICharacteristic =
        gainService->createCharacteristic(relaxICharacteristicUUID,
                                            gainProperties);

    gainService->start();

    advertise();
}


#endif
