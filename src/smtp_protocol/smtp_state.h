#ifndef SMTP_STATE
#define SMTP_STATE

#include "../message.h"
#include "../responses_parser.h"
#include <Poco/Net/StreamSocket.h>
#include <memory>

class SmtpState {
public:
    virtual std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                        const Message &messageData) = 0;

protected:
    bool baseStateHandler(Poco::Net::StreamSocket &socket,
                          const std::string &stateCaption,
                          const std::string &stateValue,
                          ResponseCode expectedCode);
};

#endif