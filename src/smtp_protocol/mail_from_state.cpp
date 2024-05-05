#include "mail_from_state.h"
#include "../logger_wrapper.h"
#include "../responses_parser.h"
#include "error_state.h"
#include "rcpt_to_state.h"
#include <memory>

#define LOG_MODULE "MAIL FROM STATE"

MailFromState::MailFromState() {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> MailFromState::handleTransition(Poco::Net::StreamSocket &socket,
                                                           const Message &messageData) {
    LOG_FUNC

    constexpr char const *MAIL_FROM_STATE_MESSAGE = "MAIL FROM";
    const bool handlingStatus = baseStateHandler(socket, MAIL_FROM_STATE_MESSAGE, messageData.from, ResponseCode::ActionCompleted);

    if (!handlingStatus) {
        return std::make_unique<ErrorState>("Mail from state handling error");
    }

    return std::make_unique<RcptToState>();
}