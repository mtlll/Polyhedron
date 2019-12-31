#pragma once

#include "shared/cube.h"
#include "shared/networking/cl_frametimestate.h"
#include "shared/networking/sv_frametimestate.h"

namespace game {
    namespace client {
        //
        // AuthorizationKey struct, used for a global client authorization key list.
        //
        struct AuthorizationKey {
            std::string name = "";
            std::string key = "";
            std::string desc = "";
            int lastAuth = 0;

            AuthorizationKey(const std::string &authName, const std::string &authKey, const std::string &authDesc)
                : name(authName), key(authKey), desc(authDesc) {
            }
        }; extern vector<AuthorizationKey *> authorizationKeys; // Global.

        // Authorization Functions.
        extern game::client::AuthorizationKey *FindAuthorizationKey(const std::string &authDesc = "");
        extern void AddAuthorizationKey(const std::string &authName, const std::string &authKey, const std::string &authDesc);
        extern bool HasAuthorizationKey(const std::string &authName, const std::string & authDesc);
        extern void GenerateAuthorizationKey(const std::string &authSecret);
        extern void GetPublicKey(const std::string &authDesc);
        extern void SaveAuthorizationkeys();
    }; // client
}; // game