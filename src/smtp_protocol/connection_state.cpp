#include "connection_state.h"
#include "helo_state.h"
#include "smtp_state.h"
#include <memory>

ConnectionState::ConnectionState(const Poco::Net::SocketAddress &addr) : m_addr(addr) {
}

std::unique_ptr<SmtpState> ConnectionState::handleTransition(Poco::Net::StreamSocket &socket) {
    socket.bind(m_addr);
    return std::make_unique<HeloState>();
}