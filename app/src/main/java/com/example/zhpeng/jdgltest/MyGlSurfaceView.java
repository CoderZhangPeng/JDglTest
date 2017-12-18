package com.example.zhpeng.jdgltest;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by zhpeng on 2017/11/21.
 */

public class MyGlSurfaceView extends GLSurfaceView{
    public MyGlSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        NativeUtils.initAssetManager(context.getAssets());
        setRenderer(new MyGlRender());
    }
}
