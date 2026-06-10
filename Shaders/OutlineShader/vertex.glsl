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
    // 1. Calculate the normal in world space (or model space)
    // We use the normal matrix to keep it accurate if the model is scaled
    vec3 worldNormal = normalize(mat3(transpose(inverse(uModelMatrix))) * aNorm);

    // 2. Calculate the base world position of the vertex
    vec3 worldPos = vec3(uModelMatrix * vec4(aPos, 1.0));

    // 3. Extrude the position outward along the normal
    vec3 extrudedPos = worldPos + (worldNormal * uOutlineThickness);

    // 4. Pass the extruded position to clip space
    gl_Position = uProjectionMatrix * uViewMatrix * vec4(extrudedPos, 1.0);
}