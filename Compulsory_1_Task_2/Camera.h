#pragma once

class Camera
{
public:
	void lookAt(float* cameraPosition, float* target, float* upVector, float* result);

	void perspective(float fov, float aspectRatio, float near, float far, float* result);

	void normalize(float* v);

	void cross(float* a, float* b, float* result);

	void subtract(float* a, float* b, float* result);
};

