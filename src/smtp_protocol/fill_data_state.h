#ifndef FILL_DATA_STATE
#define FILL_DATA_STATE

#include "smtp_state.h"

class FillDataState : public SmtpState {
public:
    std::unique_ptr<SmtpState> handleMessage(const std::string &message) override;
};

#endif