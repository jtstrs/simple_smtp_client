#include "smtp_client.h"
#include "message.h"
#include "smtp_protocol/connection_state.h"
#include <memory>

SmtpClient::SmtpClient(const std::string &host, int32_t port) : m_addr(host, port), m_currentState(nullptr) {
}

void SmtpClient::sendMessage(const Message &message) {
    m_currentState = std::make_unique<ConnectionState>(m_addr);

    char inputMessageBuffer[sc_maxInputBufferSize];
    memset(inputMessageBuffer, 0, sc_maxInputBufferSize);

    while (m_currentState != nullptr) {
        m_currentState = m_currentState->handleTransition(m_connectionSocket);
    }
}