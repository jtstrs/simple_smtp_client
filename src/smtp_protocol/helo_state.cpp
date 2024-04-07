#include "helo_state.h"
#include "../common.h"
#include "error_state.h"

constexpr char const *HELO_STATE_MESSAGE = "HELO";

std::unique_ptr<SmtpState> HeloState::handleTransition(Poco::Net::StreamSocket &socket) {
    char inputBuffer[INPUT_BUFFER_SIZE + 1];

    int32_t bytesReceived = socket.receiveBytes(inputBuffer, INPUT_BUFFER_SIZE);

    if (bytesReceived == 0) {
        return std::make_unique<ErrorState>();
    }

    std::cout << "Receive buffer from server: " << inputBuffer << std::endl;

    socket.sendBytes((void *) HELO_STATE_MESSAGE, strlen(HELO_STATE_MESSAGE), 0);
    return nullptr;
}