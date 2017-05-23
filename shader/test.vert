#version 330

layout(location = 0) in vec2 p;  
layout(location = 1) in vec2 texCoord;

out float flag;

out vec2 st;

void main() {  
    gl_Position = vec4(p, 0.0, 1.0);  
	st = vec2(texCoord.x, -texCoord.y);

	//flag = p.z;
} 