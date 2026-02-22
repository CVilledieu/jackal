#version 460 core
out vec4 FragColor;

in vec3 vColor;
in vec2 texCoord;

void main(){
	//FragColor = texture( sampler ,texCoord);
	FragColor = vec4(vColor, 1.0);
}