#version 330 core
#define NUM_LIGHTS 2
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light[NUM_LIGHTS];

uniform sampler2D texture_diffuse;

void main()
{
    vec3 result = vec3(0.0);  // Inicializa el color resultante

    for (int i = 0; i < NUM_LIGHTS; i++) {
        // Ambient
        vec3 ambient = light[i].ambient * material.diffuse;
    
        // Diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light[i].diffuse * diff * material.diffuse;
    
        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light[i].specular * (spec * material.specular);
    
        result += ambient + diffuse + specular;  // Suma la contribución de cada luz
    }

    color = vec4(result, 1.0f) * texture(texture_diffuse, TexCoords);
}