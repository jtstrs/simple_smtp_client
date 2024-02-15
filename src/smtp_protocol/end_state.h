#ifndef END_STATE
#define END_STATE

#include "smtp_state.h"

class EndState : public SmtpState {
public:
    void handleMessage(const std::string &message) override;
};

#endif