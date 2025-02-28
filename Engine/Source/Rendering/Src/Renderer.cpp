//
// Created by johnk on 2022/8/3.
//

#include <Renderer/Renderer.h>

namespace Rendering {
    Renderer& Renderer::Get()
    {
        static Renderer instance;
        return instance;
    }

    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::Initialize(const RendererInitializer& inInitializer)
    {
        // TODO
    }

    Render::Canvas* Renderer::CreateCanvas(void* nativeWindow, uint32_t width, uint32_t height)
    {
        // TODO
        return nullptr;
    }

    void Renderer::RenderFrame(Render::Canvas* inCanvas, const Render::SceneView& inSceneView)
    {
        // TODO
    }
}
