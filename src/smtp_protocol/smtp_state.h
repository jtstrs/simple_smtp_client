#ifndef SMTP_STATE
#define SMTP_STATE

#include <Poco/Net/SocketStream.h>
#include <memory>

class SmtpState {
public:
    virtual std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket) = 0;
};

#endif