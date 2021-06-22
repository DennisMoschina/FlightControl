#ifndef _THROTTLE_READER_H
#define _THROTTLE_READER_H

class ThrottleReader {
public:
    ThrottleReader(int resolution = 1024) {
        this->resolution = resolution;
    }

    virtual int getThrottle() = 0;
    virtual int getRawThrottle() = 0;

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