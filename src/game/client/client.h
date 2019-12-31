#pragma once

#include "shared/cube.h"

#include "shared/utils/stream.h"
#include "shared/networking/cl_frametimestate.h"
#include "shared/networking/protocol.h"
#include "shared/entities/coreentity.h"

namespace game {
    namespace client {
        // Send/Write...
        extern void SendMapInfo();
        extern void WriteClientInfo(stream *f);
        
        // Names
        extern const char *GenerateClientColorName(entities::classes::BaseEntity *ce, const std::string &name);
        extern void ClientColorName(const char *name);
        extern void SwitchName(const char *name);
        extern void PrintName();

        // Messages
        bool AddMessages(shared::network::protocol::Messages type, const char * fmt = NULL, ...);
    }; // client
}; // game