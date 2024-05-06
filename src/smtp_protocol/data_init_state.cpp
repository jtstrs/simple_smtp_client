#include "data_init_state.h"
#include "error_state.h"
#include "fill_data_state.h"

std::unique_ptr<SmtpState> DataInitState::handleTransition(Poco::Net::StreamSocket &socket,
                                                           const Message &messageData) {
    constexpr char const *DATA_INIT_STATE_MESSAGE = "DATA";

    std::stringstream dataInitMessageBuilder;
    dataInitMessageBuilder << DATA_INIT_STATE_MESSAGE;
    const auto status = baseStateHandler(socket,
                                         dataInitMessageBuilder.str(),
                                         ResponseCode::StartMessageInput);

    if (status != StateHandlingStatus::Ok) {
        return std::make_unique<ErrorState>(status);
    }

    return std::make_unique<FillDataState>();
}