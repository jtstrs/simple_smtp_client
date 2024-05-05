#include "message.h"
#include <ostream>
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

std::string Message::toString() const {
    std::stringstream messageSerializer;
    dump(messageSerializer);
    return messageSerializer.str();
}

void Message::dump(std::ostream &os) const {
    os << "Server domain: " << domain << "\n"
       << "From: " << from << "\n"
       << "To: " << to << "\n"
       << "Subject: " << subject << "\n"
       << "Body: " << body << "\n";
}