#include <Menu.h>

Menu::Menu(Controller* controller) {
    this->controller = controller;
}

Menu::Menu(Controller* controller, AxisData<ServoOutput*> servoOutputs, ServoInputReader* inputReader) {
    this->controller = controller;
    this->servos = servoOutputs;
    this->inputs = inputReader;
}

void Menu::endTrimming() {
    vTaskDelete(this->trimHandle);
}

void trim(void * parameter) {
    Menu* menu = (Menu*) parameter;
    for(;;) {
        AxisData<int> input = menu->inputs->readInput();
        menu->servos.x->setMiddle(input.x);
        menu->servos.y->setMiddle(input.y);
        menu->servos.z->setMiddle(input.z);
        delay(100);
    }
}

void Menu::trimServos(AxisData<ServoOutput*> servoOutputs,
                        ServoInputReader* inputReader) {
    xTaskCreatePinnedToCore(trim, "trimTask", 10000, this, 0, &this->trimHandle, 0);
}