#ifndef ERROR_STATE
#define ERROR_STATE

#include "smtp_state.h"
#include <Poco/Logger.h>

#define LOG_MODULE "ERROR STATE"

class ErrorState : public SmtpState {
public:
    template<typename T>
    explicit ErrorState(T &&errorReason) : m_errorReason(std::move(errorReason)),
                                           m_logger(Poco::Logger::get(LOG_MODULE)) {}
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                const Message &messageData) override;

private:
    Poco::Logger &m_logger;
    std::string m_errorReason;
};

#endif