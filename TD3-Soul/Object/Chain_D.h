#pragma once
#include <vector>
#include <cmath>
#include "Tool/MyVector2.h" // 一个 Vector2 类的实现
#include "Util.h"    //包含 constrainDistance 和 constrainAngle 函数
#include "Novice.h"

class Chain_D{
public:
	std::vector<Vector2> joints; //关节的位置
	float linkSize; //关节之间的间距

    
	std::vector<float> angles;//关节之间的角度差
	float angleConstraint; //两个相邻关节之间的最大角度差，大=柔软，小=刚性
    

    //Chain(Vector2 origin, int jointCount, float linkSize) : Chain(origin, jointCount, linkSize, TWO_PI) {}

    Chain_D(Vector2 origin, int jointCount, float linkSize, float angleConstraint) {
        this->linkSize = linkSize;
        this->angleConstraint = angleConstraint;
        joints.push_back(origin.copy());
        angles.push_back(0.0f);
        for (int i = 1; i < jointCount; i++) {
            joints.push_back(Vector2::add(joints[i - 1], Vector2(0, this->linkSize)));
            angles.push_back(0.0f);
        }
    }

	//通过一个点的位置，处理链条
    void resolve(Vector2 pos) {
        angles[0] = Vector2::sub(pos, joints[0]).heading();
        joints[0] = pos;
        for (auto i = 1; i < joints.size(); i++) {
            float curAngle = Vector2::sub(joints[i - 1], joints[i]).heading();
            angles[i] = constrainAngle(curAngle, angles[i - 1], angleConstraint);
            joints[i] = Vector2::sub(joints[i - 1], Vector2::fromAngle(angles[i]).setMag(linkSize));
        }
    }

	//通过两个点的位置，处理链条（第一个点是固定的）（IK处理）
    void fabrikResolve(Vector2 pos, Vector2 anchor) {
        // Forward pass
        joints[0] = pos;
        for (int i = 1; i < static_cast<int>(joints.size()); i++) {
            joints[i] = constrainDistance(joints[i], joints[i - 1], linkSize);
        }

        // Backward pass
        joints[joints.size() - 1] = anchor;
        for (int i = static_cast<int>(joints.size()) - 2; i >= 0; i--) {
            joints[i] = constrainDistance(joints[i], joints[i + 1], linkSize);
        }
    }

    void display() {

        //setStrokeWeight(8);
        //setStrokeColor(255);
        //for (int i = 0; i < joints.size() - 1; i++) {
        //    Vector2 startJoint = joints[i];
        //    Vector2 endJoint = joints[i + 1];
        //    drawLine(startJoint.x, startJoint.y, endJoint.x, endJoint.y);
        //}

        //setFillColor(42, 44, 53);
        //for (Vector2 joint : joints) {
        //    drawEllipse(joint.x, joint.y, 32, 32);
        //}
        for (Vector2 joint : joints)
        {
			Novice::DrawEllipse(static_cast<int>(joint.x), static_cast<int>(joint.y), 32, 32,0.0f, WHITE,kFillModeSolid);
        }

    }
};