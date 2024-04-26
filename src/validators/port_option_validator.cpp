#include "port_option_validator.h"
#include <Poco/Util/OptionException.h>
#include <sstream>

void PortOptionValidator::validate(const Poco::Util::Option &option, const std::string &value) {
    int32_t parsedPort = 0;
    std::from_chars(value.c_str(), value.c_str() + value.size(), parsedPort);
    if (parsedPort == 0) {
        std::stringstream errorMsgBuilder;
        errorMsgBuilder << "Incorrect value for [--port] opt provided: " << value;
        throw Poco::Util::OptionException(errorMsgBuilder.str());
    }
}