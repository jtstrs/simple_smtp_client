#ifndef RCPT_TO_STATE
#define RCPT_TO_STATE

#include "smtp_state.h"

class RcptToState : public SmtpState {
public:
    void handleMessage(const std::string &message) override;
};

#endif