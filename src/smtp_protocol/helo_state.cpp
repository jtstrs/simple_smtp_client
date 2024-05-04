#include "helo_state.h"
#include "../common.h"
#include "../responses_parser.h"
#include "error_state.h"
#include <Poco/Logger.h>
#include <memory>

#define LOG_MODULE "HELO STATE"

constexpr char const *HELO_STATE_MESSAGE = "HELO";

HeloState::HeloState() : m_logger(Poco::Logger::get(LOG_MODULE)) {
}

std::unique_ptr<SmtpState> HeloState::handleTransition(Poco::Net::StreamSocket &socket,
                                                       const Message &messageData) {
    char inputBuffer[INPUT_BUFFER_SIZE + 1];
    memset(inputBuffer, 0, sizeof(inputBuffer));

    int32_t bytesReceived = socket.receiveBytes(inputBuffer, INPUT_BUFFER_SIZE);
    m_logger.information("Receive message: %s", std::string(inputBuffer));
    m_logger.information("Accepted bytes: %d", bytesReceived);

    if (bytesReceived == 0) {
        return std::make_unique<ErrorState>("No additional lines from server");
    }

    ResponseCode responseCode = parseCode(inputBuffer);
    m_logger.information("Server response code: %d", static_cast<int32_t>(responseCode));

    if (responseCode != ResponseCode::ServiceReady) {
        m_logger.information("Bad response code. Move to error state");
        return std::make_unique<ErrorState>(std::format("Received incorrect response code: {}. Expected: {}\n",
                                                        static_cast<int32_t>(responseCode),
                                                        static_cast<int32_t>(ResponseCode::ServiceReady)));
    }

    if (messageData.domain.empty()) {
        m_logger.information("Provided domain is an empty. Move to error state.");
        return std::make_unique<ErrorState>("Provided incorrect message configuration. Domain is an empty");
    }

    const std::string messageBuffer = std::move(std::format("{} {}\r\n", HELO_STATE_MESSAGE, messageData.domain));
    m_logger.information("OK. Move to MAIL FROM STATE. Send message to server: %s",
                         messageBuffer);
    socket.sendBytes(messageBuffer.c_str(), messageBuffer.size(), 0);
    return nullptr;
}