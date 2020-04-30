#ifndef POLYHEDRON_NUI_H
#define POLYHEDRON_NUI_H

struct nk_context;
struct SDL_Window;

namespace engine {
	namespace nui {
		/// Initialize Nuklear UI Framework.
		int Initialize(SDL_Window *wnd);

		/// Render Nuklear UI Framework.
		int Render();

		/// Begin handling Nuklear UI Framework User Input.
		int UserInputBeginPoll();

		/// Poll events for Nuklear UI Framework User Input.
		int UserInputPolLEvent(const SDL_Event &evt);

		/// End handling Nklear UI Framework User Input.
		int UserInputEndPoll();

		/// Destroy Nuklear UI Framework.
		int Destroy();

		/// Return a pointer to the NUI Nuklear UI Framework Context.
		nk_context *GetNKContext();
	}
}

#endif //POLYHEDRON_NUI_H
