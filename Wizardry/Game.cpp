//
//  Game.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//


#include <iostream>
#include "Game.h"
#include "Env.h"
#include "Texture.h"

Game::Game() { }

void Game::tick(double dt) {
    player_->move(dt);
    
    for(std::vector<Projectile*>::iterator it = projectiles_.begin() ; it != projectiles_.end() ; ++it) {
        (*it)->move(dt);
    }
}

void Game::shootFireball() {
    Texture* texture = new Texture(Env::PLAYER_WIDTH, Env::PLAYER_HEIGHT);
    texture->loadFromFile("img/fireball.png", renderer_);
    
    projectiles_.push_back(player_->generateProjectile(texture));
}

void Game::play() {
    player_ = new Player(Position(100.0,100.0));
    player_->setTexture(playerTexture_);
    
    bool quit = false;
    Uint32 lastTime = SDL_GetTicks();
    
    while(!quit) {
        SDL_Event e;
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_DOWN:
                        player_->addDir(Dir::South);
                        break;
                    case SDLK_UP:
                        player_->addDir(Dir::North);
                        break;
                    case SDLK_RIGHT:
                        player_->addDir(Dir::East);
                        break;
                    case SDLK_LEFT:
                        player_->addDir(Dir::West);
                        break;
                    case SDLK_SPACE:
                        Game::shootFireball();
                        break;
                }
            }
            else if( e.type == SDL_KEYUP )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_DOWN:
                        player_->removeDir(Dir::South);
                        break;
                    case SDLK_UP:
                        player_->removeDir(Dir::North);
                        break;
                    case SDLK_RIGHT:
                        player_->removeDir(Dir::East);
                        break;
                    case SDLK_LEFT:
                        player_->removeDir(Dir::West);
                        break;
                }
            }
            
        }
        
        Uint32 timeNow = SDL_GetTicks();
        
        Game::tick((timeNow - lastTime)/1000.0f);
        
        std::cout << (timeNow - lastTime) << std::endl;
        
        lastTime = timeNow;
        
        Game::render();
    }
}

void Game::render() {
    //Clear screen
    SDL_RenderClear(renderer_);
    
    player_->render(renderer_);
    
    for(std::vector<Projectile*>::iterator it = projectiles_.begin() ; it != projectiles_.end() ; ++it) {
        (*it)->render(renderer_);
    }
    //Update screen
    SDL_RenderPresent(renderer_);
}


bool Game::initSDL() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        window_ = SDL_CreateWindow( "Super Mario Bros.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Env::SCREEN_WIDTH, Env::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window_ == NULL )
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            //Create renderer_ for window__
            renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer_ == NULL )
            {
                std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                return false;
            }
            else
            {
                //Initialize renderer_ color
                SDL_SetRenderDrawColor( renderer_, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    std::cout << "SDL_image could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
                    return false;
                }
                
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
            }
        }
    }
    
    return true;
}


void Game::close() {
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    
    SDL_Quit();
    IMG_Quit();
}

void Game::loadImg() {
    playerTexture_ = new Texture(Env::PLAYER_WIDTH, Env::PLAYER_HEIGHT);
    playerTexture_->loadFromFile("img/wizard.png", renderer_);
}
