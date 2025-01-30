#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse;
uniform vec3 lightposition;
uniform vec3 lightcolor;
uniform vec3 cameraposition;

void main() {

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightcolor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightposition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraposition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightcolor;

    vec3 lighting = (ambient + diffuse + specular);
    vec3 color = texture(texture_diffuse, TexCoords).rgb * lighting;
    FragColor = vec4(color, 1.0);
}
