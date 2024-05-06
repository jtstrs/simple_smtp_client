#include "mail_from_state.h"
#include "../logger_wrapper.h"
#include "../responses_parser.h"
#include "error_state.h"
#include "rcpt_to_state.h"
#include "smtp_state.h"
#include <memory>
#include <sstream>

#define LOG_MODULE "MAIL FROM STATE"

MailFromState::MailFromState() {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> MailFromState::handleTransition(Poco::Net::StreamSocket &socket,
                                                           const Message &messageData) {
    LOG_FUNC

    constexpr char const *MAIL_FROM_STATE_MESSAGE = "MAIL FROM";
    std::stringstream mailFromMessageBuilder;
    mailFromMessageBuilder << MAIL_FROM_STATE_MESSAGE << ":"
                           << "<" << messageData.from << ">";
    const auto status = baseStateHandler(socket,
                                         mailFromMessageBuilder.str(),
                                         ResponseCode::ActionCompleted);

    if (status != StateHandlingStatus::Ok) {
        return std::make_unique<ErrorState>(status);
    }

    return std::make_unique<RcptToState>();
}