#include "end_state.h"

std::unique_ptr<SmtpState> EndState::handleTransition(Poco::Net::StreamSocket &socket,
                                                      const Message &messageData) {
    return nullptr;
}