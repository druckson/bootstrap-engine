#include "Graphics.h"

Graphics::Graphics() {
    if (!glfwInit()) {
        cerr << "ERROR: Failed to initialize GLFW" << endl;    
        exit(-1);
    }
}

Graphics::~Graphics() {
    glfwTerminate();    
}

void Graphics::_printShaderInfoLog(const string location, GLuint shader)
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

void Graphics::_printGLErrors(const string location) {
    GLuint error = glGetError();
    if (error) cout << location << ": " << gluErrorString(error) << endl;
}

void Graphics::Init() {
    this->_window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    this->_currentIndex = 0;

    if (!this->_window) {
        cerr << "ERROR: Failed to set up GLFW window" << endl;    
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(this->_window);
    glewInit();
      
    int width, height;
    glfwGetFramebufferSize(this->_window, &width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glScaled(50./(double)width, 50./(double)height, 1.);

    glGenBuffers(3, this->_vbos);
}

GLuint Graphics::_createVertexShader(const string shaderFile) {
    const char *cShaderFile = shaderFile.c_str();
    const GLint len = shaderFile.length();
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &cShaderFile, &len);
    glCompileShader(shader);

    this->_printShaderInfoLog("Vertex Shader", shader);
    this->_printGLErrors("Vertex Shader");
    return shader;
}

GLuint Graphics::_createFragmentShader(const string shaderFile) {
    const char *cShaderFile = shaderFile.c_str();
    const GLint len = shaderFile.length();
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &cShaderFile, &len);
    glCompileShader(shader);

    this->_printShaderInfoLog("Fragment Shader", shader);
    this->_printGLErrors("Fragment Shader");
    return shader;
}

GLuint Graphics::_createShaderProgram(const string vertexShaderFile, const string fragmentShaderFile) {
    GLuint vertexShader = this->_createVertexShader(vertexShaderFile);
    GLuint fragmentShader = this->_createFragmentShader(fragmentShaderFile);
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glUseProgram(program);
    this->_printShaderInfoLog("Shader Program", program);
    this->_printGLErrors("Shader Program");
    return program;
}

void Graphics::AddEntity(Entity entity, void *data) {
    Sprite *obj = new Sprite();
    obj->index = this->_currentIndex++;

    this->_vertices[obj->index*6+0] = -0.6f;
    this->_vertices[obj->index*6+1] = -0.4f;
    this->_vertices[obj->index*6+2] =  0.6f;
    this->_vertices[obj->index*6+3] = -0.4f;
    this->_vertices[obj->index*6+4] =  0.0f;
    this->_vertices[obj->index*6+5] =  0.6f;

    this->_printGLErrors("Add Entity 1");

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

        //glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, this->_currentIndex*6, this->_vertices, GL_STATIC_DRAW);
        glVertexPointer(2, GL_FLOAT, 2*sizeof(float), 0);
        glDrawArrays(GL_TRIANGLES, 0, 3*this->_currentIndex);

        //for (auto &item: this->_entities) {
        //    glPushMatrix();
        //        glTranslated(item.second->position[0], 
        //                     item.second->position[1], 
        //                     item.second->position[2]);
        //        glEnableClientState(GL_VERTEX_ARRAY);
        //        glBindBuffer(GL_ARRAY_BUFFER, item.second->vbos[0]);
        //        glVertexPointer(3, GL_FLOAT, 3*sizeof(float), 0);

        //        glEnableClientState(GL_COLOR_ARRAY);
        //        glBindBuffer(GL_ARRAY_BUFFER, item.second->vbos[1]);
        //        glColorPointer(3, GL_FLOAT, 3*sizeof(float), 0);

        //        glUseProgram(item.second->shaderProgram);
        //        glDrawArrays(GL_TRIANGLES,0,3);
        //    glPopMatrix();
        //}
        glFlush();  

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
    this->_printGLErrors("Draw");
    return;
}
