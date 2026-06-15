#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aUV;
uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform float uOutlineThickness;
void main()
{
    vec4 clipPos = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPos, 1.0);
    mat3 normalMatrix = mat3(transpose(inverse(uViewMatrix * uModelMatrix)));
    vec3 viewNormal = normalize(normalMatrix * aNorm);

    clipPos.xy += viewNormal.xy * uOutlineThickness;

    gl_Position = clipPos;
}
