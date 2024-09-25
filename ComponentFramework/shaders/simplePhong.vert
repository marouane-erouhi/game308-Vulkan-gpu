#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;
layout (location = 2) in  vec2 texCoords;

// the binding value is described in the VkDescriptorSetLayoutBinding structure, 
// created in createDescriptorSetLayout function
// binding is set in the Descriptor set 
layout(binding = 0) uniform CameraUniformBufferObject {
    mat4 projectionMatrix;
    mat4 viewMatrix;
    mat4 modelMatrix;
	vec4 lightPos;
} cameraUbo;

layout(binding = 1) uniform LightsUniformBufferObject {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
    vec4 ambient;
} lightsUbo;

layout (location = 0) out vec3 vertNormal;
layout (location = 1) out vec3 lightDir;
layout (location = 2) out vec3 eyeDir;
layout (location = 3) out vec2 fragTexCoords;


void main() {
	fragTexCoords = texCoords;
	/// We must fix this, just load the normalMatrix in to the cameraUbo
	mat3 normalMatrix = mat3(transpose(inverse(cameraUbo.modelMatrix)));

	vertNormal = normalize(normalMatrix * vNormal.xyz); /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(cameraUbo.viewMatrix * cameraUbo.modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;
	lightDir = normalize(vec3(lightsUbo.position) - vertPos); /// Create the light direction.
	
	gl_Position =  cameraUbo.projectionMatrix * cameraUbo.viewMatrix * cameraUbo.modelMatrix * vVertex; 
}
