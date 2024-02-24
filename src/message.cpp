#include "message.h"
#include <sstream>
#include <string>

Message Message::parse_message(std::istream &source) {
    Message out;

    std::getline(source, out.from);
    std::getline(source, out.to);
    std::getline(source, out.subject);

    std::stringstream body_builder;
    while (!source.eof()) {
        std::string tmp;
        std::getline(source, tmp);
        body_builder << std::move(tmp) << '\n';
    }
    out.body = body_builder.str();

    return out;
}