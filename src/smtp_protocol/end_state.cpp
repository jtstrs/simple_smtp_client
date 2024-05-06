#include "end_state.h"
#include "../logger_wrapper.h"

#define LOG_MODULE "END STATE"

std::unique_ptr<SmtpState> EndState::handleTransition(Poco::Net::StreamSocket &socket,
                                                      const Message &messageData) {
    // Do nothing
    LOG_FUNC
    LOG_MESSAGE("Transition completed")
    return nullptr;
}