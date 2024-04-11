#ifndef SMTP_STATE
#define SMTP_STATE

#include "../message.h"
#include <Poco/Net/SocketStream.h>
#include <memory>

class SmtpState {
public:
    virtual std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                        const Message &messageData) = 0;
};

#endif