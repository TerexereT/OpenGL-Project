#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 mColorL;
uniform bool luz;
uniform vec3 lightPos;
uniform vec3 viewPos;

//uniform float objectColor;

void main()
{
    if(!luz){
   
   FragColor = vec4(objectColor, 1.0);
   
   }else
   {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * mColorL;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * mColorL;

    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * mColorL; 

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
    }
} 