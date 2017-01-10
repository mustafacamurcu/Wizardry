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

Projectile::Projectile(Position pos, Texture* texture, std::set<Dir> dirs) {
    pos_ = pos;
    texture_ = texture;
    dirs_ = dirs;
}

void Projectile::move(double dt) {
    pos_.move(dirs_, Env::PROJECTILE_SPEED, dt);
}

void Projectile::render(SDL_Renderer* renderer) {
    texture_->render(pos_.x-Env::PLAYER_WIDTH /2, pos_.y-Env::PROJECTILE_HEIGHT/2, renderer);
}