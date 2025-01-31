#pragma once
#include <vector>
#include <cmath>
#include "Tool/MyVector2.h"
#include "Node.h"
#include "Util.h"    //包含 constrainDistance 和 constrainAngle 函数
#include "Novice.h"
#include "Manager/ObjectManager.h"
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG

class Chain {
public:
    std::vector<std::shared_ptr<Node>> joints; //关节
    //std::vector<Node> joints; //关节的位置
	float linkSize; //关节之间的间距离

    
	//std::vector<float> angles;//关节之间的角度差
	std::vector<std::pair<float, float>> angles; //关节之间的角度差
	//float angleConstraint; //两个相邻关节之间的最大角度差，大=柔软，小=刚性
    float azimuthalConstraint; //方向角的最大角度差
    float polarConstraint; //极角的最大角度差
    

    Chain() = default;
    Chain(Vector3 origin, int jointCount, float linkSize, float azimuthalConstraint, float polarConstraint) {
        this->linkSize = linkSize;
		this->azimuthalConstraint = azimuthalConstraint;
        this->polarConstraint = polarConstraint;
        
		//初始化关节，并将其添加到链条中，每个关节由ObjectManager管理
		joints.push_back(std::make_shared<Node>(origin));
		
		//angles.push_back(0.0f);
        angles.push_back({ 0.0f, 0.0f });
        for (int i = 1; i < jointCount; i++) {
			joints.push_back(std::make_shared<Node>(Vector3::add(joints[i-1]->GetPos(),Vector3(0,this->linkSize,0))));
			//angles.push_back(0.0f);
            angles.push_back({ 30.0f, 0.0f });
        }

		//添加到ObjectManager
        for (auto& joint : joints)
        {
			ObjectManager::Instance()->AddObject(joint);
        }

    }

	//通过一个点的位置，处理链条
    void resolve(Vector3 pos,Vector3 toward) {
		Vector3 p = pos;
		//计算toward的方位角和极角
		auto [toward_a, toward_p] = calculateAngles(toward);
        auto [azimuthal, polar] = calculateAngles(Vector3::sub(toward, joints[0]->GetPos())); // 计算第一个关节与给定位置之间的角度
		angles[0].first = constrainAngle(azimuthal, toward_a, azimuthalConstraint);
		angles[0].second = constrainAngle(polar, toward_p, polarConstraint);
        //angles[0] = { azimuthal, polar };
        joints[0]->SetPos(p);
        for (auto i = 1; i < joints.size(); i++) {
            auto [curAzimuthal, curPolar] = Vector3::sub(joints[i - 1]->GetPos(), joints[i]->GetPos()).heading(); // 计算两个点之间的角度
            angles[i].first = constrainAngle(curAzimuthal, angles[i - 1].first, azimuthalConstraint);
            angles[i].second = constrainAngle(curPolar, angles[i - 1].second, polarConstraint);

            joints[i]->SetPos(Vector3::sub(joints[i - 1]->GetPos(), Vector3::fromAngle(angles[i].second, angles[i].first).setMag(linkSize))); // 使用fromAngle方法生成新的位置
			//joints[i]->SetPos(Vector3::sub(joints[i - 1]->GetPos(), Vector3::fromAngle(curPolar, curAzimuthal).setMag(linkSize))); // 使用fromAngle方法生成新的位置
        }
#ifdef _DEBUG
        ImGui::Begin("Chain");
		for (int i = 0; i < joints.size(); i++) {
            ImGui::Text("Joint %d: (%.2f, %.2f, %.2f)", i, joints[i]->GetPos().x, joints[i]->GetPos().y, joints[i]->GetPos().z);
        }
        //angle
		for (int i = 0; i < joints.size(); i++) {
			ImGui::Text("angle %d: (%.2f, %.2f)", i, angles[i].first, angles[i].second);
		}

        ImGui::End();

#endif
        
    }




	//通过两个点的位置，处理链条（第一个点是固定的）（IK处理）
    void fabrikResolve(Vector2 pos, Vector2 anchor) {
        Vector2 p = pos;
		Vector2 a = anchor;
        // Forward pass
       // joints[0] = pos;
        //for (int i = 1; i < static_cast<int>(joints.size()); i++) {
        //    joints[i] = constrainDistance(joints[i], joints[i - 1], linkSize);
        //}

        //// Backward pass
        //joints[joints.size() - 1] = anchor;
        //for (int i = static_cast<int>(joints.size()) - 2; i >= 0; i--) {
        //    joints[i] = constrainDistance(joints[i], joints[i + 1], linkSize);
        //}
    }

    private:
        // 计算向量的方位角和极角
        std::pair<float, float> calculateAngles(const Vector3& vec) const {
            float azimuthal = atan2(vec.y, vec.x);
            float polar = atan2(sqrt(vec.x * vec.x + vec.y * vec.y), vec.z);
            return { azimuthal, polar };
        }
};