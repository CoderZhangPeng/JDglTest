//
// Created by zhpeng on 2017/11/21.
//

#include "util.h"
#include <android/log.h>
#define TAG "这是C语言："
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
GLuint CompileShader(GLenum shaderTyoe,const char* shaderCode){
    GLint  shader = glCreateShader(shaderTyoe);
    glShaderSource(shader,1,&shaderCode, nullptr);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compileResult);
    if (compileResult==GL_FALSE){
        char szLog[1024] ={0};
        GLsizei  logLen = 0;
        glGetShaderInfoLog(shader,1024,&logLen,szLog);
        printf("编译shader错误：%s\nshader code:\n%s\n",szLog,shaderCode);
        glDeleteShader(shader);
        shader=0;
    }
    return shader;
}


GLuint CreateProgram(GLuint vsShader,GLuint fsShader){
    GLuint  program = glCreateProgram();
    glAttachShader(program,vsShader);
    glAttachShader(program,fsShader);
    glLinkProgram(program);
    glDetachShader(program,vsShader);
    glDetachShader(program,fsShader);
    GLint  nResult;
    glGetProgramiv(program,GL_LINK_STATUS,&nResult);
    if (nResult==GL_FALSE){
        char log[1024] = {0};
        GLsizei  writed = 0;
        glGetProgramInfoLog(program,1024,&writed,log);
        printf("创建程序失败：%s\n",log);
        glDeleteProgram(program);
        program=0;
    }
    return program;
}
//返回像素数据的起始地址
unsigned char* DecodeBMP(unsigned char*bmpFileData,int&width,int&height){
    LOGD("DecodeBMP:%s","1");

    if(0x4D42 == *((unsigned short*)bmpFileData)){//判断是否是位图
        int pixelDataOffset = *((int*)(bmpFileData+10));//
        width = *((int*)(bmpFileData+18));
        height = *((int*)(bmpFileData+22));
        unsigned char*pixelData = bmpFileData+pixelDataOffset;
        for(int i=0;i<width*height*3;i+=3){
            unsigned char temp = pixelData[i];
            pixelData[i] = pixelData[i+2];
            pixelData[i+2] = temp;
        }
    LOGD("DecodeBMP:%s","2");
    return  pixelData;
    }
    return nullptr;
}



/**
 * pixelData  像素数据的起始位置
 * width、height 图像的宽高
 * type 图片的像素类型 rgb rgba
 */
GLuint CreateTexture2D(unsigned char* pixelData,int width,int height,GLenum type){
    GLuint texture;
    glGenTextures(1,&texture);//1 ---申请1个纹理对象 texture---地址
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//纹理过滤函数 较小的纹理贴到较大的多边形
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//较大的纹理贴到较大的多边形
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    //GL_CLAMP ：在边界处双线性处理，但是很多硬件不支持边界处理，故此效果跟GL_CLAMP_TO_EDGE效果看起来相同
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    //将像素数据上传到显卡
    glTexImage2D(GL_TEXTURE_2D,0,type,width,height,0,type,GL_UNSIGNED_BYTE,pixelData);
    glBindTexture(GL_TEXTURE_2D,0);
    return texture;
}


/**
 * 创建纹理
 */
GLint CreateTexture2DFromBMP(const char* bmpPath){
    int fileSize = 0;
    unsigned char *bmpFileContent = LoadFileContent(bmpPath,fileSize);
    LOGD("CreateTexture2DFromBMP:\n%s",bmpFileContent);
    if (bmpFileContent== nullptr){
        return 0;
    }
    int bmpWidth = 0,bmpHeight=0;
    unsigned char*pixlData = DecodeBMP(bmpFileContent,bmpWidth,bmpHeight);
    if (bmpWidth==0){
        delete bmpFileContent;
        return 0;// 默认的纹理单元 0号纹理单元(黑色)
    }
    GLuint texture = CreateTexture2D(pixlData,bmpWidth,bmpHeight,GL_RGB);
    delete bmpFileContent;
    return texture;
}


/**
 * 创建bufferobject
 */
GLint CreateBufferObject(GLenum bufferType,GLsizeiptr size,GLenum usage,void*data /*= nullptr*/){
    GLuint  object;
    glGenBuffers(1,&object);
    glBindBuffer(bufferType,object);
    glBufferData(bufferType,size,data,usage);
    glBindBuffer(bufferType,0);
    return object;
}
