#pragma once
#include <Matrix.h>
#include "VulkanRendererStructs.h"

using namespace MATH;

class Entity {
public:
	std::string name;
	std::string modelName;
	Matrix4 model;
	Matrix4 normal;
	IndexedVertexBuffer vertexBuffer;
	unsigned int textureIndex;
	bool pushConstant;
	ModelPushConstant pushConstant;

	Entity();
	Entity(std::string name_, std::string modelName_, unsigned int textureIndex_);

};