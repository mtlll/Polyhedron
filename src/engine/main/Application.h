#pragma once
#include "AppConfig.h"
#include "engine/console.h"
#include "shared/tools/stream.h"
#include "shared/stream.h"
#include <nlohmann/json.hpp>
#include <SDL_events.h>
#include <list>

class CommandlineArguments;
class Input;
class Renderer;
class Window;
class SoundConfig;

#ifdef __APPLE__
#define main SDL_main
#endif

class Application {
public:
    Application(const CommandlineArguments& commandlineArguments);
    ~Application();

    enum class PeekEventAction {
        Cache, Drop
    };
    using PeekEventCallback = std::function<PeekEventAction(SDL_Event&)>;

    static Application& Instance();

    Window& GetWindow() const;
    Renderer& GetRenderer() const;
    Input& GetInput() const;
    SoundConfig& GetSoundConfig() const;
    const AppState& GetAppState() const;

    void RunFrame();
    void ProcessEvents();
    void PeekEvents(const PeekEventCallback& peekCallback);

    template <class... Args>
    void Fatal(const std::string& s, Args&&...);
    void Fatal(const std::string& s);

    void Quit();
    bool GetQuitRequested() const;
private:

    bool m_QuitRequested = false;
    AppConfig m_AppConfig;
    AppState m_AppState;
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;
    std::unique_ptr<Input> m_Input;
    std::unique_ptr<SoundConfig> m_SoundConfig;

    std::list<SDL_Event> m_CachedEvents;
};


template <typename T>
bool LoadJson(Application& app, const std::string& filename, T& intoObject, bool required = false)
{
    std::function<void(std::string, std::string)> report;
    if (required)
    {
        report = [&app](std::string filename, std::string msg){
            app.Fatal("Unable to read json %s: %s", filename.c_str(), msg.c_str());
        };
    }
    else
    {
        report = [](std::string filename, std::string msg){
            conoutf(CON_ERROR, "Unable to read json %s: %s", filename.c_str(), msg.c_str());
        };
    }

    stream* fileHandle = openrawfile(filename.c_str(), "r");
    if (fileHandle)
    {
        auto size = fileHandle->size();
        std::string buffer;
        buffer.resize(size);
        if (fileHandle->read(buffer.data(), size))
        {
            try {
                auto document = nlohmann::json::parse(buffer);
                document.get_to(intoObject);

                return true;
            }
            catch(nlohmann::json::exception& error)
            {
                report(filename, error.what());
            }
            catch(...)
            {
                report(filename, "unknown exception occurred");
            }
        }
    }

    report(filename, "unable to read file");
    return !required;
}
