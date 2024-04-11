#include "mail_from_state.h"

std::unique_ptr<SmtpState> MailFromState::handleTransition(Poco::Net::StreamSocket &socket,
                                                           const Message &messageData) {
    return nullptr;
}