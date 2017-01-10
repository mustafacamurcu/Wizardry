//
//  Texture.h
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

//Texture wrapper class
class Texture
{
public:
    //Initializes variables
    Texture();
    
    //Initializes variables
    Texture(int width, int height);
    
    //Deallocates memory
    ~Texture();
    
    //Loads image at specified path
    bool loadFromFile( std::string path, SDL_Renderer* renderer );
    
    //Loads the given text as image
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, std::string fontPath);
    
    //Deallocates texture
    void free();
    
    //Sets the scale of this Texture
    void setScale(int s);
    
    //Renders texture at given point
    void render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, SDL_RendererFlip = SDL_FLIP_NONE );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* texture_;
    
    //Image dimensions
    int width_;
    int height_;
    int scale_;
};

#endif /* Texture_h */
