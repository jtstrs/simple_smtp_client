#ifndef SMTP_CLIENT
#define SMTP_CLIENT

#include "message.h"
#include "smtp_protocol/smtp_state.h"
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <cstdint>
#include <memory>
#include <string>

class SmtpClient {
public:
    SmtpClient(const std::string &host, int32_t port);
    void sendMessage(const Message &message);

private:
    Poco::Net::SocketAddress m_addr;
    Poco::Net::StreamSocket m_connectionSocket;
    std::unique_ptr<SmtpState> m_currentState;

    static constexpr int32_t sc_maxInputBufferSize = 2048;
    static constexpr int32_t sc_maxOutputBufferSize = 2048;
};

#endif