#include <iostream>
#define GLEW_STATIC  // define GLEW_STATIC since we're using the static version of the GLEW library.
#include <GL/glew.h>
#include <stdio.h>
#include <string>
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <../Triangle/objloader.cpp>

using namespace std;

const GLuint WIDTH = 800, HEIGHT = 800;

//const GLchar *vertexShaderSource = "#version 330 core\n" // Each shader begins with a declaration of its version
//"layout (location = 0) in vec3 position; \n" // Since each vertex has a 3D coordinate we create a vec3 input variable with the name position
//"layout (location = 1) in vec3 color; \n"
//"out vec3 ourColor; \n"
//
//"uniform mat4 model_matrix;\n"
//"uniform mat4 view_matrix;\n"
//"uniform mat4 projection_matrix;\n"
//"void main( )\n"
//"{\n"
//"gl_Position = projection_matrix * view_matrix * model_matrix * vec4( position.x, position.y, position.z, 1.0);\n" //To set the output of the vertex shader we have to assign the position data to the predefined gl_Position variable which is a vec4 behind the scenes
//"ourColor = color; \n"
//
//"}";
//
//const GLchar *fragmentShaderSource = "#version 330 core\n"
//"in vec3 ourColor; \n"
//"in vec4 vertexColor; \n" // The input variable from the vertex shader (same name and same type)
//"out vec4 color;\n"//declare output values with the out keyword, that we here promptly named color
//"void main( )\n"
//"{\n"
//"color = vec4( ourColor, 1.0f);\n"//Colors in computer graphics are represented as an array of 4 values: the red, green, blue and alpha (opacity)
//"}";



glm::vec3 triangle_scale_R;
glm::vec3 triangle_scale_S;

GLfloat rotation_Angle;
GLfloat Coordinates_Angle_X;
GLfloat Coordinates_Angle_Z;

const float TRIANGLE_MOVEMENT_STEP = 0.3f;
glm::vec3 camera_translation = glm::vec3(0.0f, 0.0f, -1.0f);
const float CAMERA_PAN_STEP = 0.2f;
const float BLACKLINE_ROTATE_ANGLE_STEP = 1.0f;
const float COORDINATE_ROTATE_ANGLE_STEP = 1.0f;
bool Space_Bar = false;
bool Key_A = false;

// Camera
glm::vec3 cameraPos   = glm::vec3(1.0f, 1.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

glm::mat4 projection_matrix;
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    
    // Update the Projection matrix after a window resize event
    projection_matrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.0f, 1000.0f);
}


// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        Space_Bar = !Space_Bar;
    }
    
    if (key == GLFW_KEY_S && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
    {
        triangle_scale_S.x += TRIANGLE_MOVEMENT_STEP;
        
        triangle_scale_S.y += TRIANGLE_MOVEMENT_STEP;
        
        triangle_scale_S.z += TRIANGLE_MOVEMENT_STEP;
    }
    
    
    if (key == GLFW_KEY_S && action == GLFW_PRESS && mode != GLFW_MOD_SHIFT)
    {
        triangle_scale_S.x -= TRIANGLE_MOVEMENT_STEP;
        
        triangle_scale_S.y -= TRIANGLE_MOVEMENT_STEP;
        
        triangle_scale_S.z -= TRIANGLE_MOVEMENT_STEP;
    }
    
    if (key == GLFW_KEY_R && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
    {
        triangle_scale_R.x += TRIANGLE_MOVEMENT_STEP;
        
        triangle_scale_R.y += TRIANGLE_MOVEMENT_STEP;
        
        triangle_scale_R.z += TRIANGLE_MOVEMENT_STEP;
    }
    
    
    if (key == GLFW_KEY_R && action == GLFW_PRESS && mode != GLFW_MOD_SHIFT)
    {
        triangle_scale_R.x -= TRIANGLE_MOVEMENT_STEP;
        
        triangle_scale_R.y -= TRIANGLE_MOVEMENT_STEP;
        
        triangle_scale_R.z -= TRIANGLE_MOVEMENT_STEP;
    }
    
    // Camera controls
//    GLfloat cameraSpeed = 0.05f;
//    
//    if (key == GLFW_KEY_W )
//        cameraPos += cameraSpeed * cameraFront;
//    
//    if (key == GLFW_KEY_S )
//        cameraPos -= cameraSpeed * cameraFront;
//    
//    if (key == GLFW_KEY_A && action == GLFW_PRESS)
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    
//    if (key == GLFW_KEY_D && action == GLFW_PRESS)
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    
    // scence control for world orientation
    
    if (key == GLFW_KEY_A && action == GLFW_PRESS) // Pressing key A will toggle between changing orientation of the world or of the axis of rotation
    {
        Key_A = !Key_A;
    }
    
    if(key == GLFW_KEY_D && action == GLFW_PRESS) // Pressing key D should return you to the defaults
    {
        rotation_Angle = 0.0f;
        Coordinates_Angle_X = 0.0f;
        Coordinates_Angle_Z = 0.0f;
    }
    
    if (key == GLFW_KEY_UP )
    {
      
        Coordinates_Angle_X += COORDINATE_ROTATE_ANGLE_STEP;
    }
    
    if (key == GLFW_KEY_DOWN )
    {
        
        Coordinates_Angle_X -= COORDINATE_ROTATE_ANGLE_STEP;
    }
    
    
    if (key == GLFW_KEY_LEFT )
        if(Key_A == false)
    {
        
        Coordinates_Angle_Z += COORDINATE_ROTATE_ANGLE_STEP;
    }
    
    if (key == GLFW_KEY_RIGHT )
        if(Key_A == false)
    {
        
        Coordinates_Angle_Z -= COORDINATE_ROTATE_ANGLE_STEP;
    }
    
    // Black Line Rotation controls
    if (key == GLFW_KEY_LEFT )
        if(Key_A == true)
    {
        rotation_Angle -= BLACKLINE_ROTATE_ANGLE_STEP;
    }
    
    if (key == GLFW_KEY_RIGHT && Key_A == true)
        if(Key_A == true)
    {
      rotation_Angle += BLACKLINE_ROTATE_ANGLE_STEP;
    }
    
    
    // rendering mode controls
    
    if(key == GLFW_KEY_P)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glPointSize(5.0);
    }
    
    if(key == GLFW_KEY_T)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    if(key == GLFW_KEY_W)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
}

// mouse functions
bool Left_Click = false;
bool Right_Click = false;
bool Middle_Click = false;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)// mouse click
{
    if (button== GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        Left_Click = true;
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        Left_Click = false;
    }
    
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        Right_Click = true;
    }
    
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        Right_Click = false;
    }
    
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        Middle_Click = true;
    }
    
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        Middle_Click = false;
    }
    
}


GLfloat yaw    = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch  =  0.0f;
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
GLfloat fov =  45.0f;

// mouse
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
    lastX = xpos;
    lastY = ypos;
    
    GLfloat sensitivity = 0.05;	// Change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    if(Right_Click)
    {
        yaw += xoffset;
    }
    
    if(Middle_Click)
    {
        pitch += yoffset;
    }
 
    
    if(Left_Click == true)
    {
        if (fov >= 1.0f && fov <= 45.0f)
            fov -= yoffset;
        if (fov <= 1.0f)
            fov = 1.0f;
        if (fov >= 45.0f)
            fov = 45.0f;
    }
    
    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 front;
   
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    
   
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}



int main()
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set the major and minor version both to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3 is the OpenGL version we want to use
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // tell GLFW we want to explicitly use the core-profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );// on Mac OS X initialization code for it to work
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE ); // the window should not be resizable by a user
    
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LEARN OPENGL", nullptr, nullptr);// The function returns a GLFWwindow object that we'll later need for other GLFW operations
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return -1;
    }
    
    glfwMakeContextCurrent(window); // tell GLFW to make the context of our window the main context on the current thread
    
    glfwSetKeyCallback(window, key_callback); // Set the required callback functions
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // GLEW manages function pointers for OpenGL so we want to initialize GLEW before we call any OpenGL functions.
    
    glewExperimental = GL_TRUE; // Setting glewExperimental to true ensures GLEW uses more modern techniques for managing OpenGL functionality
    
    if(GLEW_OK !=   glewInit()) // initialize the GLEW library
    {
        std ::cout << "Failed to initialize GLEW" << std::endl;
        
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    // Read the Vertex Shader code from the file
    string vertex_shader_path = "vertex.shader";
    string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_shader_path, ios::in);
    
    if (VertexShaderStream.is_open()) {
        string Line = "";
        while (getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }
    else {
        printf("Impossible to open %s. Are you in the right directory ?\n", vertex_shader_path.c_str());
        getchar();
        exit(-1);
    }
    
    // Read the Fragment Shader code from the file
    string fragment_shader_path = "fragment.shader";
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);
    
    if (FragmentShaderStream.is_open()) {
        std::string Line = "";
        while (getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }
    else {
        printf("Impossible to open %s. Are you in the right directory?\n", fragment_shader_path.c_str());
        getchar();
        exit(-1);
    }
    
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER);//create a shader object, again referenced by an ID. So we store the vertex shader as a GLuint and create the shader with glCreateShader
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource( vertexShader, 1, &VertexSourcePointer, NULL);//attach the shader source code to the shader object and compile the shader:
    glCompileShader(vertexShader);
    
    GLint sucess;
    GLchar infoLog[512];
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &sucess);
    
    if(!sucess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR:: SHADER::VERTEX::COMPLICATION_FAILED\n" << infoLog << std::endl;
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &FragmentSourcePointer, NULL);
    glCompileShader(fragmentShader );
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
    
    if(!sucess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR:: SHADER::FRAGMENT::COMPLICATION_FAILED\n" << infoLog << std::endl;
    }
    
    GLuint shaderProgram = glCreateProgram();// To use the recently compiled shaders we have to link them to a shader program object and then activate this shader program when rendering objects.
    glAttachShader(shaderProgram, vertexShader);//linking the shaders into a program it links the outputs of each shader to the inputs of the next shader
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);//attach the previously compiled shaders to the program object and then link them
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    
    if(!sucess)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR:: SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    glEnable(GL_DEPTH_TEST);
    
    // 3. use the shader program when we want to render an object
    glUseProgram(shaderProgram);//The result is a program object that we can activate by calling glUseProgram with the newly created program object as its argument
    
    GLfloat vertices[] = {
                            // Blue cube
                            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
                            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
                            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        
                            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.5f,
                            0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.5f,
                            0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.5f,
                            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
        
                            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
        
                            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
        
                            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
                            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.5f,
                            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        
                            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
                            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
                            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        
      /Users/xiaoyang/Documents/大学/2017 summer/COMP 371/Triangle/Triangle/vertex.shader                      // red cube
                            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        
                            -0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
                            0.5f, -0.5f,  0.5f,   0.5f, 0.0f, 0.0f,
                            0.5f,  0.5f,  0.5f,   0.5f, 0.0f, 0.0f,
                            0.5f,  0.5f,  0.5f,   0.5f, 0.0f, 0.0f,
                            -0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
                            -0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
        
                            -0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
                            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            -0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
                            -0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
        
                            0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 0.0f,
                            0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
                            0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
        
                            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
                            0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
                            -0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 0.0f,
                            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        
                            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
                            0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
                            0.5f,  0.5f,  0.5f,   0.5f, 0.0f, 0.0f,
                            0.5f,  0.5f,  0.5f,   0.5f, 0.0f, 0.0f,
                            -0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
                            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        
                            // 3 coordinates lines
                            0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                            1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
                            // black line
                            0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
                            0.0f, -1.0f, 0.0f,  0.0f, 0.0f, 0.0f };
    
  //  std::vector<GLfloat> vertices;
  //  loadOBJ("teapot.obj", vertices); //read the vertices from the teapot.obj file
    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //generate one VBO with a buffer ID
    glBindVertexArray(VAO); // To use a VAO all you have to do is bind the VAO
    
    // 1. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// bind the newly created buffer to the GL_ARRAY_BUFFER target with the glBindBuffer function
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copies the previously defined vertex data into the buffer's memory.  the first argument is the type of the buffer we want to copy data into: the vertex buffer object currently bound to the GL_ARRAY_BUFFER target. The second argument specifies the size of the data (in bytes) we want to pass to the buffer; a simple sizeof of the vertex data suffices. The third parameter is the actual data we want to send.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 2. Then set the vertex attributes pointers
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0 );
    glEnableVertexAttribArray(0);
    
    
    
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBindVertexArray(0);
    
    triangle_scale_R = glm::vec3(0.5f, 0.5f, 0.5f);
    triangle_scale_S = glm::vec3(0.5f, 0.5f, 0.5f);
    rotation_Angle = 0.0f;
    Coordinates_Angle_X = 0.0f;
    Coordinates_Angle_Z = 0.0f;
   
    while(!glfwWindowShouldClose(window)) // checks at the start of each loop iteration if GLFW has been instructed to close, if so, the function returns true and the game loop stops running
    {
        
        glfwPollEvents(); // checks if any events are triggered (like keyboard input or mouse movement events) and calls the corresponding functions (which we can set via callback methods). We usually call eventprocessing functions at the start of a loop iteration.

        if(Space_Bar == false)
        {
            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            // Camera/View transformation
            glm::mat4 view_matrix;
            view_matrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);//camera positioned here + looks at origin + up vector
            view_matrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, -4.0f));
            view_matrix = glm::rotate(view_matrix, Coordinates_Angle_X, glm::vec3(1.0f, 0.0f, 0.0f));// pressing up and down button rotation around x axis
            view_matrix = glm::rotate(view_matrix, Coordinates_Angle_Z, glm::vec3(0.0f, 0.0f, 1.0f));// pressing left and right button rotation around z axis
            
            // Get matrix's uniform location and set matrix
            GLuint modelMatrixLoc = glGetUniformLocation(shaderProgram, "model_matrix");
            GLuint viewMatrixLoc = glGetUniformLocation(shaderProgram, "view_matrix");
            GLuint projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projection_matrix");
            
            
            
            glm::mat4 projection_matrix;
            projection_matrix = glm::perspective(fov, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.01f, 100.0f);
            
            
            glUniformMatrix4fv(viewMatrixLoc,  1, GL_FALSE, glm::value_ptr(view_matrix));
            glUniformMatrix4fv(projectionMatrixLoc,  1, GL_FALSE, glm::value_ptr(projection_matrix));
            
            glBindVertexArray(VAO);//take the corresponding VAO, bind it
            
            // Create transformations for Coordinate Lines
            glm::mat4 model_matrix_Line;
            
            model_matrix_Line = glm::translate(model_matrix_Line, glm::vec3(0.0f, 0.0f, 0.0f));
            //model_matrix_Line = glm::rotate(model_matrix_Line, Coordinates_Angle, Coordinates_Rotate_Axis);
            model_matrix_Line = glm::scale(model_matrix_Line, glm::vec3(2.5f, 2.5f, 2.5f));
            
            
            glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(model_matrix_Line)); //broadcast the uniform value to the shaders
            
            
            glm::vec4 blackLine = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
            glm::mat4 trans;
            trans = glm::rotate(trans, rotation_Angle, glm::vec3(0.0f, 0.0f, 1.0f));
            blackLine = trans * blackLine;
            
            glDrawArrays(GL_LINES, 72, 6); // draw the 3 coordiantes Lines
            
            // Create transformations for Black Line
            glm::mat4 model_BlackLine_matrix;
            model_BlackLine_matrix = glm::rotate(model_BlackLine_matrix, rotation_Angle, glm::vec3(0.0f, 0.0f, 1.0f));
            glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(model_BlackLine_matrix));
            glDrawArrays(GL_LINES, 78, 4); // draw the black Line
            
            // Create transformations for CUBE 1
            glm::mat4 model_matrix;
            
            model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, 0.0f));
            model_matrix = glm::rotate(model_matrix, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(blackLine.x, blackLine.y, blackLine.z));
            model_matrix = glm::scale(model_matrix, triangle_scale_S);
            
            
            glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(model_matrix)); //broadcast the uniform value to the shaders
            
            
            glDrawArrays(GL_TRIANGLES, 0, 36);// draw the CUBE 1
            //Since we said at the start we wanted to draw a triangle and I don't like lying to you, we pass in GL_TRIANGLES. The second argument specifies the starting index of the vertex array we'd like to draw; we just leave this at 0. The last argument specifies how many vertices we want to draw, which is 3 (we only render 1 triangle from our data
            
            
            
            // Create transformations for CUBE 2
            glm::mat4 model_matrix2;
            
            model_matrix2 = glm::rotate(model_matrix2, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(blackLine.x, blackLine.y, blackLine.z));
            
            model_matrix2 = glm::translate(model_matrix2, glm::vec3( -1.0f, 0.0f, 0.0f ));
            //model_matrix2 = glm::rotate(model_matrix2, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(blackLine.x, blackLine.y, blackLine.z));
            model_matrix2 = glm::scale(model_matrix2, triangle_scale_R);
            model_matrix2 = glm::scale(model_matrix2, glm::vec3(0.3f, 0.3f, 0.3f));
            
            
            glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(model_matrix2)); //broadcast the uniform value to the shaders
            
            
            
            glDrawArrays(GL_TRIANGLES, 36, 36);//  draw the CUBE 2
            
            glBindVertexArray(0);//unbind the VAO again
            
            
            glfwSwapBuffers(window); // will swap the color buffer (a large buffer that contains color values for each pixel in GLFW's window) that has been used to draw in during this iteration and show it as output to the screen.
        }
        
        
        
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    
    
    glfwTerminate(); // As soon as we exit the game loop we would like to properly clean/delete all resources that were allocated
    return 0;
    
    
    
}


