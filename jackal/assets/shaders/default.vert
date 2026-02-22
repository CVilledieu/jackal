#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

layout(binding = 0, std430) buffer ssbo{
    mat4 model[];
}; 


uniform mat4 uView;

out vec3 vColor;
out vec2 texCoord;

void main(){
    gl_Position = uView * model[gl_InstanceID] * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    vColor = aColor;
}