#version 330

in vec2 st;
uniform sampler2D tex;
out vec4 FragColor;  

void main()  
{
    vec4 C = texture2D(tex, st);
	//FragColor = vec4(C.a, C.a, C.a, 0.0);
	FragColor = C;
}