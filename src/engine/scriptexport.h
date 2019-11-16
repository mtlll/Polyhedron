#pragma once
#include <functional>

#ifdef SCRIPTBIND_RUN
#define VISIBLE_SYMBOL
#else
#define VISIBLE_SYMBOL __attribute__((__visibility__("default")))
#endif

#define SCRIPTEXPORT __attribute__((annotate("scriptexport"))) VISIBLE_SYMBOL
#define SCRIPTEXPORT_AS(NAME) __attribute__((annotate("scriptexport" #NAME))) VISIBLE_SYMBOL

#define DONTSERIALIZE __attribute__((annotate("dontserialize")))


#define PHUI_HIDDEN(label) __attribute__((annotate("phui;" #label ";hidden")))
#define PHUI_SLIDER(label, minVal, maxVal, stepVal) __attribute__((annotate("phui;slider;" #label ";" #minVal ";" #maxVal ";" #stepVal)))
#define PHUI_CHECKBOX(label) __attribute__((annotate("phui;checkbox;" #label)))
#define PHUI_INPUT(label) __attribute__((annotate("phui;input;" #label )))
