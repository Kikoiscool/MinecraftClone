#version 330 core

//	The color being displayed on the screen
//in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D tex0;

void main () {
	//FragColor = texture(tex0, vec2(TexCoord.x, TexCoord.y));
	FragColor = texture(tex0, vec2(0.22f, 0.87f));
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
