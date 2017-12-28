//
//  Player.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#include "Player.h"

#include <iostream>

Player::Player(double x, double y) {
    x_ = x;
    y_ = y;
}

void Player::addDir(Dir dir) {
    dirs_.insert(dir);
}

void Player::removeDir(Dir dir) {
    dirs_.erase(dir);
}

void Player::tick(double dt) {
    Player::move(dt);
}

void Player::move(double dt) {
    bool moved = false;
    if (dirs_.count(North) && y_ - dt * Env::PLAYER_SPEED > 0) {
        y_ -= dt * Env::PLAYER_SPEED;
        moved = true;
    }
    if (dirs_.count(South) && y_ + dt * Env::PLAYER_SPEED < Env::SCREEN_HEIGHT) {
        y_ += Env::PLAYER_SPEED * dt;
        moved = true;
    }
    if (dirs_.count(East) && x_ + dt * Env::PLAYER_SPEED < Env::SCREEN_WIDTH) {
        x_ += Env::PLAYER_SPEED * dt;
        moved = true;
    }
    if (dirs_.count(West) && x_ - dt * Env::PLAYER_SPEED > 0) {
        x_ -= Env::PLAYER_SPEED * dt;
        moved = true;
    }
    if (moved) {
        lastFrame_ = (lastFrame_ + 1) % 20;
    }
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect r = {0, 32*(lastFrame_/10), 31, 31};
    texture_->render(x_-Env::PLAYER_WIDTH/2, y_-Env::PLAYER_HEIGHT/2, renderer, &r);
}

double Player::x() {
    return x_;
}

double Player::y() {
    return y_;
}

void Player::setTexture(Texture* texture) {
    texture_ = texture;
}

Projectile* Player::generateProjectile(Texture *texture, double dx, double dy, double speed) {
    std::set<Dir> dirs;
    dirs.insert(Dir::East);
    return new Projectile(x_+dx, y_+dy, speed, texture, dirs);
}
