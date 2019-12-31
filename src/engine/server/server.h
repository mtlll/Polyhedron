#pragma once

namespace engine {
    // Server.
    namespace server {
        SVAR(serverauth, "");
        
        void InitServer(bool listen, bool dedicated);
        void ServerSlice(bool dedicated, uint timeout);
        void UpdateTime();
        void CleanupServer();


        void *GetClientInfo(int i);
        ENetPeer *GetClientPeer(int i);

        ENetPacket *Sendf(int cn, int chan, const char *format, ...);
        ENetPacket *SendFile(int cn, int chan, stream *file, const char *format, ...);
        void SendPacket(int cn, int chan, ENetPacket *packet, int exclude = -1);

        int GetServerMTU();
        int GetNumClients();
        uint GetClientIP(int n);

        void LocalConnect();
        void LocalDisconnect();
        
        const char *DisconnectReason(shared::network::protocol::DisconnectReason reason);
        
        void Disconnect_Client(int n, int reason);
        void KickNonLocalClients(shared::network::protocol::DisconnectReason reason = shared::network::protocol::DisconnectReason::Default);
        bool HasNonLocalClients();
        bool HasLocalClients();

        void SendServerInfoReply(ucharbuf &p);
        
        void FlushServer(bool force = false);
        void FlushMasterOutput();
        bool RequestMaster(const char *req);
        bool RequestMasterf(const char *fmt, ...) PRINTFARGS(1, 2);
        bool IsDedicatedServer();

    }; // server
}; // engine