//
//  Animation.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#include <stdio.h>

#include "Animation.h"
#include <algorithm>

Animation::Animation(int frames, Player* player, double x, double y, Texture* texture,
                     std::function<SDL_Rect(int,Texture*)> render) {
    frames_ = frames;
    totalFrames_ = frames;
    x_ = x;
    y_ = y;
    texture_ = texture;
    render_ = render;
    player_ = player;
}

void Animation::render(SDL_Renderer* renderer) {
    SDL_Rect r = render_(frames_, texture_);
    texture_->render(player_->x()+x_, player_->y()+y_, renderer, &r);
    frames_ -= 1;
}

bool Animation::done() {
    return !(frames_ > 0);
}
