#include <Result.h>

Result::Result(ResultType resultType, const char* message) {
    this->type = resultType;
    this->message = message;
}

Result::Result(ResultType resultType) {
    this->type = resultType;
}

Result::ResultType Result::getType() {
    return this->type;
}

const char* Result::getMessage() {
    return this->message;
}
