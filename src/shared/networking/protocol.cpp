#include "cube.h"
#include "ents.h"

#include "game/game.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/protocol.h"


namespace game {
    namespace network {
        namespace protocol {
            //
            // Return -1 in case the willing to send message happens to be invalid.
            //
            int MessageSizeLookup(const shared::network::protocol::Messages &message);
            {
                // We already have one...
                static int sizetable[Messages::NumberOfMessages] = { -1 };
                if(sizetable[0] < 0)
                {
                    memset(sizetable, -1, sizeof(sizetable));
                    for(const int *p = MessageSizes; *p >= 0; p += 2) sizetable[p[0]] = p[1];
                }
                return message >= 0 && message < Messages::NumberOfMessages ? sizetable[message] : -1;
            }
        }; // protocol
    }; // network
}; // game