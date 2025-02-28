//
// Created by johnk on 2022/11/18.
//

#pragma once

#include <string>

#include <Runtime/World.h>
#include <Runtime/Asset/Level.h>

namespace Runtime {
    class EClass(editorHide) EntityInfoComponent : public Component {
    public:
        EProperty()
        std::string name;

        EProperty()
        Level* ownerLevel;
    };
}
