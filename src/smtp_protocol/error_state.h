#ifndef ERROR_STATE
#define ERROR_STATE

#include "smtp_state.h"
#include <Poco/Logger.h>

class ErrorState : public SmtpState {
public:
    explicit ErrorState(const std::string &errorReason);
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                const Message &messageData) override;

private:
    Poco::Logger &m_logger;
    std::string m_errorReason;
};

#endif