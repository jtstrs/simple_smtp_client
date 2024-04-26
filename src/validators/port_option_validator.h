#ifndef PORT_OPT_VALIDATOR
#define PORT_OPT_VALIDATOR

#include <Poco/Util/Option.h>
#include <Poco/Util/Validator.h>

class PortOptionValidator : public Poco::Util::Validator {
public:
    void validate(const Poco::Util::Option &option, const std::string &value) override;
};

#endif