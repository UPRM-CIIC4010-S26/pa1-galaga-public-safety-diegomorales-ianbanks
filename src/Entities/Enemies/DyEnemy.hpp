#pragma once
#include "Enemy.hpp"
static int nextTexture = 0;

class DyEnemy : public Enemy {
    private: 
        float angle = 135;
        float aimAngle = 225;
        bool loop = false;
        int randomNumber;


    public:
        int pointvalue = 100;
        DyEnemy(float x, float y) : Enemy(x, y) { 
            this->cooldown = GetRandomValue(90, 300);
            this->health = 1;
            this->randomNumber = nextTexture;
            nextTexture = 1 - nextTexture;
        }

        void draw() override;
        void update(std::pair<float, float> pos, HitBox target) override;
        void attack(HitBox target) override;
        int getScore() override { return pointvalue; }
};