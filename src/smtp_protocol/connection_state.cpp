#include "connection_state.h"
#include "../logger_wrapper.h"
#include "helo_state.h"
#include "smtp_state.h"
#include <Poco/Logger.h>
#include <memory>

#define LOG_MODULE "CONNECTION STATE MODULE"

ConnectionState::ConnectionState(const Poco::Net::SocketAddress &addr) : m_addr(addr) {
    LOG_FUNC;
}

std::unique_ptr<SmtpState> ConnectionState::handleTransition(Poco::Net::StreamSocket &socket, const Message &messageData) {
    LOG_FUNC
    LOG_FMT_MESSAGE("Connectig to socker with addr: %s", m_addr.toString())
    socket.connect(m_addr);
    return std::make_unique<HeloState>();
}