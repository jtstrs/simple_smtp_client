#include "helo_state.h"
#include "../common.h"
#include "../logger_wrapper.h"
#include "../responses_parser.h"
#include "error_state.h"
#include "mail_from_state.h"
#include <memory>

#define LOG_MODULE "HELO STATE"


HeloState::HeloState() {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> HeloState::handleTransition(Poco::Net::StreamSocket &socket,
                                                       const Message &messageData) {
    LOG_FUNC

    char inputBuffer[INPUT_BUFFER_SIZE + 1];
    memset(inputBuffer, 0, sizeof(inputBuffer));

    int32_t bytesReceived = socket.receiveBytes(inputBuffer, INPUT_BUFFER_SIZE);

    if (bytesReceived == 0) {
        return std::make_unique<ErrorState>("No additional lines from server");
    }

    LOG_FMT_MESSAGE("Receive message: %s", std::string(inputBuffer))
    LOG_FMT_MESSAGE("Accepted bytes: %d", bytesReceived)

    ResponseCode responseCode = parseCode(inputBuffer);

    LOG_FMT_MESSAGE("Server response code: %d", static_cast<int32_t>(responseCode))

    if (responseCode != ResponseCode::ServiceReady) {
        LOG_MESSAGE("Bad response code")
        return std::make_unique<ErrorState>(std::format("Received incorrect response code: {}. Expected: {}\n",
                                                        static_cast<int32_t>(responseCode),
                                                        static_cast<int32_t>(ResponseCode::ServiceReady)));
    }

    if (messageData.domain.empty()) {
        LOG_MESSAGE("Provided domain is an empty");
        return std::make_unique<ErrorState>("Provided incorrect message configuration. Domain is an empty");
    }

    constexpr char const *HELO_STATE_MESSAGE = "HELO";
    const std::string messageBuffer = std::move(std::format("{} {}\r\n", HELO_STATE_MESSAGE, messageData.domain));
    LOG_FMT_MESSAGE("Send message to server: %s", messageBuffer)
    socket.sendBytes(messageBuffer.c_str(), messageBuffer.size(), 0);
    return std::make_unique<MailFromState>();
}