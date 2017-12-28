//
//  Game.h
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Texture.h"
#include "Player.h"
#include <queue>
#include "Animation.h"

/**
 * Game. Represents a Game
 */
class Game {
public:
    /**
     * Construct a Game
     */
    Game();
    /**
     * pass the time in the Game
     * @param dt, time passed in seconds
     */
    void tick(double dt);
    /**
     * render the game
     */
    void render();
    /**
     * render the menu
     */
    void renderMenu();
    /**
     * start and play the game
     */
    void play();
    /**
     * start the menu
     */
    void menu();
    /**
     * initialize SDL
     * @return if safe
     */
    bool initSDL();
    /**
     * load images for the game
     * @param root, root folder for the images
     */
    void loadImg();
    /**
     * close the game safely
     */
    void close();
    
    void shootFireball();
    
    void shootLightning();
    void shootLightning2();
    
    void addKey(SDL_Keycode keycode);
    
    void checkSpells();
private:
    /*Window*/
    SDL_Window* window_ = NULL;
    /*Renderer*/
    SDL_Renderer* renderer_ = NULL;
    /*Player*/
    Player* player_;
    /*Zombie*/
    Player* zombie_;
    /*Projectiles*/
    std::vector<Projectile*> projectiles_;
    /*keys*/
    std::queue<SDL_Keycode> keys_;
    /*last key time*/
    Uint32 lastKeyTime_;
    /*animations*/
    std::vector<Animation*> animations_;
    
    /* TEXTURES */
    /*Image for the Ground*/
    Texture* groundTexture_;
    /*Image for the Player*/
    Texture* playerTexture_;
    /*Image for the Zombie*/
    Texture* zombieTexture_;
    
    /* SPELLS */
    /*Image for the Player*/
    Texture* fireballTexture_;
    /*Image for the Player*/
    Texture* lightningTexture_;
};

#endif /* Game_h */
