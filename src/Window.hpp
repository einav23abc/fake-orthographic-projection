#ifndef Window_HPP
#define Window_HPP

#include "LinkedList.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string.h>

typedef void (*eventFunct_t)(void* This,SDL_Event* event);

class Window {
    public:
        Window(const char* title,int xpos,int ypos,int _width,int _height,int minWidth,int minHeight,bool resizable,bool fullscreen);
        ~Window();
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running(){ return isRunning; };
        SDL_Renderer* renderer;
#define MAX_TEXT_INPUT_LENGTH 12
        char textInput[MAX_TEXT_INPUT_LENGTH];
        int textInputBackspaces = 0;
        int width, height;
        int mouseX, mouseY;
        void listenToMousePressEvent( void* listner , eventFunct_t funcptr );
        void listenToMouseReleaseEvent( void* listner , eventFunct_t funcptr );
        void listenToKeyDownEvent( void* listner , eventFunct_t funcptr );
        void listenToKeyUpEvent( void* listner , eventFunct_t funcptr );
    private:
        LinkedListNode<eventFunct_t>* mousePressEventListenFuncList = nullptr;
        LinkedListNode<eventFunct_t>* mousePressEventListenFuncListTail = nullptr;
        LinkedListNode<void*>* mousePressEventListenListnerList = nullptr;
        LinkedListNode<void*>* mousePressEventListenListnerListTail = nullptr;
        
        LinkedListNode<eventFunct_t>* mouseReleaseEventListenFuncList = nullptr;
        LinkedListNode<eventFunct_t>* mouseReleaseEventListenFuncListTail = nullptr;
        LinkedListNode<void*>* mouseReleaseEventListenListnerList = nullptr;
        LinkedListNode<void*>* mouseReleaseEventListenListnerListTail = nullptr;
        
        LinkedListNode<eventFunct_t>* keyDownEventListenFuncList = nullptr;
        LinkedListNode<eventFunct_t>* keyDownEventListenFuncListTail = nullptr;
        LinkedListNode<void*>* keyDownEventListenListnerList = nullptr;
        LinkedListNode<void*>* keyDownEventListenListnerListTail = nullptr;

        LinkedListNode<eventFunct_t>* keyUpEventListenFuncList = nullptr;
        LinkedListNode<eventFunct_t>* keyUpEventListenFuncListTail = nullptr;
        LinkedListNode<void*>* keyUpEventListenListnerList = nullptr;
        LinkedListNode<void*>* keyUpEventListenListnerListTail = nullptr;

        bool isRunning;
        SDL_Window* window;
        void* app; /* supose to be (App*) app */
};

#include "App.hpp"
#include "Window.cpp"
#endif