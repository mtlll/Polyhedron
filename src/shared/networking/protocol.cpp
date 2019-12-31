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
            // The disconnection reasons to string map mapper.
            //
            DisconnectedToStringMapper {
                {DisconnectReason::Default, ""},
                {DisconnectReason::EndOfPacket, "End of Packet"},
                {DisconnectReason::Local, "The server is in Local Mode"},
                {DisconnectReason::Kick, "Kicked or Banned"},
                {DisconnectReason::MessageError, "Message Error"},
                {DisconnectReason::IPBan, "Your IP is banned"},
                {DisconnectReason::Private, "This server is in Private Mode"},
                {DisconnectReason::MaximumClients, "This server has reached the maximum amount of clients"},
                {DisconnectReason::TimeOut, "Connection timed out"},
                {DisconnectReason::Password, "Invalid Password"}
            };

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