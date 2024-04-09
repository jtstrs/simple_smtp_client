#ifndef RESPONSES_PARSER
#define RESPONSES_PARSER

#include <charconv>
#include <sstream>
#include <string>
#include <system_error>
#include <type_traits>

enum ResponseCode : int32_t {
    ServiceReady = 220,
    ServiceClosing = 221,
    ActionCompleted = 250,
    StartMessageInpuit = 354,
    ServiceNotAvailable = 421,
    UserMailboxUnavailableTryLater = 450,
    ServerError = 451,
    ServerStorageIfFull = 452,
    CannotHandleCommandTryLater = 455,
    UnknownCommand = 500,
    IncorrectCommandSyntax = 501,
    CommandNotImplemented = 502,
    BadCommandsSequence = 503,
    CommandParamNotImplemented = 504,
    DummyServerResponse = 521,
    SupressedBySpamFilter = 451,
    UserMailboxUnavailable = 550,
    RecipientIsNotLocalToServer = 551,
    ExceedStorageAllocation = 552,
    InvalidMailboxName = 553,
    MailboxIsDisabled = 554
};

template<typename T>
ResponseCode parseCode(T &&line) {
    static_assert(!std::is_same_v<T, std::string> ||
                          !std::is_same_v<std::remove_cvref_t<T>, char *>,
                  "Input parameter must be std::string");
    std::stringstream tokenizer(line);

    for (std::string token; !tokenizer.eof(); tokenizer >> token) {
        int32_t parsable = 0;
        const auto [ptr, errorCode] = std::from_chars(token.c_str(), token.c_str() + token.size(), parsable);

        if (errorCode == std::errc::result_out_of_range) {
            return ResponseCode::UnknownCommand;
        }

        if (errorCode != std::errc::invalid_argument) {
            // TODO: Add check that parsed code lay in scope of variables, which defined in enum
            ResponseCode responseCode = static_cast<ResponseCode>(parsable);
            return responseCode;
        }
    }
    return ResponseCode::UnknownCommand;
}


#endif