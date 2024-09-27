#ifndef SCENE0_H
#define SCENE0_H
#include "Scene.h"
#include "Vector.h"
#include "Renderer.h"
#include "VulkanRenderer.h"
#include "Camera.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;


class Scene0 : public Scene {
private:
	Renderer *renderer;
	Camera *camera;
	Matrix4 mariosModelMatrix;

	std::array<LightData, 2> lights;
public:
	explicit Scene0(Renderer* renderer_);
	virtual ~Scene0();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H