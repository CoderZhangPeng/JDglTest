//
// Created by zhpeng on 2017/11/21.
//
#include "gl.h"
#include "scene.h"
#include "util.h"
#include <android/log.h>
#define TAG "这是C语言："
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
GLuint program;
GLuint vbo,ebo;
GLint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation,colorLocation;//插槽
GLint texcoordLocation,textureLocation;//声明插槽位置
GLint texture;
glm::mat4 modelMatrix, viewMatrix, projectionMatrix;

void init() {
    //顶点3  颜色3  2D纹理3
    float data[] = {
            -0.2f, -0.2f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,1.0f,  0.0f,0.0f,
             0.2f, -0.2f, 0.0f, 1.0f,  0.0f,1.0f,0.0f,1.0f,  1.0f,0.0f,
             0.0f, 0.2f, 0.0f, 1.0f,   1.0f,0.0f,0.0f,1.0f,  0.5f,1.0f
    };
//    float data[] = {
//            -0.2f, -0.2f, -0.6f, 1.0f,
//            0.2f, -0.2f, -0.6f, -1.0f,
//            0.0f, 0.2f, -0.6f, 1.0f
//    };


//    glGenBuffers(1, &vbo);//生成新缓存对象
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);//绑定缓存对象 当缓存对象创建之后，在使用缓存对象之前，我们需要将缓存对象连接到相应的缓存上
////    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, data, GL_STATIC_DRAW);//将顶点数据拷贝到缓存对象中
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, data, GL_STATIC_DRAW);//将顶点数据拷贝到缓存对象中
//    glBindBuffer(GL_ARRAY_BUFFER, 0);//VBO用0大小的内存缓存初始化该缓存，并且设置VBO的初始状态，如用途与访问属性。

    vbo = CreateBufferObject(GL_ARRAY_BUFFER,sizeof(float) * 30,GL_STATIC_DRAW,data);

    unsigned short indexes[] = {0,1,2};//

//    glGenBuffers(1,&ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*3,indexes,GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    ebo = CreateBufferObject(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned short)*3,GL_STATIC_DRAW,indexes);


    int fileSize = 0;
    unsigned char *shaderCode = LoadFileContent("vs.text", fileSize);
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char *) shaderCode);
    delete shaderCode;
    shaderCode = LoadFileContent("fs.text", fileSize);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char *) shaderCode);
    delete shaderCode;
    program = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);

    //获取插槽
    positionLocation = glGetAttribLocation(program, "position");
    colorLocation = glGetAttribLocation(program,"color");
    texcoordLocation = glGetAttribLocation(program,"texcoord");
    modelMatrixLocation = glGetUniformLocation(program, "modelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "viewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix");
    textureLocation = glGetUniformLocation(program,"U_Texture");
    modelMatrix = glm::translate(0.0f,0.0f,-0.6f);

    texture = CreateTexture2DFromBMP("test.bmp");
}

void setViewPortSize(float w, float h) {
    projectionMatrix = glm::perspective(60.0f, w / h, 0.1f, 1000.0f);
}

void draw() {
    float frameTime = GetFrameTime();
//    LOGD("每一帧的时间：%f",frameTime);
    glClearColor(0.1f, 0.4f, 0.6f, 1.0f);//设置颜色缓存的清除值 就是用来设置这个 “  底色 ” 的，即所谓的背景颜色。glClearColor ( ) 只起到Set 的作用，并不Clear 任何。
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//将缓存清除为预先的设置值  是用来清除屏幕颜色，即将屏幕的所有像素点都还原为 “底色 ”。
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindTexture(GL_TEXTURE_2D,texture);
    glUniform1i(textureLocation,0);


    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
//    glDrawArrays(GL_TRIANGLES, 0, 3);

    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation,4,GL_FLOAT,GL_FALSE, sizeof(float)*10,(void*)(sizeof(float)*4));

    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation,2,GL_FLOAT,GL_FALSE, sizeof(float)*10,(void*)(sizeof(float)*8));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_SHORT,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}