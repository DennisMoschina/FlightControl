#include <SerialMonitorInterface.h>

const char SerialMonitorInterface::TERMINATOR = '\n';

String SerialMonitorInterface::TRIM_COMMAND = "trim";
String SerialMonitorInterface::TRIM_END_COMMAND = "end trim";

String SerialMonitorInterface::CONTROLLER_COMMAND = "controller";
String SerialMonitorInterface::CONTROLLER_END_COMMAND = "end controller";


SerialMonitorInterface::SerialMonitorInterface(Menu* menu) {
    this->menu = menu;
}

void SerialMonitorInterface::handle() {
    log_v("handling UI");
    if (Serial.available()) {
        String command = Serial.readStringUntil(TERMINATOR);

        if (command == TRIM_COMMAND) {
            Serial.println("started trimming");
            this->menu->trimServos();
        } else if (command == TRIM_END_COMMAND) {
            this->menu->endTrimming();
            Serial.println("ended trimming");
        } else if (command == CONTROLLER_COMMAND) {
            Serial.println("started controller");
            this->menu->startController();
        } else if (command == CONTROLLER_END_COMMAND) {
            this->menu->stopController();
            Serial.println("ended controller");
        }
        else {
            Serial.println("unknown command");
        }
    }
}