#include "CustomException.h"

CustomException::CustomException(ErrorCode errorCode) {
    code = errorCode;
}

const char* CustomException::ErrorMessage() const throw () {

    if (code == INVALID_MAPPING) {
        std::cerr << "Unable to find mapping to cell state.\n";
    } else if (code == INVALID_FILE) {
        std::cerr << "Invalid filename provided.";
    } else if (code == NULL_PARAMETER)
        std::cerr << "Invalid parameter passed to the function.";

}

CustomException::ErrorCode CustomException::getError() {
    return code;
}
