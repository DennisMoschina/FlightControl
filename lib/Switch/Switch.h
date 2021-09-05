#ifndef _SWITCH_H
#define _SWITCH_H

class Switch {
public:
    Switch(int positions);
    virtual int getPosition() = 0;

    int getNumberOfPositions();
private:
    const int positions;
};

#endif