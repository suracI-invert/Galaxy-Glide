#include "Core.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include "SpaceShip.hpp"
#include "Rock.h"

SDL_Renderer* Core::gRenderer = nullptr;
SDL_Window* Core::gWindow = nullptr;
TTF_Font* Core::gFont = nullptr;
Mix_Music* Core::Music = NULL;
SDL_Event Core::e;

LTexture background;
SpaceShip* Core::player = nullptr;
vector<Rock*> Core::rocks;


int spawn_speed = 2000;
Uint64 timeNow = 0;
int Random;

Core::Core() {}

Core::~Core(){}

void Core::init()
{
    bool success = true;
    
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;

                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }

                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }

    isRunning = success;
}
void Core::loadMedia()
{
    bool success = true;

    player = new SpaceShip("/Users/raiju/Downloads/abc.png");
    background.loadFromFile("/Users/raiju/Downloads/cba.jpeg");
    Music = Mix_LoadMUS( "/Users/raiju/Downloads/Nhạc/SorryiLikeYou.mp3" );
    
    isRunning = success;
}
void Core::handleEvent()
{
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
        {
            isRunning = false;
        }

        if( e.type == SDL_KEYDOWN ) {}
        player->handleEvent( e );
        
        if( e.type == SDL_KEYDOWN )
        {
             switch( e.key.keysym.sym )
             {
             case SDLK_9:
                 if( Mix_PlayingMusic() == 0 )
                 {
                 Mix_PlayMusic( Music, -1 );
                 }
             else
             {
                 if( Mix_PausedMusic() == 1 )
                 {
                 Mix_ResumeMusic();
                 }
                 else
                 {
                     Mix_PauseMusic();
                 }
             }
             break;
             
             case SDLK_0:
             Mix_HaltMusic();
             break;
             }
         }

    }
}
void Core::update()
{
    player->move();
    if(SDL_GetTicks64() > timeNow)
    {
        Random = rand()%2;
        RandomObjectOutsideScreen(Random);
        timeNow = SDL_GetTicks64() + spawn_speed;
    }
    for(auto& r : rocks) r->Update();

}
void Core::render()
{
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    
    SDL_RenderCopy( gRenderer, background.getTexture(), NULL, NULL);
    player->render();
    for(auto& r : rocks) r->Render();

    SDL_RenderPresent( gRenderer );
}
void Core::close()
{
    TTF_CloseFont( gFont );
    gFont = NULL;

    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Core::RandomObjectOutsideScreen(int _random)
{
     switch(_random)
    {
        case 0:
        {
            float d = -50 - player->getXPos();
            float e = -50 - player->getYPos();
            normalize_vector(d,e);
            rocks.push_back(new Rock(-50,-50, d,e));
            break;
        }
        case 1:
        {
            float d = player->getXPos() - 1150;
            float e = player->getYPos() + 50;
            normalize_vector(d,e);
            rocks.push_back(new Rock(1150,-50, d,e));
            break;
        }
    }
}

void Core::normalize_vector(float &a, float &b)
{
    float c = max(a, b);
    a = a/c;
    b = b/c;
}
