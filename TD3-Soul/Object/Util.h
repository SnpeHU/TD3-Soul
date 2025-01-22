#pragma once
#include "Tool/MyVector2.h"
#include "Tool/MyVector3.h"
#define M_PI (float)3.14159265358979323846
#define TWO_PI (2 * M_PI)

// 限制向量的长度
inline Vector2 constrainDistance(Vector2 pos, Vector2 anchor, float constraint) {
    return Vector2::add(anchor, Vector2::sub(pos, anchor).setMag(constraint));
}
inline Vector3 constrainDistance(Vector3 pos, Vector3 anchor, float constraint) {
    return Vector3::add(anchor, Vector3::sub(pos, anchor).setMag(constraint));
}

// 简化角度（将角度转换到 0 到 2π 之间）
inline float simplifyAngle(float angle) {
    while (angle >= TWO_PI) {
        angle -= TWO_PI;
    }

    while (angle < 0) {
        angle += TWO_PI;
    }

    return angle;
}

// 计算相对角度差
inline float relativeAngleDiff(float angle, float anchor) {
    angle = simplifyAngle(angle + M_PI - anchor);
    anchor = M_PI;

    return anchor - angle;
}

// 限制角度
inline float constrainAngle(float angle, float anchor, float constraint) {
    // 第一步：计算 angle 和 anchor 之间的相对角度差，并判断其绝对值是否小于等于 constraint
    if (abs(relativeAngleDiff(angle, anchor)) <= constraint) {
        // 如果相对角度差的绝对值小于等于 constraint，则返回简化后的 angle
        return simplifyAngle(angle);
    }
    // 第二步：如果相对角度差大于 constraint，则返回简化后的 anchor - constraint
    if (relativeAngleDiff(angle, anchor) > constraint) {
        return simplifyAngle(anchor - constraint);
    }
    // 第三步：如果相对角度差小于 -constraint，则返回简化后的 anchor + constraint
    return simplifyAngle(anchor + constraint);
}



