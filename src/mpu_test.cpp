#include <MPU6050.h>
#include <Filter.h>
#include <FilteredGyro.h>
#include <EWMA.h>
#include <OverflowFilter.h>

#define FILTER_DIMENSION 1

#define SHOW_RAW
#define SHOW_FILTERED
// #define SHOW_OVERFLOW
// #define SHOW_FILTER_OVERFLOW
// #define SHOW_OVERFLOW_FILTER

MPU6050* mpu = new MPU6050();
Filter<int, FILTER_DIMENSION>* filter = new EWMA<int, FILTER_DIMENSION>(0.5);
OverflowFilter<int, FILTER_DIMENSION>* overflowFilter = new OverflowFilter<int, FILTER_DIMENSION>();
Filter<int, FILTER_DIMENSION>* combinedFilterOverflow = new CombinedFilter<int, FILTER_DIMENSION>(filter, overflowFilter);
Filter<int, FILTER_DIMENSION>* combinedOverflowFilter = new CombinedFilter<int, FILTER_DIMENSION>(overflowFilter, filter);

void setup() {
    Serial.begin(115200);
    mpu->begin();
}

void loop() {
    int rawData = mpu->getRotation().roll;
    Serial.println((String) ""
        #ifdef SHOW_RAW
        + (String) rawData
        #endif
        #ifdef SHOW_FILTERED
        + ","
        + (String) filter->addValue(&rawData)[0]
        #endif
        #ifdef SHOW_OVERFLOW
        + ","
        + (String) overflowFilter->addValue(&rawData)[0]
        #endif
        #ifdef SHOW_FILTER_OVERFLOW
        + ","
        + (String) combinedFilterOverflow->addValue(&rawData)[0]
        #endif
        #ifdef SHOW_OVERFLOW_FILTER
        + ","
        + (String) combinedOverflowFilter->addValue(&rawData)[0]
        #endif
    );
    delay(50);
}