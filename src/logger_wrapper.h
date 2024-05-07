#ifndef LOGGER_WRAPPER
#define LOGGER_WRAPPER

#include <Poco/Logger.h>
#include <format>

static Poco::Logger &getGlobalLogger() {
    constexpr char const *GLOBAL_LOGGER_TAG = "GLOBAL";
    static Poco::Logger &globalLogger = Poco::Logger::get(GLOBAL_LOGGER_TAG);
    return globalLogger;
}

template<typename Logger>
class ScopeLogger {
public:
    explicit ScopeLogger(const std::string &moduleName,
                         const std::string &funcName,
                         Logger &logger) : m_moduleName(moduleName),
                                           m_funcName(funcName),
                                           m_logger(logger) {
        logger.information("[%s] Enter %s", m_moduleName, m_funcName);
    }

    ~ScopeLogger() {
        m_logger.information("[%s] Exit %s", m_moduleName, m_funcName);
    }

private:
    Logger &m_logger;
    std::string m_funcName;
    std::string m_moduleName;
};

#define LOG_FUNC auto SCOPE_LOGGER = ScopeLogger(LOG_MODULE, __FUNCTION__, getGlobalLogger());

template<typename... Args>
void logMessage(const std::string &module,
                const std::string &function,
                const std::string &msg,
                int32_t line,
                Args... args) {
    std::string messageFormat = std::format("[Line: {}][{}][{}] {}", line,
                                            module, function, msg);
    if constexpr (sizeof...(Args) <= 0) {
        getGlobalLogger().information(messageFormat);
        return;
    }
    getGlobalLogger().information(messageFormat, args...);
}

#define LOG_MESSAGE(msg) logMessage(LOG_MODULE, __FUNCTION__, msg, __LINE__);
#define LOG_FMT_MESSAGE(fmt, args...) logMessage(LOG_MODULE, __FUNCTION__, fmt, __LINE__, args);


#endif