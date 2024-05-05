#include "smtp_state.h"
#include "../common.h"
#include "../logger_wrapper.h"

#define LOG_MODULE "SMTP STATE"

bool SmtpState::baseStateHandler(Poco::Net::StreamSocket &socket,
                                 const std::string &stateCaption,
                                 const std::string &stateValue,
                                 ResponseCode expectedCode) {
    LOG_FUNC

    char inputBuffer[INPUT_BUFFER_SIZE + 1];
    memset(inputBuffer, 0, sizeof(inputBuffer));
    const int32_t receivedBytes = socket.receiveBytes(inputBuffer, sizeof(inputBuffer), 0);

    if (receivedBytes == 0) {
        return false;
    }

    LOG_FMT_MESSAGE("Received message: %s", std::string(inputBuffer))
    LOG_FMT_MESSAGE("Accepted bytes: %d", receivedBytes)

    ResponseCode responseCode = parseCode(inputBuffer);

    if (responseCode != expectedCode) {
        return false;
    }

    const std::string messageBuffer = std::move(std::format("{}: <{}>\r\n",
                                                            stateCaption,
                                                            stateValue));
    socket.sendBytes(messageBuffer.c_str(), messageBuffer.size(), 0);
    LOG_FMT_MESSAGE("Send message %s to server", messageBuffer)

    return true;
}