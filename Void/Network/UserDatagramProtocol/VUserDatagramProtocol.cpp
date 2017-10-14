#include "VUserDatagramProtocol.h"
#include <unistd.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VUDPServer
    //----------------------------------------------------------------------------------------------------
    VUDPServer::VUDPServer()
        :
        VSocket()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VUDPServer::VUDPServer(const VUDPServer& _server)
        :
        VSocket(_server)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VUDPServer::~VUDPServer()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VUDPServer::Bind(const VIPv4Address& _address)
    {
        mAddress = _address;
        mFileDescriptor = ::socket(AF_INET, SOCK_DGRAM, 0);
        VSocket::SetNonBlock(true);
        int result = ::bind(mFileDescriptor, (struct sockaddr*)&mAddress.Address(), sizeof(struct sockaddr));
        if (result)
        {
            ::close(mFileDescriptor);
            return false;
        }
        return true;
    }
    
    // VUDPClient
    //----------------------------------------------------------------------------------------------------
    VUDPClient::VUDPClient()
        :
        VSocket()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VUDPClient::VUDPClient(const VUDPClient& _client)
        :
        VSocket(_client)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VUDPClient::~VUDPClient()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VUDPClient::Connect(const VIPv4Address& _address)
    {
        mAddress = _address;
        mFileDescriptor = ::socket(AF_INET, SOCK_DGRAM, 0);
        VSocket::SetNonBlock(true);
        int result = ::connect(mFileDescriptor, (struct sockaddr*)&mAddress.Address(), sizeof(struct sockaddr));
        if (result)
        {
            ::close(mFileDescriptor);
            return false;
        }
        return true;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VUserDatagramProtocolTest()
    {
        
        return;
    }
    
}
