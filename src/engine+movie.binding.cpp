// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void movie(char * a);
extern void movierecording();

static bool __dummy_movie_bool = addcommand("movie", (identfun)movie, "s", ID_COMMAND, "");

static bool __dummy_movierecording_bool = addcommand("movierecording", (identfun)movierecording, "", ID_COMMAND, "");



    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = movie
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = movie
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = movierecording
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = movierecording
    


