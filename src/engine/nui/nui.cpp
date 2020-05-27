#include "nui.h"
#include "shared/entities/EntityEditorMenu.h"

//FIXME: use some kind of gamestate/editorstate controller for this
extern bool editmode;

namespace engine { namespace nui {

    std::unique_ptr<NkPolyhedron> NuklearPolyhedronDevice;

    void Initialize()
    {
        NuklearPolyhedronDevice.reset(new NkPolyhedron);
    }

    void Render()
    {
        NuklearPolyhedronDevice->Render();
    }

    void InputProcessBegin()
    {
        NuklearPolyhedronDevice->InputProcessBegin();
    }

    InputEventProcessState InputEvent(const SDL_Event &evt)
    {
        return NuklearPolyhedronDevice->InputEvent(evt);
    }
    void InputProcessEnd()
    {
        NuklearPolyhedronDevice->InputProcessEnd();
    }

    void Destroy()
    {
        NuklearPolyhedronDevice.reset();
    }

    nk_context *GetNKContext()
    {
        return NuklearPolyhedronDevice->GetContext();
    }


    namespace {
        std::unique_ptr<EntityEditorMenu> ActiveEntityEditorMenu;
    }

    void StartEntityEditor(entities::classes::CoreEntity* entity)
    {
        if (::editmode)
        {
            if (!ActiveEntityEditorMenu)
            {
                ActiveEntityEditorMenu = std::make_unique<EntityEditorMenu>(entity);
            }
            else
            {
                 if (ActiveEntityEditorMenu->HasEntity(entity))
                 {
                     ActiveEntityEditorMenu->Show();
                 }
                 else
                 {
                     ActiveEntityEditorMenu = std::make_unique<EntityEditorMenu>(entity);
                 }
            }
        }
    }

    void StopEntityEditor(entities::classes::CoreEntity* entity)
    {
        if (ActiveEntityEditorMenu && ActiveEntityEditorMenu->HasEntity(entity))
        {
            ActiveEntityEditorMenu->Hide();
        }
    }

    void DemoUI()
    {
        if (ActiveEntityEditorMenu)
        {
            ActiveEntityEditorMenu->Render();
        }
    }
}
}