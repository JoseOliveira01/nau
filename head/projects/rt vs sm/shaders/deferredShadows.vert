#version 330

uniform mat4 PVM, V, M;
uniform mat3 NormalMatrix;
uniform vec4 lightDirection;
uniform mat4 lightSpaceMat;

in vec4 position;
in vec4 normal;
in vec4 texCoord0;

out vec4 VertexPos;
out vec2 TexCoord;
out vec3 Normal;
out vec3 LightDirection;
out vec4 projShadowCoord;

void main()
{
	projShadowCoord = lightSpaceMat * M * position;
	VertexPos = M * position;
	Normal = normalize(NormalMatrix * vec3(normal));
	LightDirection = normalize(NormalMatrix * vec3(lightDirection));
	TexCoord = vec2(texCoord0);
	gl_Position = PVM * position;
}