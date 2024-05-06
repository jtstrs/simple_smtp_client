#include "smtp_state.h"
#include "../common.h"
#include "../logger_wrapper.h"
#include <sstream>
#include <stdexcept>
#include <string_view>

#define LOG_MODULE "SMTP STATE"

std::string handlingStatusToString(StateHandlingStatus status) {
    switch (status) {
        case StateHandlingStatus::Ok:
            return "Ok";
        case StateHandlingStatus::ResponseBad:
            return "Wrong response string";
        case StateHandlingStatus::ResponseEmpty:
            return "Received empty string from server";
        default:
            // Should never be here
            throw std::runtime_error("Error reason unknown");
    }
}

StateHandlingStatus SmtpState::baseStateHandler(Poco::Net::StreamSocket &socket,
                                                const std::string &messageBody,
                                                ResponseCode expectedCode) {
    LOG_FUNC

    if (!messageBody.empty()) {
        std::stringstream messageBuilder;
        messageBuilder << messageBody << "\r\n";
        const std::string_view message = messageBuilder.view();
        socket.sendBytes(message.data(), message.size(), 0);
        LOG_FMT_MESSAGE("Send message %s to server", std::string(message))
    }

    char inputBuffer[INPUT_BUFFER_SIZE + 1];
    memset(inputBuffer, 0, sizeof(inputBuffer));
    const int32_t receivedBytes = socket.receiveBytes(inputBuffer, sizeof(inputBuffer), 0);

    if (receivedBytes == 0) {
        return StateHandlingStatus::ResponseEmpty;
    }

    LOG_FMT_MESSAGE("Received message: %s", std::string(inputBuffer))
    LOG_FMT_MESSAGE("Accepted bytes: %d", receivedBytes)

    ResponseCode responseCode = parseCode(inputBuffer);

    if (responseCode != expectedCode) {
        return StateHandlingStatus::ResponseBad;
    }

    return StateHandlingStatus::Ok;
}