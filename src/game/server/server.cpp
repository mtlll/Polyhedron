#include "game/game.h"
#include "shared/networking/cl_sv.h"
#include "shared/networking/protocol.h"
#include "game/server/server.h"
#include "shared/tools.h"

// This file only servers as an empty basic server implementation.
namespace game {
	namespace server
	{
		void *NewClientInfo() {
			return newgame::networking::ClientInfo;
		}
		void DeleteClientInfo(void *ci) {
			delete (networking::ClientInfo *)ci;
		}
		void ServerInit() {

		}
		int ReserveClients() {
			return 3; // Return 3, no clue why, but their default function does.
		}
		int GetNumChannels() {
			return 0;
		}
		void ClientDisconnect(int n) {

		}
		int ClientConnect(int n, uint ip) {
			
			return DISC_NONE;
		}
		void LocalDisconnect(int n) {

		}
		void LocalConnect(int n) {

		}
		bool AllowBroadcast(int n) {
			return true;
		}
		void RecordPacket(int chan, void *data, int len) {

		}
		void ParsePacket(int sender, int chan, packetbuf &p) {

		}
		void SendServMsg(const char *s) {
			
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
		void ProcessMasterInput(const char *cmd, int cmdlen, const char *args) {

		}
		void MasterConnected() {

		}
		void MasterDisconnected() {

		}
		bool IsPaused() {
			return false;
		}
		int ScaleTime(int t) {
			return t*100;
		}
	}
}


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
