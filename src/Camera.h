#ifndef CAMERA_H
#define CAMERA_H

#include "Headers.h"

class Camera {
public:
	Camera(glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f)
		, float speed = 3.0f, float rotSpeed = 6.0f);
	glm::mat4 getView();
	void rotateX(float timeDelta);
	void rotateY(float timeDelta);
	void moveForward(float timeDelta, int steps = 1);
	void moveBackward(float timeDelta, int steps = 1);
	void moveRight(float timeDelta, int steps = 1);
	void moveLeft(float timeDelta, int steps = 1);
	void moveUp(float timeDelta, int steps = 1);
	void moveDown(float timeDelta, int steps = 1);
	void setSpeed(float speed);
	void setRotSpeed(float rotSpeed);
protected:
	void recalculateFront();
	bool dirty = false;
	float speed;
	float rotSpeed;
	float yaw, pitch;
	glm::mat4 view;
	glm::vec3 cameraPos, cameraFront, cameraUp;
};

#endif