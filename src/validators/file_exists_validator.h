
#ifndef FILE_EXISTS_VALIDATOR
#define FILE_EXISTS_VALIDATOR

#include <Poco/Util/Option.h>
#include <Poco/Util/Validator.h>

class FileExistsValidator : public Poco::Util::Validator {
public:
    void validate(const Poco::Util::Option &option, const std::string &value) override;
};

#endif