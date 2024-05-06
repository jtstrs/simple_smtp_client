#include "error_state.h"
#include "../logger_wrapper.h"
#include "smtp_state.h"
#include <stdexcept>

#define LOG_MODULE "ERROR STATE"

ErrorState::ErrorState(StateHandlingStatus errorCode) : m_errorCode(errorCode) {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> ErrorState::handleTransition(Poco::Net::StreamSocket &socket,
                                                        const Message &messageData) {
    LOG_FUNC
    const std::string errorReasonMessage = handlingStatusToString(m_errorCode);
    LOG_MESSAGE(errorReasonMessage)
    throw std::runtime_error(
            std::format("Error happened during handling resposne from server. Error reason: {}",
                        errorReasonMessage));
}