//
// Created by Zach Lee on 2022/10/1.
//

#pragma once

#include <RHI/SwapChain.h>
#include <Metal/Queue.h>
#include <Metal/MetalView.h>
#include <Metal/Texture.h>
#import <Metal/Metal.h>
#include <vector>

namespace RHI::Metal {
    class MTLDevice;

    class MTLSwapChain : public SwapChain {
    public:
        NON_COPYABLE(MTLSwapChain)
        explicit MTLSwapChain(MTLDevice& dev, const SwapChainCreateInfo& createInfo);
        ~MTLSwapChain() override;

        Texture* GetTexture(uint8_t index) override;
        uint8_t AcquireBackTexture() override;
        void Present() override;
        void Destroy() override;
        void AddSignalEventToCmd(id<MTLCommandBuffer> commandBuffer);
    private:
        void CreateNativeSwapChain(const SwapChainCreateInfo& createInfo);
        MTLDevice& mtlDevice;
        MetalView* view = nullptr;
        NSWindow* nativeWindow = nullptr;
        id<MTLEvent> event = nil;
        std::vector<id<CAMetalDrawable>> drawables;
        std::vector<std::unique_ptr<MTLTexture>> textures;
        uint32_t swapChainImageCount = 0;
        uint32_t currentImage = 0;
    };
}
