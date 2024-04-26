#include "smtp_client_application.h"
#include <Poco/Util/OptionException.h>

int32_t main(int32_t argc, char *argv[]) {
    SmtpClientApplication app;
    try {
        app.init(argc, argv);
        app.run();
    } catch (Poco::Util::MissingOptionException &exception) {
        std::cerr << "[" << exception.what() << "] " << exception.message() << std::endl;
    } catch (Poco::Util::OptionException &exception) {
        std::cerr << "[" << exception.what() << "] " << exception.message() << std::endl;
    }
    return 0;
}