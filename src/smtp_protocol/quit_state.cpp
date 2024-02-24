#include "quit_state.h"

std::unique_ptr<SmtpState> QuitState::handleTransition(Poco::Net::StreamSocket &socket) {
    return nullptr;
}