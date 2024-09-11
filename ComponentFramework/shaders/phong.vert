#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;
layout (location = 2) in  vec2 texCoords;

layout(binding = 0) uniform CameraUBO {
    mat4 viewMatrix;
    mat4 projectionMatrix;
} camera;

layout(binding = 1) uniform GlobalLightingUBO {
    vec4 position;
    vec4 diffuse;
} glights;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
	mat4 normalMatrix;
} push;


layout (location = 0) out vec3 vertNormal;
layout (location = 1) out vec3 lightDir;
layout (location = 2) out vec3 eyeDir;
layout (location = 3) out vec2 fragTexCoords;


void main() {
	fragTexCoords = texCoords;
	
	mat3 normalMatrix = mat3(push.normalMatrix);

	vertNormal = normalize(normalMatrix * vNormal.xyz); /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(camera.viewMatrix * push.modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;
	lightDir = normalize(vec3(glights.position) - vertPos); /// Create the light direction.
	
	gl_Position =  camera.projectionMatrix * camera.viewMatrix * push.modelMatrix * vVertex; 
}

