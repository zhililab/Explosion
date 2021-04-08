//
// Created by John Kindem on 2021/4/8.
//

#include <Explosion/Driver/Platform.h>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

#ifdef TARGET_OS_MAC
#include <vulkan/vulkan_macos.h>

#define VK_MVK_MACOS_SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"

const char* INSTANCE_EXTENSIONS[] = {
    VK_MVK_MACOS_SURFACE_EXTENSION_NAME
};

uint32_t GetPlatformInstanceExtensionNum()
{
    return sizeof(INSTANCE_EXTENSIONS) / sizeof(const char*);
}

const char** GetPlatformInstanceExtensions()
{
    return INSTANCE_EXTENSIONS;
}

bool CreatePlatformSurface(const VkInstance& vkInstance, void* surface, VkSurfaceKHR& vkSurface)
{
    VkMacOSSurfaceCreateInfoMVK createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    createInfo.pView = surface;
    createInfo.pNext = nullptr;

    if (vkCreateMacOSSurfaceMVK(vkInstance, &createInfo, nullptr, &vkSurface) != VK_SUCCESS) {
        return false;
    }
    return true;
}

#endif
