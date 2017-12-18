//
// Created by 张鹏 on 2017/11/24.
//

#ifndef JDGLTEST_VERTEXBUFFER_H
#define JDGLTEST_VERTEXBUFFER_H

#endif //JDGLTEST_VERTEXBUFFER_H
#pragma once

#include "gl.h"
struct Vertex{
    float Position[4];//位置
    float Color[4];//颜色
    float Texcoord[4];//贴图
    float Normal[4];//法线
};

class VertexBuffer{
public:
    Vertex *mVertexes;
    int mVertexCount;//vertexbuffer 有多少个点。
    void SetSize(int vertexCount);//设置当前的vertexbuffer有多大。


    //index 设置第几个点
    void SetPosition(int index,float x,float y,float z,float w=1.0f);
    void SetColor(int index,float r,float g,float b,float a=1.0f);
    void SetTexcoord(int index,float x,float y);
    void SetNormal(int index,float x,float y,float z);


};