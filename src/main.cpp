#include "message.h"
#include "smtp_client_application.h"
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>

void test_parse_message() {
    const std::string test_message_path = "../../resources/test_message";

    std::fstream message_source(test_message_path, std::ios_base::in);

    if (!message_source.is_open()) {
        throw std::runtime_error("Couldnt open file with test message");
    }

    std::cout << "Parse message from source" << std::endl;

    Message message = Message::parse_message(message_source);

    std::cout << std::format("From: {}\nTo: {}\nSubject: {}\nBody: {}\n",
                             message.from,
                             message.to,
                             message.subject,
                             message.body);
}

int32_t main(int32_t argc, char *argv[]) {
#ifdef TEST_ENABLE
    test_parse_message();
#endif
    SmtpClientApplication app;
    return app.run();
}