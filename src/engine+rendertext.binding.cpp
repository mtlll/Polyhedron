// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void newfont(char * a, char * b, int * c, int * d, int * e);
extern void fontborder(float * a, float * b);
extern void fontoutline(float * a, float * b);
extern void fontoffset(char * a);
extern void fontscale(int * a);
extern void fonttex(char * a);
extern void fontchar(float * a, float * b, float * c, float * d, float * e, float * f, float * g);
extern void fontskip(int * a);
extern void fontalias(const char * a, const char * b);
extern void tabify(const char * a, int * b);

static bool __dummy_font_bool = addcommand("font", (identfun)newfont, "ssiii", ID_COMMAND, "");

static bool __dummy_fontborder_bool = addcommand("fontborder", (identfun)fontborder, "ff", ID_COMMAND, "");

static bool __dummy_fontoutline_bool = addcommand("fontoutline", (identfun)fontoutline, "ff", ID_COMMAND, "");

static bool __dummy_fontoffset_bool = addcommand("fontoffset", (identfun)fontoffset, "s", ID_COMMAND, "");

static bool __dummy_fontscale_bool = addcommand("fontscale", (identfun)fontscale, "i", ID_COMMAND, "");

static bool __dummy_fonttex_bool = addcommand("fonttex", (identfun)fonttex, "s", ID_COMMAND, "");

static bool __dummy_fontchar_bool = addcommand("fontchar", (identfun)fontchar, "fffffff", ID_COMMAND, "");

static bool __dummy_fontskip_bool = addcommand("fontskip", (identfun)fontskip, "i", ID_COMMAND, "");

static bool __dummy_fontalias_bool = addcommand("fontalias", (identfun)fontalias, "ss", ID_COMMAND, "");

static bool __dummy_tabify_bool = addcommand("tabify", (identfun)tabify, "si", ID_COMMAND, "");



    // cubeScriptProto = ssiii
    // cppArgumentTypes = ['char *', 'char *', 'int *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['char * a', 'char * b', 'int * c', 'int * d', 'int * e']
    // cppOriginalFunctionName = newfont
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = font
    

    // cubeScriptProto = ff
    // cppArgumentTypes = ['float *', 'float *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'float * b']
    // cppOriginalFunctionName = fontborder
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fontborder
    

    // cubeScriptProto = ff
    // cppArgumentTypes = ['float *', 'float *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'float * b']
    // cppOriginalFunctionName = fontoutline
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fontoutline
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = fontoffset
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fontoffset
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = fontscale
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fontscale
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = fonttex
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fonttex
    

    // cubeScriptProto = fffffff
    // cppArgumentTypes = ['float *', 'float *', 'float *', 'float *', 'float *', 'float *', 'float *']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
    // cppArgumentDecls = ['float * a', 'float * b', 'float * c', 'float * d', 'float * e', 'float * f', 'float * g']
    // cppOriginalFunctionName = fontchar
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fontchar
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = fontskip
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fontskip
    

    // cubeScriptProto = ss
    // cppArgumentTypes = ['const char *', 'const char *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['const char * a', 'const char * b']
    // cppOriginalFunctionName = fontalias
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = fontalias
    

    // cubeScriptProto = si
    // cppArgumentTypes = ['const char *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['const char * a', 'int * b']
    // cppOriginalFunctionName = tabify
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = tabify
    


