#ifndef MAIL_FROM_STATE
#define MAIL_FROM_STATE

#include "smtp_state.h"

class MailFromState : public SmtpState {
public:
    explicit MailFromState();
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                const Message &messageData) override;
};

#endif