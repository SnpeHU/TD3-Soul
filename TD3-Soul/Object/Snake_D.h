#pragma once
#pragma once
#include <vector>
#include "Chain_D.h"

class Snake_D {
public:
    Chain_D spine;

	//初始位置   spine(第一个关节的位置，关节个数， 间距约束，角度约束)
    Snake_D(Vector2 origin) : spine(origin, 30, 16, M_PI / 5) {
		pos = origin;
    }

    void resolve() {
        Vector2 headPos = spine.joints[0];
		//Vector2 targetPos = Vector2::add(headPos, Vector2::sub(mousePos, headPos).setMag(2));
        spine.resolve(pos);
    }
    void Input(char* keys, char* prekeys)
    {
		(void)prekeys;
        if (keys[DIK_W])
        {
			pos.y -= 1;
        }
        if (keys[DIK_S])
        {
			pos.y += 1;
        }

        if (keys[DIK_A])
        {
			pos.x -= 1;
        }
        if (keys[DIK_D])
        {
			pos.x += 1;
        }
    }

    void display() {

        spine.display();
    }


private:
    float bodyWidth(int i) {
        switch (i) {
        case 0:
            return 76.0f;
        case 1:
            return 80.0f;
        default:
            return 64.0f - i;
        }
    }

    Vector2 getPos(int i, float angleOffset, float lengthOffset) {
        float angle = spine.angles[i] + angleOffset;
        float width = bodyWidth(i) + lengthOffset;
        return spine.joints[i] + Vector2(cos(angle) * width, sin(angle) * width);
    }
private:
	Vector2 pos;

    //Vector2 normalize(const Vector2& v) {
    //    float mag = sqrt(v.x * v.x + v.y * v.y);
    //    return v / mag;
    //}
};