/**
 * @author Gökay Cömert
 */

#include "gpioexception.h"
#include "jnicontroller.h"

GPIO_STATUS gpioStatusCheck(JNIEnv *env, const GPIO_STATUS status){

    switch (status) {
        case GPIO_DEVICE_FILE_OPEN_ERROR: {
            char message[250]; // performance check
            sprintf(message, "GPIO device file could not be opened");
            jniController.throwANewJNIException(env, message);
            return GPIO_EXCEPTION_OCCURRED;
        }
        case GPIO_MEMORY_MAP_ERROR: {
            char message[250]; // performance check
            sprintf(message, "GPIO memory mapping could not be setup");
            jniController.throwANewJNIException(env, message);
            return GPIO_EXCEPTION_OCCURRED;
        }
        case GPIO_MEMORY_UNMAP_ERROR: {
            char message[250]; // performance check
            sprintf(message, "GPIO memory unmapping could not be setup");
            jniController.throwANewJNIException(env, message);
            return GPIO_EXCEPTION_OCCURRED;
        }
        case GPIO_PIN_FUNCTION_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Pin function could not be setup");
            jniController.throwANewJNIException(env, message);
            return GPIO_EXCEPTION_OCCURRED;
        }
        case GPIO_PUD_STATUS_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Pull-up Pull-down status could not be setup");
            jniController.throwANewJNIException(env, message);
            return GPIO_EXCEPTION_OCCURRED;
        }
        case GPIO_GET_LINE_EVENT_IOCTL_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I/O control could not be setup");
            jniController.throwANewJNIException(env, message);
            return GPIO_EXCEPTION_OCCURRED;
        }
        default: {
            return GPIO_SUCCESS;
        }
    }

}