#pragma once
#include "MyVector2.h"
#include <cassert>
struct Matrix3x3 {
	float m[3][3];
};

inline Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 result = {};
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	return result;

}

inline Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 result = {};
	result.m[0][0] = cosf(theta);
	result.m[0][1] = -sinf(theta);
	result.m[1][0] = sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[2][2] = 1.0f;
	return result;

}

inline Matrix3x3 Inverse(const Matrix3x3 m)
{
	Matrix3x3 result = {};
	float det = m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1];
	float invDet = 1.0f / det;
	result.m[0][0] = (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) * invDet;
	result.m[0][1] = -(m.m[0][1] * m.m[2][2] - m.m[0][2] * m.m[2][1]) * invDet;
	result.m[0][2] = (m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1]) * invDet;

	result.m[1][0] = -(m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) * invDet;
	result.m[1][1] = (m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0]) * invDet;
	result.m[1][2] = -(m.m[0][0] * m.m[1][2] - m.m[0][2] * m.m[1][0]) * invDet;

	result.m[2][0] = (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]) * invDet;
	result.m[2][1] = -(m.m[0][0] * m.m[2][1] - m.m[0][1] * m.m[2][0]) * invDet;
	result.m[2][2] = (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]) * invDet;
	return result;
}

inline Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom)
{
	Matrix3x3 result = {};
	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1.0f;
	return result;
}

inline Matrix3x3 MakeViewportMartrix(float left, float top, float width, float height)
{
	Matrix3x3 result = {};
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -(height / 2.0f);
	result.m[2][0] = left + width / 2.0f;
	result.m[2][1] = top + height / 2.0f;
	result.m[2][2] = 1.0f;
	return result;
}

inline Matrix3x3 Multiply(const Matrix3x3& matrix1, const Matrix3x3& matrix2) {
	Matrix3x3 result = {};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;
}

inline Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result = {};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}