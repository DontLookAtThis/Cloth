#version 450 core

in vec2 TexCoord;
in vec3 worldPos;
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

void main(){
	color = vec4(1.0f,0.0f,0.5f,1.0f);
}