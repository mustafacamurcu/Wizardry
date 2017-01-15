//
//  Animation.h
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#ifndef Animation_h
#define Animation_h

#include "Texture.h"
#include "Position.h"

class Animation {
public:
    Animation(int frames, Position* pos, Texture* texture, Position transform = Position());
    
    void render(SDL_Renderer* renderer);
    
    bool done();
private:
    int frames_;
    int totalFrames_;
    Texture* texture_;
    Position* pos_;
    Position transform_;
};

#endif /* Animation_h */
