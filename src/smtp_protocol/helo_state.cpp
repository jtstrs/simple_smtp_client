#include "helo_state.h"
#include "../common.h"
#include "../logger_wrapper.h"
#include "../responses_parser.h"
#include "error_state.h"
#include "mail_from_state.h"
#include "smtp_state.h"
#include <memory>
#include <sstream>

#define LOG_MODULE "HELO STATE"


HeloState::HeloState() {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> HeloState::handleTransition(Poco::Net::StreamSocket &socket,
                                                       const Message &messageData) {
    LOG_FUNC

    constexpr char const *HELO_STATE_MESSAGE = "HELO";
    std::stringstream heloMessageBuilder;
    heloMessageBuilder << HELO_STATE_MESSAGE << " " << messageData.fromDomain;

    const auto status = baseStateHandler(socket,
                                         heloMessageBuilder.str(),
                                         ResponseCode::ActionCompleted);
    if (status != StateHandlingStatus::Ok) {
        return std::make_unique<ErrorState>(status);
    }
    return std::make_unique<MailFromState>();
}