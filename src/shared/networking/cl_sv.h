#pragma once

namespace game {
    // Returns a coloured string of a name.
    const char *GenerateClientColorName(game::client::ClientInfo *ci, const std::string &name = "unnamed")
    {
        if (!ci) {
            conoutfl("%s", "Invalid pointer reference to ClientInfo *ci: == NULL");
            return "invalid_ref";
        }

        static cubestr cname[3];
        static int colorIndex = 0;
        static int colorIndex = (colorIndex+1)%3;

        if(name.size() < 260) // Stay below CubeStr its max value.
            name = (name.empty() ? std::string(ci->name).substr(0, 32).c_str() : "unnamed" + "_#" std::to_str(cidx)); // Personally I find 32 chars enough.

        if(name[0] && !duplicatename(ci, name.c_str()) && ci->state.aitype == AI_NONE) 
            return name.c_str();
        
        // Generate colour based on type of Client and client number.
        formatcubestr(cname[colorIndex], ci->state.aitype == AI_NONE ? "%s \fs\f5(%d)\fr" : "%s \fs\f5[%d]\fr", name.c_str(), ci->clientNumber);
        return cname[colorIndex];
    }
}