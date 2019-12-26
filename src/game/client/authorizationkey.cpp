#include "game/game.h"

#include "game/client/client.h"
#include "game/client/authorizationkey.h"
#include "game/entities/player.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/protocol.h"

namespace game {
    namespace client {
        // Global vector.
        vector<AuthorizationKey *> authorizationKeys;

        AuthorizationKey *FindAuthorizationKey(const char *desc = "")
        {
            loopv(authorizationKeys) {
                if(authorizationKeys[i]->desc == std::string_view(desc) && (authorizationKeys[i]->name == std::string_view(clPlayer->nickname))) 
                                return authorizationKeys[i];
            }
            loopv(authorizationKeys) {
                if(authorizationKeys[i]->desc == std::string_view(desc)) return authorizationKeys[i];
            }
            return NULL;
        }

        VARP(autoauth, 0, 1, 1);

        void AddAuthorizationKey(const char *name, const char *key, const char *desc)
        {
            loopvrev(authorizationKeys) {
                if((authorizationKeys[i]->desc == desc) && authorizationKeys[i]->name == std::string_view(name)) 
                    delete authorizationKeys.remove(i);
            } 
            if(name[0] && key[0]) 
                authorizationKeys.add(new AuthorizationKey(name, key, desc));
        }
        ICOMMAND(authkey, "sss", (char *name, char *key, char *desc), AddAuthorizationKey(name, key, desc));

        bool HasAuthorizationKey(const std::string &authName, const std::string &authDesc) {
            if(authName.empty() && authDesc.empty()) 
                return authorizationKeys.length() > 0;

            loopvrev(authorizationKeys) {
                if((authorizationKeys[i]->desc == authDesc) && (authorizationKeys[i]->name == authName))
                    return true;
            }

            return false;
        }

        ICOMMAND(hasauthkey, "ss", (char *name, char *desc), intret(HasAuthorizationKey(name, desc) ? 1 : 0));

        void GenerateAuthorizationKey(const std::string &secret)
        {
            if(secret.empty()) { conoutf(CON_ERROR, "You must specify a secret password"); return; }
            vector<char> privateKey, publicKey;
            genprivkey(secret, privateKey, publicKey);
            conoutf("Private key: %s", privateKey.getbuf());
            conoutf("Public key: %s", publicKey.getbuf());
            result(privateKey.getbuf());
        }
        ICOMMAND(genauthkey, "s", (char *secret), return(GenerateAuthorizationKey(secret), "Returns a newly generated Authorization Key"));

        void GetPublicKey(const std::string &authDesc)
        {
            AuthorizationKey *k = FindAuthorizationKey(desc);
            if(!k) { if(authDesc.empty()) conoutf("No Authorization Key found: %s", authDesc.c_str()); else conoutf("No global Authorization Key found"); return; }
            vector<char> pubkey;
            if(!calcpubkey(k->key, pubkey)) { conoutf("Failed calculating Public Key"); return; }
            result(pubkey.getbuf());
        }
        COMMAND(getpubkey, "s");

        void SaveAuthorizationkeys()
        {
            const std::string &fname = "config/auth.cfg";
            stream *f = openfile(path(fname.c_str()), "w");
            if(!f) { conoutf(CON_ERROR, "Failed to open %s for writing", fname.c_str()); return; }
            loopv(authkeys)
            {
                AuthorizationKey *a = authkeys[i];
                f->printf("Authorization Key %s %s %s\n", escapecubestr(a->name.c_str()), escapecubestr(a->key.c_str()), escapecubestr(a->desc.c_str()));
            }
            conoutf("Saved Authorization Keys to %s", fname.c_str());
            delete f;
        }
        ICOMMAND(saveauthkeys, "", () { result(SaveAuthorizationkeys)});
    }; // client
}; // game