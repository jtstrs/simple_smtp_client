#ifndef SMTP_STATE
#define SMTP_STATE

#include <string>

class SmtpState {
public:
    virtual void handleMessage(const std::string &message) = 0;
};

#endif