#include "error_state.h"
#include <stdexcept>

std::unique_ptr<SmtpState> ErrorState::handleTransition(Poco::Net::StreamSocket &socket,
                                                        const Message &messageData) {
    m_logger.information(m_errorReason);
    throw std::runtime_error(m_errorReason);
    return nullptr;
}