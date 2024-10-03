#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"
#include "VulkanRenderer.h"
#include "OpenGLRenderer.h"
#include "Camera.h"

Scene0::Scene0(Renderer *renderer_): 
	Scene(nullptr),renderer(renderer_), camera(nullptr) {
	camera = new Camera();
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	if(camera) delete camera;

}

bool Scene0::OnCreate() {
	int width = 0, height = 0;
	float aspectRatio;

	// create lights ---------------
	lights[0] = {};
	//lights[0].position = Vec4(5.0f, 5.0f, 5.0f, 0.0f);
	lights[0].diffuse = Vec4(1.0, 0.0, 0.0, 0.0);
	lights[0].specular = Vec4(1.0, 0.0, 0.0, 0.0);

	lights[1] = {};
	//lights[1].position = Vec4(-5.0f, 5.0f, 5.0f, 0.0f);
	lights[1].diffuse = Vec4(0.0, 1.0, 0.0, 0.0);
	lights[1].specular = Vec4(0.0, 1.0, 0.0, 0.0);

	lights[2] = {};
	//lights[2].position = Vec4(5.0f, 5.0f, 5.0f, 0.0f);
	lights[2].diffuse = Vec4(0.0, 0.0,1.0,0.0);
	lights[2].specular = Vec4(0.0, 0.0, 1.0, 0.0);

	float angleStep = 2.0f * M_PI / 3.0f;  // 120 degrees apart
	float radius = 5.0f;

	lights[0].position = Vec4(cos(0) * radius, sin(0) * radius, 0.0f, 0.0f);
	lights[1].position = Vec4(cos(angleStep) * radius, sin(angleStep) * radius, 0.0f, 0.0f);
	lights[2].position = Vec4(cos(2 * angleStep) * radius, sin(2 * angleStep) * radius, 0.0f, 0.0f);
	// create lights end -------------

	switch (renderer->getRendererType()){
	case RendererType::VULKAN:
		
		SDL_GetWindowSize(dynamic_cast<VulkanRenderer*>(renderer)->GetWindow(), &width, &height);
		aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		camera->Perspective(45.0f, aspectRatio, 0.5f, 20.0f);
		camera->LookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
		
		break;

	case RendererType::OPENGL:
		break;
	}

	return true;
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_WINDOWEVENT) {
		switch (sdlEvent.window.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			printf("size changed %d %d\n", sdlEvent.window.data1, sdlEvent.window.data2);
			float aspectRatio = static_cast<float>(sdlEvent.window.data1) / static_cast<float>(sdlEvent.window.data2);
			camera->Perspective(45.0f, aspectRatio, 0.5f, 20.0f);
			if(renderer->getRendererType() == RendererType::VULKAN){
				dynamic_cast<VulkanRenderer*>(renderer)->RecreateSwapChain();
			}
			break;
		}
	}
}
void Scene0::Update(const float deltaTime) {
	static float elapsedTime = 0.0f;
	elapsedTime += deltaTime;
	mariosModelMatrix = MMath::rotate(elapsedTime * 90.0f, Vec3(0.0f, 1.0f, 0.0f));

	lights[0].position = Vec3(sin(elapsedTime) * 5.0, cos(elapsedTime) * 5.0, 0);
	lights[1].position = Vec3(sin(elapsedTime + 2.0) * 5.0, cos(elapsedTime + 2.0) * 5.0, 0);
	lights[2].position = Vec3(sin(elapsedTime + 4.0) * 5.0, cos(elapsedTime + 4.0) * 5.0, 0);


}

void Scene0::Render() const {
	
	switch (renderer->getRendererType()) {

	case RendererType::VULKAN:
		VulkanRenderer* vRenderer;
		vRenderer = dynamic_cast<VulkanRenderer*>(renderer);
		vRenderer->SetCameraUBO(camera->GetProjectionMatrix(), camera->GetViewMatrix()/*, mariosModelMatrix*/);

		// push constant---------------
		//pushConstant.modelMatrix = mariosModelMatrix;
		//// mat3 normalMatrix = mat3(transpose(inverse(push.modelMatrix)));
		//pushConstant.normalMatrix = MMath::transpose(MMath::inverse(mariosModelMatrix));
		vRenderer->SetPushConstantModelMatrix(mariosModelMatrix);

		// push contant end --------------

		vRenderer->SetLightsUbo(lights.data(), Vec4(0.0, 0.0, 0.0, 0.0));
		vRenderer->Render();
		break;

	case RendererType::OPENGL:
		OpenGLRenderer* glRenderer;
		glRenderer = dynamic_cast<OpenGLRenderer*>(renderer);
		/// Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		/// Draw your scene here
		
		
		glUseProgram(0);
		
		break;
	}
}


void Scene0::OnDestroy() {
	
}
