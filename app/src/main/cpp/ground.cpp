//
// Created by 张鹏 on 2017/11/24.
//

#include "ground.h"
void Ground::Init(){
//    Vertex vertex[1600];//表示地形有1600个点
    mVertexBuffer = new VertexBuffer;
    mVertexBuffer->SetSize(1600);
    //生成x-z平面的数据 y坐标写死为-1.0======》组织顶点数据
    for (int z = 0; z < 20; ++z) {
        float zStart = 100.0f - z*10.0f;
        for (int x = 0; x < 20; ++x) {
            int offset = (x+z*20)*4;
            float xStart = x*10.0f-100.0f;
//            vertex[offset].Position[0] = xStart;
//            vertex[offset].Position[1] = -1.0f;
//            vertex[offset].Position[2] = zStart;
//            vertex[offset].Position[3] = 1.0f;
//
//            vertex[offset+1].Position[0] = xStart+10.0f;
//            vertex[offset+1].Position[1] = -1.0f;
//            vertex[offset+1].Position[2] = zStart;
//            vertex[offset+1].Position[3] = 1.0f;
//
//            vertex[offset+2].Position[0] = xStart;
//            vertex[offset+2].Position[1] = -1.0f;
//            vertex[offset+2].Position[2] = zStart-10.0f;
//            vertex[offset+2].Position[3] = 1.0f;
//
//            vertex[offset+3].Position[0] = xStart+10.0f;
//            vertex[offset+3].Position[1] = -1.0f;
//            vertex[offset+3].Position[2] = zStart-10.0f;
//            vertex[offset+3].Position[3] = 1.0f;
            //设置顶点
            mVertexBuffer->SetPosition(offset,xStart,-1.0f,zStart);
            mVertexBuffer->SetPosition(offset+1,xStart+10.0f,-1.0f,zStart);
            mVertexBuffer->SetPosition(offset+2,xStart,-1.0f,zStart-10.0f);
            mVertexBuffer->SetPosition(offset+3,xStart+10.0f,-1.0f,zStart-10.0f);
            //设置法线
            mVertexBuffer->SetNormal(offset,0.0f,1.0f,0.0f);
            mVertexBuffer->SetNormal(offset+1,0.0f,1.0f,0.0f);
            mVertexBuffer->SetNormal(offset+2,0.0f,1.0f,0.0f);
            mVertexBuffer->SetNormal(offset+3,0.0f,1.0f,0.0f);

            //设置颜色 黑白相间
            if((z%2)){

            } else{

            }

        }
    }

    mVBO = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex)*1600,GL_STATIC_DRAW,vertex);
}