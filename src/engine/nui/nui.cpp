#include "nui.h"
#include "shared/entities/EntityEditorMenu.h"

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
        entities::classes::CoreEntity* ActiveEntityEditorEntity = nullptr;
        std::unique_ptr<EntityEditorMenu> ActiveEntityEditorMenu;
    }

    void StartEntityEditor(entities::classes::CoreEntity* entity)
    {
        ActiveEntityEditorEntity = entity;
        ActiveEntityEditorMenu = std::make_unique<EntityEditorMenu>(entity);
    }

    void StopEntityEditor(entities::classes::CoreEntity* entity)
    {
        if (ActiveEntityEditorEntity == entity)
        {
            ActiveEntityEditorEntity = nullptr;
            ActiveEntityEditorMenu.release();
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