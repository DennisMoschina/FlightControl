#ifndef _SERIAL_MONITOR_INTERFACE_H
#define _SERIAL_MONITOR_INTERFACE_H

#include <UserInterface.h>

class SerialMonitorInterface: public UserInterface {
public:
    SerialMonitorInterface(Menu* menu);

    void handle();

private:
    static const char TERMINATOR;
    static String TRIM_COMMAND;
    static String TRIM_END_COMMAND;

    static String CONTROLLER_COMMAND;
    static String CONTROLLER_END_COMMAND;
};

#endif