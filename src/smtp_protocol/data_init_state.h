#ifndef DATA_INIT_STATE
#define DATA_INIT_STATE

#include "smtp_state.h"

class DataInitState : public SmtpState {
public:
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket) override;
};

#endif