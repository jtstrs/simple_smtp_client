#include "message.h"
#include "common.h"
#include "logger_wrapper.h"
#include <Poco/Exception.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/JSONException.h>
#include <Poco/JSON/Object.h>
#include <Poco/Util/OptionException.h>
#include <exception>
#include <ostream>
#include <sstream>
#include <string>

#define LOG_MODULE "MESSAGE"

#include <Poco/JSON/Parser.h>

constexpr std::string_view DOMAIN_KEY = "domain";
constexpr std::string_view MAIL_FROM_KEY = "mail_from";
constexpr std::string_view DESTINATION_ADDRESES_KEY = "destination_addresses";
constexpr std::string_view MESSAGE_SUBJECT_KEY = "message_subject";
constexpr std::string_view MESSAGE_CONTENT_KEY = "message_content";

Message Message::parse_message(std::istream &source) {
    LOG_FUNC

    using namespace Poco::JSON;
    using Poco::Dynamic::Var;

    Message smtpMessage;
    try {
        Parser parser;
        Var result = parser.parse(source);

        Object::Ptr root = result.extract<Object::Ptr>();
        CHECK_NULL(root, std::string("Root"))

        smtpMessage.fromDomain = root->getValue<std::string>(DOMAIN_KEY.data());
        smtpMessage.fromAddress = root->getValue<std::string>(MAIL_FROM_KEY.data());
        smtpMessage.subject = root->getValue<std::string>(MESSAGE_SUBJECT_KEY.data());

        Array::Ptr destinationAddressesArray = root->getArray(DESTINATION_ADDRESES_KEY.data());
        CHECK_NULL(destinationAddressesArray, std::string("destionAddressesArray"))

        const int32_t destionationAddressesCount = destinationAddressesArray->size();
        for (int32_t addressIndex = 0; addressIndex < destionationAddressesCount; ++addressIndex) {
            Var address = destinationAddressesArray->getElement<std::string>(addressIndex);
            if (!address) {
                throw Poco::BadCastException("Trying to access to out of bound array item");
            }
            smtpMessage.destinationAddresses.emplace_back(address.toString());
        }
        smtpMessage.messageBody = root->getValue<std::string>(MESSAGE_CONTENT_KEY.data());

        // Rethrow any exception happened during parsing
        // as incorrect option exception, since there
        // some problems with input
    } catch (Poco::BadCastException &badCastException) {
        LOG_MESSAGE(badCastException.what())
        throw Poco::Util::OptionException("Error happened during parsing of provided json. Cannot extract object");
    } catch (Poco::InvalidAccessException &invalidAccessException) {
        LOG_MESSAGE(invalidAccessException.what())
        throw Poco::Util::OptionException("Error happened during parsing of provided json. Cannot extract object");
    } catch (std::exception &parsingError) {
        LOG_MESSAGE(parsingError.what())
        throw Poco::Util::OptionException("Error happened during parsing of provided json. Cannot parse json");
    }

    return smtpMessage;
}

std::string Message::toString() const {
    std::stringstream messageSerializer;
    dump(messageSerializer);
    return messageSerializer.str();
}

void Message::dump(std::ostream &os) const {
    os << "Server domain: " << fromDomain << "\n";
    os << "From: " << fromAddress << "\n";
    const int32_t addressesCount = destinationAddresses.size();
    for (int32_t i = 0; i < addressesCount; ++i) {
        os << "To: " << destinationAddresses.at(i) << "\n";
    }
    os << "Subject: " << subject << "\n";
    os << "Body: " << messageBody << "\n";
}