#version 330 core
in vec3 ourColor;
in vec4 vertexColor;  // The input variable from the vertex shader (same name and same type)
out vec4 color; //declare output values with the out keyword, that we here promptly named color
void main( )
{
    color = vec4( ourColor, 1.0f);  //Colors in computer graphics are represented as an array of 4 values: the red, green, blue and alpha (opacity)
}
