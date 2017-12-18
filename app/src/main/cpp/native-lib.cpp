#include "gl.h"
#include "scene.h"
#include "util.h"
#include <sys/time.h>

#include <android/log.h>
#define TAG "这是C语言："
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
AAssetManager* assetManager = nullptr;
unsigned char* LoadFileContent(const char*path,int&filesize){
    unsigned char*fileContent = nullptr;
    filesize=0;
    AAsset* asset = AAssetManager_open(assetManager,path,AASSET_MODE_UNKNOWN);
    if (asset== nullptr){
        return nullptr;
    }
    filesize=AAsset_getLength(asset);
    fileContent = new unsigned char[filesize+1];
    AAsset_read(asset,fileContent,filesize);

    LOGD("LoadFileContent:%s",fileContent);

    fileContent[filesize]='\0';
    AAsset_close(asset);

    return fileContent;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_zhpeng_jdgltest_NativeUtils_initAssetManager(JNIEnv *env, jclass type, jobject manager) {
    assetManager=AAssetManager_fromJava(env,manager);
    return;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_zhpeng_jdgltest_NativeUtils_onGlCreate(JNIEnv *env, jclass type) {
    init();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_zhpeng_jdgltest_NativeUtils_onGlChanged(JNIEnv *env, jclass type, jfloat w, jfloat h) {

    // TODO
    setViewPortSize(w,h);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_zhpeng_jdgltest_NativeUtils_onGlFrame(JNIEnv *env, jclass type) {
    draw();
}

extern "C" jstring Java_com_example_zhpeng_jdgltest_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


float GetFrameTime(){
    static unsigned long long lastTime = 0,timeCurrent = 0;
    timeval current;
    gettimeofday(&current, nullptr);
    timeCurrent= current.tv_sec*1000+current.tv_usec/1000;
    unsigned long long frameTime = lastTime == 0?0:timeCurrent-lastTime;
    lastTime=timeCurrent;
    return float(frameTime)/1000.0f;
}
