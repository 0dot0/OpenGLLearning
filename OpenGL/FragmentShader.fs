#version 330 core                                                             
out vec4 FragColor;                                                           
in vec3 outVertexColor;                                                       
                                                                              
void main()                                                                   
{                                                                             
    FragColor = vec4(outVertexColor.x, outVertexColor.y, outVertexColor.z, 1);
}
