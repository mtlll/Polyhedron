#pragma once

// Room for 8 clients by default.
#define DEFAULTCLIENTS 8

//
// ServerClient structure.
//
struct ServerClient                   // server side version of "dynent" type
{
    int type;
    int clientNumber;
    ENetPeer *peer;
    cubestr hostname;
    void *info;
};