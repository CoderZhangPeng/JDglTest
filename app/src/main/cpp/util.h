//
// Created by zhpeng on 2017/11/21.
//

#pragma once

#include "gl.h"

unsigned char* LoadFileContent(const char*path,int&filesize);

GLuint CompileShader(GLenum shaderTyoe,const char* shaderCode);

GLuint CreateProgram(GLuint vsShader,GLuint fsShader);

float GetFrameTime();//计算每帧消耗的时间

unsigned char* DecodeBMP(unsigned char*bmpFileData,int &width,int&height);//解码bmp 返回像素数据的起始地址

//创建纹理对象
GLuint CreateTexture2D(unsigned char* pixelData,int width,int height,GLenum type);

GLint CreateTexture2DFromBMP(const char* bmpPath);


//GLenum GL枚举的无符号整型
/**
 * bufferType buffer 的类型
 * size buffer的大小
 * usage GL_STATIC_DRAW
 * data 数据源
 */
GLint CreateBufferObject(GLenum bufferType,GLsizeiptr size,GLenum usage,void*data= nullptr);