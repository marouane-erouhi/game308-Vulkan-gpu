#version 450
#extension GL_ARB_separate_shader_objects : enable

#define LIGHT_COUNT 3

layout (location = 0) in vec3 vertNormal;
//layout (location = 1) in vec3 lightDir;
layout (location = 10) in vec3 lightDir[LIGHT_COUNT];
layout (location = 2) in vec3 eyeDir; 
layout (location = 3) in vec2 fragTexCoords;

layout (location = 0) out vec4 fragColor;

layout(binding = 2) uniform sampler2D texSampler;

struct LightData {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};
layout(binding = 1) uniform LightsUniformBufferObject {
	LightData lightData[3];
    vec4 ambient;
} lightsUbo;

void main() { 
	vec4 finalColor = vec4(0.0);
	vec4 ka = 0.1 * lightsUbo.ambient;
	vec4 kt = texture(texSampler, fragTexCoords);

	for(int i = 0; i < LIGHT_COUNT; i++) {
		// Normalize the light direction for current light
		vec3 normLightDir = normalize(lightDir[i]);

		// Diffuse calculation
		float diff = max(dot(vertNormal, normLightDir), 0.0);
		vec4 diffuse = diff * lightsUbo.lightData[i].diffuse;

		// Specular calculation
		vec3 reflection = normalize(reflect(-normLightDir, vertNormal));
		float spec = pow(max(dot(eyeDir, reflection), 0.0), 14.0);
		vec4 specular = spec * lightsUbo.lightData[i].specular;

		// Accumulate lighting for this light
		finalColor += diffuse + specular;
	}

	// Combine ambient, texture, and accumulated lighting
	fragColor = ka + (kt * finalColor);	
}
