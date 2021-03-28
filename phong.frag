
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

//Help from https://learnopengl.com/Lighting/Basic-Lighting
void main()
{
    //Determines the ambient
    float ambientStrenght = 0.1;
    vec3 ambient = ambientStrenght * lightColor;

    //Determines the diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //Determines the specular
    float specularStrenght = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrenght * spec * lightColor;

    //Applies the resulting color to the object
    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0);
} 
