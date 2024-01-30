#include "Camera.h"
#include <cmath>






void Camera::normalize(float* v)
{
	float norm = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= norm; v[1] /= norm; v[2] /= norm;
}

void Camera::cross(float* a, float* b, float* result)
{
	result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

void Camera::subtract(float* a, float* b, float* result)
{
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
}

void Camera::lookAt(float* eye, float* target, float* upVector, float* result)
{
    float f[3], s[3], u[3];
    subtract(target, eye, f);
    normalize(f);
    cross(f, upVector, s);
    normalize(s);
    cross(s, f, u);

    result[0] = s[0];
    result[1] = u[0];
    result[2] = -f[0];
    result[3] = 0.0f;

    result[4] = s[1];
    result[5] = u[1];
    result[6] = -f[1];
    result[7] = 0.0f;

    result[8] = s[2];
    result[9] = u[2];
    result[10] = -f[2];
    result[11] = 0.0f;

    result[12] = -s[0] * eye[0] - s[1] * eye[1] - s[2] * eye[2];
    result[13] = -u[0] * eye[0] - u[1] * eye[1] - u[2] * eye[2];
    result[14] = f[0] * eye[0] + f[1] * eye[1] + f[2] * eye[2];
    result[15] = 1.0f;
}
void Camera::perspective(float fov, float aspectRatio, float near, float far, float* result)
{
    float tanHalfFovy = tan(fov / 2.0f);

    result[0] = 1.0f / (aspectRatio * tanHalfFovy);
    result[1] = 0.0f;
    result[2] = 0.0f;
    result[3] = 0.0f;

    result[4] = 0.0f;
    result[5] = 1.0f / tanHalfFovy;
    result[6] = 0.0f;
    result[7] = 0.0f;

    result[8] = 0.0f;
    result[9] = 0.0f;
    result[10] = -(far + near) / (far - near);
    result[11] = -1.0f;

    result[12] = 0.0f;
    result[13] = 0.0f;
    result[14] = -(2.0f * far * near) / (far - near);
    result[15] = 0.0f;
}