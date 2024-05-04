#include "error_state.h"
#include "../logger_wrapper.h"
#include <stdexcept>

#define LOG_MODULE "ERROR STATE"

ErrorState::ErrorState(const std::string &errorReason) : m_errorReason(errorReason) {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> ErrorState::handleTransition(Poco::Net::StreamSocket &socket,
                                                        const Message &messageData) {
    LOG_FUNC
    LOG_MESSAGE(m_errorReason)
    throw std::runtime_error(m_errorReason);
    return nullptr;
}