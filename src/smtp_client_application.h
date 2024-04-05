#ifndef APPLICATION_H
#define APPLICATION_H

#include "Poco/Util/Application.h"
#include <Poco/Util/OptionSet.h>
#include <type_traits>

class SmtpClientApplication : public Poco::Util::Application {
public:
    void initialize(Application &self) override;
    void uninitialize() override;
    int32_t main(const std::vector<std::string> &args) override;
    void defineOptions(Poco::Util::OptionSet &options) override;
    void handleHelp(const std::string &name, const std::string &value);

    ~SmtpClientApplication() override;

private:
    void displayHelp();

    template<typename T>
    void handleCliOption(const std::string &opt, T &optVal) {
        if constexpr (std::is_same_v<T, bool>) {
            config().setBool(opt, optVal);
        } else if constexpr (std::is_same_v<T, int32_t>) {
            config().setInt(opt, optVal);
        } else if constexpr (std::is_same_v<T, std::string>) {
            config().setString(opt, optVal);
        } else {
        }
    }
};

#endif