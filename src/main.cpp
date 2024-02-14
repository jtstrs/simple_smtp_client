#include <Poco/Net/DNS.h>
#include <Poco/Net/HostEntry.h>
#include <Poco/Net/IPAddress.h>
#include <iostream>

using Poco::Net::DNS;
using Poco::Net::HostEntry;
using Poco::Net::IPAddress;

int32_t main(int32_t argc, char *argv[]) {
    const HostEntry &entry = DNS::hostByName("www.google.com");
    std::cout << "Canonical name: " << entry.name() << std::endl;

    const HostEntry::AliasList &aliases = entry.aliases();
    HostEntry::AliasList::const_iterator alias_it = aliases.begin();

    for (; alias_it != aliases.end(); ++alias_it) {
        std::cout << "Alias: " << *alias_it << std::endl;
    }

    const HostEntry::AddressList &addrs = entry.addresses();
    HostEntry::AddressList::const_iterator addr_it = addrs.begin();
    for (; addr_it != addrs.end(); ++addr_it) {
        std::cout << "Address: " << addr_it->toString() << std::endl;
    }

    return 0;
}