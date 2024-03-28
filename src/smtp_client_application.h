#ifndef APPLICATION_H
#define APPLICATION_H

#include "Poco/Util/Application.h"
#include <Poco/Util/OptionSet.h>

class SmtpClientApplication : public Poco::Util::Application {
public:
    void initialize(Application &self) override;
    void uninitialize() override;
    int32_t main(const std::vector<std::string> &args) override;
    void defineOptions(Poco::Util::OptionSet &options) override;
    void handleHelp(const std::string &name, const std::string &value);

    ~SmtpClientApplication() override;
};

#endif