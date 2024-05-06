#include "quit_state.h"
#include "../logger_wrapper.h"
#include "end_state.h"
#include "error_state.h"

#define LOG_MODULE "QUIT STATE"

std::unique_ptr<SmtpState> QuitState::handleTransition(Poco::Net::StreamSocket &socket,
                                                       const Message &messageData) {
    LOG_FUNC

    constexpr char const *QUIT_STATE_MESSAGE = "QUIT";
    std::stringstream quitStateMessageBuilder;
    quitStateMessageBuilder << QUIT_STATE_MESSAGE;
    const auto status = baseStateHandler(socket,
                                         quitStateMessageBuilder.str(),
                                         ResponseCode::ServiceClosing);

    if (status != StateHandlingStatus::Ok) {
        return std::make_unique<ErrorState>(status);
    }

    return std::make_unique<EndState>();
}