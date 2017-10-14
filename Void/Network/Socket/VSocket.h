#pragma once
#ifndef _V_SOCKET_H_
#define _V_SOCKET_H_

#include "../NetworkAddress/VNetworkAddress.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSocket
    //----------------------------------------------------------------------------------------------------
    class VSocket
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VSocket();
        VSocket(const VSocket& _socket);
        virtual ~VSocket();
        
        //----------------------------------------------------------------------------------------------------
        bool SetNonBlock(bool _isNonBlock);
        bool SetReusePort(bool _isReusePort);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        VIPv4Address mAddress;
        int mFileDescriptor;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSocketTest();
}

#endif
