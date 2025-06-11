#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "bonus_malus.h"

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

extern BonusMalus bonusMalus;

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 3.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float CAM_HEIGHT = 1.2f;



// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, CAM_HEIGHT, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        position.y = CAM_HEIGHT;
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, CAM_HEIGHT, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    float distanza(float x1, float x2, float z1, float z2) {
        return sqrt((x1 - x2) * (x1 - x2) + (z1 - z2) * (z1 - z2));
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity;
        if (bonusMalus.getIsBonusMalusActive() && bonusMalus.getNumBonusMalusActive() == 1)
            velocity = MovementSpeed * deltaTime * 0.6f;
        else
            velocity = MovementSpeed * deltaTime;
        
        // fix camera height to CAM_HEIGHT
        glm::vec3 front1 = Front;
        front1.y = 0.0;

        //aggiunta di limiti al movimento della camera sul piano        
        if (Position.x > 4.8f)
            Position.x = 4.8f;        
        else if (Position.x < -4.8f)
            Position.x = -4.8f;        
        if (Position.z > 4.8f)
            Position.z = 4.8f;        
        else if (Position.z < -4.8f)
            Position.z = -4.8f;

        //aggiunta di limiti per non entrare nel tavolo attaccato al muro
        // il maxXTavoloMuro corrisponde al muro, gi� limitato precedentemente
        const float minXTavoloMuro = 3.7f;
        const float minZTavoloMuro = -2.11f;
        const float maxZTavoloMuro = 1.97f;
        if (Position.z < maxZTavoloMuro && Position.z > minZTavoloMuro) {
            if (Position.x > minXTavoloMuro)
                Position.x = minXTavoloMuro;
        }
        if (Position.x > minXTavoloMuro) {
            if (Position.z < maxZTavoloMuro + 0.05f && Position.z > 0)
                Position.z = maxZTavoloMuro + 0.05f;
            else if (Position.z > minZTavoloMuro - 0.05f && Position.z < 0)
                Position.z = minZTavoloMuro - 0.05f;
        }

        // aggiunta di limiti per non entrare nell'isola al centro
        const float minXIsola = -1.07f;
        const float maxXIsola = 0.86f;
        const float minZIsola = -1.65f;
        const float maxZIsola = 1.68f;
        if (Position.z < maxZIsola && Position.z > minZIsola) {
            if (Position.x > minXIsola - 0.05f && Position.x < 0)
                Position.x = minXIsola - 0.05f;
            else if (Position.x < maxXIsola + 0.05f && Position.x > 0)
                Position.x = maxXIsola + 0.05f;
        }
        if (Position.x > minXIsola && Position.x < maxXIsola) {
            if (Position.z < maxZIsola + 0.05f && Position.z > 0)
                Position.z = maxZIsola + 0.05f;
            else if (Position.z > minZIsola - 0.05f && Position.z < 0)
                Position.z = minZIsola - 0.05f;
        }

        //aggiunta di limiti per non entrare nel cestino vicino all'isola
        const float minXCestino = -0.60f;
        const float maxXCestino = 0.20f;
        const float minZCestino = -2.15f;
        if (Position.x > minXCestino && Position.x < maxXCestino && distanza(Position.x, -0.25f, Position.z, -1.8f) < 0.5f) {
            if (Position.z > minZCestino - 0.05f)
                Position.z = minZCestino - 0.05f;
        }
        if (Position.z < minZIsola + 0.05f && Position.z > minZCestino && distanza(Position.x, -0.25f, Position.z, -1.8f) < 0.5f) {
            if (Position.x > minXCestino - 0.2f && Position.x < 0)
                Position.x = minXCestino - 0.2f;
            else if (Position.x < maxXCestino + 0.05f /* && Position.x > 0*/)
                Position.x = maxXCestino + 0.05f;
        }

        //aggiunta di limiti per non entrare nel frigo
        //x min e z min corrispondono al muro
        const float maxXFrigo = -3.3f;
        const float maxZFrigo = -3.2f;
        if (Position.z < maxZFrigo) {
            if (Position.x < maxXFrigo) {
                Position.x = maxXFrigo;
            }
        }
        if (Position.x < maxXFrigo) {
            if (Position.z < maxZFrigo + 0.05f) {
                Position.z = maxZFrigo + 0.05f;
            }
        }

        //aggiunta di limiti per non entrare nel mobilio (quello con il forno)
        //x min corrisponde al muro
        const float maxXMobilio = -3.4f;
        const float minZMobilio = -1.99f;
        const float maxZMobilio = 1.97f;
        if (Position.z < maxZMobilio && Position.z > minZMobilio) {
            if (Position.x < maxXMobilio) {
                Position.x = maxXMobilio;
            }
        }
        if (Position.x < maxXMobilio) {
            if (Position.z < maxZMobilio + 0.05f && Position.z > 0) {
                Position.z = maxZMobilio + 0.05f;
            }
            else if (Position.z > minZMobilio - 0.05f && Position.z < 0) {
                Position.z = minZMobilio - 0.05f;
            }
        }


        if (direction == FORWARD)
            Position += front1 * velocity;
        if (direction == BACKWARD)
            Position -= front1 * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif