#ifndef _USER_INTERFACE_H
#define _USER_INTERFACE_H

#include <Menu.h>

class UserInterface {
public:
    virtual void handle() = 0;

protected:
    Menu* menu;
};

#endif