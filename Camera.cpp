#include "Camera.hpp"

namespace gps {


        Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));

    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, this->cameraUpDirection);
    }


    void Camera::move(MOVE_DIRECTION direction, float speed) {
        //TODO
        if (direction == MOVE_FORWARD) {
            cameraPosition += cameraFrontDirection * speed;
        }
        else if (direction == MOVE_BACKWARD) {
            cameraPosition -= cameraFrontDirection * speed;
        }
        else if (direction == MOVE_RIGHT) {
            cameraPosition += cameraRightDirection * speed;
        }
        else if (direction == MOVE_LEFT) {
            cameraPosition -= cameraRightDirection * speed;
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
         if (pitch > 89.0f)
        pitch = 89.0f;
         if (pitch < -89.0f)
        pitch = -89.0f;

         glm::vec3 direction;
         direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
         direction.y = sin(glm::radians(pitch));
         direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    this->cameraFrontDirection = glm::normalize(direction);
    this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));

    // Recalculate cameraTarget based on cameraPosition and cameraFrontDirection
    this->cameraTarget = cameraPosition + cameraFrontDirection;
        
    }  

   

    
}
