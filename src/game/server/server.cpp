#include "engine/engine.h"
#include "engine/server/server.h"
#include "engine/client/client.h"

#include "game/game.h"
#include "game/client/client.h"
#include "game/server/server.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/cl_frametimestate.h"
#include "shared/networking/sv_frametimestate.h"
#include "shared/networking/protocol.h"

// This file only servers as an attempt at a server implementation.
namespace game {
	namespace server {
		// Server frame time state.
		shared::network::ServerFrameTimeState ftsServer;

		// Our list of server clients.
		game::server::ServerClients svClients;

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
		int NumberOfChannels() {
			return 3;
		}
		
		shared::network::ClientInfo *GetInfo(int cn)
		{
			if(cn < MAXCLIENTS) 
				return (shared::network::ClientInfo *)engine::server::GetClientInfo(cn);
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
			
			// WatIsDeze: Mike: TODO: This checks whether we're in multiplayer mode(or at least, in a game mode that is multiplayer. For now tis is not the case. TODO: FIXIT: 
			//if(!m_mp(ftsServer.gameMode))
				return shared::network::protocol::DisconnectReason::Local;
			SendServInfo(ci);
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

		void RecordPacket(int chan, void *data, int len) {

		}
		void ParsePacket(int sender, int chan, packetbuf &p) {

		}
		void SendServerMessage(const char *s) {

		}
		bool SendPackets(bool force) {
			return false;
		}
		
		void SendServInfo(shared::network::ClientInfo *ci)
		{
			engine::server::Sendf(ci->clientNumber, 1, "ri5ss", shared::network::protocol::Messages::ServerInfo, ci->clientNumber, shared::network::POLYHEDRON_PROTOCOL_VERSION, ci->sessionID, serverpass[0] ? 1 : 0, serverdesc, serverauth);
		}
		void ServerInfoReply(ucharbuf &req, ucharbuf &p) {

		}
		void ServerUpdate() {

		}
		bool ServerCompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np) {
			return true;
		}

		int ProtocolVersion() {
			return 1;
		}
		int ServerInfoPort(int servport) {
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
	}; // server
}; // game


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
