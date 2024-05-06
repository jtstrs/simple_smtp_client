#ifndef ERROR_STATE
#define ERROR_STATE

#include "smtp_state.h"

class ErrorState : public SmtpState {
public:
    explicit ErrorState(StateHandlingStatus reasonCode);
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                const Message &messageData) override;

private:
    StateHandlingStatus m_errorCode;
};

#endif