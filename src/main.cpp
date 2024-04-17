#include "smtp_client_application.h"

int32_t main(int32_t argc, char *argv[]) {

    SmtpClientApplication app;
    app.init(argc, argv);
    return app.run();
}