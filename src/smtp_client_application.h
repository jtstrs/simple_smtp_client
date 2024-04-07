#ifndef APPLICATION_H
#define APPLICATION_H

#include "Poco/Util/Application.h"
#include <Poco/Util/OptionSet.h>

class SmtpClientApplication : public Poco::Util::Application {
public:
    ~SmtpClientApplication() override;

private:
    void initialize(Application &self) override;
    void uninitialize() override;
    int32_t main(const std::vector<std::string> &args) override;
    void defineOptions(Poco::Util::OptionSet &options) override;

    void displayHelp();

    // Cli opt handlers
    void handleHelp(const std::string &key, const std::string &value);
    void handleAddrOpt(const std::string &key, const std::string &value);
    void handlePortOpt(const std::string &key, const std::string &value);
};

#endif