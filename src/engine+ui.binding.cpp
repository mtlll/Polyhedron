// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void textlist();
extern void textshow();
extern void textfocus_f(char * a, int * b);
extern void textprev();
extern void textmode(int * a);
extern void textsave(char * a);
extern void textload(char * a);
extern void textinit(char * a, char * b, char * c);
extern void textcopy();
extern void textpaste();
extern void textmark(int * a);
extern void textselectall();
extern void textclear();
extern void textcurrentline();
extern void textexec(int * a);
namespace UI { extern void uicontextscale_scriptimpl(); }
namespace UI { extern void newui(char * a, char * b, char * c, char * d); }
namespace UI { extern void uiallowinput(CommandTypes::Boolean a); }
namespace UI { extern void uieschide(CommandTypes::Boolean a); }
namespace UI { extern void showui_scriptimpl(char * a); }
namespace UI { extern void hideui_scriptimpl(char * a); }
namespace UI { extern void hidetopui_scriptimpl(); }
namespace UI { extern void hideallui_scriptimpl(); }
namespace UI { extern void toggleui_scriptimpl(char * a); }
namespace UI { extern void holdui_scriptimpl(char * a, CommandTypes::KeyPress b); }
namespace UI { extern void uivisible_scriptimpl(char * a); }
namespace UI { extern void uiname(); }
namespace UI { extern void uialign(int * a, int * b); }
namespace UI { extern void uiclamp(int * a, int * b, int * c, int * d); }
namespace UI { extern void uigroup(CommandTypes::Expression a); }
namespace UI { extern void uihlist(float * a, CommandTypes::Expression b); }
namespace UI { extern void uivlist(float * a, CommandTypes::Expression b); }
namespace UI { extern void uilist(float * a, CommandTypes::Expression b); }
namespace UI { extern void uigrid(int * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uitableheader(CommandTypes::Expression a, CommandTypes::Expression b); }
namespace UI { extern void uitablerow(CommandTypes::Expression a, CommandTypes::Expression b); }
namespace UI { extern void uitable(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uispace(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uioffset(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uifill(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uitarget(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uiclip(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uiscroll(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uihscrolloffset(); }
namespace UI { extern void uivscrolloffset(); }
namespace UI { extern void uihscrollbar(CommandTypes::Expression a); }
namespace UI { extern void uivscrollbar(CommandTypes::Expression a); }
namespace UI { extern void uiscrollarrow(float * a, CommandTypes::Expression b); }
namespace UI { extern void uiscrollbutton(CommandTypes::Expression a); }
namespace UI { extern void uihslider(ident * a, float * b, float * c, float * d, CommandTypes::Expression e, CommandTypes::Expression f); }
namespace UI { extern void uivslider(ident * a, float * b, float * c, float * d, CommandTypes::Expression e, CommandTypes::Expression f); }
namespace UI { extern void uisliderarrow(float * a, CommandTypes::Expression b); }
namespace UI { extern void uisliderbutton(CommandTypes::Expression a); }
namespace UI { extern void uicolor(int * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uimodcolor(int * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uivgradient(int * a, int * b, float * c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uimodvgradient(int * a, int * b, float * c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uihgradient(int * a, int * b, float * c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uimodhgradient(int * a, int * b, float * c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uioutline(int * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uiline(int * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uitriangle(int * a, float * b, float * c, int * d, CommandTypes::Expression e); }
namespace UI { extern void uitriangleoutline(int * a, float * b, float * c, int * d, CommandTypes::Expression e); }
namespace UI { extern void uimodtriangle(int * a, float * b, float * c, int * d, CommandTypes::Expression e); }
namespace UI { extern void uicircle(int * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uicircleoutline(int * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uimodcircle(int * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uicolortext(tagval * a, int * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uitext(tagval * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uitextfill(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uiwrapcolortext(tagval * a, float * b, int * c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uiwraptext(tagval * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uicolorcontext(tagval * a, int * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uicontext(tagval * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uicontextfill(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uiwrapcolorcontext(tagval * a, float * b, int * c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uiwrapcontext(tagval * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uitexteditor(char * a, int * b, int * c, float * d, char * e, int * f, CommandTypes::Expression g); }
namespace UI { extern void uifont(char * a, CommandTypes::Expression b); }
namespace UI { extern void uiabovehud(); }
namespace UI { extern void uiconsole(float * a, float * b, CommandTypes::Expression c); }
namespace UI { extern void uifield(ident * a, int * b, CommandTypes::Expression c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uikeyfield(ident * a, int * b, CommandTypes::Expression c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uiimage(char * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uistretchedimage(char * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uicroppedimage(char * a, float * b, float * c, tagval * d, tagval * e, tagval * f, tagval * g, CommandTypes::Expression h); }
namespace UI { extern void uiborderedimage(char * a, tagval * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uitiledimage(char * a, float * b, float * c, float * d, float * e, CommandTypes::Expression f); }
namespace UI { extern void uimodelpreview(char * a, char * b, float * c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uiplayerpreview(int * a, int * b, int * c, int * d, float * e, float * f, CommandTypes::Expression g); }
namespace UI { extern void uiprefabpreview(char * a, int * b, float * c, float * d, CommandTypes::Expression e); }
namespace UI { extern void uislotview(int * a, float * b, float * c, CommandTypes::Expression d); }
namespace UI { extern void uivslotview(int * a, float * b, float * c, CommandTypes::Expression d); }

static bool __dummy_textlist_bool = addcommand("textlist", (identfun)textlist, "", ID_COMMAND, "return list of all the editors");

static bool __dummy_textshow_bool = addcommand("textshow", (identfun)textshow, "", ID_COMMAND, "return the start of the buffer");

static bool __dummy_textfocus_bool = addcommand("textfocus", (identfun)textfocus_f, "si", ID_COMMAND, "focus on a (or create a persistent) specific editor, else returns current name");

static bool __dummy_textprev_bool = addcommand("textprev", (identfun)textprev, "", ID_COMMAND, "return to the previous editor");

static bool __dummy_textmode_bool = addcommand("textmode", (identfun)textmode, "i", ID_COMMAND, "(1= keep while focused, 2= keep while used in gui, 3= keep forever (i.e. until mode changes)) topmost editor, return current setting if no args");

static bool __dummy_textsave_bool = addcommand("textsave", (identfun)textsave, "s", ID_COMMAND, "saves the topmost (filename is optional)");

static bool __dummy_textload_bool = addcommand("textload", (identfun)textload, "s", ID_COMMAND, "loads into the textfocusmost editor, returns filename if no args");

static bool __dummy_textinit_bool = addcommand("textinit", (identfun)textinit, "sss", ID_COMMAND, "loads into named editor if no file assigned and editor has been rendered");

static bool __dummy_textcopy_bool = addcommand("textcopy", (identfun)textcopy, "", ID_COMMAND, "");

static bool __dummy_textpaste_bool = addcommand("textpaste", (identfun)textpaste, "", ID_COMMAND, "");

static bool __dummy_textmark_bool = addcommand("textmark", (identfun)textmark, "i", ID_COMMAND, "(1=mark, 2=unmark), return current mark setting if no args");

static bool __dummy_textselectall_bool = addcommand("textselectall", (identfun)textselectall, "", ID_COMMAND, "");

static bool __dummy_textclear_bool = addcommand("textclear", (identfun)textclear, "", ID_COMMAND, "");

static bool __dummy_textcurrentline_bool = addcommand("textcurrentline", (identfun)textcurrentline, "", ID_COMMAND, "");

static bool __dummy_textexec_bool = addcommand("textexec", (identfun)textexec, "i", ID_COMMAND, "execute script commands from the buffer (0=all, 1=selected region only)");

static bool __dummy_uicontextscale_bool = addcommand("uicontextscale", (identfun)UI::uicontextscale_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_newui_bool = addcommand("newui", (identfun)UI::newui, "ssss", ID_COMMAND, "");

static bool __dummy_uiallowinput_bool = addcommand("uiallowinput", (identfun)UI::uiallowinput, "b", ID_COMMAND, "");

static bool __dummy_uieschide_bool = addcommand("uieschide", (identfun)UI::uieschide, "b", ID_COMMAND, "");

static bool __dummy_showui_bool = addcommand("showui", (identfun)UI::showui_scriptimpl, "s", ID_COMMAND, "");

static bool __dummy_hideui_bool = addcommand("hideui", (identfun)UI::hideui_scriptimpl, "s", ID_COMMAND, "");

static bool __dummy_hidetopui_bool = addcommand("hidetopui", (identfun)UI::hidetopui_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_hideallui_bool = addcommand("hideallui", (identfun)UI::hideallui_scriptimpl, "", ID_COMMAND, "");

static bool __dummy_toggleui_bool = addcommand("toggleui", (identfun)UI::toggleui_scriptimpl, "s", ID_COMMAND, "");

static bool __dummy_holdui_bool = addcommand("holdui", (identfun)UI::holdui_scriptimpl, "sD", ID_COMMAND, "");

static bool __dummy_uivisible_bool = addcommand("uivisible", (identfun)UI::uivisible_scriptimpl, "s", ID_COMMAND, "");

static bool __dummy_uiname_bool = addcommand("uiname", (identfun)UI::uiname, "", ID_COMMAND, "");

static bool __dummy_uialign_bool = addcommand("uialign", (identfun)UI::uialign, "ii", ID_COMMAND, "");

static bool __dummy_uiclamp_bool = addcommand("uiclamp", (identfun)UI::uiclamp, "iiii", ID_COMMAND, "");

static bool __dummy_uigroup_bool = addcommand("uigroup", (identfun)UI::uigroup, "e", ID_COMMAND, "");

static bool __dummy_uihlist_bool = addcommand("uihlist", (identfun)UI::uihlist, "fe", ID_COMMAND, "");

static bool __dummy_uivlist_bool = addcommand("uivlist", (identfun)UI::uivlist, "fe", ID_COMMAND, "");

static bool __dummy_uilist_bool = addcommand("uilist", (identfun)UI::uilist, "fe", ID_COMMAND, "");

static bool __dummy_uigrid_bool = addcommand("uigrid", (identfun)UI::uigrid, "iffe", ID_COMMAND, "");

static bool __dummy_uitableheader_bool = addcommand("uitableheader", (identfun)UI::uitableheader, "ee", ID_COMMAND, "");

static bool __dummy_uitablerow_bool = addcommand("uitablerow", (identfun)UI::uitablerow, "ee", ID_COMMAND, "");

static bool __dummy_uitable_bool = addcommand("uitable", (identfun)UI::uitable, "ffe", ID_COMMAND, "");

static bool __dummy_uispace_bool = addcommand("uispace", (identfun)UI::uispace, "ffe", ID_COMMAND, "");

static bool __dummy_uioffset_bool = addcommand("uioffset", (identfun)UI::uioffset, "ffe", ID_COMMAND, "");

static bool __dummy_uifill_bool = addcommand("uifill", (identfun)UI::uifill, "ffe", ID_COMMAND, "");

static bool __dummy_uitarget_bool = addcommand("uitarget", (identfun)UI::uitarget, "ffe", ID_COMMAND, "");

static bool __dummy_uiclip_bool = addcommand("uiclip", (identfun)UI::uiclip, "ffe", ID_COMMAND, "");

static bool __dummy_uiscroll_bool = addcommand("uiscroll", (identfun)UI::uiscroll, "ffe", ID_COMMAND, "");

static bool __dummy_uihscrolloffset_bool = addcommand("uihscrolloffset", (identfun)UI::uihscrolloffset, "", ID_COMMAND, "");

static bool __dummy_uivscrolloffset_bool = addcommand("uivscrolloffset", (identfun)UI::uivscrolloffset, "", ID_COMMAND, "");

static bool __dummy_uihscrollbar_bool = addcommand("uihscrollbar", (identfun)UI::uihscrollbar, "e", ID_COMMAND, "");

static bool __dummy_uivscrollbar_bool = addcommand("uivscrollbar", (identfun)UI::uivscrollbar, "e", ID_COMMAND, "");

static bool __dummy_uiscrollarrow_bool = addcommand("uiscrollarrow", (identfun)UI::uiscrollarrow, "fe", ID_COMMAND, "");

static bool __dummy_uiscrollbutton_bool = addcommand("uiscrollbutton", (identfun)UI::uiscrollbutton, "e", ID_COMMAND, "");

static bool __dummy_uihslider_bool = addcommand("uihslider", (identfun)UI::uihslider, "rfffee", ID_COMMAND, "");

static bool __dummy_uivslider_bool = addcommand("uivslider", (identfun)UI::uivslider, "rfffee", ID_COMMAND, "");

static bool __dummy_uisliderarrow_bool = addcommand("uisliderarrow", (identfun)UI::uisliderarrow, "fe", ID_COMMAND, "");

static bool __dummy_uisliderbutton_bool = addcommand("uisliderbutton", (identfun)UI::uisliderbutton, "e", ID_COMMAND, "");

static bool __dummy_uicolor_bool = addcommand("uicolor", (identfun)UI::uicolor, "iffe", ID_COMMAND, "");

static bool __dummy_uimodcolor_bool = addcommand("uimodcolor", (identfun)UI::uimodcolor, "iffe", ID_COMMAND, "");

static bool __dummy_uivgradient_bool = addcommand("uivgradient", (identfun)UI::uivgradient, "iiffe", ID_COMMAND, "");

static bool __dummy_uimodvgradient_bool = addcommand("uimodvgradient", (identfun)UI::uimodvgradient, "iiffe", ID_COMMAND, "");

static bool __dummy_uihgradient_bool = addcommand("uihgradient", (identfun)UI::uihgradient, "iiffe", ID_COMMAND, "");

static bool __dummy_uimodhgradient_bool = addcommand("uimodhgradient", (identfun)UI::uimodhgradient, "iiffe", ID_COMMAND, "");

static bool __dummy_uioutline_bool = addcommand("uioutline", (identfun)UI::uioutline, "iffe", ID_COMMAND, "");

static bool __dummy_uiline_bool = addcommand("uiline", (identfun)UI::uiline, "iffe", ID_COMMAND, "");

static bool __dummy_uitriangle_bool = addcommand("uitriangle", (identfun)UI::uitriangle, "iffie", ID_COMMAND, "");

static bool __dummy_uitriangleoutline_bool = addcommand("uitriangleoutline", (identfun)UI::uitriangleoutline, "iffie", ID_COMMAND, "");

static bool __dummy_uimodtriangle_bool = addcommand("uimodtriangle", (identfun)UI::uimodtriangle, "iffie", ID_COMMAND, "");

static bool __dummy_uicircle_bool = addcommand("uicircle", (identfun)UI::uicircle, "ife", ID_COMMAND, "");

static bool __dummy_uicircleoutline_bool = addcommand("uicircleoutline", (identfun)UI::uicircleoutline, "ife", ID_COMMAND, "");

static bool __dummy_uimodcircle_bool = addcommand("uimodcircle", (identfun)UI::uimodcircle, "ife", ID_COMMAND, "");

static bool __dummy_uicolortext_bool = addcommand("uicolortext", (identfun)UI::uicolortext, "tife", ID_COMMAND, "");

static bool __dummy_uitext_bool = addcommand("uitext", (identfun)UI::uitext, "tfe", ID_COMMAND, "");

static bool __dummy_uitextfill_bool = addcommand("uitextfill", (identfun)UI::uitextfill, "ffe", ID_COMMAND, "");

static bool __dummy_uiwrapcolortext_bool = addcommand("uiwrapcolortext", (identfun)UI::uiwrapcolortext, "tfife", ID_COMMAND, "");

static bool __dummy_uiwraptext_bool = addcommand("uiwraptext", (identfun)UI::uiwraptext, "tffe", ID_COMMAND, "");

static bool __dummy_uicolorcontext_bool = addcommand("uicolorcontext", (identfun)UI::uicolorcontext, "tife", ID_COMMAND, "");

static bool __dummy_uicontext_bool = addcommand("uicontext", (identfun)UI::uicontext, "tfe", ID_COMMAND, "");

static bool __dummy_uicontextfill_bool = addcommand("uicontextfill", (identfun)UI::uicontextfill, "ffe", ID_COMMAND, "");

static bool __dummy_uiwrapcolorcontext_bool = addcommand("uiwrapcolorcontext", (identfun)UI::uiwrapcolorcontext, "tfife", ID_COMMAND, "");

static bool __dummy_uiwrapcontext_bool = addcommand("uiwrapcontext", (identfun)UI::uiwrapcontext, "tffe", ID_COMMAND, "");

static bool __dummy_uitexteditor_bool = addcommand("uitexteditor", (identfun)UI::uitexteditor, "siifsie", ID_COMMAND, "");

static bool __dummy_uifont_bool = addcommand("uifont", (identfun)UI::uifont, "se", ID_COMMAND, "");

static bool __dummy_uiabovehud_bool = addcommand("uiabovehud", (identfun)UI::uiabovehud, "", ID_COMMAND, "");

static bool __dummy_uiconsole_bool = addcommand("uiconsole", (identfun)UI::uiconsole, "ffe", ID_COMMAND, "");

static bool __dummy_uifield_bool = addcommand("uifield", (identfun)UI::uifield, "riefe", ID_COMMAND, "");

static bool __dummy_uikeyfield_bool = addcommand("uikeyfield", (identfun)UI::uikeyfield, "riefe", ID_COMMAND, "");

static bool __dummy_uiimage_bool = addcommand("uiimage", (identfun)UI::uiimage, "sffe", ID_COMMAND, "");

static bool __dummy_uistretchedimage_bool = addcommand("uistretchedimage", (identfun)UI::uistretchedimage, "sffe", ID_COMMAND, "");

static bool __dummy_uicroppedimage_bool = addcommand("uicroppedimage", (identfun)UI::uicroppedimage, "sfftttte", ID_COMMAND, "");

static bool __dummy_uiborderedimage_bool = addcommand("uiborderedimage", (identfun)UI::uiborderedimage, "stfe", ID_COMMAND, "");

static bool __dummy_uitiledimage_bool = addcommand("uitiledimage", (identfun)UI::uitiledimage, "sffffe", ID_COMMAND, "");

static bool __dummy_uimodelpreview_bool = addcommand("uimodelpreview", (identfun)UI::uimodelpreview, "ssffe", ID_COMMAND, "");

static bool __dummy_uiplayerpreview_bool = addcommand("uiplayerpreview", (identfun)UI::uiplayerpreview, "iiiiffe", ID_COMMAND, "");

static bool __dummy_uiprefabpreview_bool = addcommand("uiprefabpreview", (identfun)UI::uiprefabpreview, "siffe", ID_COMMAND, "");

static bool __dummy_uislotview_bool = addcommand("uislotview", (identfun)UI::uislotview, "iffe", ID_COMMAND, "");

static bool __dummy_uivslotview_bool = addcommand("uivslotview", (identfun)UI::uivslotview, "iffe", ID_COMMAND, "");



    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = textlist
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textlist
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = textshow
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textshow
    

    // cubeScriptProto = si
    // cppArgumentTypes = ['char *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'int * b']
    // cppOriginalFunctionName = textfocus_f
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textfocus
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = textprev
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textprev
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = textmode
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textmode
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = textsave
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textsave
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = textload
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textload
    

    // cubeScriptProto = sss
    // cppArgumentTypes = ['char *', 'char *', 'char *']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['char * a', 'char * b', 'char * c']
    // cppOriginalFunctionName = textinit
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textinit
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = textcopy
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textcopy
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = textpaste
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textpaste
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = textmark
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textmark
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = textselectall
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textselectall
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = textclear
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textclear
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = textcurrentline
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textcurrentline
    

    // cubeScriptProto = i
    // cppArgumentTypes = ['int *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['int * a']
    // cppOriginalFunctionName = textexec
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = textexec
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = uicontextscale_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicontextscale
    

    // cubeScriptProto = ssss
    // cppArgumentTypes = ['char *', 'char *', 'char *', 'char *']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['char * a', 'char * b', 'char * c', 'char * d']
    // cppOriginalFunctionName = newui
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = newui
    

    // cubeScriptProto = b
    // cppArgumentTypes = ['CommandTypes::Boolean']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Boolean a']
    // cppOriginalFunctionName = uiallowinput
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiallowinput
    

    // cubeScriptProto = b
    // cppArgumentTypes = ['CommandTypes::Boolean']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Boolean a']
    // cppOriginalFunctionName = uieschide
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uieschide
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = showui_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = showui
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = hideui_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = hideui
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = hidetopui_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = hidetopui
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = hideallui_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = hideallui
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = toggleui_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = toggleui
    

    // cubeScriptProto = sD
    // cppArgumentTypes = ['char *', 'CommandTypes::KeyPress']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'CommandTypes::KeyPress b']
    // cppOriginalFunctionName = holdui_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = holdui
    

    // cubeScriptProto = s
    // cppArgumentTypes = ['char *']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['char * a']
    // cppOriginalFunctionName = uivisible_scriptimpl
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uivisible
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = uiname
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiname
    

    // cubeScriptProto = ii
    // cppArgumentTypes = ['int *', 'int *']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['int * a', 'int * b']
    // cppOriginalFunctionName = uialign
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uialign
    

    // cubeScriptProto = iiii
    // cppArgumentTypes = ['int *', 'int *', 'int *', 'int *']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'int * b', 'int * c', 'int * d']
    // cppOriginalFunctionName = uiclamp
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiclamp
    

    // cubeScriptProto = e
    // cppArgumentTypes = ['CommandTypes::Expression']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Expression a']
    // cppOriginalFunctionName = uigroup
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uigroup
    

    // cubeScriptProto = fe
    // cppArgumentTypes = ['float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = uihlist
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uihlist
    

    // cubeScriptProto = fe
    // cppArgumentTypes = ['float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = uivlist
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uivlist
    

    // cubeScriptProto = fe
    // cppArgumentTypes = ['float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = uilist
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uilist
    

    // cubeScriptProto = iffe
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uigrid
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uigrid
    

    // cubeScriptProto = ee
    // cppArgumentTypes = ['CommandTypes::Expression', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['CommandTypes::Expression a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = uitableheader
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitableheader
    

    // cubeScriptProto = ee
    // cppArgumentTypes = ['CommandTypes::Expression', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['CommandTypes::Expression a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = uitablerow
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitablerow
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uitable
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitable
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uispace
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uispace
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uioffset
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uioffset
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uifill
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uifill
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uitarget
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitarget
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uiclip
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiclip
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uiscroll
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiscroll
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = uihscrolloffset
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uihscrolloffset
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = uivscrolloffset
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uivscrolloffset
    

    // cubeScriptProto = e
    // cppArgumentTypes = ['CommandTypes::Expression']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Expression a']
    // cppOriginalFunctionName = uihscrollbar
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uihscrollbar
    

    // cubeScriptProto = e
    // cppArgumentTypes = ['CommandTypes::Expression']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Expression a']
    // cppOriginalFunctionName = uivscrollbar
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uivscrollbar
    

    // cubeScriptProto = fe
    // cppArgumentTypes = ['float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = uiscrollarrow
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiscrollarrow
    

    // cubeScriptProto = e
    // cppArgumentTypes = ['CommandTypes::Expression']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Expression a']
    // cppOriginalFunctionName = uiscrollbutton
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiscrollbutton
    

    // cubeScriptProto = rfffee
    // cppArgumentTypes = ['ident *', 'float *', 'float *', 'float *', 'CommandTypes::Expression', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f']
    // cppArgumentDecls = ['ident * a', 'float * b', 'float * c', 'float * d', 'CommandTypes::Expression e', 'CommandTypes::Expression f']
    // cppOriginalFunctionName = uihslider
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uihslider
    

    // cubeScriptProto = rfffee
    // cppArgumentTypes = ['ident *', 'float *', 'float *', 'float *', 'CommandTypes::Expression', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f']
    // cppArgumentDecls = ['ident * a', 'float * b', 'float * c', 'float * d', 'CommandTypes::Expression e', 'CommandTypes::Expression f']
    // cppOriginalFunctionName = uivslider
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uivslider
    

    // cubeScriptProto = fe
    // cppArgumentTypes = ['float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['float * a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = uisliderarrow
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uisliderarrow
    

    // cubeScriptProto = e
    // cppArgumentTypes = ['CommandTypes::Expression']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::Expression a']
    // cppOriginalFunctionName = uisliderbutton
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uisliderbutton
    

    // cubeScriptProto = iffe
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uicolor
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicolor
    

    // cubeScriptProto = iffe
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uimodcolor
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uimodcolor
    

    // cubeScriptProto = iiffe
    // cppArgumentTypes = ['int *', 'int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['int * a', 'int * b', 'float * c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uivgradient
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uivgradient
    

    // cubeScriptProto = iiffe
    // cppArgumentTypes = ['int *', 'int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['int * a', 'int * b', 'float * c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uimodvgradient
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uimodvgradient
    

    // cubeScriptProto = iiffe
    // cppArgumentTypes = ['int *', 'int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['int * a', 'int * b', 'float * c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uihgradient
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uihgradient
    

    // cubeScriptProto = iiffe
    // cppArgumentTypes = ['int *', 'int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['int * a', 'int * b', 'float * c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uimodhgradient
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uimodhgradient
    

    // cubeScriptProto = iffe
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uioutline
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uioutline
    

    // cubeScriptProto = iffe
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uiline
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiline
    

    // cubeScriptProto = iffie
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'int *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'int * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uitriangle
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitriangle
    

    // cubeScriptProto = iffie
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'int *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'int * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uitriangleoutline
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitriangleoutline
    

    // cubeScriptProto = iffie
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'int *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'int * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uimodtriangle
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uimodtriangle
    

    // cubeScriptProto = ife
    // cppArgumentTypes = ['int *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['int * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uicircle
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicircle
    

    // cubeScriptProto = ife
    // cppArgumentTypes = ['int *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['int * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uicircleoutline
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicircleoutline
    

    // cubeScriptProto = ife
    // cppArgumentTypes = ['int *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['int * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uimodcircle
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uimodcircle
    

    // cubeScriptProto = tife
    // cppArgumentTypes = ['tagval *', 'int *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['tagval * a', 'int * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uicolortext
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicolortext
    

    // cubeScriptProto = tfe
    // cppArgumentTypes = ['tagval *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['tagval * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uitext
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitext
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uitextfill
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitextfill
    

    // cubeScriptProto = tfife
    // cppArgumentTypes = ['tagval *', 'float *', 'int *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['tagval * a', 'float * b', 'int * c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uiwrapcolortext
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiwrapcolortext
    

    // cubeScriptProto = tffe
    // cppArgumentTypes = ['tagval *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['tagval * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uiwraptext
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiwraptext
    

    // cubeScriptProto = tife
    // cppArgumentTypes = ['tagval *', 'int *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['tagval * a', 'int * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uicolorcontext
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicolorcontext
    

    // cubeScriptProto = tfe
    // cppArgumentTypes = ['tagval *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['tagval * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uicontext
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicontext
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uicontextfill
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicontextfill
    

    // cubeScriptProto = tfife
    // cppArgumentTypes = ['tagval *', 'float *', 'int *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['tagval * a', 'float * b', 'int * c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uiwrapcolorcontext
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiwrapcolorcontext
    

    // cubeScriptProto = tffe
    // cppArgumentTypes = ['tagval *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['tagval * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uiwrapcontext
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiwrapcontext
    

    // cubeScriptProto = siifsie
    // cppArgumentTypes = ['char *', 'int *', 'int *', 'float *', 'char *', 'int *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
    // cppArgumentDecls = ['char * a', 'int * b', 'int * c', 'float * d', 'char * e', 'int * f', 'CommandTypes::Expression g']
    // cppOriginalFunctionName = uitexteditor
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitexteditor
    

    // cubeScriptProto = se
    // cppArgumentTypes = ['char *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b']
    // cppArgumentDecls = ['char * a', 'CommandTypes::Expression b']
    // cppOriginalFunctionName = uifont
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uifont
    

    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = uiabovehud
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiabovehud
    

    // cubeScriptProto = ffe
    // cppArgumentTypes = ['float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c']
    // cppArgumentDecls = ['float * a', 'float * b', 'CommandTypes::Expression c']
    // cppOriginalFunctionName = uiconsole
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiconsole
    

    // cubeScriptProto = riefe
    // cppArgumentTypes = ['ident *', 'int *', 'CommandTypes::Expression', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['ident * a', 'int * b', 'CommandTypes::Expression c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uifield
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uifield
    

    // cubeScriptProto = riefe
    // cppArgumentTypes = ['ident *', 'int *', 'CommandTypes::Expression', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['ident * a', 'int * b', 'CommandTypes::Expression c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uikeyfield
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uikeyfield
    

    // cubeScriptProto = sffe
    // cppArgumentTypes = ['char *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['char * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uiimage
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiimage
    

    // cubeScriptProto = sffe
    // cppArgumentTypes = ['char *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['char * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uistretchedimage
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uistretchedimage
    

    // cubeScriptProto = sfftttte
    // cppArgumentTypes = ['char *', 'float *', 'float *', 'tagval *', 'tagval *', 'tagval *', 'tagval *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']
    // cppArgumentDecls = ['char * a', 'float * b', 'float * c', 'tagval * d', 'tagval * e', 'tagval * f', 'tagval * g', 'CommandTypes::Expression h']
    // cppOriginalFunctionName = uicroppedimage
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uicroppedimage
    

    // cubeScriptProto = stfe
    // cppArgumentTypes = ['char *', 'tagval *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['char * a', 'tagval * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uiborderedimage
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiborderedimage
    

    // cubeScriptProto = sffffe
    // cppArgumentTypes = ['char *', 'float *', 'float *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f']
    // cppArgumentDecls = ['char * a', 'float * b', 'float * c', 'float * d', 'float * e', 'CommandTypes::Expression f']
    // cppOriginalFunctionName = uitiledimage
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uitiledimage
    

    // cubeScriptProto = ssffe
    // cppArgumentTypes = ['char *', 'char *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['char * a', 'char * b', 'float * c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uimodelpreview
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uimodelpreview
    

    // cubeScriptProto = iiiiffe
    // cppArgumentTypes = ['int *', 'int *', 'int *', 'int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
    // cppArgumentDecls = ['int * a', 'int * b', 'int * c', 'int * d', 'float * e', 'float * f', 'CommandTypes::Expression g']
    // cppOriginalFunctionName = uiplayerpreview
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiplayerpreview
    

    // cubeScriptProto = siffe
    // cppArgumentTypes = ['char *', 'int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd', 'e']
    // cppArgumentDecls = ['char * a', 'int * b', 'float * c', 'float * d', 'CommandTypes::Expression e']
    // cppOriginalFunctionName = uiprefabpreview
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uiprefabpreview
    

    // cubeScriptProto = iffe
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uislotview
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uislotview
    

    // cubeScriptProto = iffe
    // cppArgumentTypes = ['int *', 'float *', 'float *', 'CommandTypes::Expression']
    // cppArgumentNames = ['a', 'b', 'c', 'd']
    // cppArgumentDecls = ['int * a', 'float * b', 'float * c', 'CommandTypes::Expression d']
    // cppOriginalFunctionName = uivslotview
    // cppReturnType = void
    // cppNamespaceHierarchy = ['UI']
    // bindWithFunctionName = uivslotview
    


