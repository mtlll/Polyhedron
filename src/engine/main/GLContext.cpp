#include "GLContext.h"
#include "Application.h"
#include "Window.h"
#include "engine/console.h"
#include "engine/rendergl.h"
#include <array>
#include "engine/includegl.h"
#include <glad/glad.h>

namespace {
    struct OpenGLContextCreationFlags
    {
        int major, minor, mask;
        OpenGLContextCreationFlags(int major, int minor, int mask)
            : major(major), minor(minor), mask(mask)
        {}
    };

    const std::array<OpenGLContextCreationFlags, 6> ContextConfigsToTry {
        OpenGLContextCreationFlags {4, 0, (int)SDL_GL_CONTEXT_PROFILE_CORE},
        OpenGLContextCreationFlags {3, 3, (int)SDL_GL_CONTEXT_PROFILE_ES},
        OpenGLContextCreationFlags {3, 2, (int)SDL_GL_CONTEXT_PROFILE_CORE},
        OpenGLContextCreationFlags {3, 1, 0},
        OpenGLContextCreationFlags {3, 0, 0},
        OpenGLContextCreationFlags {2, 0, 0}
    };
}

GLContext::GLContext(Window& window, const GLConfig& config)
    : m_Config(config)
    , m_Window(window)
{
    SDL_GL_ResetAttributes();
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, m_Config.DoubleBuffering ? 1 : 0);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, m_Config.StencilBufferSize);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, m_Config.DepthBufferSize);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, m_Config.FrameBufferSize);
#ifndef NDEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
}

bool GLContext::CreateContext()
{
    for (auto &contextConfig : ContextConfigsToTry)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, contextConfig.major);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, contextConfig.minor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, contextConfig.mask);

        m_Context = SDL_GL_CreateContext(m_Window.GetWindowHandle());
        if (m_Context) {
            break;
        }
    }

    if (!m_Context)
    {
        Application::Instance().Fatal("Unable to create an Open GL Context: %s\n", SDL_GetError());
    }

#ifdef OPEN_GL_ES
    if (!gladLoadGLES2Loader(SDL_GL_GetProcAddress)) {
#else
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
#endif
        Application::Instance().Fatal("Unable to load GL through glad!\n");
    }
    conoutf("OpenGL:   %d.%d", GLVersion.major, GLVersion.minor);
    conoutf("Vendor:   %s", glGetString(GL_VENDOR));
    conoutf("Renderer: %s", glGetString(GL_RENDERER));
    conoutf("Shader:   %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    Resize();
}

void GLContext::ApplyValuesToCubeScript()
{
    extern int renderw, renderh, hudw, hudh;

    renderw = m_ContextState.FrameBufferWidth;
    renderh = m_ContextState.FrameBufferHeight;
    hudw = m_ContextState.FrameBufferWidth;
    hudh = m_ContextState.FrameBufferHeight;
}

void GLContext::Resize()
{
    SDL_GL_GetDrawableSize(m_Window.GetWindowHandle(), &m_ContextState.FrameBufferWidth, &m_ContextState.FrameBufferHeight);
    ApplyValuesToCubeScript();
    glCheckError(glViewport(0, 0, m_ContextState.FrameBufferWidth, m_ContextState.FrameBufferHeight));
}

GLContext::~GLContext()
{
    SDL_GL_DeleteContext(m_Context);
    m_Context = nullptr;
}

void GLContext::GetFramebufferSize(int& w, int& h) const
{
    w = m_ContextState.FrameBufferWidth;
    h = m_ContextState.FrameBufferHeight;
}
