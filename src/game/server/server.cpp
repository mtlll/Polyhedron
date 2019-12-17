#include "engine.h"
#include "scriptexport.h"
#include "log.h"
#include "game/game.h"

#include "game/server/server.h"
#include "game/client/client.h"

#include "shared/tools.h"
#include "shared/entities/coreentity.h"
#include "shared/entities/baseentity.h"
#include "shared/entities/basephysicalentity.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/entities/basecliententity.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/protocol.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"

#include "game/entities/player.h"

// Server map name, structurize these?
cubestr smapname;


// This file only servers as an empty basic server implementation.
namespace game {
	namespace server
	{
		vector<game::networking::ServerClient*> clients;
		
		//
		// Backend related functions.
		//
		struct banlist
		{
			vector<game::networking::IPMask> bans;

			void Clear() { 
				bans.shrink(0); 
			}

			bool Check(uint ip)
			{
				loopv(bans) 
					if(bans[i].Check(ip)) 
						return true;

				return false;
			}

			void Add(const char *ipname)
			{
				game::networking::IPMask ban;
				ban.parse(ipname);
				bans.add(ban);

				verifybans();
			}
		} ipbans, gbans;

		bool CheckBans(uint ip)
		{
			loopv(bannedips) if(bannedips[i].ip==ip) return true;
			return ipbans.Check(ip) || gbans.Check(ip);
		}

		void VerifyBans()
		{
			loopvrev(clients)
			{
				game::networking::ClientInfo *ci = clients[i];
				if(ci->state.aitype != AI_NONE || ci->local || ci->privilege >= protocol::Priviliges::Admin) continue;
				if(CheckBans(GetClientIP(ci->clientNumber))) Disconnect_Client(ci->clientNumber, game::networking::protocol::DisconnectReason::IPBan);
			}
		}

		//
		// Client related functions.
		//
		void *NewClientInfo() {
			return new game::networking::ClientInfo;
		}
		void DeleteClientInfo(void *ci) {
			delete (networking::ClientInfo *)ci;
		}
		void ServerInit() {
			serverMapName[0] = '\0';
		}
		int ReserveClients() {
			return 3; // Return 3, no clue why, but their default function does.
		}
		int GetNumChannels() {
			return 3;
		}
		void ClientDisconnect(int n) {

		}
		int ClientConnect(int n, uint ip) {
			
			return static_cast<int>(game::networking::protocol::DisconnectReason::Default);
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
			return networking::POLYHEDRON_SERVER_PORT;
		}
		const char *DefaultMaster() {
			return "master.polyhedron.gg";
		}
		int MasterPort() {
			return networking::POLYHEDRON_MASTER_PORT;
		}
		int LanInfoPort() {
			return networking::POLYHEDRON_LANINFO_PORT;
		}
		void ProcessMasterInput(const char *cmd, int cmdlen, const char *args) {
			uint id;
			cubestr val;
			if(sscanf(cmd, "failauth %u", &id) == 1)
				AuthFailed(id);
			else if(sscanf(cmd, "succauth %u", &id) == 1)
				AuthSucceeded(id);
			else if(sscanf(cmd, "chalauth %u %255s", &id, val) == 2)
				AuthChallenged(id, val);
			else if(matchcubestr(cmd, cmdlen, "cleargbans"))
				gbans.Clear();
			else if(sscanf(cmd, "addgban %100s", val) == 1)
				gbans.Add(val);
		}
		void MasterConnected() {

		}
		void MasterDisconnected() {
			loopvrev(clients)
			{
				game::networking::ClientInfo *ci = clients[i];
				if(ci->authRequired) AuthFailed(ci);
			}
		}
		bool IsPaused() {
			return false;
		}
		int ScaleTime(int t) {
			return t*100;
		}

		void PrintName()
		{
			conoutf("Your name is: %s", game::player1->name.c_str());
		//    conoutf("your name is: %s", d);
		}

		SCRIPTEXPORT_AS(name) void name(char *s, int *numargs) {
			if(*numargs > 0) name(s);
			else if(!*numargs) PrintName();
			else result((game::player1->name.c_str()));
		}
		SCRIPTEXPORT_AS(getname) const char * getname() {
			result(game::player1->name.c_str());
			return game::player1->name.c_str();
		}
		
		bool DuplicateName(entities::classes::BaseClientEntity *d, const std::string &name, const std::string &alt) {
			if (!d) {
				conoutf(CON_ERROR, "%s", "No entity found while executing 'DuplicateName', '%s' en '%s'", name.c_str(), alt.c_str());	
				return false;
			}

			if(name.empty()) name = d->name.substr(0, 260); // 260 is the old cubestr limit.
			if(!alt.empty() && d != game::player1 && !(name.compare(alt))) return true;
			loopv(players) if(d!=players[i] && !name == players[i]->name) return true;
			return false;
		}
	}
}


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
