#ifndef HELO_STATE
#define HELO_STATE

#include "smtp_state.h"
#include <Poco/Logger.h>

class HeloState : public SmtpState {
public:
    explicit HeloState();
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                const Message &messageData) override;

private:
    Poco::Logger &m_logger;
};

#endif