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

Animation::Animation(int frames, Position* pos, Texture* texture, Position transform) {
    frames_ = frames;
    totalFrames_ = frames;
    pos_ = pos;
    texture_ = texture;
    transform_ = transform;
}

void Animation::render(SDL_Renderer* renderer) {
    SDL_Rect r = {0,0,std::min(int(texture_->getWidth()*(totalFrames_-frames_)/(totalFrames_*0.8f)), texture_->getWidth()),texture_->getHeight()};
    texture_->render(pos_->x+transform_.x, pos_->y+transform_.y, renderer, &r);
    frames_ -= 1;
}

bool Animation::done() {
    return !(frames_ > 0);
}