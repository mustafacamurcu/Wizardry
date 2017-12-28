//
//  Projectile.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#include <stdio.h>
#include "Projectile.h"
#include "Position.h"

Projectile::Projectile(double x, double y, double speed, Texture* texture, std::set<Dir> dirs) {
    x_ = x;
    y_ = y;
    speed_ = speed;
    texture_ = texture;
    dirs_ = dirs;
}

void Projectile::move(double dt) {
    if( dirs_.count(North) && y_ - dt * speed_ > 0) {
        y_ -= dt * speed_;
    }
    if( dirs_.count(South) && y_ + dt * speed_ < Env::SCREEN_HEIGHT ) {
        y_ += speed_ * dt;
    }
    if( dirs_.count(East) && x_ + dt * speed_ < Env::SCREEN_WIDTH ) {
        x_ += speed_ * dt;
    }
    if( dirs_.count(West) && x_ - dt * speed_ > 0 ) {
        x_ -= speed_ * dt;
    }
}

void Projectile::render(SDL_Renderer* renderer) {
    texture_->render(x_-Env::PLAYER_WIDTH /2, y_-Env::PROJECTILE_HEIGHT/2, renderer);
}
