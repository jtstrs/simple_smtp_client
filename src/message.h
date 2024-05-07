#ifndef CLI_PARSER
#define CLI_PARSER

#include <istream>
#include <ostream>
#include <string>
#include <vector>

struct Message {
    // This field mostly ignor in modern SMTP servers
    std::string fromDomain;
    std::string fromAddress;
    std::string subject;
    std::vector<std::string> destinationAddresses;
    std::string messageBody;

    static Message parse_message(std::istream &source);

    std::string toString() const;
    void dump(std::ostream &os) const;
};


#endif