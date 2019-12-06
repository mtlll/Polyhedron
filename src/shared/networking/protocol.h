#pragma once

//
// This enum is used for client to server message types.
//
enum class NetCLMsg : short {
    Connect = 1,
    Disconnect = 2,
    Ping = 3,

    Say,
    TeamSay,
    ExecSay,

    SwitchName,

    // Maximum of network client messages.
    MaxNetCLMsg
};