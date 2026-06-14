#version 330 core
layout(location = 0) out vec4 FragColor;

#define MAX_POINT_LIGHTS 5

struct Light {
    vec3 position;
    vec3 diffuse;
    vec3 specular;

    // uitdoving
    float constant;
    float lineair;
    float quadratic;
};

uniform vec3 uAmbient;

uniform Light uPointLights[MAX_POINT_LIGHTS];
uniform int numPointLights;

uniform sampler2D uTexture;
uniform float uSpecularStrength;

uniform vec3 uCameraPos; // camera location
in vec3 FragPos; // pixel position
in vec3 Normal;
in vec2 UV;

void main()
{
    vec4 texColor = texture(uTexture, UV);

    if (texColor.a < 0.5) {
        discard;
    }

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(uCameraPos - FragPos);
    vec3 totalLight = uAmbient * vec3(texColor);

    for (int i = 0; i < numPointLights; i++) {
        Light light = uPointLights[i];

        vec3 lightDirection = normalize(light.position - FragPos);
        float distance = length(light.position - FragPos);

        float diff = max(dot(norm, lightDirection), 0.0);

        float attenuation = 1.0 / (light.constant + light.lineair * distance + light.quadratic * (distance * distance));
        vec3 diffuse = light.diffuse * diff * vec3(texColor);

        totalLight += ((diffuse) * attenuation);
    }

    vec4 outColor = vec4(totalLight, texColor.a);
    FragColor = outColor;
}
