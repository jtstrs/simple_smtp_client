#include "fill_data_state.h"
#include "../logger_wrapper.h"
#include "error_state.h"

#define LOG_MODULE "FILL DATA STATE"

std::unique_ptr<SmtpState> FillDataState::handleTransition(Poco::Net::StreamSocket &socket,
                                                           const Message &messageData) {
    LOG_FUNC

    std::stringstream fillDataMessageBuilder;
    fillDataMessageBuilder << "Subject: " << messageData.subject
                           << "\r\n";

    std::stringstream mailBodyStream(messageData.body);

    while (!mailBodyStream.eof()) {
        std::string temp;
        std::getline(mailBodyStream, temp);
        fillDataMessageBuilder << std::move(temp) << "\r\n";
    }

    constexpr char const *SMTP_END_SEQUENCE = "\r\n.";
    fillDataMessageBuilder << SMTP_END_SEQUENCE;

    const auto status = baseStateHandler(socket,
                                         fillDataMessageBuilder.str(),
                                         ResponseCode::ActionCompleted);

    if (status != StateHandlingStatus::Ok) {
        return std::make_unique<ErrorState>(status);
    }

    return nullptr;
}