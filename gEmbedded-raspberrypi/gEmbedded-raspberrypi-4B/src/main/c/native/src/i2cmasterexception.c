/**
 * @author Gökay Cömert
 */

#include "i2cmasterexception.h"
#include "jnicontroller.h"

I2C_STATUS i2cStatusCheck(JNIEnv *env, const I2C_STATUS status){

    switch (status) {
        case I2C_BUS_DEV_FILE_OPEN_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C bus device file could not be opened");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_UNSUPPORTED_BUS_ERROR:{
            char message[250]; // performance check
            sprintf(message, "I2C bus is not supported");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_BUS_MEM_MAP_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C bus memory mapping could not be configured");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_BUS_MEM_UNMAP_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C bus memory unmapping could not be configured");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_BUS_DIV_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C bus divider could not be configured");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_BUS_CLKT_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C clock stretch timeout could not be configured");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_SEND_ACK_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Slave acknowledge error while sending data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_SEND_CLOCK_TIMEOUT_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Slave timeout error while sending data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_SEND_DATA_LOSS_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Data loss while sending data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_RECEIVE_ACK_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Slave acknowledge error while receiving data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_RECEIVE_CLOCK_TIMEOUT_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Slave timeout error while receiving data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_RECEIVE_DATA_LOSS_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Data loss while receiving data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        default: {
            return I2C_SUCCESS;
        }
    }

}