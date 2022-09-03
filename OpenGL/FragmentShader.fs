#version 330 core                                                             
out vec4 FragColor;                                                           
in vec3 outVertexColor;                                                       
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;

void main()                                                                   
{                                                                             
    //FragColor = vec4(outVertexColor.x, outVertexColor.y, outVertexColor.z, 1);
    //FragColor = texture(ourTexture, texCoord) * vec4(outVertexColor.x, outVertexColor.y, outVertexColor.z, 1.0);
    FragColor = mix(texture(ourTexture, texCoord), texture(ourFace, texCoord), 0.2);
}
