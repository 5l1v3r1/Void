#include "VNetworkAddress.h"
#include "../../Utility/Logger/VLogger.h"
#include <sstream>
#include <netdb.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VIPv4Address
    //----------------------------------------------------------------------------------------------------
    VIPv4Address::VIPv4Address()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VIPv4Address::VIPv4Address(const std::string& _host, short _port)
    {
        memset(&mAddress, 0, sizeof(mAddress));
        mAddress.sin_family = AF_INET;
        mAddress.sin_port = htons(_port);
        if (_host.size())
        {
            struct hostent* he = gethostbyname(_host.c_str());
            if (he && he->h_addrtype == AF_INET)
            {
                mAddress.sin_addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
            }
            else
            {
                mAddress.sin_addr.s_addr = INADDR_NONE; // Error
            }
        }
        else
        {
            mAddress.sin_addr.s_addr = INADDR_ANY;
        }
    }
    
    VIPv4Address::VIPv4Address(short _port)
        :
        VIPv4Address("", _port)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VIPv4Address::VIPv4Address(const VIPv4Address& _address)
    {
        memcpy(&mAddress, &_address.mAddress, sizeof(mAddress));
    }
    
    //----------------------------------------------------------------------------------------------------
    VIPv4Address::~VIPv4Address()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VIPv4Address::IsValid() const
    {
        return mAddress.sin_addr.s_addr != INADDR_NONE;
    }
    
    //----------------------------------------------------------------------------------------------------
    unsigned int VIPv4Address::IP() const
    {
        return ntohl(mAddress.sin_addr.s_addr);
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VIPv4Address::IPString() const
    {
        uint32_t ip = mAddress.sin_addr.s_addr;
        std::stringstream sstream;
        sstream << ((ip >> 0) & 0xff) << '.' << ((ip >> 8) & 0xff) << '.' << ((ip >> 16) & 0xff) << '.' << ((ip >> 24) & 0xff);
        return sstream.str();
    }
    
    //----------------------------------------------------------------------------------------------------
    short VIPv4Address::Port() const
    {
        return ntohs(mAddress.sin_port);
    }
    
    //----------------------------------------------------------------------------------------------------
    sockaddr_in& VIPv4Address::Address()
    {
        return mAddress;
    }
    
    //----------------------------------------------------------------------------------------------------
    const sockaddr_in& VIPv4Address::Address() const
    {
        return mAddress;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VNetworkAddressTest()
    {
        VIPv4Address address("127.0.0.1", 8080);
        VLogger::Info("Address: %s:%d", address.IPString().c_str(), address.Port());
        address = VIPv4Address("", 8080);
        VLogger::Info("Address: %s:%d", address.IPString().c_str(), address.Port());
        
        return;
    }
    
}
