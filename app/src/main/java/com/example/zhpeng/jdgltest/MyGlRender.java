package com.example.zhpeng.jdgltest;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by zhpeng on 2017/11/21.
 */

public class MyGlRender implements GLSurfaceView.Renderer{
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeUtils.onGlCreate();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeUtils.onGlChanged(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        NativeUtils.onGlFrame();
    }
}
