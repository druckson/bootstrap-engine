#ifndef GL_MISC
#define GL_MISC
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;

void printGLErrors(const string location) {
    GLuint error = glGetError();
    if (error) cout << location << ": " << gluErrorString(error) << endl;
}

void printShaderInfoLog(const string location, GLuint shader)
{
    int infoLogLen = 0;
    int charsWritten = 0;
    GLchar *infoLog;
    
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
    
    if (infoLogLen > 0)
    {
        infoLog = new GLchar[infoLogLen];
        glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
        cout << location << ": " << endl << infoLog << endl;
        delete [] infoLog;
    }
}

GLuint createVertexShader(const string shaderFile) {
    const char *cShaderFile = shaderFile.c_str();
    const GLint len = shaderFile.length();
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &cShaderFile, &len);
    glCompileShader(shader);

    printShaderInfoLog("Vertex Shader", shader);
    printGLErrors("Vertex Shader");
    return shader;
}

GLuint createFragmentShader(const string shaderFile) {
    const char *cShaderFile = shaderFile.c_str();
    const GLint len = shaderFile.length();
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &cShaderFile, &len);
    glCompileShader(shader);

    printShaderInfoLog("Fragment Shader", shader);
    printGLErrors("Fragment Shader");
    return shader;
}

GLuint createShaderProgram(const string vertexShaderFile, const string fragmentShaderFile) {
    GLuint vertexShader = createVertexShader(vertexShaderFile);
    GLuint fragmentShader = createFragmentShader(fragmentShaderFile);
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    printGLErrors("Shader Program");
    return program;
}

#endif
