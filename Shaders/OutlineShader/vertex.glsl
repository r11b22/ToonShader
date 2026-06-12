#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

uniform float uOutlineThickness;


void main()
{
    vec4 clipPos = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPos, 1.0);

    // Get normal into view space
    mat3 normalMatrix = mat3(transpose(inverse(uViewMatrix * uModelMatrix)));
    vec3 viewNormal = normalize(normalMatrix * aNorm);

    // Only offset in screen XY, ignore Z — avoids inward extrusion
    clipPos.xy += viewNormal.xy * uOutlineThickness * clipPos.w;

    gl_Position = clipPos;
}