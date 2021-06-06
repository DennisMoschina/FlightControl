#ifndef _SETTINGS_LOADER_H
#define _SETTINGS_LOADER_H

#include <PID.h>
#include <ServoOutput.h>
#include <AxisData.h>

#if defined(ESP8266) || defined(ESP32)
#include <Preferences.h>
#else
#include <EEPROM.h>
#endif

/**
 * Load the settings made to the servos and the pid stabilizer.
 * @author Dennis Moschina
 * @version 1.0
 */
class SettingsLoader {
    ///todo finish implementation for EEPROM
public:
    SettingsLoader(PID* pid, AxisData<ServoOutput*> outputs);

    /**
     * Load and assign the configurations.
     */
    void load();

    /**
     * Store the middles of the servos (for trimming the servos).
     * @param servoMiddles the middles for the servos
     */
    void storeServoMiddles(AxisData<int> servoMiddles);

    /**
     * Store the I gains (for the maximum throttle) for the PID stabilizer.
     * @param gain the P gains
     */
    void storePGain(CorrectionData gain);
    /**
     * Store the I gains (for the maximum throttle) for the PID stabilizer.
     * @param gain the I gains
     */
    void storeIGain(CorrectionData gain);
    /**
     * Store the D gains (for the maximum throttle) for the PID stabilizer.
     * @param gain the D gains
     */
    void storeDGain(CorrectionData gain);

    /**
     * Store the P gains for the minimum throttle for the PID stabilizer.
     * @param gain the P gains
     */
    void storeMinThrottlePGain(CorrectionData gain);
    /**
     * Store the I gains for the minimum throttle for the PID stabilizer.
     * @param gain the I gains
     */
    void storeMinThrottleIGain(CorrectionData gain);
    /**
     * Store the D gains for the minimum throttle for the PID stabilizer.
     * @param gain the D gains
     */
    void storeMinThrottleDGain(CorrectionData gain);

    /**
     * Clear all saved data.
     */
    void reset();

private:
    PID* pid;
    AxisData<ServoOutput*> outputs;

#if defined(ESP8266) || defined(ESP32)
    Preferences preferences;

    static const char* FOLDER_NAME;
    static const char* SERVO_MIDDLE;
    static const char* P_GAIN;
    static const char* I_GAIN;
    static const char* D_GAIN;
    static const char* MIN_THROTTLE_P_GAIN;
    static const char* MIN_THROTTLE_I_GAIN;
    static const char* MIN_THROTTLE_D_GAIN;

    void storeData(const char* key, int value);
    void storeData(const char* key, float value);

    AxisData<int> loadInts(const char* key);
    AxisData<float> loadFloats(const char* key);

#else
    static const int FLOAT_SIZE = 4;
    static const int INT_SIZE = 2;

    static const int SERVO_MIDDLE_POS = 0;
    
    static const int P_GAIN_POS = 6;
    static const int I_GAIN_POS = 18;
    static const int D_GAIN_POS = 30;
    static const int MIN_THROTTLE_P_GAIN_POS = 42;
    static const int MIN_THROTTLE_I_GAIN_POS = 54;
    static const int MIN_THROTTLE_D_GAIN_POS = 66;

    void storeGain(int address, CorrectionData gain);
    AxisData<int> loadInts(int address);
    AxisData<float> loadFloats(int address);

#endif    
};

#endif