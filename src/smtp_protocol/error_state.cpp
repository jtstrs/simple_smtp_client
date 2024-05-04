#include "error_state.h"
#include <stdexcept>

#define LOG_MODULE "ERROR STATE"

ErrorState::ErrorState(const std::string &errorReason) : m_errorReason(errorReason),
                                                         m_logger(Poco::Logger::get(LOG_MODULE)) {
}

std::unique_ptr<SmtpState> ErrorState::handleTransition(Poco::Net::StreamSocket &socket,
                                                        const Message &messageData) {
    m_logger.information(m_errorReason);
    throw std::runtime_error(m_errorReason);
    return nullptr;
}