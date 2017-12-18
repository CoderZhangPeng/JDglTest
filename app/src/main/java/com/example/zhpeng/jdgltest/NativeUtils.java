package com.example.zhpeng.jdgltest;

import android.content.res.AssetManager;

/**
 * Created by zhpeng on 2017/11/21.
 */

public class NativeUtils {
    static {
        System.loadLibrary("native-lib");
    }

    public static native void initAssetManager(AssetManager manager);

    public static native void onGlCreate();

    public static native void onGlChanged(float w,float h);

    public static native void onGlFrame();

}
