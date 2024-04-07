#include "helo_state.h"
#include <Poco/FIFOBuffer.h>

constexpr char const *HELO_STATE_MESSAGE = "HELO";

std::unique_ptr<SmtpState> HeloState::handleTransition(Poco::Net::StreamSocket &socket) {
    socket.sendBytes((void *) HELO_STATE_MESSAGE, strlen(HELO_STATE_MESSAGE), 0);
    return nullptr;
}