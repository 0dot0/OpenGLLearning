#version 330 core                                   
layout(location = 6) in vec3 aPos;                  
layout(location = 8) in vec2 aTexCoord;                                      
out vec2 texCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()                                         
{                                                   
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texCoord = aTexCoord;
}                                                   
