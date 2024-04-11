#include "data_init_state.h"

std::unique_ptr<SmtpState> DataInitState::handleTransition(Poco::Net::StreamSocket &socket,
                                                           const Message &messageData) {
    return nullptr;
}