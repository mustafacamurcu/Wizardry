//
//  Texture.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#include "Texture.h"

Texture::Texture(int width, int height)
{
    //Initialize
    texture_ = NULL;
    width_ = width;
    height_ = height;
    scale_ = 1;
}

Texture::Texture()
{
    //Initialize
    texture_ = NULL;
    width_ = 0;
    height_ = 0;
    scale_ = 1;
}

Texture::~Texture()
{
    //Deallocate
    free();
}

void Texture::free()
{
    //Free texture if it exists
    if( texture_ != NULL )
    {
        SDL_DestroyTexture( texture_ );
        texture_ = NULL;
        width_ = 0;
        height_ = 0;
        scale_ = 1;
    }
}

bool Texture::loadFromFile( std::string path, SDL_Renderer* renderer)
{
    //Get rid of preexisting texture
    free();
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else if(width_ <= 0 || height_ <= 0)
        {
            //Get image dimensions
            width_ = loadedSurface->w;
            height_ = loadedSurface->h;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    //Return success
    texture_ = newTexture;
    return texture_ != NULL;
}

bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, std::string fontPath )
{
    //Get rid of preexisting texture
    free();
    
    SDL_Texture* newTexture = NULL;
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( TTF_OpenFont( fontPath.c_str(), 15 ), textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            width_ = textSurface->w;
            height_ = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    texture_ = newTexture;
    return texture_ != NULL;
}


void Texture::render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width_*scale_, height_*scale_ };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w*scale_;
        renderQuad.h = clip->h*scale_;
    }
    
    SDL_RenderCopyEx( renderer, texture_, clip, &renderQuad, NULL, NULL, flip);
}

void Texture::setScale(int s) {
    scale_ = s;
}

int Texture::getWidth()
{
    return width_;
}

int Texture::getHeight()
{
    return height_;
}
