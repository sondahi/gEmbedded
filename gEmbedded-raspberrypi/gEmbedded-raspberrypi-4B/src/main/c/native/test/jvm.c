#include <jni.h>

JavaVM *jvm = NULL;
JNIEnv *env;

void createJVM() {
    JavaVMInitArgs vm_args;
    JavaVMOption options[2];
    options[0].optionString = "-Djava.class.path=/usr/lib/java";
    options[1].optionString = "-Xcheck:jni";
    vm_args.version = JNI_VERSION_10;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;
    jint result = JNI_CreateJavaVM(&jvm, (void**) &env, &vm_args);

    if (result < 0) {
        printf("Can't create Java VM\n");
    } else {
        jclass syscls = (*env)->FindClass(env,"java/lang/System");
        jfieldID fid = (*env)->GetStaticFieldID(env,syscls, "out", "Ljava/io/PrintStream;");
        jobject out = (*env)->GetStaticObjectField(env,syscls, fid);
        jclass pscls = (*env)->FindClass(env,"java/io/PrintStream");
        jmethodID mid = (*env)->GetMethodID(env,pscls, "println", "(Ljava/lang/String;)V");
        jchar *cppstr = (jchar *) "Hello World";
        jstring str = (*env)->NewString(env,cppstr, sizeof(jchar));
        (*env)->CallVoidMethod(env,out, mid, str);
    }
}

void destroyJVM() {
    if(jvm == NULL){
        printf("can not destroy jvm");
    } else{
        (*jvm)->DestroyJavaVM(jvm);
        printf("jvm destroyed successfuly");
    }
}