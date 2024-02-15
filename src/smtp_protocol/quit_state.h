#ifndef QUIT_STATE
#define QUIT_STATE

#include "smtp_state.h"

class QuitState : public SmtpState {
public:
    void handleMessage(const std::string &message) override;
};

#endif