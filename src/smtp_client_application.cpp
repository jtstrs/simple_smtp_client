#include "smtp_client_application.h"
#include <Poco/Util/Application.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/OptionSet.h>
#include <iostream>

void SmtpClientApplication::initialize(Poco::Util::Application &self) {
    Poco::Util::Application::initialize(self);
}

void SmtpClientApplication::uninitialize() {
    Poco::Util::Application::uninitialize();
}

int32_t SmtpClientApplication::main(const std::vector<std::string> &args) {
    return 0;
}

void SmtpClientApplication::defineOptions(Poco::Util::OptionSet &options) {
    Poco::Util::Application::defineOptions(options);

    options.addOption(
            Poco::Util::Option("help", "h", "Display help information on command line arguments")
                    .required(false)
                    .repeatable(false)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleHelp)));

    options.addOption(
            Poco::Util::Option("addr", "a", "Remote host address")
                    .required(false)
                    .repeatable(false)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleCliOption)));

    options.addOption(
            Poco::Util::Option("port", "p", "Remote host port")
                    .required(false)
                    .repeatable(false)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleCliOption)));
}

void SmtpClientApplication::handleHelp(const std::string &name, const std::string &value) {
    displayHelp();
    stopOptionsProcessing();
}

void SmtpClientApplication::displayHelp() {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setHeader("Simple smtp cleint applicaiton");
    helpFormatter.format(std::cout);
}

SmtpClientApplication::~SmtpClientApplication() {
}
