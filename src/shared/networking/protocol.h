#pragma once

namespace networking {
    namespace protocol {
        //
        // Console message types
        //
        enum
        {
            CON_CHAT       = 1<<8,
            CON_TEAMCHAT   = 1<<9,
            CON_GAMEINFO   = 1<<10,
            CON_FRAG_SELF  = 1<<11,
            CON_FRAG_OTHER = 1<<12,
            CON_TEAMKILL   = 1<<13
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
