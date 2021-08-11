#ifndef _SPEED_READER_H
#define _SPEED_READER_H

class SpeedReader {
public:
    SpeedReader(int resolution = 1024) {
        this->resolution = resolution;
    }

    virtual int getSpeed() = 0;
    virtual int getRawSpeed() = 0;

    void setResolution(int resolution) {
        this->resolution = resolution;
    }
    int getResolution() {
        return this->resolution;
    }

protected:
    int resolution;
};

#endif