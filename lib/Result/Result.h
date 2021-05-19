#ifndef _RESULT_H
#define _RESULT_H

class Result {
public:
    enum class ResultType {
        SUCCESS,
        FAILURE
    };

    Result(ResultType resultType, const char* message);
    Result(ResultType resultType);

    const char* getMessage();
    ResultType getType();

private:
    const char* message;
    ResultType type;
};

#endif