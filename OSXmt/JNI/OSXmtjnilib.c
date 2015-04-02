//  Copyright 2009 Wayne Keenan
//  Copyright 2012 Konstantin Fick
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//
//  OSXmtjnilib.c - binds to OSX Obj-c multitouch methods
//
//  Created by Konstantin Fick on 22/08/2012.
//
//  mail@kofi.de.com
//
//
//	This is a MODIFIED version of TouchpadObservablejnilib.c
//  Created by Wayne Keenan on 30/05/2009.
//  wayne.keenan@gmail.com
//
//  The modification allows you to bind to a specific multitouch
//  devices instead of binding to the fist one
//
//  The added functionality was made possible by proof of concept published
//  Costantino Pistagna <valvoline -at- gmail -dot- com> at
//  http://hints.macworld.com/article.php?story=2009111308193783
//

#include "com_de_kofi_osxmt_OSXmt.h"

#include <math.h>
#include <unistd.h>
#import <Foundation/Foundation.h>
#include <CoreFoundation/CoreFoundation.h>

#include <stdio.h>

#define MT_CLASS "com/de/kofi/osxmt/OSXmt"
#define MT_METHOD "mtcallback"
#define MT_SIG "(IDIIFFFFFFFFI)V"

typedef struct { float x,y; } mtPoint;
typedef struct { mtPoint pos,vel; } mtReadout;


typedef struct {
	int frame;
	double timestamp;
	int identifier, state, foo3, foo4;
	mtReadout normalized;
	float size;
	int zero1;
	float angle, majorAxis, minorAxis; // ellipsoid
	mtReadout mm;
	int zero2[2];
	float unk2;
} Finger;

typedef void *MTDeviceRef;
typedef int (*MTContactCallbackFunction)(int,Finger*,int,double,int);

MTDeviceRef MTDeviceCreateDefault();
CFMutableArrayRef MTDeviceCreateList(void);

void MTRegisterContactFrameCallback(MTDeviceRef, MTContactCallbackFunction);
void MTDeviceStart(MTDeviceRef, int);
void MTDeviceStop(MTDeviceRef);

static int initOk = 0;
static JavaVM *jvm = NULL;

static MTDeviceRef dev;

static int mtshutdown = 0;

NSMutableArray *deviceList = NULL;

jclass cls;
jmethodID mid;

int mtcallback(int device, Finger *data, int nFingers, double timestamp, int frame) {
	JNIEnv *env = NULL;	
	//if (!(frame % 50)) printf("Native: MT Frame= %d\n", frame);
	if (mtshutdown) return 0;

	int res = (*jvm)->AttachCurrentThread(jvm, (void**)&env, NULL);

	if (res == 0) {
		if (cls != NULL){ 

			if (mid) {

				for (int i=0; i<nFingers; i++) {
					Finger *f = &data[i];
					(*env)->CallStaticVoidMethod(env, cls, mid, f->frame, timestamp, f->identifier, 
							f->state, f->size,
							f->normalized.pos.x, f->normalized.pos.y,
							f->normalized.vel.x, f->normalized.vel.y,
							f->angle, f->majorAxis, f->minorAxis, (i == nFingers-1 ? 1 : 0));
				}
			}
		}
		res = (*jvm)->DetachCurrentThread(jvm);
	}

	return 1;
}

void startMT(int devID) {
	if(deviceList == NULL)
		deviceList = (NSMutableArray*)MTDeviceCreateList(); // grab device list

	if(devID < 0)
		devID = 0;

	else if(devID >= [deviceList count])
		devID = [deviceList count]-1;

	if([deviceList count] == 0) {
		dev = MTDeviceCreateDefault(0);

		MTRegisterContactFrameCallback(dev, mtcallback);
		MTDeviceStart(dev, 1);
	}
	else {
		dev = [deviceList objectAtIndex:devID];

		MTRegisterContactFrameCallback(dev, mtcallback);
		MTDeviceStart(dev, 0);
	}
}

void stopMT() {
	MTDeviceStop(dev);
}


JNIEXPORT jint JNICALL Java_com_de_kofi_osxmt_OSXmt_registerListener(JNIEnv *env, jobject this, jint devID) {

	if (jvm == NULL) 
		(*env)->GetJavaVM(env, &jvm);

	cls = (*env)->FindClass(env, MT_CLASS);

	// make it a global ref so that we can use it in a nother thread.  (TODO: look at weakref for GC)
	cls = (*env)->NewGlobalRef(env, cls);
	if (cls == NULL){ 
		printf("Java class %s not found!\n", MT_CLASS);
		initOk=0;
	} else 	{
		mid = (*env)->GetStaticMethodID(env, cls, MT_METHOD, MT_SIG);
		if (mid == NULL) {
			printf("Java callback method %s not found!\n", MT_METHOD);
			initOk = 0;
		} else {
			startMT(devID);
			initOk = 1;
		}
	}

	return initOk==1?0:-1;
}

JNIEXPORT jint JNICALL Java_com_de_kofi_osxmt_OSXmt_deregisterListener(JNIEnv *env, jobject this) {
	mtshutdown=1;
	//TODO: should use a sync guard incase mtcallback is dispatching to Java.
	if (initOk) {
		stopMT();
		//TODO: delte global ref
	}
	return 0;
}

JNIEXPORT jobjectArray JNICALL Java_com_de_kofi_osxmt_OSXmt_deviceList(JNIEnv *env, jclass this) {
	deviceList = (NSMutableArray*)MTDeviceCreateList(); // grab device list

	jobjectArray ret;

	ret = (jobjectArray)(*env)->NewObjectArray(env, [deviceList count],
			(*env)->FindClass(env, "java/lang/String"),
			(*env)->NewStringUTF(env, ""));

	for(int i = 0; i<[deviceList count]; i++) { //iterate available devices
		NSString *devNSStringID = [NSString stringWithFormat:@"%@", [deviceList objectAtIndex:i]];
		const char *devID = [devNSStringID UTF8String];
		(*env)->SetObjectArrayElement(env, ret, i, (*env)->NewStringUTF(env, devID));

		//NSLog(@"%@\n", [deviceList objectAtIndex:i]);
	}

	return(ret);
}
