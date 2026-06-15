#version 330 core
layout(location = 0) out vec4 FragColor;

#define MAX_POINT_LIGHTS 64

struct PointLight {
    vec3 position;
    vec3 diffuse;
    vec3 specular;

    // uitdoving
    float constant;
    float lineair;
    float quadratic;
};
uniform PointLight uPointLights[MAX_POINT_LIGHTS];
uniform int uNumPointLights;

#define MAX_DIRECTIONAL_LIGHTS 5

struct DirectionalLight {
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectionalLight uDirectionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform int uNumDirectionalLights;

uniform vec3 uAmbient;

uniform sampler2D uTexture;
uniform float uSpecularStrength;

uniform vec3 uCameraPos; // camera location
in vec3 FragPos; // pixel position
in vec3 Normal;
in vec2 UV;

uniform int uSteps;

void main()
{
    vec4 texColor = texture(uTexture, UV);

    if (texColor.a < 0.5) {
        discard;
    }

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(uCameraPos - FragPos);
    vec3 totalLight = uAmbient * vec3(texColor);

    for (int i = 0; i < uNumPointLights; i++) {
        PointLight light = uPointLights[i];

        vec3 lightDirection = normalize(light.position - FragPos);
        float distance = length(light.position - FragPos);

        float diff = max(dot(norm, lightDirection), 0.0);

        float attenuation = 1.0 / (light.constant + light.lineair * distance + light.quadratic * (distance * distance));
        vec3 diffuse = light.diffuse * diff * vec3(texColor);

        totalLight += ((diffuse) * attenuation);
    }

    for (int i = 0; i < uNumDirectionalLights; i++) {
        DirectionalLight light = uDirectionalLights[i];

        vec3 lightDirection = normalize(light.direction);

        float diff = max(dot(norm, lightDirection), 0.0);

        vec3 diffuse = light.diffuse * diff * vec3(texColor);

        totalLight += (diffuse);
    }

    vec3 roundedLightColor = round(totalLight * uSteps) / uSteps;

    vec4 outColor = vec4(roundedLightColor, texColor.a);
    FragColor = outColor;
}
