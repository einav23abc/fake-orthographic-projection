#ifndef App_HPP
#define App_HPP
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "LinkedList.hpp"
class App;
#include "Window.hpp"

const int VIEWPORT_WIDTH = 160;
const int VIEWPORT_HEIGHT = 180;
const int OUTPUT_CANVAS_WIDTH = 160;
const int OUTPUT_CANVAS_HEIGHT = 90;

const float OUTPUT_X_MODIFIER = ((float)OUTPUT_CANVAS_WIDTH/VIEWPORT_WIDTH);
const float OUTPUT_Y_MODIFIER = ((float)OUTPUT_CANVAS_HEIGHT/VIEWPORT_HEIGHT);

typedef struct {
    short lighter;
    short darker;
    SDL_Color color;
} pallete_color_t;

typedef struct {
    float x;
    float y;
    float z;
} f3point_t;

typedef struct {
    int p1;
    int p2;
    int p3;
    short color;
    f3point_t normal;
    float cam_dotproduct;
    float shade_value;
    float cam_dist;
} triangle_t;

typedef struct {
    float rotation;
    float zoom;
    f3point_t rot_pos;
    float pos_rot_pos_dist;
    f3point_t pos;
} cam_t;

typedef struct {
    int triangles_amount;
    triangle_t* triangles;
    int points_amount;
    f3point_t* points;
} model_t;


// fast inverse square root
float Q_rsqrt ( float number ){
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = * ( long * ) &y;                        // evil floating point bit hack
    i = 0x5f3759df - ( i >> 1 );                // what the fuck?
    y = * ( float * ) &i;
    y = y * ( threehalfs - ( x2 * y * y ) );    // 1st iteration
    //y = y * ( threehalfs - ( x2 * y * y ) );  // 2nd iteration, can be removed

    return y;
};

float dot_product ( f3point_t* vec1 , f3point_t* vec2 ) {
    return (
        (
            vec1->x*vec2->x + vec1->y*vec2->y + vec1->z*vec2->z
        )
        // *(
        //     Q_rsqrt(
        //         vec1->x*vec1->x + vec1->y*vec1->y + vec1->z*vec1->z
        //     )*Q_rsqrt(
        //         vec2->x*vec2->x + vec2->y*vec2->y + vec2->z*vec2->z
        //     )
        // )
    );
};


#define RENDERING_THREADS 4


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
        
        pallete_color_t pallete[3] = {
            pallete_color_t{ 0 , 1 , SDL_Color{ 116 , 124 , 55 , 255 } },
            pallete_color_t{ 0 , 2 , SDL_Color{ 83 , 97 , 46 , 255 } },
            pallete_color_t{ 1 , 2 , SDL_Color{ 49 , 69 , 36 , 255 } }
        };
        LinkedListNode<model_t>* models;
        
        cam_t cam;

        bool keys[256];
        bool key_left = false;
        bool key_right = false;
        bool key_up = false;
        bool key_down = false;
        bool key_lshift = false;
        bool key_space = false;
        static void keyDownEvent( void* voidThis , SDL_Event* event ){
            App* This = (App*)voidThis;
            const char* keyName = SDL_GetKeyName( event->key.keysym.sym );
            if ( strlen(keyName) == 1 && keyName[0] >= 0 && keyName[0] < 256 ){
                This->keys[keyName[0]] = true;
            }else if ( strcmp( keyName , "Left" ) == 0 ){
                This->key_left = true;
            }else if ( strcmp( keyName , "Right" ) == 0 ){
                This->key_right = true;
            }else if ( strcmp( keyName , "Up" ) == 0 ){
                This->key_up = true;
            }else if ( strcmp( keyName , "Down" ) == 0 ){
                This->key_down = true;
            }else if ( strcmp( keyName , "Left Shift" ) == 0 ){
                This->key_lshift = true;
            }else if ( strcmp( keyName , "Space" ) == 0 ){
                This->key_space = true;
            };
            //std::cout << "from App (down): " << keyName << std::endl;
            return;
        };
        static void keyUpEvent( void* voidThis , SDL_Event* event ){
            App* This = (App*)voidThis;
            const char* keyName = SDL_GetKeyName( event->key.keysym.sym );
            if ( strlen(keyName) == 1 && keyName[0] >= 0 && keyName[0] < 256 ){
                This->keys[keyName[0]] = false;
            }else if ( strcmp( keyName , "Left" ) == 0 ){
                This->key_left = false;
            }else if ( strcmp( keyName , "Right" ) == 0 ){
                This->key_right = false;
            }else if ( strcmp( keyName , "Up" ) == 0 ){
                This->key_up = false;
            }else if ( strcmp( keyName , "Down" ) == 0 ){
                This->key_down = false;
            }else if ( strcmp( keyName , "Left Shift" ) == 0 ){
                This->key_lshift = false;
            }else if ( strcmp( keyName , "Space" ) == 0 ){
                This->key_space = false;
            };
            //std::cout << "from App (up): " << keyName << std::endl;
            return;
        };
        static void mousePressEvent( void* voidThis , SDL_Event* event ){
            App* This = (App*)voidThis;
            
            return;
        };
        static void mouseReleaseEvent( void* voidThis , SDL_Event* event ){
            App* This = (App*)voidThis;
            
            return;
        };
};

#include "App.cpp"
#endif