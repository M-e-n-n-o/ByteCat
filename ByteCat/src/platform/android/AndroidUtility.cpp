#ifdef BC_PLATFORM_ANDROID
#include "bcpch.h"
#include "byteCat/utils/Utility.h"

#include <cstdarg>
#include <android/asset_manager.h>
#include <android/native_activity.h>
#include <jni.h>
#include <glfm.h>
#define FILE_COMPAT_ANDROID_ACTIVITY glfmAndroidGetActivity()

namespace BC
{
	namespace Utils
	{
        jstring permissionName(JNIEnv* lJNIEnv, const char* perm_name)
        {
            // nested class permission in class android.Manifest,
            // hence android 'slash' Manifest 'dollar' permission
            jclass ClassManifestpermission = lJNIEnv->FindClass(
                "android/Manifest$permission"
            );

            jfieldID lid_PERM = lJNIEnv->GetStaticFieldID(
                ClassManifestpermission, perm_name, "Ljava/lang/String;"
            );

            jstring ls_PERM = (jstring)(lJNIEnv->GetStaticObjectField(
                ClassManifestpermission, lid_PERM
            ));

            return ls_PERM;
        }

        bool hasPermission(const char* perm_name)
        {
            ANativeActivity* nativeActivity = FILE_COMPAT_ANDROID_ACTIVITY;

            JavaVM* lJavaVM = nativeActivity->vm;
            JNIEnv* lJNIEnv = nullptr;
            bool lThreadAttached = false;

            // Get JNIEnv from lJavaVM using GetEnv to test whether
            // thread is attached or not to the VM. If not, attach it
            // (and note that it will need to be detached at the end
            //  of the function).
            switch (lJavaVM->GetEnv((void**)&lJNIEnv, JNI_VERSION_1_6))
            {
            case JNI_OK:
                break;
            case JNI_EDETACHED:
            {
                jint lResult = lJavaVM->AttachCurrentThread(&lJNIEnv, nullptr);
                if (lResult == JNI_ERR)
                {
                    throw std::runtime_error("Could not attach current thread");
                }
                lThreadAttached = true;
            } break;
            case JNI_EVERSION:
                throw std::runtime_error("Invalid java version");
            }

            bool result = false;

            jstring ls_PERM = permissionName(lJNIEnv, perm_name);

            jint PERMISSION_GRANTED = jint(-1);
            {
                jclass ClassPackageManager = lJNIEnv->FindClass(
                    "android/content/pm/PackageManager"
                );
                jfieldID lid_PERMISSION_GRANTED = lJNIEnv->GetStaticFieldID(
                    ClassPackageManager, "PERMISSION_GRANTED", "I"
                );
                PERMISSION_GRANTED = lJNIEnv->GetStaticIntField(
                    ClassPackageManager, lid_PERMISSION_GRANTED
                );
            }
            {
                jobject activity = nativeActivity->clazz;
                jclass ClassContext = lJNIEnv->FindClass(
                    "android/content/Context"
                );
                jmethodID MethodcheckSelfPermission = lJNIEnv->GetMethodID(
                    ClassContext, "checkSelfPermission", "(Ljava/lang/String;)I"
                );
                jint int_result = lJNIEnv->CallIntMethod(
                    activity, MethodcheckSelfPermission, ls_PERM
                );
                result = (int_result == PERMISSION_GRANTED);
            }

            if (lThreadAttached) {
                lJavaVM->DetachCurrentThread();
            }

            return result;
        }

        void requestPermissions(std::initializer_list<const char*> permissions)
        {
            ANativeActivity* nativeActivity = FILE_COMPAT_ANDROID_ACTIVITY;
            JavaVM* lJavaVM = nativeActivity->vm;
            JNIEnv* lJNIEnv = nullptr;
            bool lThreadAttached = false;

            // Get JNIEnv from lJavaVM using GetEnv to test whether
            // thread is attached or not to the VM. If not, attach it
            // (and note that it will need to be detached at the end
            //  of the function).
            switch (lJavaVM->GetEnv((void**)&lJNIEnv, JNI_VERSION_1_6))
            {
            case JNI_OK:
                break;
            case JNI_EDETACHED:
            {
                jint lResult = lJavaVM->AttachCurrentThread(&lJNIEnv, nullptr);
                if (lResult == JNI_ERR)
                {
                    throw std::runtime_error("Could not attach current thread");
                }
                lThreadAttached = true;
            } break;
            case JNI_EVERSION:
                throw std::runtime_error("Invalid java version");
            }

            jobjectArray perm_array = lJNIEnv->NewObjectArray(
                permissions.size(),
                lJNIEnv->FindClass("java/lang/String"),
                lJNIEnv->NewStringUTF("")
            );

            for (int i = 0; i < permissions.size(); i++)
            {
                lJNIEnv->SetObjectArrayElement(
                    perm_array, i,
                    permissionName(lJNIEnv, *(permissions.begin() + i))
                );
            }

            jobject activity = nativeActivity->clazz;

            jclass ClassActivity = lJNIEnv->FindClass(
                "android/app/Activity"
            );

            jmethodID MethodrequestPermissions = lJNIEnv->GetMethodID(
                ClassActivity, "requestPermissions", "([Ljava/lang/String;I)V"
            );

            // Last arg (0) is just for the callback (that I do not use)
            lJNIEnv->CallVoidMethod(
                activity, MethodrequestPermissions, perm_array, 0
            );

            if (lThreadAttached)
            {
                lJavaVM->DetachCurrentThread();
            }
        }

        // void requestFilePermissions()
        // {
        //     LOG_INFO("Requesting Android file permissions...");
        //
        //     ANativeActivity* nativeActivity = FILE_COMPAT_ANDROID_ACTIVITY;
        //     JavaVM* lJavaVM = nativeActivity->vm;
        //     JNIEnv* lJNIEnv = nullptr;
        //     bool lThreadAttached = false;
        //
        //     // Get JNIEnv from lJavaVM using GetEnv to test whether
        //     // thread is attached or not to the VM. If not, attach it
        //     // (and note that it will need to be detached at the end
        //     //  of the function).
        //     switch (lJavaVM->GetEnv((void**)&lJNIEnv, JNI_VERSION_1_6))
        //     {
        //     case JNI_OK:
        //         break;
        //     case JNI_EDETACHED:
        //     {
        //         jint lResult = lJavaVM->AttachCurrentThread(&lJNIEnv, nullptr);
        //         if (lResult == JNI_ERR)
        //         {
        //             throw std::runtime_error("Could not attach current thread");
        //         }
        //         lThreadAttached = true;
        //     } break;
        //     case JNI_EVERSION:
        //         throw std::runtime_error("Invalid java version");
        //     }
        //
        //     jobjectArray perm_array = lJNIEnv->NewObjectArray(
        //         2,
        //         lJNIEnv->FindClass("java/lang/String"),
        //         lJNIEnv->NewStringUTF("")
        //     );
        //
        //     lJNIEnv->SetObjectArrayElement(
        //         perm_array, 0,
        //         permissionName(lJNIEnv, "READ_EXTERNAL_STORAGE")
        //     );
        //
        //     lJNIEnv->SetObjectArrayElement(
        //         perm_array, 1,
        //         permissionName(lJNIEnv, "WRITE_EXTERNAL_STORAGE")
        //     );
        //
        //     jobject activity = nativeActivity->clazz;
        //
        //     jclass ClassActivity = lJNIEnv->FindClass(
        //         "android/app/Activity"
        //     );
        //
        //     jmethodID MethodrequestPermissions = lJNIEnv->GetMethodID(
        //         ClassActivity, "requestPermissions", "([Ljava/lang/String;I)V"
        //     );
        //
        //     // Last arg (0) is just for the callback (that I do not use)
        //     lJNIEnv->CallVoidMethod(
        //         activity, MethodrequestPermissions, perm_array, 0
        //     );
        //
        //     if (lThreadAttached)
        //     {
        //         lJavaVM->DetachCurrentThread();
        //     }
        // }
		
		void Utility::Android::RequestPermissions(std::initializer_list<const char*> permissions)
		{
            bool hasPermissions = true;
			for (const char* p : permissions)
			{
				if (!hasPermission(p))
                {
                    hasPermissions = false;
                }
			}

        	if(!hasPermissions)
        	{
                LOG_INFO("Requesting Android permissions...");
        		requestPermissions(permissions);

        		while(true)
        		{
        			if (hasPermission(*permissions.begin()))
        			{
                        LOG_INFO("Android permissions received");
                        break;
        			}
        		}
        	} else
        	{
                LOG_INFO("Already got Android permissions");
        	}

		}
	}
}

#endif