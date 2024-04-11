#include "message.h"
#include "smtp_client_application.h"
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>

int32_t main(int32_t argc, char *argv[]) {

    SmtpClientApplication app;
    app.init(argc, argv);
    return app.run();
}