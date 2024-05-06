#ifndef SMTP_STATE
#define SMTP_STATE

#include "../message.h"
#include "../responses_parser.h"
#include <Poco/Net/StreamSocket.h>
#include <memory>

enum class StateHandlingStatus {
    Ok,
    ResponseEmpty,
    ResponseBad
};

std::string handlingStatusToString(StateHandlingStatus status);

class SmtpState {
public:
    virtual std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket,
                                                        const Message &messageData) = 0;

protected:
    StateHandlingStatus baseStateHandler(Poco::Net::StreamSocket &socket,
                                         const std::string &messageBody,
                                         ResponseCode expectedCode);
};

#endif