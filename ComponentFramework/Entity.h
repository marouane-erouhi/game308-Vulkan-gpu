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
	bool isPushConstant;
	ModelPushConstant pushConstant;

	Entity(const std::string name, const std::string model_name, unsigned int texture_index)
		: name(name),
		  modelName(model_name),
		  textureIndex(texture_index)
	{}
	void set_push_constant(Matrix4 model_){
		isPushConstant = true;
		model = model_;
		normal = MMath::transpose(MMath::inverse(model));
	}
	bool OnCreate(VulkanRenderer* renderer)
	{
		vertexBuffer = renderer->LoadModelIndexed(modelName.c_str());
		return true;
	}

	std::string getName()
	{
		return name;
	}
};