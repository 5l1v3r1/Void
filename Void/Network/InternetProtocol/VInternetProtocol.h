#pragma once
#ifndef _V_INTERNETPROTOCOL_H_
#define _V_INTERNETPROTOCOL_H_

#include <netinet/in.h>
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VInternetProtocol
    // Internet layer
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
        VIPv4Address(const VIPv4Address& _address);
        ~VIPv4Address();
        
        //----------------------------------------------------------------------------------------------------
        unsigned int IPUInt() const;
        std::string IPString() const;
        short Port() const;
        
    protected:
        //----------------------------------------------------------------------------------------------------
        
        
    protected:
        //----------------------------------------------------------------------------------------------------
        struct sockaddr_in mAddress;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VInternetProtocolTest();
}

#endif
