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
     * set the path of the font to be used
     * @param fontPath, path of the font
     */
    void setFontPath(std::string fontPath);
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
private:
    /*Window*/
    SDL_Window* window_ = NULL;
    /*Renderer*/
    SDL_Renderer* renderer_ = NULL;
    /*Image for the Alien*/
    Texture* alienTexture_;
    /*Image for the Player*/
    Texture* playerTexture_;
    /*Image for the Laser*/
    Texture* laserTexture_;
    /*Path to the font*/
    std::string fontPath_;
};

#endif /* Game_h */
