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
#include "Player.h"

class Animation {
public:
    Animation(int frames, Player* player, double x, double y, Texture* texture,
              std::function<SDL_Rect(int,Texture*)> render);
    
    void render(SDL_Renderer* renderer);
    
    bool done();
private:
    int frames_;
    int totalFrames_;
    Texture* texture_;
    double x_;
    double y_;
    Player* player_;
    std::function<SDL_Rect(int,Texture*)> render_;
};

#endif /* Animation_h */
