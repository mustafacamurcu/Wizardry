//
//  Game.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//


#include <iostream>
#include <vector>
#include "Game.h"
#include "Env.h"
#include "Texture.h"

Game::Game() { }

void Game::tick(double dt) {
    player_->move(dt);
    zombie_->move(dt);
    
    for(std::vector<Projectile*>::iterator it = projectiles_.begin() ; it != projectiles_.end() ; ++it) {
        (*it)->move(dt);
    }
}

void Game::shootFireball() {
    projectiles_.push_back(player_->generateProjectile(fireballTexture_, 35, 55, 300));
}

void Game::shootLightning() {
    int totalFrames = 25;
    std::function<SDL_Rect(int,Texture*)> lightning_render = [totalFrames](int frames, Texture* texture)->SDL_Rect{
        return {0,32*((frames/5)%2),std::min(int(texture->getWidth()*(totalFrames-frames)/(totalFrames*0.3f)), texture->getWidth()),texture->getHeight()/2};
    };
    animations_.push_back(new Animation(totalFrames, player_, 40, -7, lightningTexture_, lightning_render));
}

void Game::addKey(SDL_Keycode keycode) {
    keys_.push(keycode);
    if(keys_.size() > Env::KEY_LIMIT) {
        keys_.pop();
    }
    
    lastKeyTime_ = SDL_GetTicks();
}

void Game::play() {
    player_ = new Player(300, 200);
    player_->setTexture(playerTexture_);
    
    zombie_ = new Player(500, 200);
    zombie_->setTexture(zombieTexture_);
    zombie_->addDir(Dir::West);
    
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
                    case SDLK_1:
                        Game::shootFireball();
                        break;
                    case SDLK_2:
                        Game::shootLightning();
                        break;
                }
                
                if( e.key.keysym.sym >= 97 && e.key.keysym.sym <= 122 ) {
                    Game::addKey(e.key.keysym.sym);
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
        
        if( timeNow - lastKeyTime_ > Env::KEY_TIME ) {
            keys_ = {};
        }
        
        std::queue<SDL_Keycode> s = keys_;
        
        while(!s.empty())
        {
            const char* w = SDL_GetKeyName(s.front());
            std::cout << w << " ";
            s.pop();
        }
        std::cout << std::endl;
        
        std::cout << (timeNow - lastTime) << std::endl;
        
        lastTime = timeNow;
        Game::checkSpells();
        Game::render();
    }
}

void Game::checkSpells() {
    std::vector<std::string> fire = {"F", "I", "R", "E"};
    std::vector<std::string> bzzt = {"B", "Z", "Z", "T"};
    
    std::queue<SDL_Keycode> s = keys_;
    std::vector<std::string> chars;
    while(!s.empty())
    {
        std::string w(SDL_GetKeyName(s.front()), 0, 2);
        chars.push_back(w);
        s.pop();
    }
    
    for(int i = 0 ; i < chars.size() ; i++) {
        std::cout << chars[i];
    }
    std::cout << std::endl;
    
    if(chars.size() >= fire.size() && std::equal(chars.end()-fire.size(), chars.end(), fire.begin())) {
        Game::shootFireball();
        keys_ = {};
    }
    
    if(chars.size() >= bzzt.size() && std::equal(chars.end()-bzzt.size(), chars.end(), bzzt.begin())) {
        Game::shootLightning();
        keys_ = {};
    }
}

void Game::render() {
    //Clear screen
    SDL_RenderClear(renderer_);
    
    player_->render(renderer_);
    zombie_->render(renderer_);
    
    for(std::vector<Projectile*>::iterator it = projectiles_.begin() ; it != projectiles_.end() ; ++it) {
        (*it)->render(renderer_);
    }
    
    for(std::vector<Animation*>::iterator it = animations_.begin() ; it != animations_.end() ; ++it) {
        (*it)->render(renderer_);
    }
    
    if(animations_.size() > 0) {
        animations_.erase(std::remove_if(animations_.begin(),
                                         animations_.end(),
                                         [](Animation* a){return a->done();}), animations_.end());
    }
    
    
    //groundTexture_->render(0, 0, renderer_);
    
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
        window_ = SDL_CreateWindow( "Wizardry", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Env::SCREEN_WIDTH, Env::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
    playerTexture_ = new Texture();
    playerTexture_->loadFromFile("img/wizard.png", renderer_);
    playerTexture_->setScale(2);
    
    zombieTexture_ = new Texture();
    zombieTexture_->loadFromFile("img/zombie.png", renderer_);
    zombieTexture_->setScale(2);
    
    fireballTexture_ = new Texture();
    fireballTexture_->loadFromFile("img/fireball.png", renderer_);
    
    lightningTexture_ = new Texture();
    lightningTexture_->loadFromFile("img/lightning.png", renderer_);
    lightningTexture_->setScale(2);
}
