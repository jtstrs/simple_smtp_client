#include "smtp_client_application.h"
#include "message.h"
#include "smtp_client.h"
#include <Poco/Util/Application.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/OptionSet.h>
#include <charconv>
#include <iostream>
#include <memory>
#include <stdexcept>


constexpr char const *g_addr = "addr";
constexpr char const *g_port = "port";
constexpr char const *g_domain = "domain";

SmtpClientApplication::SmtpClientApplication() : m_helpRequested(false), m_client(nullptr) {
}


void SmtpClientApplication::initialize(Poco::Util::Application &self) {
    Poco::Util::Application::initialize(self);
}

void SmtpClientApplication::uninitialize() {
    Poco::Util::Application::uninitialize();
}

int32_t SmtpClientApplication::main(const std::vector<std::string> &args) {
    if (m_helpRequested) {
        return 0;
    }

    const std::string address = config().getString(g_addr);
    const int32_t port = config().getInt32(g_port);

    Message smtpMessage;
    smtpMessage.domain = config().getString(g_domain);

    m_client = std::make_unique<SmtpClient>(address, port);
    m_client->sendMessage(smtpMessage);
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
                    .required(true)
                    .repeatable(false)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleAddrOpt)));

    options.addOption(
            Poco::Util::Option("port", "p", "Remote host port")
                    .required(true)
                    .repeatable(false)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handlePortOpt)));

    options.addOption(
            Poco::Util::Option("domain", "d", "Mail server domain")
                    .required(true)
                    .repeatable(false)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleDomainOpt)));
}

void SmtpClientApplication::handleHelp(const std::string &key, const std::string &value) {
    m_helpRequested = true;
    displayHelp();
    stopOptionsProcessing();
}

void SmtpClientApplication::handleAddrOpt(const std::string &key, const std::string &value) {
    config().setString(g_addr, value);
}

void SmtpClientApplication::handlePortOpt(const std::string &key, const std::string &value) {
    int32_t portVal = 0;
    std::from_chars(value.c_str(), value.c_str() + value.size(), portVal);
    if (portVal == 0) {
        throw std::runtime_error("Bad port value");
    }
    config().setInt32(g_port, portVal);
}

void SmtpClientApplication::handleDomainOpt(const std::string &key, const std::string &value) {
    std::cout << "Domain opt: " << value << std::endl;
    config().setString(g_domain, value);
}

void SmtpClientApplication::displayHelp() {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setHeader("Simple smtp client application");
    helpFormatter.format(std::cout);
}

SmtpClientApplication::~SmtpClientApplication() {
}
