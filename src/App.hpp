#ifndef App_HPP
#define App_HPP
#include <cmath>
#include "Line.hpp"
#include <string.h>
class App;
#include "Window.hpp"

typedef struct {
    int p1;
    int p2;
    int p3;
    float depth;
    SDL_Color color;
    point_t normal;
} triangle_t;


#define VIEWPORT_WIDTH 160
#define VIEWPORT_HEIGHT 160
#define OUTPUT_CANVAS_WIDTH 160
#define OUTPUT_CANVAS_HEIGHT 80

class App {
    public:
        App( Window* parentWindow );
        ~App();
        void Render();
        void Update();
    private:
        SDL_Surface* canvas;
        SDL_Renderer* renderer;
        Window* parentWindow;
        
        point_t cam; // cam's 'z' value represents the horisonal rotation

#define TRIANGLES_AMOUNT 22
        triangle_t triangles[TRIANGLES_AMOUNT];
        //SDL_Color triangles_colors[TRIANGLES_AMOUNT];
#define POINTS_AMOUNT 14
        point_t points[POINTS_AMOUNT/*+TRIANGLES_AMOUNT*/];
        SDL_Point pointsOnCanvas[POINTS_AMOUNT/*+TRIANGLES_AMOUNT*/];
        
        bool keys[256];
        bool left = false;
        bool right = false;
        static void keyDownEvent( void* voidThis , SDL_Event* event ){
            App* This = (App*)voidThis;
            const char* keyName = SDL_GetKeyName( event->key.keysym.sym );
            if ( strlen(keyName) == 1 && keyName[0] >= 0 && keyName[0] < 256 ){
                This->keys[keyName[0]] = true;
            }else if ( strcmp( keyName , "Left" ) == 0 ){
                This->left = true;
            }else if ( strcmp( keyName , "Right" ) == 0 ){
                This->right = true;
            };
            std::cout << "from App (down): " << keyName << std::endl;
            return;
        };
        static void keyUpEvent( void* voidThis , SDL_Event* event ){
            App* This = (App*)voidThis;
            const char* keyName = SDL_GetKeyName( event->key.keysym.sym );
            if ( strlen(keyName) == 1 && keyName[0] >= 0 && keyName[0] < 256 ){
                This->keys[keyName[0]] = false;
            }else if ( strcmp( keyName , "Left" ) == 0 ){
                This->left = false;
            }else if ( strcmp( keyName , "Right" ) == 0 ){
                This->right = false;
            };
            std::cout << "from App (up): " << keyName << std::endl;
            return;
        };
};

#include "App.cpp"
#endif