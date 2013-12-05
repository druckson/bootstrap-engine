#include "Graphics.h"

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

void printGLErrors(const string location) {
    GLuint error = glGetError();
    if (error) cout << location << ": " << gluErrorString(error) << endl;
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

    glUseProgram(program);
    printShaderInfoLog("Shader Program", program);
    printGLErrors("Shader Program");
    return program;
}

Graphics::Graphics() {
    if (!glfwInit()) {
        cerr << "ERROR: Failed to initialize GLFW" << endl;    
        exit(-1);
    }
}

Graphics::~Graphics() {
    glfwTerminate();    
}

void Graphics::Init() {
    this->_window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    this->_currentIndex = 0;

    if (!this->_window) {
        cerr << "ERROR: Failed to set up GLFW window" << endl;    
        glfwTerminate();
        exit(-1);
    }

    this->_shaderProgram = createShaderProgram("\
    void main() {\
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
    }\
    ", "\
    void main() {\
        gl_FragColor = gl_Color;\
    }\
    ");

    glfwMakeContextCurrent(this->_window);
    glewInit();
      
    int width, height;
    glfwGetFramebufferSize(this->_window, &width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glScaled(50./(double)width, 50./(double)height, 1.);

    glGenBuffers(3, this->_vbos);
}

void Graphics::AddEntity(Entity entity, void *data) {
    Sprite *obj = new Sprite();
    obj->index = this->_currentIndex++;

    this->_vertices[obj->index*9+0] = -0.6f;
    this->_vertices[obj->index*9+1] = -0.4f;
    this->_vertices[obj->index*9+2] =  0.0f;

    this->_vertices[obj->index*9+3] =  0.6f;
    this->_vertices[obj->index*9+4] = -0.4f;
    this->_vertices[obj->index*9+5] =  0.0f;

    this->_vertices[obj->index*9+6] =  0.0f;
    this->_vertices[obj->index*9+7] =  0.6f;
    this->_vertices[obj->index*9+8] =  0.0f;

    printGLErrors("Add Entity 1");

    //glBindBuffer(GL_ARRAY_BUFFER, obj->vbos[1]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    //obj->position[0] = 0.006 * (double)((rand() % 400) - 200.);
    //obj->position[1] = 0.006 * (double)((rand() % 400) - 200.);
    //obj->position[2] = 0.006 * (double)((rand() % 400) - 200.);

    this->_entities[entity] = obj;
}

void Graphics::RemoveEntity(Entity entity) {}

void Graphics::Update(float dt) {
    for (auto &item: this->_entities) {
        item.second->position[0] += 0.1*cos((float)glfwGetTime());
    }
}

void Graphics::Draw() {
    if (glfwWindowShouldClose(this->_window))
        glfwDestroyWindow(this->_window);
    else {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(this->_shaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, this->_currentIndex*6, this->_vertices, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 3*sizeof(float), 0);
        glDrawArrays(GL_TRIANGLES, 0, 3*this->_currentIndex);

        glFlush();  

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
    printGLErrors("Draw");
    return;
}
