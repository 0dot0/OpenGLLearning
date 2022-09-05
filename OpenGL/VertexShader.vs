#version 330 core                                   
layout(location = 6) in vec3 aPos;                  
layout(location = 7) in vec3 vertexColor;           
layout(location = 8) in vec2 aTexCoord;           
out vec3 outVertexColor;                            
out vec2 texCoord;

uniform mat4 transform;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()                                         
{                                                   
    //gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    outVertexColor = vertexColor;
    texCoord = aTexCoord;
}                                                   
