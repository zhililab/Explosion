//
// Created by johnk on 2023/3/21.
//

#pragma once

#include <RHI/CommandBuffer.h>

namespace RHI::Dummy {
    class DummyCommandBuffer : public CommandBuffer {
    public:
        DummyCommandBuffer();

        CommandEncoder* Begin() override;
        void Destroy() override;
    };
}
