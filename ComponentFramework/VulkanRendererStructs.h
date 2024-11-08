#pragma once
#include <vulkan/vulkan.h>
#include <MMath.h>
using namespace MATH;
/// <summary>
/// Holds all the data needed to keep a buffer
///     bufferID - Opaque handle to a buffer object
///     bufferMemoryID - Opaque handle to a device memory object
///     bufferMemoryLength - Vulkan device memory size and offsets
/// </summary>
struct BufferMemory {
    VkBuffer bufferID;
    VkDeviceMemory bufferMemoryID;
    VkDeviceSize bufferMemoryLength;
};

struct IndexedVertexBuffer {
    VkBuffer vertBufferID;
    VkDeviceMemory vertBufferMemoryID;
    VkDeviceSize vertBufferLength;

    VkBuffer indexBufferID;
    VkDeviceMemory indexBufferMemoryID;
    VkDeviceSize indexBufferLength;
};

struct ModelPushConstant {
    Matrix4 model;
    //Matrix4 normal;
    Vec4 normalMatrix[3];
    uint32_t textureIndex;
};