#include "cube.h"
#include "ents.h"

#include "game/game.h"
#include "game/server/server.h"
#include "game/client/client.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/protocol.h"

#include "shared/entities/animinfo.h"
#include "shared/entities/coreentity.h"
#include "shared/entities/baseentity.h"
#include "shared/entities/basephysicalentity.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/entities/basecliententity.h"

namespace game {
    namespace networking {
        // Is a name a duplicate?
        ServerGame serverGame;

        // Returns a coloured string of a name.
        const char *GenerateClientColorName(game::networking::ClientInfo *ci, const std::string &name) {
            if (!ci) {
                conoutfl(CON_WARN, "%s", "Invalid pointer reference to ClientInfo *ci: == NULL");
                return "invalid_ref";
            }

            static cubestr cname[3];
            static int colorIndex = 0;
            colorIndex = (colorIndex+1)%3;

            if(name.size() < 260) // Stay below CubeStr its max value.
                name = (name.empty() ? std::string(ci->name).substr(0, 32).c_str() : (std::string("unnamed_#") + std::to_str(cidx)).c_str()); // Personally I find 32 chars enough.

            if(name[0] && !DuplicateName(ci, name, && ci->state.aitype == AI_NONE) 
                return name.c_str();
            
            // Generate colour based on type of Client and client number.
            formatcubestr(cname[colorIndex], ci->state.aitype == AI_NONE ? "%s \fs\f5(%d)\fr" : "%s \fs\f5[%d]\fr", name.c_str(), ci->clientNumber);
            return cname[colorIndex];
        }
    };
};