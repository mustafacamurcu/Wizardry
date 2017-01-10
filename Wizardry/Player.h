//
//  Player.h
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "Position.h"
#include "Env.h"
#include "Projectile.h"
#include "Texture.h"

/**
 * Player. Represents a Player
 */
class Player {
public:
    /**
     * Construct a Player
     */
    Player(Position pos);
    /**
     * add the given direction to the set of directions
     * @param dir, direction
     */
    void addDir(Dir dir);
    /**
     * removes the given direction from the set of directions
     * @param dir, direction
     */
    void removeDir(Dir dir);
    /**
     * pass the time for this Player
     * @param dt, time passed in seconds
     */
    void tick(double dt);
    /**
     * moves the Player
     * @param dt, time passed in seconds
     */
    void move(double dt);
    /**
     * render this Player
     * @param renderer, renderer to render the Player
     */
    void render(SDL_Renderer* renderer);
    /**
     * set the image texture for this Player
     * @param texture, texture pointer that represents an image
     */
    void setTexture(Texture* texture);
    
    Projectile* generateProjectile(Texture* texture);
private:
    /*Set of Directions*/
    std::set<Dir> dirs_;
    /*Position*/
    Position pos_;
    /*Image Texture*/
    Texture* texture_;
    
};

#endif /* Player_h */
