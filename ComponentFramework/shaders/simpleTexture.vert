#version 450 // don't use any version lower then this

// this extension means there is only a single file in this file
#extension GL_ARB_separate_shader_objects : enable

// 
layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texureCoord;

// this is how you bring in a "Uniform Buffer Object"
// the block size transfer is the mat4 regardless of what u send in
// that's why all imports are mat4
// look up std140 for more info
layout(std140, binding = 0) uniform UniformBufferObject {
// the order of decleration matters here
    mat4 projection;
    mat4 view;
    mat4 model;
} ubo; // object name here

// the location can be any number as long as u match the channel 
// in the file that is supposed to get that info
layout(location = 1) out vec2 texCoord;

void main() {
    texCoord = texureCoord;
    gl_Position = ubo.projection * ubo.view * ubo.model * vertex;
   
}