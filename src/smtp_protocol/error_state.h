#ifndef ERROR_STATE
#define ERROR_STATE

#include "smtp_state.h"

class ErrorState : public SmtpState {
public:
    template<typename T>
    explicit ErrorState(T &&errorReason) : m_errorReason(std::move(errorReason)) {}
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                const Message &messageData) override;

private:
    std::string m_errorReason;
};

#endif