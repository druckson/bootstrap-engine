#include "Graphics.h"
#include "../tools/ImageLoader.h"

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

    glfwMakeContextCurrent(this->_window);
    glewInit();
      
    int width, height;
    glfwGetFramebufferSize(this->_window, &width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glScaled(50./(double)width, 50./(double)height, 1.);

    glGenBuffers(5, this->_vbos);

    this->_shaderProgram = createShaderProgram("\
    void main() {\
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
    }\
    ", "\
    void main() {\
        gl_FragColor = gl_Color;\
    }\
    ");

    glGenTextures(5, this->_textures);

    ImageLoader *img = new ImageLoader();
    img->loadImage("assests/images/crossnrm.jpg", &this->_textures[0]);
}

void Graphics::AddEntity(Entity entity, void *data) {
    Sprite *obj = new Sprite();
    obj->index = this->_currentIndex++;


    this->_colors[obj->index*9+0] = 1.0f;
    this->_colors[obj->index*9+1] = 0.0f;
    this->_colors[obj->index*9+2] = 0.0f;

    this->_colors[obj->index*9+3] = 0.0f;
    this->_colors[obj->index*9+4] = 1.0f;
    this->_colors[obj->index*9+5] = 0.0f;

    this->_colors[obj->index*9+6] = 0.0f;
    this->_colors[obj->index*9+7] = 0.0f;
    this->_colors[obj->index*9+8] = 1.0f;

    obj->position[0] = 0.01 * (double)((rand() % 400) - 200.);
    obj->position[1] = 0.01 * (double)((rand() % 400) - 200.);
    obj->position[2] = 0.01 * (double)((rand() % 400) - 200.);

    this->_entities[entity] = obj;
}

void Graphics::RemoveEntity(Entity entity) {}

void Graphics::Update(float dt) {
    for (auto &item: this->_entities) {
        //item.second->position[0] += 0.1*cos((float)glfwGetTime());
        item.second->position[0] += 0.1*((float)(rand() % 100) / 100.0f - 0.5);
        item.second->position[1] += 0.1*((float)(rand() % 100) / 100.0f - 0.5);
    }
}

void Graphics::Draw() {
    if (glfwWindowShouldClose(this->_window))
        glfwDestroyWindow(this->_window);
    else {
        for (auto &item: this->_entities) {
            this->_vertices[item.second->index*6+0] = -0.6f + item.second->position[0];
            this->_vertices[item.second->index*6+1] = -0.4f + item.second->position[1];
                                       
            this->_vertices[item.second->index*6+2] =  0.6f + item.second->position[0];
            this->_vertices[item.second->index*6+3] = -0.4f + item.second->position[1];
                                       
            this->_vertices[item.second->index*6+4] =  0.0f + item.second->position[0];
            this->_vertices[item.second->index*6+5] =  0.6f + item.second->position[1];
        }
        
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glScaled(1.5, 1.5, 1.5);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        {   // Draw sprite VBO
            glEnableClientState(GL_VERTEX_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
            glBufferData(GL_ARRAY_BUFFER, this->_currentIndex*6*sizeof(float), this->_vertices, GL_STATIC_DRAW);
            glVertexPointer(2, GL_FLOAT, 2*sizeof(float), 0);

            glEnableClientState(GL_COLOR_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[1]);
            glBufferData(GL_ARRAY_BUFFER, this->_currentIndex*9*sizeof(float), this->_colors, GL_STATIC_DRAW);
            glColorPointer(3, GL_FLOAT, 3*sizeof(float), 0);

            //glUseProgram(this->_shaderProgram);
            glDrawArrays(GL_TRIANGLES, 0, 3*this->_currentIndex);
        }
        glPopMatrix();

        glFlush();  

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
    printGLErrors("Draw");
    return;
}
