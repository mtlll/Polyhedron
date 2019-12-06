#include "game/game.h"
#include "server.h"
#include "shared/tools.h"

// This file only servers as an empty basic server implementation.
namespace server
{
	void *NewClientInfo() {
		return new ClientInfo;
	}
	void DeleteClientInfo(void *ci) {
		delete (ClientInfo *)ci;
	}
	void ServerInit() {

	}
	int ReserveClients() {
		return 3; // Return 3, no clue why, but their default function does.
	}
	int GetGetNumChannels() {
		return 0;
	}
	void ClientDisconnect(int n) {

	}
	int ClientConnect(int n, uint ip) {
		
		return DISC_NONE;
	}
	void LocalDisconnect(int n) {

	}
	void localconnect(int n) {

	}
	bool AllowBroadcast(int n) {
		return true;
	}
	void RecordPacket(int chan, void *data, int len) {

	}
	void ParsePacket(int sender, int chan, packetbuf &p) {

	}
	void sendservmsg(const char *s) {
		
	}
	bool SendPackets(bool force) {

		return false;
	}
	void ServerInfoReply(ucharbuf &req, ucharbuf &p) {

	}
	void ServerUpdate() {

	}
	bool servercompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np) {
		return true;
	}

	int ProtocolVersion() {
		return 1;
	}
	int serverinfoport(int servport) {
		return 0;
	}
	int ServerPort() {
		return 0;
	}
	const char *DefaultMaster() {
		return "";
	}
	int MasterPort() {
		return 0;
	}
	int LanInfoPort() {
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
