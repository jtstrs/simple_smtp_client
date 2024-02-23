#ifndef SMTP_STATE
#define SMTP_STATE

#include <memory>
#include <string>

class SmtpState {
public:
    virtual std::unique_ptr<SmtpState> handleMessage(const std::string &message) = 0;
};

#endif