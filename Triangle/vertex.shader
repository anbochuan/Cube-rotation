#version 330 core // Each shader begins with a declaration of its version
layout (location = 0) in vec3 position;  // Since each vertex has a 3D coordinate we create a vec3 input variable with the name position
layout (location = 1) in vec3 color;
out vec3 ourColor;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
void main( )
{
    //To set the output of the vertex shader we have to assign the position data to the predefined gl_Position variable which is a vec4 behind the scenes
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4( position.x, position.y, position.z, 1.0);

    ourColor = color;

}
