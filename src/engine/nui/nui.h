#pragma once
#include "nuklear_polyhedron.h"

struct nk_context;

namespace entities {
    namespace classes {
        class CoreEntity;
    }
}

namespace engine {
	namespace nui {
        using InputEventProcessState = NkPolyhedron::InputEventProcessState;

		void Initialize();

		void Render();

		void InputProcessBegin();
        InputEventProcessState InputEvent(const SDL_Event &evt);
		void InputProcessEnd();

		void Destroy();

		nk_context *GetNKContext();

        void StartEntityEditor(entities::classes::CoreEntity* entity);
        void StopEntityEditor(entities::classes::CoreEntity* entity);


		void DemoUI();
	}
}
