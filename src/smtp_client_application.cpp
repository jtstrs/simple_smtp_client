#include "smtp_client_application.h"
#include "logger_wrapper.h"
#include "message.h"
#include "smtp_client.h"
#include "validators/file_exists_validator.h"
#include "validators/port_option_validator.h"
#include <Poco/Logger.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/OptionSet.h>
#include <bits/getopt_core.h>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <stdexcept>

#define LOG_MODULE "SMTP CLIENT APPLICATION"

constexpr char const *g_log_lvl = "log_lvl";
constexpr char const *g_addr = "addr";
constexpr char const *g_port = "port";
constexpr char const *g_domain = "domain";
constexpr char const *g_msg_file = "msg_file";
constexpr int32_t defaultLogLevel = Poco::Message::Priority::PRIO_FATAL;

SmtpClientApplication::SmtpClientApplication() : m_helpRequested(false), m_client(nullptr) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    setUnixOptions(false);
#else
    setUnixOptions(true);
#endif
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

    const int32_t requestedLogLevel = [&]() {
        if (config().has(g_log_lvl)) {
            return config().getInt32(g_log_lvl);
        }
        return defaultLogLevel;
    }();
    logger().setLevel(requestedLogLevel);

    Message smtpMessage;
    if (config().has(g_msg_file)) {
        std::fstream messageSource(config().getString(g_msg_file), std::ios_base::in);
        smtpMessage = Message::parse_message(messageSource);
    } else {
        throw std::runtime_error("Manual input not implemented yet. Please provide the file");
    }

    const std::string address = config().getString(g_addr);
    const int32_t port = config().getInt32(g_port);
    smtpMessage.domain = config().getString(g_domain);

    LOG_FMT_MESSAGE("Created message to send:\n%s", smtpMessage.toString());
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
                    .argument("addr", true)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleAddrOpt)));

    options.addOption(
            Poco::Util::Option("port", "p", "Remote host port")
                    .required(true)
                    .repeatable(false)
                    // Poco takes ownership of validator
                    .validator(new PortOptionValidator)
                    .argument("port", true)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handlePortOpt)));

    options.addOption(
            Poco::Util::Option("domain", "d", "Mail server domain")
                    .required(true)
                    .repeatable(false)
                    .argument("domain", true)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleDomainOpt)));

    options.addOption(
            Poco::Util::Option("l_level", "l", "Log level")
                    .required(false)
                    .repeatable(false)
                    .argument("l_level", true)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleLogLevel)));

    options.addOption(
            Poco::Util::Option("msg_file", "f", "File which contains smtp message data")
                    .required(false)
                    .repeatable(false)
                    .validator(new FileExistsValidator)
                    .argument("msg_file", true)
                    .callback(Poco::Util::OptionCallback<SmtpClientApplication>(this, &SmtpClientApplication::handleMessageFileOpt)));
}

void SmtpClientApplication::handleLogLevel(const std::string &key, const std::string &value) {
    int32_t parsedLevel = defaultLogLevel;
    if (!value.empty()) {
        std::from_chars(value.c_str(), value.c_str() + value.size(), parsedLevel);
        config().setInt32(g_log_lvl, parsedLevel);
    } else {
        config().setInt32(g_log_lvl, defaultLogLevel);
    }
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
    int32_t parsedPort = 0;
    std::from_chars(value.c_str(), value.c_str() + value.size(), parsedPort);
    config().setInt32(g_port, parsedPort);
}

void SmtpClientApplication::handleDomainOpt(const std::string &key, const std::string &value) {
    config().setString(g_domain, value);
}

void SmtpClientApplication::handleMessageFileOpt(const std::string &key, const std::string &value) {
    config().setString(g_msg_file, value);
}

void SmtpClientApplication::displayHelp() {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setHeader("Simple smtp client application");
    helpFormatter.format(std::cout);
}

SmtpClientApplication::~SmtpClientApplication() {
}
