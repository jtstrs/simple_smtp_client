#ifndef CONNECTION_STATE
#define CONNECTION_STATE

#include "smtp_state.h"
#include <Poco/Net/SocketAddress.h>

class ConnectionState : public SmtpState {
public:
    explicit ConnectionState(const Poco::Net::SocketAddress &addr);
    std::unique_ptr<SmtpState> handleTransition(Poco::Net::StreamSocket &socket) override;

private:
    Poco::Net::SocketAddress m_addr;
};

#endif