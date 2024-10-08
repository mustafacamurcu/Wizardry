//
//  Env.h
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#ifndef Env_h
#define Env_h

/**
 * Class to store environment constants
 */
class Env {
public:
    const static int SCREEN_HEIGHT = 500;
    const static int SCREEN_WIDTH = 800;
    
    const static int PLAYER_HEIGHT= 0;
    const static int PLAYER_WIDTH = 0;
    const static int PLAYER_SPEED = 100;
    
    const static int GROUND_HEIGHT= 0;
    const static int GROUND_WIDTH = 0;
    
    const static int PROJECTILE_SPEED = 200;
    const static int PROJECTILE_WIDTH = 80;
    const static int PROJECTILE_HEIGHT = 80;
    
    const static int KEY_LIMIT = 5;
    const static int KEY_TIME = 1000;
};

/**
 * Represents directions
 */
enum Dir {
    North,
    South,
    East,
    West
};


#endif /* Env_h */
