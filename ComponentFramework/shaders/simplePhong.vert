#version 450
#extension GL_ARB_separate_shader_objects : enable
#define LIGHT_COUNT 3

layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;
layout (location = 2) in  vec2 texCoords;

// the binding value is described in the VkDescriptorSetLayoutBinding structure, 
// created in createDescriptorSetLayout function
// binding is set in the Descriptor set 
layout(binding = 0) uniform CameraUniformBufferObject {
    mat4 projectionMatrix;
    mat4 viewMatrix;
} cameraUbo;

struct LightData {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};
layout(binding = 1) uniform LightsUniformBufferObject {
    LightData lightData[LIGHT_COUNT];
    vec4 ambient;
} lightsUbo;


layout (location = 0) out vec3 vertNormal;
//layout (location = 1) flat out vec3 textureIndex;
layout (location = 2) out vec3 eyeDir;
layout (location = 3) out vec2 fragTexCoords;
layout (location = 4) out vec4 ambient;

layout (location = 10) out vec3 lightDir[LIGHT_COUNT];

//push constants block
layout(push_constant) uniform Push {
//	mat4 normalMatrix;
	mat4 modelMatrix;
    vec4 normalMatrix[3];
    uint textureIndex;
} push;

void main() {
	fragTexCoords = texCoords;
//	textureIndex = push.textureIndex;
	/// We must fix this, just load the normalMatrix in to the cameraUbo
	mat3 normalMatrix = mat3(
		push.normalMatrix[0].xyz,
		push.normalMatrix[1].xyz,
		push.normalMatrix[2].xyz
	);
//= mat3(push.normalMatrix); // scott sais this is bs and should be moved to the cpu through the push constant

	vertNormal = normalize(normalMatrix * vNormal.xyz); /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(cameraUbo.viewMatrix * push.modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;

	// account for multiple lights here
	for(int i=0;i<LIGHT_COUNT;i++){
		lightDir[i] = normalize(vec3(lightsUbo.lightData[i].position) - vertPos); /// Create the light direction.
	}
	
	gl_Position =  cameraUbo.projectionMatrix * cameraUbo.viewMatrix * push.modelMatrix * vVertex; 
}
