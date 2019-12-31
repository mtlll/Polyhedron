#pragma once

namespace engine {
    namespace client {
        bool Multiplayer(bool msg);
        
        void SetRate(int rate);
        void Throttle();

        bool IsConnected(bool attempt, bool local);
        const ENetAddress *ConnectedPeer();
        void ConnectedIP();
        void ConnectedPort();

        void AbortConnect();
        void connectserv(const char *servername, int serverport, const char *serverpassword);
        void Reconnect(const char *serverpassword);
        void Disconnect(bool async, bool cleanup);
        void TryDisconnect(bool local);
        void LanConnect(int *port, char *pw);
        
        void SendClientPacket(ENetPacket *packet, int chan);
        void LocalServerToClient(int chan, ENetPacket *packet);

        void ClientKeepAlive();
        void FlushClient();
        void GetS2C();

        void NetError(const char *s, bool disc);
    };
};