#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 UV;

void main()
{
    FragPos = vec3(uModelMatrix * vec4(aPos, 1.0));
    gl_Position = uProjectionMatrix * uViewMatrix * vec4(FragPos, 1.0);

    //Normal = normalize(aNorm);
    Normal = mat3(transpose(inverse(uModelMatrix))) * aNorm;
    UV = aUV;
}