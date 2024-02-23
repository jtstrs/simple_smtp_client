#ifndef HELO_STATE
#define HELO_STATE

#include "smtp_state.h"

class HeloState : public SmtpState {
public:
    std::unique_ptr<SmtpState> handleMessage(const std::string &message) override;
};

#endif