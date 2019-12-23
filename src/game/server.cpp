#include "engine/engine.h"

#include "game/game.h"
#include "game/client/client.h"
#include "game/server/server.h"

#include "shared/networking/protocol.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/cl_sv.h"

// This file only servers as an empty basic server implementation.
namespace server
{
	void *newclientinfo() {
		return new shared::network::ClientInfo;
	}

	void deleteclientinfo(void *ci) {
		shared::network::ClientInfo info = dynamic_cast<shared::network::ClientInfo*>(ci);
		delete info; ci = nullptr;
	}
	void serverinit() {

	}
	int reserveclients() {
		return 3;
	}
	int numchannels() {
		return 0;
	}
	
	shared::network::ClientInfo *GetInfo(int cn)
    {
        if(cn < MAXCLIENTS) return (ClientInfo *)GetClientInfo(cn);
        cn -= MAXCLIENTS;
        return bots.inrange(n) ? bots[ccn] : NULL;
    }
	void clientdisconnect(int cn) {
        shared::network::ClientInfo *ci = GetInfo(cn);
        ci->clientNumber = ci->ownerNumber = cn;
        ci->connectedMilliseconds = fstClient.totalMilliseconds;
        ci->sessionID = (rnd(0x1000000)*((fstClient.totalMilliseconds%10000)+1))&0xFFFFFF;

        connects.add(ci);
        if(!m_mp(gamemode)) return shared::network::protocol::DisconnectReason::Local;
        sendservinfo(ci);
        return shared::network::protocol::DisconnectReason::Default;
	}
	int clientconnect(int n, uint ip) {
		return shared::network::protocol::DisconnectReason;
	}
	void localdisconnect(int n) {

	}
	void localconnect(int n) {

	}
	bool allowbroadcast(int n) {
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
