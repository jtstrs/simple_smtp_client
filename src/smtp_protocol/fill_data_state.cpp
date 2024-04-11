#include "fill_data_state.h"

std::unique_ptr<SmtpState> FillDataState::handleTransition(Poco::Net::StreamSocket &socket,
                                                           const Message &messageData) {
    return nullptr;
}