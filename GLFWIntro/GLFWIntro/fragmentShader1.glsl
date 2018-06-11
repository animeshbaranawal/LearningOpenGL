#version 330 core
in vec3 color;
in vec2 texCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float ratio;

out vec4 fragColor;

void main()
{
	vec2 newTexCoord = vec2(1.0f - texCoord.x, texCoord.y);
	fragColor = mix(texture(ourTexture1, texCoord), texture(ourTexture2, newTexCoord), ratio) * vec4(color, 1.0f);
}
