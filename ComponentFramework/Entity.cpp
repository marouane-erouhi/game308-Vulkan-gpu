#include "Entity.h"

Entity::Entity(std::string name_, std::string modelName_, unsigned int textureIndex_) :
	name(name_), modelName(modelName_) {
	model = Matrix4();
	normal = Matrix4();
	vertexBuffer = IndexedVertexBuffer();
	pushConstant = false;
	textureIndex = textureIndex_;
}
