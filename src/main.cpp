#include <Poco/Net/DNS.h>
#include <Poco/Net/HostEntry.h>
#include <Poco/Net/IPAddress.h>
#include <cstdint>
#include <iostream>

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

int32_t main(int32_t argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Too low arguments count" << std::endl;
        return 0;
    }

    std::cout << "Resolving: " << argv[1] << std::endl;

    const Poco::Net::HostEntry &entry = Poco::Net::DNS::hostByName(argv[1]);
    const Poco::Net::HostEntry::AddressList &addresses = entry.addresses();

    Poco::Net::IPAddress ipv4Address;
    for (auto address : addresses) {
        std::cout << address.toString() << std::endl;
        if (address.isIPv4Mapped()) {
            ipv4Address = address;
        }
    }

    // Port for establishing tls connection
    const uint16_t smtpPort = 5555;

    Poco::Net::SocketAddress socketAddress(ipv4Address, smtpPort);

    std::cout << "Trying connect to address: " << socketAddress.toString() << std::endl;

    Poco::Net::StreamSocket socket(socketAddress);

    constexpr int32_t bufferSize = 256;
    char messageBuffer[bufferSize];
    memset(messageBuffer, 0, bufferSize);

    return 0;
}