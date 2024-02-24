#ifndef CLI_PARSER
#define CLI_PARSER

#include <istream>
#include <string>

struct Message {
    std::string from;
    std::string subject;
    std::string to;
    std::string body;

    static Message parse_message(std::istream &source);
};


#endif