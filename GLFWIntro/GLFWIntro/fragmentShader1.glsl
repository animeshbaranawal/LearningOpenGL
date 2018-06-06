#version 330 core
uniform vec3 timeColor;
in vec3 color;

out vec4 fragColor;

void main()
{
	fragColor = vec4(timeColor * color, 1.0f);
}
