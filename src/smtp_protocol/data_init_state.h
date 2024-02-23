#ifndef DATA_INIT_STATE
#define DATA_INIT_STATE

#include "smtp_state.h"

class DataInitState : public SmtpState {
public:
    std::unique_ptr<SmtpState> handleMessage(const std::string &message) override;
};

#endif