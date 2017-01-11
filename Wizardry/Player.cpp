//
//  Player.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#include "Player.h"

#include <iostream>

Player::Player(Position pos) {
    pos_ = pos;
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
    pos_.move(dirs_, Env::PLAYER_SPEED, dt);
}

void Player::render(SDL_Renderer* renderer) {
    texture_->render(pos_.x-Env::PLAYER_WIDTH/2, pos_.y-Env::PLAYER_HEIGHT/2, renderer);
}

Position* Player::getPositionPtr() {
    return &pos_;
}

void Player::setTexture(Texture* texture) {
    texture_ = texture;
}

Projectile* Player::generateProjectile(Texture *texture) {
    std::set<Dir> dirs;
    dirs.insert(Dir::East);
    return new Projectile(pos_, texture, dirs);
}