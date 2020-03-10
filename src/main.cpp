#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "def.h"
#include "sdlutils.h"
#include "resourceManager.h"
#include "commander.h"

// Globals
SDL_Surface *Globals::g_screen = NULL;
SDL_Window *Globals::g_sdlwindow = NULL;
SDL_Joystick *Globals::g_joy=NULL;

const SDL_Color Globals::g_colorTextNormal = {COLOR_TEXT_NORMAL};
const SDL_Color Globals::g_colorTextTitle = {COLOR_TEXT_TITLE};
const SDL_Color Globals::g_colorTextDir = {COLOR_TEXT_DIR};
const SDL_Color Globals::g_colorTextSelected = {COLOR_TEXT_SELECTED};
std::vector<CWindow *> Globals::g_windows;

int main(int argc, char** argv)
{
    // Avoid crash due to the absence of mouse
    {
        char l_s[]="SDL_NOMOUSE=1";
        putenv(l_s);
    }

    // Init SDL
    SDL_Init(SDL_INIT_VIDEO |  SDL_INIT_JOYSTICK);
    

    // Screen
    Globals::g_sdlwindow = SDL_CreateWindow("Commander",  
                              SDL_WINDOWPOS_UNDEFINED,  
                              SDL_WINDOWPOS_UNDEFINED,  
                              SCREEN_WIDTH, SCREEN_HEIGHT,  
                              SDL_WINDOW_OPENGL);  

    // Globals::g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SURFACE_FLAGS);
    Globals::g_screen = SDL_GetWindowSurface(Globals::g_sdlwindow);
    if (Globals::g_screen == NULL)
    {
        std::cerr << "SDL_SetVideoMode failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // Check for joystick
    if (SDL_NumJoysticks() > 0) {
        // Open joystick
        Globals::g_joy = SDL_JoystickOpen(0);

        if (Globals::g_joy) {
            printf("Opened Joystick 0\n");
            printf("Name: %s\n", SDL_JoystickNameForIndex(0));
            printf("Number of Axes: %d\n", SDL_JoystickNumAxes(Globals::g_joy));
            printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(Globals::g_joy));
            printf("Number of Balls: %d\n", SDL_JoystickNumBalls(Globals::g_joy));
        } else {
            printf("Couldn't open Joystick 0\n");
        }
       
    }

    // Hide cursor
    SDL_ShowCursor(SDL_DISABLE);

    // Init font
    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create instances
    CResourceManager::instance();
    char *home = getenv("HOME");
    std::string l_path = home ? home : PATH_DEFAULT;
    CCommander l_commander(l_path, l_path);

    // Main loop
    l_commander.execute();
    

     // Close if opened
    if ( Globals::g_joy!=NULL && SDL_JoystickGetAttached(Globals::g_joy)) {
        SDL_JoystickClose(Globals::g_joy);
    }

    //Quit
    SDL_utils::hastalavista();

    return 0;
}
