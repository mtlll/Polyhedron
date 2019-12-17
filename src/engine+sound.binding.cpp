// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void startmusic(char * a, char * b);
extern void registersound(char * a, int * b);
extern void mapsound(char * a, int * b, int * c);
extern void altsound(char * a, int * b);
extern void altmapsound(char * a, int * b);
extern void numsounds();
extern void nummapsounds();
extern void soundreset();
extern void mapsoundreset();
extern void playsound_scriptimpl(int * a);
extern void resetsound();

static bool __dummy_music_bool = addcommand("music", (identfun)startmusic, "ss", ID_COMMAND, "");

static bool __dummy_registersound_bool = addcommand("registersound", (identfun)registersound, "si", ID_COMMAND, "");

static bool __dummy_mapsound_bool = addcommand("mapsound", (identfun)mapsound, "sii", ID_COMMAND, "");

static bool __dummy_altsound_bool = addcommand("altsound", (identfun)altsound, "si", ID_COMMAND, "");

static bool __dummy_altmapsound_bool = addcommand("altmapsound", (identfun)altmapsound, "si", ID_COMMAND, "");

static bool __dummy_numsounds_bool = addcommand("numsounds", (identfun)numsounds, "", ID_COMMAND, "");

static bool __dummy_nummapsounds_bool = addcommand("nummapsounds", (identfun)nummapsounds, "", ID_COMMAND, "");

static bool __dummy_soundreset_bool = addcommand("soundreset", (identfun)soundreset, "", ID_COMMAND, "");

static bool __dummy_mapsoundreset_bool = addcommand("mapsoundreset", (identfun)mapsoundreset, "", ID_COMMAND, "");

static bool __dummy_playsound_bool = addcommand("playsound", (identfun)playsound_scriptimpl, "i", ID_COMMAND, "");

static bool __dummy_resetsound_bool = addcommand("resetsound", (identfun)resetsound, "", ID_COMMAND, "");



    // cubeScriptProto = ss
    // cppArgumentTypes = ['char *', 'char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'char * b']
    // cppOriginalFunctionName = startmusic
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = music
    

    // cubeScriptProto = si
    // cppArgumentTypes = ['char *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'int * b']
    // cppOriginalFunctionName = registersound
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = registersound
    

    // cubeScriptProto = sii
    // cppArgumentTypes = ['char *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['char * a', 'int * b', 'int * c']
    // cppOriginalFunctionName = mapsound
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mapsound
    

    // cubeScriptProto = si
    // cppArgumentTypes = ['char *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'int * b']
    // cppOriginalFunctionName = altsound
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = altsound
    

    // cubeScriptProto = si
    // cppArgumentTypes = ['char *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'int * b']
    // cppOriginalFunctionName = altmapsound
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = altmapsound
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = numsounds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = numsounds
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = nummapsounds
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = nummapsounds
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = soundreset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = soundreset
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = mapsoundreset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = mapsoundreset
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = playsound_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = playsound
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = resetsound
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = resetsound
    


