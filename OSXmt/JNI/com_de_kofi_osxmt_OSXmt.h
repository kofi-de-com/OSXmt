/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_de_kofi_osxmt_OSXmt */

#ifndef _Included_com_de_kofi_osxmt_OSXmt
#define _Included_com_de_kofi_osxmt_OSXmt
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_de_kofi_osxmt_OSXmt
 * Method:    registerListener
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_de_kofi_osxmt_OSXmt_registerListener
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_de_kofi_osxmt_OSXmt
 * Method:    deregisterListener
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_de_kofi_osxmt_OSXmt_deregisterListener
  (JNIEnv *, jclass);

/*
 * Class:     com_de_kofi_osxmt_OSXmt
 * Method:    getDeviceList
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_de_kofi_osxmt_OSXmt_getDeviceList
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
