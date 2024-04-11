#include "error_state.h"
#include <stdexcept>

std::unique_ptr<SmtpState> ErrorState::handleTransition(Poco::Net::StreamSocket &socket) {
    throw new std::runtime_error(m_errorReason);
    return nullptr;
}