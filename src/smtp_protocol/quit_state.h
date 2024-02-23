#ifndef QUIT_STATE
#define QUIT_STATE

#include "smtp_state.h"

class QuitState : public SmtpState {
public:
    std::unique_ptr<SmtpState> handleMessage(const std::string &message) override;
};

#endif