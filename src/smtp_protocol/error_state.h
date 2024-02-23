#ifndef ERROR_STATE
#define ERROR_STATE

#include "smtp_state.h"

class ErrorState : public SmtpState {
public:
    std::unique_ptr<SmtpState> handleMessage(const std::string &message) override;
};

#endif