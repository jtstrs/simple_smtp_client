#include "connection_state.h"
#include "helo_state.h"
#include "smtp_state.h"
#include <Poco/Logger.h>
#include <memory>

#define LOG_MODULE "CONNECTION STATE MODULE"

ConnectionState::ConnectionState(const Poco::Net::SocketAddress &addr) : m_addr(addr),
                                                                         m_logger(Poco::Logger::get(LOG_MODULE)) {
}

std::unique_ptr<SmtpState> ConnectionState::handleTransition(Poco::Net::StreamSocket &socket,
                                                             const Message &messageData) {

    m_logger.information("Connectig to socker with addr: %s", m_addr.toString());
    socket.connect(m_addr);
    return std::make_unique<HeloState>();
}