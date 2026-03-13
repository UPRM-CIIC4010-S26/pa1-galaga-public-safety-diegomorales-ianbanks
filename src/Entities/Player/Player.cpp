#include "Player.hpp"
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

void Player::draw() {
    if (HitBox::drawHitbox) this->hitBox.draw();
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{0, 0, 17, 18}, 
                   Rectangle{this->position.first, this->position.second, 30, 30}, 
                   Vector2{0, 0}, 0, WHITE);
}

void Player::update() {
    this->hitBox.box.x = this->position.first;
    this->hitBox.box.y = this->position.second;
    this->cooldown--;

    if (HitBox::Collision(Background::sideWalls.first, this->hitBox)) {
        std::pair<double, double> collision = HitBox::CollisionMargins(this->hitBox, Background::sideWalls.first);
        if (abs(collision.second) < abs(collision.first)) {
            this->position.second += collision.second;
        } else {
            this->position.first += collision.first + 1;
        }
    }
    if (HitBox::Collision(Background::sideWalls.second, this->hitBox)) {
        std::pair<double, double> collision = HitBox::CollisionMargins(this->hitBox, Background::sideWalls.second);
        if (abs(collision.second) < abs(collision.first)) {
            this->position.second += collision.second;
        } else {
            this->position.first += collision.first + 1;
        }
    }
}

void Player::keyInputs() {

    // bool boost = false;
    // int stamina = 500;

    // if (IsKeyDown(KEY_LEFT_SHIFT)) {
    //     boost = true;
    //     while (boost == true) {
    //         stamina--;
    //     }
    // }

    if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) this->position.first -= this->speed;
    if ((IsKeyDown('A') || IsKeyDown(KEY_RIGHT)) && IsKeyDown(KEY_RIGHT_SHIFT)) this->position.first -= this->speed + 0.7;
    if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) this->position.first += this->speed;
    if ((IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) && IsKeyDown(KEY_RIGHT_SHIFT)) this->position.first += this->speed + 0.7;
    if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_SPACE)) this->attack();

    //======================================================================================================

    // this entire code down checks if the keys A-D-W-S are typed in the sequence 
    if (IsKeyPressed('A')) {
        if ( userInput.empty() ) {
            userInput.push_back('A');
        } else { userInput.clear(); }
    }
    if (IsKeyPressed('D')) {
        if ( !userInput.empty() && userInput.back() == 'A') {
            userInput.push_back('D');
        } else { userInput.clear(); }
    }
    if ( IsKeyPressed('W')) {
        if (!userInput.empty() && userInput.back() == 'D') {
            userInput.push_back('W');
        } else { userInput.clear(); }
    }
    if ( IsKeyPressed('S')) {
        if (!userInput.empty() && userInput.back() == 'W') {
            userInput.push_back('S');
        } else { userInput.clear(); }
    }
    if (userInput == reference) {
        burstFireUnlocked = true;
        PlaySound(SoundManager::burstFire);
        burstFireTimer = 2.0f;
        userInput.clear();
    }
    if(burstFireUnlocked) {
        burstFireTimer -= GetFrameTime();
       if (burstFireTimer <= 0.0f) {
            burstFireUnlocked = false;
        }
    }  
}

void Player::attack() {
    if (cooldown <= 0) {
        Projectile::projectiles.push_back(Projectile(position.first + + this->hitBox.box.width / 2, position.second, 0));
        PlaySound(SoundManager::shoot);
        
        if (burstFireUnlocked) 
            cooldown = 5;
        else 
            cooldown = 30;
    }
}