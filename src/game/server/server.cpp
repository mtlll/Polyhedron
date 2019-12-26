#include "engine/engine.h"

#include "game/game.h"

#include "shared/networking/protocol.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/cl_sv.h"

#include "game/client/client.h"
#include "game/server/server.h"


// This file only servers as an attempt at a server implementation.
namespace server
{
    // Our list of server clients.
    ServerClients svClients;

	//
	// Unwillingly, who cares for demos, some do... But one thing is true
	// they'll at least allow me to test shit.
	//
    struct DemoFile
    {
        cubestr info;
        uchar *data;
        int len;
    };
	// Vector of "demoFiles"
    vector<DemoFile> demoFiles;

	// Demo playback and recording streams and states.
    bool demoNextMatch = false;
    stream *demoTemp = NULL, *demoRecord = NULL, *demoPlayback = NULL;
    int nextPlayback = 0, demoMilliseconds = 0;

	// Server demo settings.
    VAR(maxdemos, 0, 5, 25);
    VAR(maxdemosize, 0, 16, 64);
    VAR(restrictdemos, 0, 1, 1);

	// Server restrictions.
    VAR(restrictpausegame, 0, 1, 1);
    VAR(restrictgamespeed, 0, 1, 1);

	// Should be a struct, server frame time state.
	struct ServerFrameTimeState {
		int gameMode = 0;
		int gameMilliseconds = 0;
		int gameLimit = 0;
		int nextExceeded = 0;
		int gameSpeed = 100;

		bool gamePaused = false;
		bool shouldstep = true;
		bool notgotitems = true;        // true when map has changed and waiting for clients to send item

		int intermission = 0;
		enet_uint32 lastSend = 0;

		cubestr serverMapName = "";
		stream *mapData = NULL;

	}; ServerFrameTimeState ftsServer;

	// Default master mode and mask.
	shared::network::protocol::MasterMode masterMode = shared::network::protocol::MasterMode::Open;
	shared::network::protocol::MasterMask masterMask = shared::network::protocol::MasterMask::PrivateServer;

	// Base server settings (description, password, adminpassword, public or...)
    SVAR(serverdesc, "");
    SVAR(serverpass, "");
    SVAR(adminpass, "");
    VARF(publicserver, 0, 0, 2, {
		switch(publicserver)
		{
			case 0: default: masterMask = shared::network::protocol::MasterMask::PrivateServer; break;
			case 1: masterMask = shared::network::protocol::MasterMask::OpenServer; break;
			case 2: masterMask = shared::network::protocol::MasterMask::Cooperative; break;
		}
	});
    SVAR(servermotd, "Server Message of the damn Day!");

	void *NewClientInfo() {
		return new shared::network::ClientInfo;
	}

	void DeleteClientInfo(void *ci) {
		shared::network::ClientInfo *info = static_cast<shared::network::ClientInfo*>(ci);
		delete info; ci = nullptr;
	}
	void ServerInit() {

	}
	int ReserveClients() {
		return 3;
	}
	int NumChannels() {
		return 3;
	}
	
	shared::network::ClientInfo *GetInfo(int cn)
    {
        if(cn < MAXCLIENTS) return (shared::network::ClientInfo *)GetClientInfo(cn));
        cn -= MAXCLIENTS;

		return NULL;
        //return bots.inrange(n) ? dynamic_cast<shared::network::ClientInfo*>(bots[ccn]) : NULL;
    }
	shared::network::protocol::DisconnectReason clientdisconnect(int cn) {
		// Idk why the fuck this is... clientdisconnect?
        shared::network::ClientInfo *ci = GetInfo(cn);
        ci->clientNumber = ci->ownerNumber = cn;
        ci->connectedMilliseconds = shared::network::ftsClient.totalMilliseconds;
        ci->sessionID = (rnd(0x1000000)*((shared::network::ftsClient.totalMilliseconds%10000)+1))&0xFFFFFF;

		// Add client to the server client list.
        game::server::svClients.connected.add(ci);
        if(!m_mp(gamemode)) 
            return shared::network::protocol::DisconnectReason::Local;
            
        sendservinfo(ci);
        return shared::network::protocol::DisconnectReason::Default;
	}
	shared::network::protocol::DisconnectReason clientconnect(int n, uint ip) {
		return shared::network::protocol::DisconnectReason::Default;
	}
	void LocalDisconnect(int n) {

	}
	void LocalConnect(int n) {

	}
	bool AllowBroadcast(int n) {
		return true;
	}
	void recordpacket(int chan, void *data, int len) {

	}
	void parsepacket(int sender, int chan, packetbuf &p) {

	}
	void sendservmsg(const char *s) {

	}
	bool sendpackets(bool force) {
		return false;
	}
	void sendservinfo(shared::network::ClientInfo *ci)
    {
        sendf(ci->clientnum, 1, "ri5ss", N_SERVINFO, ci->clientNumber, shared::network::POLYHEDRON_PROTOCOL_VERSION, ci->sessionID, serverpass[0] ? 1 : 0, serverdesc, serverauth);
    }
	void serverinforeply(ucharbuf &req, ucharbuf &p) {

	}
	void serverupdate() {

	}
	bool servercompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np) {
		return true;
	}

	int protocolversion() {
		return 1;
	}
	int serverinfoport(int servport) {
		return 0;
	}
	int serverport() {
		return 0;
	}
	const char *defaultmaster() {
		return "";
	}
	int masterport() {
		return 0;
	}
	int laninfoport() {
		return 0;
	}
	void processmasterinput(const char *cmd, int cmdlen, const char *args) {

	}
	void masterconnected() {

	}
	void masterdisconnected() {

	}
	bool ispaused() {
		return false;
	}
	int scaletime(int t) {
		return t*100;
	}
}


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
