#version 330 core

//	The color being displayed on the screen

out vec4 FragColor;

//in vec2 TexCoord;

in vec3 color;

uniform sampler2D tex0;

void main () {
	//FragColor = texture(tex0, TexCoord);
	//FragColor = texture(tex0, vec2(0.22f, 0.87f));
	FragColor = vec4(color, 1.0f);
}
