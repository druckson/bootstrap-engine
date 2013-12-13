#include "Graphics.h"
#include "../tools/ImageLoader.h"

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

    // Set up directional light
    this->lightAngle = 0;

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
        gl_TexCoord[0] = gl_MultiTexCoord0;\
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
    }\
    ", "\
    uniform vec3 light;\
    uniform sampler2D diffuseMap;\
    uniform sampler2D normalMap;\
    void main() {\
        vec4 diffuse = texture2D(diffuseMap, gl_TexCoord[0].st);\
        vec3 normal = (texture2D(normalMap, gl_TexCoord[0].st).rgb - 0.5) * 2.0;\
        float intensity = dot(normalize(light), normalize(normal.xyz));\
        gl_FragColor = diffuse * intensity;\
    }\
    ");

    glGenTextures(5, this->_textures);

    ImageLoader *img = new ImageLoader();
    img->loadImage("./assets/images/crossColor.jpg", &this->_textures[0]);
    img->loadImage("./assets/images/crossnrm.jpg", &this->_textures[1]);
    printGLErrors("Image load");
}

void Graphics::AddEntity(Entity entity, void *data) {
    Sprite *obj = new Sprite();
    obj->index = this->_currentIndex++;


    this->_colors[obj->index*18+0] = 1.0f;
    this->_colors[obj->index*18+1] = 0.0f;
    this->_colors[obj->index*18+2] = 0.0f;

    this->_colors[obj->index*18+3] = 0.0f;
    this->_colors[obj->index*18+4] = 1.0f;
    this->_colors[obj->index*18+5] = 0.0f;

    this->_colors[obj->index*18+6] = 0.0f;
    this->_colors[obj->index*18+7] = 0.0f;
    this->_colors[obj->index*18+8] = 1.0f;

    this->_colors[obj->index*18+9] =  0.0f;
    this->_colors[obj->index*18+10] = 1.0f;
    this->_colors[obj->index*18+11] = 0.0f;

    this->_colors[obj->index*18+12] = 0.0f;
    this->_colors[obj->index*18+13] = 0.0f;
    this->_colors[obj->index*18+14] = 1.0f;

    this->_colors[obj->index*18+15] = 1.0f;
    this->_colors[obj->index*18+16] = 1.0f;
    this->_colors[obj->index*18+17] = 1.0f;

    this->_uvs[obj->index*12+0] = 0.0f;
    this->_uvs[obj->index*12+1] = 0.0f;

    this->_uvs[obj->index*12+2] = 1.0f;
    this->_uvs[obj->index*12+3] = 0.0f;

    this->_uvs[obj->index*12+4] = 0.0f;
    this->_uvs[obj->index*12+5] = 1.0f;

    this->_uvs[obj->index*12+6] = 0.0f;
    this->_uvs[obj->index*12+7] = 1.0f;

    this->_uvs[obj->index*12+8] = 1.0f;
    this->_uvs[obj->index*12+9] = 0.0f;

    this->_uvs[obj->index*12+10] = 1.0f;
    this->_uvs[obj->index*12+11] = 1.0f;

    obj->position[0] = 0.9 * (double)((rand() % 400) - 200.);
    obj->position[1] = 0.9 * (double)((rand() % 400) - 200.);
    obj->position[2] = 0.9 * (double)((rand() % 400) - 200.);

    this->_entities[entity] = obj;
}

void Graphics::RemoveEntity(Entity entity) {}

void Graphics::Update(float dt) {
    this->lightAngle += dt*2.0f;
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
            this->_vertices[item.second->index*12+0] =  -0.5f + item.second->position[0];
            this->_vertices[item.second->index*12+1] =  -0.5f + item.second->position[1];
                                       
            this->_vertices[item.second->index*12+2] =   0.5f + item.second->position[0];
            this->_vertices[item.second->index*12+3] =  -0.5f + item.second->position[1];
                                       
            this->_vertices[item.second->index*12+4] =  -0.5f + item.second->position[0];
            this->_vertices[item.second->index*12+5] =   0.5f + item.second->position[1];
                                       
            this->_vertices[item.second->index*12+6] =  -0.5f + item.second->position[0];
            this->_vertices[item.second->index*12+7] =   0.5f + item.second->position[1];
                                       
            this->_vertices[item.second->index*12+8] =   0.5f + item.second->position[0];
            this->_vertices[item.second->index*12+9] =  -0.5f + item.second->position[1];

            this->_vertices[item.second->index*12+10] =  0.5f + item.second->position[0];
            this->_vertices[item.second->index*12+11] =  0.5f + item.second->position[1];
        }
        
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        double scale = 2.5;
        glScaled(scale, scale, scale);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        {   // Draw sprite VBO
            glEnableClientState(GL_VERTEX_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
            glBufferData(GL_ARRAY_BUFFER, this->_currentIndex*12*sizeof(float), this->_vertices, GL_STATIC_DRAW);
            glVertexPointer(2, GL_FLOAT, 2*sizeof(float), 0);

            //glEnableClientState(GL_COLOR_ARRAY);
            //glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[1]);
            //glBufferData(GL_ARRAY_BUFFER, this->_currentIndex*9*sizeof(float), this->_colors, GL_STATIC_DRAW);
            //glColorPointer(3, GL_FLOAT, 3*sizeof(float), 0);

            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[2]);
            glBufferData(GL_ARRAY_BUFFER, this->_currentIndex*12*sizeof(float), this->_uvs, GL_STATIC_DRAW);
            glTexCoordPointer(2, GL_FLOAT, 2*sizeof(float), 0);

            glActiveTexture(GL_TEXTURE0);
            int textureLocation = glGetUniformLocation(this->_shaderProgram, "diffuseMap");
            if (textureLocation == -1)
                cout << "Invalid diffuse variable" << endl;
            glUniform1i(textureLocation, 0);
            glBindTexture(GL_TEXTURE_2D, this->_textures[0]);
            glEnable(GL_TEXTURE_2D);

            glActiveTexture(GL_TEXTURE1);
            textureLocation = glGetUniformLocation(this->_shaderProgram, "normalMap");
            if (textureLocation == -1)
                cout << "Invalid normals variable" << endl;
            glUniform1i(textureLocation, 1);
            glBindTexture(GL_TEXTURE_2D, this->_textures[1]);
            glEnable(GL_TEXTURE_2D);

            textureLocation = glGetUniformLocation(this->_shaderProgram, "light");
            glUniform3f(textureLocation, sin(this->lightAngle),
                                         cos(this->lightAngle), 0.1f);

            glUseProgram(this->_shaderProgram);
            glDrawArrays(GL_TRIANGLES, 0, 6*this->_currentIndex);

            glDisableClientState(GL_VERTEX_ARRAY);
            //glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        glPopMatrix();

        glFlush();  

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
    printGLErrors("Draw");
    return;
}
