#pragma once
#include "Hitbox.hpp"
#include "Projectile.hpp"
#include "Background.hpp"
#include "ImageManager.hpp"
#include<vector>
using namespace std;

class Player {
    private:
        int cooldown = 30;
        int speed = 3;
        vector<char> reference{'A', 'D', 'W', 'S'}; // this is the vector I'm comparing with the user input in order to activate the cheat
        vector<char> userInput; // this takes user inputs in order to activate the cheat
        bool rapidFireUnlocked = false; // flag to activateeee
        float rapidFireTimer = 0.0f;
    
    public:
        std::pair<float, float> position;
        HitBox hitBox;

        Player(float x, float y) {
            this->position.first = x;
            this->position.second = y;
            this->hitBox = HitBox(x, y, 30, 30);
        }

        void draw();
        void update();
        void keyInputs();
        void attack();
};