
#include "file_exists_validator.h"
#include <Poco/Util/OptionException.h>
#include <filesystem>

void FileExistsValidator::validate(const Poco::Util::Option &option, const std::string &value) {
    if (!std::filesystem::exists(value)) {
        throw Poco::Util::OptionException("Provided incorrect path to msg file source");
    }
}