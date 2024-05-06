#include "rcpt_to_state.h"
#include "../logger_wrapper.h"
#include "../responses_parser.h"
#include "data_init_state.h"
#include "error_state.h"
#include "smtp_state.h"
#include <memory>

#define LOG_MODULE "RCPT TO STATE"

RcptToState::RcptToState() {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> RcptToState::handleTransition(Poco::Net::StreamSocket &socket,
                                                         const Message &messageData) {
    LOG_FUNC

    constexpr char const *RCPT_TO_STATE_MSG = "RCPT TO";
    std::stringstream rcptToMessageBuilder;
    rcptToMessageBuilder << RCPT_TO_STATE_MSG << ":"
                         << "<" << messageData.to << ">";
    const auto status = baseStateHandler(socket,
                                         rcptToMessageBuilder.str(),
                                         ResponseCode::ActionCompleted);

    if (status != StateHandlingStatus::Ok) {
        return std::make_unique<ErrorState>(status);
    }

    return std::make_unique<DataInitState>();
}