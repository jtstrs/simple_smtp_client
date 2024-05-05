#ifndef CLI_PARSER
#define CLI_PARSER

#include <istream>
#include <ostream>
#include <string>

struct Message {
    std::string domain;
    std::string from;
    std::string subject;
    std::string to;
    std::string body;

    static Message parse_message(std::istream &source);

    std::string toString() const;
    void dump(std::ostream &os) const;
};


#endif