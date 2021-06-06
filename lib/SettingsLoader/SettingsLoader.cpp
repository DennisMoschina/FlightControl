#include <SettingsLoader.h>

const char* SettingsLoader::FOLDER_NAME = "settings";
const char* SettingsLoader::SERVO_MIDDLE = "servo-middle";
const char* SettingsLoader::P_GAIN = "p-gain";
const char* SettingsLoader::I_GAIN = "i-gain";
const char* SettingsLoader::D_GAIN = "d-gain";
const char* SettingsLoader::MIN_THROTTLE_P_GAIN = "min-p-gain";
const char* SettingsLoader::MIN_THROTTLE_I_GAIN = "min-i-gain";
const char* SettingsLoader::MIN_THROTTLE_D_GAIN = "min-d-gain";


SettingsLoader::SettingsLoader(PID* pid, AxisData<ServoOutput*> outputs) {
    this->pid = pid;
    this->outputs = outputs;
}

void SettingsLoader::load() {
#if defined(ESP8266) || defined(ESP32)
    AxisData<int> servoMiddles = this->loadInts(SERVO_MIDDLE);
    for (int i = 0; i < 3; i++) this->outputs[i]->setMiddle(servoMiddles[i]);

    if (this->preferences.isKey(P_GAIN)) this->pid->setPGain(this->loadFloats(P_GAIN));
    if (this->preferences.isKey(I_GAIN)) this->pid->setIGain(this->loadFloats(I_GAIN));
    if (this->preferences.isKey(D_GAIN)) this->pid->setDGain(this->loadFloats(D_GAIN));

    if (this->preferences.isKey(MIN_THROTTLE_P_GAIN))
        this->pid->setMinThrottlePGain(this->loadFloats(MIN_THROTTLE_P_GAIN));
    if (this->preferences.isKey(MIN_THROTTLE_I_GAIN))
        this->pid->setMinThrottleIGain(this->loadFloats(MIN_THROTTLE_I_GAIN));
    if (this->preferences.isKey(MIN_THROTTLE_D_GAIN))
        this->pid->setMinThrottleDGain(this->loadFloats(MIN_THROTTLE_D_GAIN));

#else

#endif
}



void SettingsLoader::storeServoMiddles(AxisData<int> servoMiddles) {
#if defined(ESP8266) || defined(ESP32)
    for (int i = 0; i < 3; i++) {
        const char* address = SERVO_MIDDLE + (char) i;
        this->storeData(address, servoMiddles[i]);
    }
#else
    for (int i = 0; i < 3; i++) {
        const int address = SERVO_MIDDLE_POS + i * INT_SIZE;
        EEPROM.writeInt(address, servoMiddles[i]);
    }
    EEPROM.commit();
#endif
}


void SettingsLoader::storePGain(CorrectionData gain) {
#if defined(ESP8266) || defined(ESP32)
    for (int i = 0; i < 3; i++) {
        const char* address = P_GAIN + (char) i;
        this->storeData(address, gain[i]);
    }
#else
    this->storeGain(P_GAIN_POS, gain);
#endif
}

void SettingsLoader::storeIGain(CorrectionData gain) {
#if defined(ESP8266) || defined(ESP32)
    for (int i = 0; i < 3; i++) {
        const char* address = I_GAIN + (char) i;
        this->storeData(address, gain[i]);
    }
#else
    this->storeGain(I_GAIN_POS, gain);
#endif
}

void SettingsLoader::storeDGain(CorrectionData gain) {
#if defined(ESP8266) || defined(ESP32)
    for (int i = 0; i < 3; i++) {
        const char* address = D_GAIN + (char) i;
        this->storeData(address, gain[i]);
    }
#else
    this->storeGain(D_GAIN_POS, gain);
#endif
}

void SettingsLoader::storeMinThrottlePGain(CorrectionData gain) {
#if defined(ESP8266) || defined(ESP32)
    for (int i = 0; i < 3; i++) {
        const char* address = MIN_THROTTLE_P_GAIN + (char) i;
        this->storeData(address, gain[i]);
    }
#else
    this->storeGain(MIN_THROTTLE_P_GAIN_POS, gain);
#endif
}

void SettingsLoader::storeMinThrottleIGain(CorrectionData gain) {
#if defined(ESP8266) || defined(ESP32)
    for (int i = 0; i < 3; i++) {
        const char* address = MIN_THROTTLE_I_GAIN + (char) i;
        this->storeData(address, gain[i]);
    }
#else
    this->storeGain(MIN_THROTTLE_I_GAIN_POS, gain);
#endif
}

void SettingsLoader::storeMinThrottleDGain(CorrectionData gain) {
#if defined(ESP8266) || defined(ESP32)
    for (int i = 0; i < 3; i++) {
        const char* address = MIN_THROTTLE_D_GAIN + (char) i;
        this->storeData(address, gain[i]);
    }
#else
    this->storeGain(MIN_THROTTLE_D_GAIN_POS, gain);
#endif
}

void SettingsLoader::reset() {
#if defined(ESP8266) || defined(ESP32)
    this->preferences.clear();
#else
#endif
}


#if defined(ESP8266) || defined(ESP32)
void SettingsLoader::storeData(const char* address, int value) {
    this->preferences.begin(FOLDER_NAME, false);
    this->preferences.putInt(address, value);
    this->preferences.end();
}

void SettingsLoader::storeData(const char* address, float value) {
    this->preferences.begin(FOLDER_NAME, false);
    this->preferences.putFloat(address, value);
    this->preferences.end();
}


AxisData<int> SettingsLoader::loadInts(const char* key) {
    this->preferences.begin(FOLDER_NAME, true);

    AxisData<int> output;
    for (int i = 0; i < 3; i++) {
        const char* address = key + (char) i;
        this->preferences.getInt(address);
    }

    this->preferences.end();
    return output;
}

AxisData<float> SettingsLoader::loadFloats(const char* key) {
    this->preferences.begin(FOLDER_NAME, true);

    AxisData<float> output;
    for (int i = 0; i < 3; i++) {
        const char* address = key + (char) i;
        this->preferences.getFloat(address);
    }

    this->preferences.end();
    return output;
}


#else

void SettingsLoader::storeGain(int address, CorrectionData gain) {
    for (int i = 0; i < 3; i++) {
        const int address = address + i * FLOAT_SIZE;
    }
    EEPROM.commit();
}

AxisData<int> SettingsLoader::loadInts(int address) {

}
AxisData<float> SettingsLoader::loadFloats(int address) {

}
#endif