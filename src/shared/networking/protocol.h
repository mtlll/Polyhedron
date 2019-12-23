#pragma once

#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/cl_sv.h"

namespace shared {
    namespace network {
        namespace protocol {
            //
            // Disconnect message types (reasons for having been dIsConnected).
            //
            enum class DisconnectReason : int {
                Default = 0,
                EndOfPacket,
                Local,
                Kick,
                MessageError,
                IPBan,
                Private,
                MaximumClients,
                TimeOut,
                Password
            };

            //
            // DIsConnectedToStringMapper, for mapping 
            //
            const std::map<DisconnectReason, std::string> DisConnectedToStringMapper {
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
            // Enum class copy MasterMode flags. Open to join, password, vote, locked etc.
            //
            enum struct MasterMode : int {
                Authorize = 0,
                Open,
                Veto,
                Locked,
                Private,
                Password,
                Start = Authorize,
                Invalid = Start - 1
            };

            //
            // Enum Class copy of GameMode flags.
            //            
            enum struct GameMode : int {
                Team       = 1<<0,
                Ctf        = 1<<1,
                OverTime   = 1<<2,
                Edit       = 1<<3,
                Demo       = 1<<4,
                Local      = 1<<5,
                Lobby      = 1<<6,
                Rail       = 1<<7,
                Pulse      = 1<<8
            };
            
            //
            // Console message types
            //
            enum class ConsoleMessage : short
            {
                Chat            = 1<<8,
                TeamChat        = 1<<9,
                GameInfo        = 1<<10,
                FraggedSelf     = 1<<11,
                FraggedOther    = 1<<12,
                TeamKill        = 1<<13
            };

            //
            // This enum is used for client to server message types.
            //
            enum struct ClientMessage : int {
                Connect = 1,
                Disconnect,
                Ping,

                Say,
                TeamSay,
                ExecSay,

                SwitchName,

                // Maximum of network client messages.
                MaxNetClientMsg
            };

            //
            // A class enum copy of the old default priviliges
            //
            enum struct Priviliges : int { 
                None = 0, 
                Master,
                Auth,
                Admin
            };

            //
            // A class enum copy of the old default network message codes.
            // Network messages codes, c2s, c2c, s2c)
            //
            enum struct Messages : int
            {
                Connect = 0, ServerInfo, Welcome, InitClient, Position, Text, Sound, ClientDisconnect,
                Shoot, Explode, Suicide,
                Died, Damage, HitPush, ShotFX, ExplodeFX,
                TrySpawn, SpawnState, Spawn, ForceDeath,
                GunSelect, Taunt,
                MapChange, MapVote, TeamInfo, ItemSpawn, ItemPickup, ItemAcc, Teleport, JumpPad,
                Ping, Pong, ClientPing,
                TimeUp, ForceIntermission,
                ServerMessage, ItemList, Resume,
                EditMode, EditEntity, EditF, EditT, EditM, Flip, Copy, Paste, Rotate, Replace, DeleteCube, CalculateLight, Remip, EditVSlot, Undo, Redo, NewMap, GetMap, SendMap, ClipBoard, EditVar,
                MasterMode, Kick, ClearBans, CurrentMaster, Spectator, SetMaster, SetTeam,
                ListDemos, SendDemoList, GetDemo, SendDemo,
                DemoPlayback, RecordDemo, StopDemo, ClearDemos,
                TakeFlag, ReturnFlag, ResetFlag, TryDropFlag, DropFlag, ScoreFlag, InitFlags,
                SayTeam,
                Client,
                AuthTry, AuthKick, AuthChallenge, AuthAnswer, RequireAuth,
                PauseGame, GameSpeed,
                AddBot, DeleteBot, InitializeAI, FromAI, BotLimit, BotBalance,
                MapCRC, CheckMaps,
                SwitchName, SwitchModel, SwitchColor, SwitchTeam,
                ServerCommand,
                DemoPacket,
                NumberOfMessages
            };
            
            // Message size value.
            typedef std::pair<shared::network::protocol::Messages, int> MessageSize;
            typedef std::vector<MessageSize> MessageSizes;

            // Structure with a comparison function for messageSizes set array.
            struct messageSizesCmp {
                bool operator() (shared::network::protocol::Messages a, shared::network::protocol::Messages b) { return static_cast<int>(a) < static_cast<int>(b); }
            };
            static const std::vector<MessageSize> messageSizes = {                // size inclusive message token, 0 for variable or not-checked sizes
            
                // Basic connect, welcome, position, text, disconnect sizes.
                MessageSize{shared::network::protocol::Messages::Connect, 0},
                MessageSize{shared::network::protocol::Messages::ServerInfo, 0},MessageSize{shared::network::protocol::Messages::Welcome, 1}, 
                MessageSize{shared::network::protocol::Messages::InitClient, 0}, MessageSize{shared::network::protocol::Messages::Position, 0}, 
                MessageSize{shared::network::protocol::Messages::Text, 0}, MessageSize{shared::network::protocol::Messages::Sound, 2}, 
                MessageSize{shared::network::protocol::Messages::ClientDisconnect, 2},
                MessageSize{shared::network::protocol::Messages::Shoot, 0}, MessageSize{shared::network::protocol::Messages::Explode, 0}, 
                MessageSize{shared::network::protocol::Messages::Suicide, 1}, MessageSize{shared::network::protocol::Messages::Died, 5},
                // Health status and FX message sizes.
                MessageSize{shared::network::protocol::Messages::Damage, 5}, MessageSize{shared::network::protocol::Messages::HitPush, 7}, 
                MessageSize{shared::network::protocol::Messages::ShotFX, 10}, MessageSize{shared::network::protocol::Messages::ExplodeFX, 4},
                // Spawn and death message sizes.
                MessageSize{shared::network::protocol::Messages::TrySpawn, 1}, MessageSize{shared::network::protocol::Messages::SpawnState, 8}, MessageSize{shared::network::protocol::Messages::Spawn, 3},
                MessageSize{shared::network::protocol::Messages::ForceDeath, 2},
                // Gunselect, taunt, item team and map message sizes.
                MessageSize{shared::network::protocol::Messages::GunSelect, 2}, MessageSize{shared::network::protocol::Messages::Taunt, 1},
                MessageSize{shared::network::protocol::Messages::MapChange, 0}, MessageSize{shared::network::protocol::Messages::MapVote, 0}, 
                MessageSize{shared::network::protocol::Messages::TeamInfo, 0}, MessageSize{shared::network::protocol::Messages::ItemSpawn, 2},
                MessageSize{shared::network::protocol::Messages::ItemPickup, 2}, MessageSize{shared::network::protocol::Messages::ItemAcc, 3},              
                // Ping pong server pause continue etc message sizes.
                MessageSize{shared::network::protocol::Messages::Ping, 2}, MessageSize{shared::network::protocol::Messages::Pong, 2}, MessageSize{shared::network::protocol::Messages::ClientPing, 2},
                MessageSize{shared::network::protocol::Messages::TimeUp, 2}, MessageSize{shared::network::protocol::Messages::ForceIntermission, 1},
                MessageSize{shared::network::protocol::Messages::ServerMessage, 0}, MessageSize{shared::network::protocol::Messages::ItemList, 0}, MessageSize{shared::network::protocol::Messages::Resume, 0},
                // Edit mode message sizes.
                MessageSize{shared::network::protocol::Messages::EditMode, 2}, MessageSize{shared::network::protocol::Messages::EditEntity, 11}, 
                MessageSize{shared::network::protocol::Messages::EditF, 16}, MessageSize{shared::network::protocol::Messages::EditT, 16}, 
                MessageSize{shared::network::protocol::Messages::EditM, 16}, MessageSize{shared::network::protocol::Messages::Flip, 14}, MessageSize{shared::network::protocol::Messages::Copy, 14}, 
                MessageSize{shared::network::protocol::Messages::Paste, 14}, MessageSize{shared::network::protocol::Messages::Rotate, 15}, {Messages::Replace, 17}, 
                MessageSize{shared::network::protocol::Messages::DeleteCube, 14}, MessageSize{shared::network::protocol::Messages::CalculateLight, 1}, MessageSize{shared::network::protocol::Messages::Remip, 1}, MessageSize{shared::network::protocol::Messages::EditVSlot, 16}, 
                MessageSize{shared::network::protocol::Messages::Undo, 0}, MessageSize{shared::network::protocol::Messages::Redo, 0}, MessageSize{shared::network::protocol::Messages::NewMap, 2}, 
                MessageSize{shared::network::protocol::Messages::GetMap, 1}, MessageSize{shared::network::protocol::Messages::SendMap, 0}, 
                MessageSize{shared::network::protocol::Messages::EditVar, 0},
                // WatIsDeze: TODO: MasterMode conflicts, had to prepend a _
                MessageSize{shared::network::protocol::Messages::MasterMode, 2}, MessageSize{shared::network::protocol::Messages::Kick, 0}, MessageSize{shared::network::protocol::Messages::ClearBans, 1}, MessageSize{shared::network::protocol::Messages::CurrentMaster, 0}, MessageSize{shared::network::protocol::Messages::Spectator, 3}, MessageSize{shared::network::protocol::Messages::SetMaster, 0}, MessageSize{shared::network::protocol::Messages::SetTeam, 0},
                // Demo mode related sizes.
                MessageSize{shared::network::protocol::Messages::ListDemos, 1}, MessageSize{shared::network::protocol::Messages::SendDemoList, 0}, MessageSize{shared::network::protocol::Messages::GetDemo, 2}, MessageSize{shared::network::protocol::Messages::SendDemo, 0},
                MessageSize{shared::network::protocol::Messages::DemoPlayback, 3}, MessageSize{shared::network::protocol::Messages::RecordDemo, 2}, MessageSize{shared::network::protocol::Messages::StopDemo, 1}, MessageSize{shared::network::protocol::Messages::ClearDemos, 2},
                // Capture the flag related sizes. (LOL, we dun have dat gamem000d)
                MessageSize{shared::network::protocol::Messages::TakeFlag, 3}, MessageSize{shared::network::protocol::Messages::ReturnFlag, 4}, MessageSize{shared::network::protocol::Messages::ResetFlag, 3}, MessageSize{shared::network::protocol::Messages::TryDropFlag, 1}, MessageSize{shared::network::protocol::Messages::DropFlag, 7}, MessageSize{shared::network::protocol::Messages::ScoreFlag, 9}, MessageSize{shared::network::protocol::Messages::InitFlags, 0},
                // Client related sizes?Messages
                MessageSize{shared::network::protocol::Messages::SayTeam, 0},
                MessageSize{shared::network::protocol::Messages::Client, 0},
                // Authorisation message sizes.
                MessageSize{shared::network::protocol::Messages::AuthTry, 0}, MessageSize{shared::network::protocol::Messages::AuthKick, 0}, MessageSize{shared::network::protocol::Messages::AuthChallenge, 0}, MessageSize{shared::network::protocol::Messages::AuthAnswer, 0}, MessageSize{shared::network::protocol::Messages::RequireAuth, 0},
                // Game speed/pause sizes.
                MessageSize{shared::network::protocol::Messages::PauseGame, 0}, MessageSize{shared::network::protocol::Messages::GameSpeed, 0},
                // Bot/AI message sizes
                MessageSize{shared::network::protocol::Messages::AddBot, 2}, MessageSize{shared::network::protocol::Messages::DeleteBot, 1}, MessageSize{shared::network::protocol::Messages::InitializeAI, 0}, MessageSize{shared::network::protocol::Messages::FromAI, 2}, MessageSize{shared::network::protocol::Messages::BotLimit, 2}, MessageSize{shared::network::protocol::Messages::BotBalance, 2},
                // Other message sizes.
                MessageSize{shared::network::protocol::Messages::MapCRC, 0}, MessageSize{shared::network::protocol::Messages::CheckMaps, 1},
                // Switch command related sizes.
                MessageSize{shared::network::protocol::Messages::SwitchName, 0}, MessageSize{shared::network::protocol::Messages::SwitchModel, 2}, MessageSize{shared::network::protocol::Messages::SwitchColor, 2}, MessageSize{shared::network::protocol::Messages::SwitchTeam, 2},
                // Server and Demo Packet related sizes.
                MessageSize{shared::network::protocol::Messages::ServerCommand, 0},
                MessageSize{shared::network::protocol::Messages::DemoPacket, 0},
                // // Or invalid, -1
                // MessageSize{shared::network::protocol::Messages::NumberOfMessages, -1}
            };

            //
            // Return -1 in case the willing to send message happens to be invalid.
            //
            extern int MessageSizeLookup(const shared::network::protocol::Messages &message);
        };
    };
};