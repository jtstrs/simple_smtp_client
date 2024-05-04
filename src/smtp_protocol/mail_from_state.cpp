#include "mail_from_state.h"
#include "../common.h"
#include "../logger_wrapper.h"
#include "../responses_parser.h"
#include "error_state.h"
#include "rcpt_to_state.h"
#include <memory>

#define LOG_MODULE "MAIL FROM STATE"

MailFromState::MailFromState() {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> MailFromState::handleTransition(Poco::Net::StreamSocket &socket,
                                                           const Message &messageData) {
    LOG_FUNC
    char inputBuffer[INPUT_BUFFER_SIZE + 1];
    memset(inputBuffer, 0, sizeof(inputBuffer));

    const int32_t receivedBytes = socket.receiveBytes(inputBuffer, sizeof(inputBuffer), 0);

    if (receivedBytes == 0) {
        return std::make_unique<ErrorState>("Cant receive message from the server");
    }
    LOG_FMT_MESSAGE("Received message: %s", std::string(inputBuffer))
    LOG_FMT_MESSAGE("Accepted bytes: %d.", receivedBytes)

    ResponseCode responseCode = parseCode(inputBuffer);

    if (responseCode != ResponseCode::ActionCompleted) {
        return std::make_unique<ErrorState>("Bad response code. Move to error state");
    }

    constexpr char const *MAIL_FROM_STATE_MESSAGE = "MAIL FROM";
    const std::string mailFromMessageBuffer = std::format("{}: <{}>\r\n",
                                                          MAIL_FROM_STATE_MESSAGE,
                                                          messageData.from);
    socket.sendBytes(mailFromMessageBuffer.c_str(), mailFromMessageBuffer.size(), 0);
    LOG_FMT_MESSAGE("Send message to %s to server.", mailFromMessageBuffer)
    return std::make_unique<RcptToState>();
}