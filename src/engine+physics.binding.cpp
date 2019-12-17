// === GENERATED FILE, EDITS WILL NOT STICK === //
#include "engine/scriptexport.h"
#include "shared/cube.h"

extern void phystest();
extern void backward(CommandTypes::KeyPress a);
extern void forward(CommandTypes::KeyPress a);
extern void left(CommandTypes::KeyPress a);
extern void right(CommandTypes::KeyPress a);
extern void jump(CommandTypes::KeyPress a);
extern void crouch(CommandTypes::KeyPress a);

static bool __dummy_phystest_bool = addcommand("phystest", (identfun)phystest, "", ID_COMMAND, "");

static bool __dummy_backward_bool = addcommand("backward", (identfun)backward, "D", ID_COMMAND, "");

static bool __dummy_forward_bool = addcommand("forward", (identfun)forward, "D", ID_COMMAND, "");

static bool __dummy_left_bool = addcommand("left", (identfun)left, "D", ID_COMMAND, "");

static bool __dummy_right_bool = addcommand("right", (identfun)right, "D", ID_COMMAND, "");

static bool __dummy_jump_bool = addcommand("jump", (identfun)jump, "D", ID_COMMAND, "");

static bool __dummy_crouch_bool = addcommand("crouch", (identfun)crouch, "D", ID_COMMAND, "");



    // cubeScriptProto = 
    // cppArgumentTypes = []
    // cppArgumentNames = []
    // cppArgumentDecls = []
    // cppOriginalFunctionName = phystest
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = phystest
    

    // cubeScriptProto = D
    // cppArgumentTypes = ['CommandTypes::KeyPress']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::KeyPress a']
    // cppOriginalFunctionName = backward
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = backward
    

    // cubeScriptProto = D
    // cppArgumentTypes = ['CommandTypes::KeyPress']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::KeyPress a']
    // cppOriginalFunctionName = forward
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = forward
    

    // cubeScriptProto = D
    // cppArgumentTypes = ['CommandTypes::KeyPress']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::KeyPress a']
    // cppOriginalFunctionName = left
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = left
    

    // cubeScriptProto = D
    // cppArgumentTypes = ['CommandTypes::KeyPress']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::KeyPress a']
    // cppOriginalFunctionName = right
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = right
    

    // cubeScriptProto = D
    // cppArgumentTypes = ['CommandTypes::KeyPress']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::KeyPress a']
    // cppOriginalFunctionName = jump
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = jump
    

    // cubeScriptProto = D
    // cppArgumentTypes = ['CommandTypes::KeyPress']
    // cppArgumentNames = ['a']
    // cppArgumentDecls = ['CommandTypes::KeyPress a']
    // cppOriginalFunctionName = crouch
    // cppReturnType = void
    // cppNamespaceHierarchy = []
    // bindWithFunctionName = crouch
    


