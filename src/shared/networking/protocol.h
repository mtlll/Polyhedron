#pragma once
namespace game {
    namespace networking {
        
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
            enum NetClientMessage : int {
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
            // A class enum copy of the old default network events
            //
            enum struct Events : int
            {
                Connect = 0, ServerInfo, Welcome, InitClient, Position, Text, Sound, ClientDisconnect,
                Shoot, Explode, Suicide,
                Died, TrySpawn, SpawnState, Spawn, ForceDeath,
                GunSelect, Taunt,
                MapChange, MapVote, TeamInfo, ItemSpawn, ItemPickup, ItemAcc, Teleport, JumpPad,
                Ping, Pong, ClientPing,
                TimeUp, ForceIntermission,
                ServerMessage, ItemList, Resume,
                EditMode, EditEnt, EditF, EditT, EditM, Flip, Copy, Paste, Rotate, Replace, DeleteCube, CalculateLight, Remip, EditVSlot, Undo, Redo, NewMap, GetMap, SendMap, ClipBoard, EditVar,
                MasterMode, Kick, ClearBans, CurrentMaster, Spectator, SetMaster, SetTeam,
                ListDemos, SendDemoList, GetDemo, SendDemo,
                DemoPlayback, RecordDemo, StopDemo, ClearDemos,
                TakeFlag, ReturnFlag, ResetFlag, TryDropFlag, DropFlag, ScoreFLag, InitFlags,
                SayTeam,
                Client,
                AuthTry, AuthKick, AuthChallenge, AuthAnswer, RequireAuth,
                PauseGame, GameSpeed,
                AddBot, DeleteBot, InitializeAI, FromAI, BotLimit, BotBalance,
                MapCRC, CheckMaps,
                SwitchName, SwitchModel, SwitchColor, SwitchTeam,
                ServerCommand,
                DemoPacket,
                NUMMSG
            };
        };
    };
};