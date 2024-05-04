#include "rcpt_to_state.h"
#include "../common.h"
#include "../responses_parser.h"
#include "error_state.h"
#include "fill_data_state.h"
#include <Poco/Logger.h>
#include <memory>

#define LOG_MODULE "RCPT TO STATE"

RcptToState::RcptToState() : m_logger(Poco::Logger::get(LOG_MODULE)) {
}

std::unique_ptr<SmtpState> RcptToState::handleTransition(Poco::Net::StreamSocket &socket,
                                                         const Message &messageData) {
    char inputBuffer[INPUT_BUFFER_SIZE + 1];
    memset(inputBuffer, 0, sizeof(inputBuffer));
    const int32_t receivedBytes = socket.receiveBytes(inputBuffer, sizeof(inputBuffer), 0);

    if (receivedBytes == 0) {
        return std::make_unique<ErrorState>("Cant receive message from server. Move to error state");
    }

    m_logger.information("Received message: %s", std::string(inputBuffer));
    m_logger.information("Accepted bytes: %d", receivedBytes);

    ResponseCode responseCode = parseCode(inputBuffer);

    if (responseCode != ResponseCode::ActionCompleted) {
        return std::make_unique<ErrorState>("Bad response code. Move to error state");
    }

    constexpr char const *RCPT_TO_STATE_MSG = "RCPT TO";
    const std::string rcptToMessageBuffer = std::move(std::format("{}: <{}>", RCPT_TO_STATE_MSG, messageData.to));
    socket.sendBytes(rcptToMessageBuffer.c_str(), rcptToMessageBuffer.size(), 0);

    return std::make_unique<FillDataState>();
}