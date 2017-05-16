#version 330

in vec2 st;
uniform sampler2D tex;
out vec4 FragColor;  

in float flag;

void main()  
{
    vec4 C = texture2D(tex, st);
	//FragColor = vec4(C.a, C.a, C.a, 0.0);
	FragColor = C;

	if (flag == 0.1) FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	if (flag == 0.2) FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}