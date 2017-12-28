//
//  Projectile.h
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#ifndef Projectile_h
#define Projectile_h

#include "Position.h"
#include "Texture.h"

class Projectile {
public:
    Projectile(double x, double y, double speed, Texture* texture, std::set<Dir> dirs);
    
    ~Projectile();
    
    void move(double dt);
    
    void render(SDL_Renderer* renderer);
    
private:
    double x_;
    double y_;
    double speed_;
    Texture* texture_;
    std::set<Dir> dirs_;
};

#endif /* Projectile_h */
