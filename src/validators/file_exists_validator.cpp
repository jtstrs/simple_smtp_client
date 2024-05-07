
#include "file_exists_validator.h"
#include <Poco/Util/OptionException.h>
#include <cstring>
#include <filesystem>

void FileExistsValidator::validate(const Poco::Util::Option &option, const std::string &value) {
    if (!std::filesystem::exists(value)) {
        throw Poco::Util::OptionException("Provided incorrect path to msg file source");
    }

    constexpr char const *JSON_EXTENSION = ".json";
    if (std::strcmp(std::filesystem::path(value).extension().c_str(), JSON_EXTENSION) != 0) {
        throw Poco::Util::OptionException("JSON file format expected");
    }
}