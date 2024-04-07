#include "smtp_client_application.h"
#include <Poco/Util/Application.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/OptionSet.h>
#include <charconv>
#include <ios>
#include <iostream>


constexpr char const *g_addr = "addr";
constexpr char const *g_port = "port";

void SmtpClientApplication::initialize(Poco::Util::Application &self) {
    Poco::Util::Application::initialize(self);
}

void SmtpClientApplication::uninitialize() {
    Poco::Util::Application::uninitialize();
}

int32_t SmtpClientApplication::main(const std::vector<std::string> &args) {
    std::cout << std::boolalpha << "Port is provided: " << config().hasOption("port") << std::endl;
    std::cout << std::boolalpha << "Host is provided: " << config().hasOption("addr") << std::endl;

    std::cout << config().getInt32("port") << std::endl;
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
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleAddrOpt)));

    options.addOption(
            Poco::Util::Option("port", "p", "Remote host port")
                    .required(false)
                    .repeatable(false)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handlePortOpt)));
}

void SmtpClientApplication::handleHelp(const std::string &key, const std::string &value) {
    displayHelp();
    stopOptionsProcessing();
}

void SmtpClientApplication::handleAddrOpt(const std::string &key, const std::string &value) {
    config().setString(g_addr, value);
}

void SmtpClientApplication::handlePortOpt(const std::string &key, const std::string &value) {
    int32_t portVal = 0;
    std::from_chars(value.c_str(), value.c_str() + value.size(), portVal);
    config().setInt32(g_port, portVal);
}

void SmtpClientApplication::displayHelp() {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setHeader("Simple smtp cleint applicaiton");
    helpFormatter.format(std::cout);
}

SmtpClientApplication::~SmtpClientApplication() {
}
