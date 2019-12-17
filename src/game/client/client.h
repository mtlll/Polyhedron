#pragma once
#include "shared/cube.h"

#include "game/game.h"
#include "game/server/server.h"

#include "shared/networking/network.h"
#include "shared/networking/cl_sv.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"

namespace game
{
    namespace client
    {
        // Connection.
        extern void GameConnect(bool _remote);
        extern void GameDisconnect(bool cleanup);

        // Messaging.
        extern bool AddMessage(game::networking::protocol::NetClientMessage type, const char *fmt, ...);

        // Map.
        extern void ChangeMap(const char *name);
        extern void ForceEdit(const char *name);
        extern void SendClientPacket(ENetPacket *packet, int chan);
    } // namespace client
} // namespace game