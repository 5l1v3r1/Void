#pragma once
#ifndef _V_NETWORKADDRESS_H_
#define _V_NETWORKADDRESS_H_

#include <netinet/in.h>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VNetworkAddress
    //----------------------------------------------------------------------------------------------------
    
    // VIPv4Address
    // 32-bit
    //----------------------------------------------------------------------------------------------------
    class VIPv4Address
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VIPv4Address();
        VIPv4Address(const std::string& _host, short _port=0);
        VIPv4Address(short _port);
        VIPv4Address(const VIPv4Address& _address);
        ~VIPv4Address();
        
        //----------------------------------------------------------------------------------------------------
        bool IsValid() const;
        unsigned int IP() const;
        std::string IPString() const;
        short Port() const;
        sockaddr_in& Address();
        const sockaddr_in& Address() const;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
        
    protected:
        //----------------------------------------------------------------------------------------------------
        struct sockaddr_in mAddress;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VNetworkAddressTest();
}

#endif
