//
//  main.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Texture.h"
#include "Game.h"

using namespace std;

int main() {
    //initialize a game object
    Game game;
    
    srand (time(NULL));
    
    //initialize sdl
    if( !game.initSDL() ) {
        std::cout << "Init failed!" << std::endl;
        return 1;
    }
    
    //load images
    game.loadImg();
    
    //start the game
    game.play();
    
    //safely close the game
    game.close();
    
    return 0;
}
