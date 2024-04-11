#include "helo_state.h"
#include "../common.h"
#include "../responses_parser.h"
#include "error_state.h"
#include <memory>

constexpr char const *HELO_STATE_MESSAGE = "HELO";

std::unique_ptr<SmtpState> HeloState::handleTransition(Poco::Net::StreamSocket &socket) {
    char inputBuffer[INPUT_BUFFER_SIZE + 1];

    int32_t bytesReceived = socket.receiveBytes(inputBuffer, INPUT_BUFFER_SIZE);

    if (bytesReceived == 0) {
        return std::make_unique<ErrorState>("No additional lines from server");
    }

    ResponseCode responseCode = parseCode(inputBuffer);

    if (responseCode != ResponseCode::ServiceReady) {
        return std::make_unique<ErrorState>(std::format("Received incorrect response code: {}. Expected: {}\n",
                                                        static_cast<int32_t>(responseCode),
                                                        static_cast<int32_t>(ResponseCode::ServiceReady)));
    }

    socket.sendBytes((void *) HELO_STATE_MESSAGE, strlen(HELO_STATE_MESSAGE), 0);
    return nullptr;
}