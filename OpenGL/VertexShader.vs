#version 330 core                                   
layout(location = 6) in vec3 aPos;                  
layout(location = 7) in vec3 vertexColor;           
out vec3 outVertexColor;                            
                                                    
void main()                                         
{                                                   
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    outVertexColor = vertexColor;                   
}                                                   
