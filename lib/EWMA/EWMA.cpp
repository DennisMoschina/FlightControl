#include <EWMA.h>

EWMA::EWMA(float alpha) {
    this->alpha = alpha;
}

float EWMA::addValue(float value) {
    this->value = (std::isnan(this->value)) ? value : (1 - this->alpha) * this->value + this->alpha * value;
    return this->value;
}