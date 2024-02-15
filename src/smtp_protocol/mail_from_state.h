#ifndef MAIL_FROM_STATE
#define MAIL_FROM_STATE

#include "smtp_state.h"

class MailFromState : public SmtpState {
public:
    void handleMessage(const std::string &message) override;
};

#endif