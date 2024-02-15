#ifndef HELO_STATE
#define HELO_STATE

#include "smtp_state.h"

class HeloState : public SmtpState {
public:
    void handleMessage(const std::string &message) override;
};

#endif