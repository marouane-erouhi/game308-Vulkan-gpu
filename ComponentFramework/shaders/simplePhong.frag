#version 450
#extension GL_ARB_separate_shader_objects : enable

#define LIGHT_COUNT 3
#define TEXTURE_COUNT 2

layout (location = 0) in vec3 vertNormal;
//layout (location = 1) flat in uint textureIndex;
layout (location = 2) in vec3 eyeDir; 
layout (location = 3) in vec2 fragTexCoords;
layout (location = 4) in vec4 ambient;
layout (location = 10) in vec3 lightDir[LIGHT_COUNT];


layout (location = 0) out vec4 fragColor;

layout(binding = 2) uniform sampler2D texSampler[TEXTURE_COUNT];

struct LightData {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};
layout(binding = 1) uniform LightsUniformBufferObject {
	LightData lightData[LIGHT_COUNT];
    vec4 ambient;
} lightsUbo;

layout(push_constant) uniform Push {
//	mat4 modelMatrix;
//	mat4 normalMatrix;
	mat4 modelMatrix;
    vec4 normalMatrix[3];
    int textureIndex;
} push;

void main() { 
	vec4 finalColor = vec4(0.0);
	vec4 ka = 0.1 * lightsUbo.ambient;
	vec4 kt = texture(texSampler[push.textureIndex], fragTexCoords);

	for(int i = 0; i < LIGHT_COUNT; i++) {
		// Diffuse calculation
		float diff = max(dot(vertNormal, lightDir[i]), 0.0);
		vec4 diffuse = diff * lightsUbo.lightData[i].diffuse;

		// Specular calculation
		vec3 reflection = normalize(reflect(-lightDir[i], vertNormal));
		float spec = pow(max(dot(eyeDir, reflection), 0.0), 14.0);
		vec4 specular = spec * lightsUbo.lightData[i].specular;

		// Accumulate lighting for this light
		finalColor += diffuse + specular;
	}

	// Combine ambient, texture, and accumulated lighting
	fragColor = ka + (kt * finalColor);	
}
