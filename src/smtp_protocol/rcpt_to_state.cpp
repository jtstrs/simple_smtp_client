#include "rcpt_to_state.h"
#include "../common.h"
#include "../logger_wrapper.h"
#include "../responses_parser.h"
#include "error_state.h"
#include "fill_data_state.h"
#include <memory>

#define LOG_MODULE "RCPT TO STATE"

RcptToState::RcptToState() {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> RcptToState::handleTransition(Poco::Net::StreamSocket &socket,
                                                         const Message &messageData) {
    LOG_FUNC

    char inputBuffer[INPUT_BUFFER_SIZE + 1];
    memset(inputBuffer, 0, sizeof(inputBuffer));
    const int32_t receivedBytes = socket.receiveBytes(inputBuffer, sizeof(inputBuffer), 0);

    if (receivedBytes == 0) {
        return std::make_unique<ErrorState>("Cant receive message from server. Move to error state");
    }

    LOG_FMT_MESSAGE("Received message: %s", std::string(inputBuffer))
    LOG_FMT_MESSAGE("Accepted bytes: %d", receivedBytes)

    ResponseCode responseCode = parseCode(inputBuffer);

    if (responseCode != ResponseCode::ActionCompleted) {
        return std::make_unique<ErrorState>("Bad response code. Move to error state");
    }

    constexpr char const *RCPT_TO_STATE_MSG = "RCPT TO";
    const std::string rcptToMessageBuffer = std::move(std::format("{}: <{}>", RCPT_TO_STATE_MSG, messageData.to));
    socket.sendBytes(rcptToMessageBuffer.c_str(), rcptToMessageBuffer.size(), 0);
    LOG_FMT_MESSAGE("Send message %s to server", rcptToMessageBuffer)

    return std::make_unique<FillDataState>();
}