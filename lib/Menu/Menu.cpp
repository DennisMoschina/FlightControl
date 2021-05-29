#include <Menu.h>

Menu::Menu(Controller* controller) {
    this->controller = controller;
}

Menu::Menu(Controller* controller, AxisData<ServoOutput*> servoOutputs, ServoInputReader* inputReader) {
    this->controller = controller;
    this->servos = servoOutputs;
    this->inputs = inputReader;
}

void Menu::startController() {
    this->controller->begin();
}

void Menu::stopController() {
    this->controller->stop();
}

void Menu::endTrimming() {
    vTaskDelete(this->trimHandle);
    this->controller->begin();
}

void trim(void * parameter) {
    Menu* menu = (Menu*) parameter;
    for(;;) {
        AxisData<int> input = menu->inputs->readInput();
        log_d("input:\t\tx:%5d, y:%5d, z:%5d", input.x, input.y, input.z);
        menu->servos.x->setMiddle(input.x);
        menu->servos.y->setMiddle(input.y);
        menu->servos.z->setMiddle(input.z);

        menu->servos.x->write(0);
        menu->servos.y->write(0);
        menu->servos.z->write(0);
        delay(100);
    }
}

void Menu::trimServos(AxisData<ServoOutput*> servoOutputs,
                        ServoInputReader* inputReader) {
    this->servos = servoOutputs;
    this->inputs = inputReader;
    this->trimServos();
}

void Menu::trimServos() {
    this->controller->stop();
    xTaskCreatePinnedToCore(trim, "trimTask", 10000, this, 2, &this->trimHandle, 0);
}