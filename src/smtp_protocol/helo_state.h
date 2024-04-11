#ifndef HELO_STATE
#define HELO_STATE

#include "smtp_state.h"

class HeloState : public SmtpState {
public:
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                const Message &messageData) override;
};

#endif