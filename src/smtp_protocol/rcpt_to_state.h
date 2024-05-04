#ifndef RCPT_TO_STATE
#define RCPT_TO_STATE

#include "smtp_state.h"

class RcptToState : public SmtpState {
public:
    explicit RcptToState();
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                const Message &messageData) override;
};

#endif