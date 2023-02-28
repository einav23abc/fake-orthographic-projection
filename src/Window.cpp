
Window::Window( const char* title , int xpos , int ypos , int _width , int _height , int minWidth , int minHeight , bool resizable , bool fullscreen ){
    this->width = _width;
    this->height = _height;
    
    Uint32 flags = 0;
    if ( fullscreen ){
        flags = SDL_WINDOW_FULLSCREEN;
    };
    if ( resizable ){
        flags |= SDL_WINDOW_RESIZABLE;
    };

    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ){
        this->isRunning = false;
        return;
    };
    
    std::cout << "Window Subsystems Initialised!..." << std::endl;
    this->window = SDL_CreateWindow( title , xpos , ypos , width , height , flags );
    SDL_SetWindowMinimumSize(this->window, minWidth , minHeight);
    
    if ( this->window ){
        std::cout << "Window Window Created!" << std::endl;
    };

    this->renderer = SDL_CreateRenderer( this->window , -1 , 0 );
    if ( this->renderer ){
        std::cout << "Window Renderer Created!" << std::endl;
    };

    textInput[0] = '\0';
    this->app = new App(this);

    this->isRunning = true;
    
    return;
};

Window::~Window(){
    return;
};

void Window::handleEvents(){

    SDL_Event event;
    while( SDL_PollEvent(&event) ){
        SDL_GetMouseState(&this->mouseX, &this->mouseY);

        if ( event.type == SDL_QUIT ){
            isRunning = false;
        }else if ( event.type == SDL_WINDOWEVENT ){
            if ( event.window.event == SDL_WINDOWEVENT_RESIZED ){
                SDL_GetWindowSize( window, &width, &height );
            };
        }else if( event.type == SDL_MOUSEBUTTONDOWN ){
            LinkedListNode<eventFunct_t>* currentFunc = mousePressEventListenFuncList;
            LinkedListNode<void*>* currentListner = mousePressEventListenListnerList;
            while( currentFunc != nullptr && currentListner != nullptr ){
                eventFunct_t func = currentFunc->getValue();
                func( currentListner->getValue() , &event );
                currentFunc = currentFunc->getNext();
                currentListner = currentListner->getNext();
            };
        }else if( event.type == SDL_MOUSEBUTTONUP ){
            LinkedListNode<eventFunct_t>* currentFunc = mouseReleaseEventListenFuncList;
            LinkedListNode<void*>* currentListner = mouseReleaseEventListenListnerList;
            while( currentFunc != nullptr && currentListner != nullptr ){
                eventFunct_t func = currentFunc->getValue();
                func( currentListner->getValue() , &event );
                currentFunc = currentFunc->getNext();
                currentListner = currentListner->getNext();
            };
        }else if ( event.type == SDL_KEYDOWN ){
            //std::cout << SDL_GetKeyName( event.key.keysym.sym ) << std::endl;
            
            LinkedListNode<eventFunct_t>* currentFunc = keyDownEventListenFuncList;
            LinkedListNode<void*>* currentListner = keyDownEventListenListnerList;
            while( currentFunc != nullptr && currentListner != nullptr ){
                eventFunct_t func = currentFunc->getValue();
                func( currentListner->getValue() , &event );
                currentFunc = currentFunc->getNext();
                currentListner = currentListner->getNext();
            };

            if ( strcmp( SDL_GetKeyName( event.key.keysym.sym ) , "Backspace" ) == 0 ){
                if ( strlen( textInput ) >= 1 ){
                    textInput[strlen( textInput )-1] = '\0';
                }else{
                    textInputBackspaces++;
                };
                std::cout << "\"" << textInput << "\" del:" << textInputBackspaces << std::endl;
            }else if ( strcmp( SDL_GetKeyName( event.key.keysym.sym ) , "Return" ) == 0 ){
                if ( event.key.keysym.mod & KMOD_LSHIFT ){
                    if ( strlen( textInput ) + 1 >= MAX_TEXT_INPUT_LENGTH ){
                        textInput[1] = '\0';
                        textInput[0] = '\3';
                        textInputBackspaces = 0;
                    }else{
                        textInput[strlen(textInput)+1] = '\0';
                        textInput[strlen(textInput)] = '\3';
                    };
                }else{
                    if ( strlen( textInput ) + 1 >= MAX_TEXT_INPUT_LENGTH ){
                        textInput[1] = '\0';
                        textInput[0] = '\n';
                        textInputBackspaces = 0;
                    }else{
                        textInput[strlen(textInput)+1] = '\0';
                        textInput[strlen(textInput)] = '\n';
                    };
                };
                std::cout << "\"" << textInput << "\" del:" << textInputBackspaces << std::endl;
            }else if ( strcmp( SDL_GetKeyName( event.key.keysym.sym ) , "Tab" ) == 0 ){
                if ( strlen( textInput ) + 4 >= MAX_TEXT_INPUT_LENGTH ){
                    strcpy( textInput , "    " );
                    textInputBackspaces = 0;
                }else{
                    strcat( textInput , "    " );
                };
                std::cout << "\"" << textInput << "\" del:" << textInputBackspaces << std::endl;
            };
        }else if ( event.type == SDL_KEYUP ){
            LinkedListNode<eventFunct_t>* currentFunc = keyUpEventListenFuncList;
            LinkedListNode<void*>* currentListner = keyUpEventListenListnerList;
            while( currentFunc != nullptr && currentListner != nullptr ){
                eventFunct_t func = currentFunc->getValue();
                func( currentListner->getValue() , &event );
                currentFunc = currentFunc->getNext();
                currentListner = currentListner->getNext();
            };
        }else if ( event.type == SDL_TEXTINPUT ){
            if ( strlen( textInput ) + strlen(event.text.text) >= MAX_TEXT_INPUT_LENGTH ){
                strcpy( textInput , "" );
                textInputBackspaces = 0;
            };
            strcat(textInput, event.text.text );
            std::cout << "\"" << textInput << "\" del:" << textInputBackspaces << std::endl;
        }else {

        };
    };
    return;
};

void Window::update(){
    ((App*)this->app)->Update();
    return;
};

void Window::render(){
    SDL_SetRenderDrawColor( this->renderer , 0 , 0 , 0 , 255 );
    SDL_RenderClear(this->renderer);

    ((App*)this->app)->Render();

    SDL_RenderPresent(this->renderer);
    return;
};

void Window::clean(){
    delete ((App*)this->app);
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    std::cout << "Window Cleaned" << std::endl;
    return;
};


void Window::listenToMousePressEvent( void* listner , eventFunct_t funcptr ){
    if ( mousePressEventListenFuncList == nullptr ){
        mousePressEventListenFuncList = new LinkedListNode<eventFunct_t>(funcptr);
        mousePressEventListenFuncListTail = mousePressEventListenFuncList;
        mousePressEventListenListnerList = new LinkedListNode<void*>(listner);
        mousePressEventListenListnerListTail = mousePressEventListenListnerList;
        return;
    };
    mousePressEventListenFuncListTail->setNext( new LinkedListNode<eventFunct_t>(funcptr) );
    mousePressEventListenFuncListTail = mousePressEventListenFuncListTail->getNext();
    mousePressEventListenListnerListTail->setNext( new LinkedListNode<void*>(listner) );
    mousePressEventListenListnerListTail = mousePressEventListenListnerListTail->getNext();
    return;
};
void Window::listenToMouseReleaseEvent( void* listner , eventFunct_t funcptr ){
    if ( mouseReleaseEventListenFuncList == nullptr ){
        mouseReleaseEventListenFuncList = new LinkedListNode<eventFunct_t>(funcptr);
        mouseReleaseEventListenFuncListTail = mouseReleaseEventListenFuncList;
        mouseReleaseEventListenListnerList = new LinkedListNode<void*>(listner);
        mouseReleaseEventListenListnerListTail = mouseReleaseEventListenListnerList;
        return;
    };
    mousePressEventListenFuncListTail->setNext( new LinkedListNode<eventFunct_t>(funcptr) );
    mousePressEventListenFuncListTail = mousePressEventListenFuncListTail->getNext();
    mousePressEventListenListnerListTail->setNext( new LinkedListNode<void*>(listner) );
    mousePressEventListenListnerListTail = mousePressEventListenListnerListTail->getNext();
    return;
};
void Window::listenToKeyDownEvent( void* listner , eventFunct_t funcptr ){
    if ( keyDownEventListenFuncList == nullptr ){
        keyDownEventListenFuncList = new LinkedListNode<eventFunct_t>(funcptr);
        keyDownEventListenFuncListTail = keyDownEventListenFuncList;
        keyDownEventListenListnerList = new LinkedListNode<void*>(listner);
        keyDownEventListenListnerListTail = keyDownEventListenListnerList;
        return;
    };
    keyDownEventListenFuncListTail->setNext( new LinkedListNode<eventFunct_t>(funcptr) );
    keyDownEventListenFuncListTail = keyDownEventListenFuncListTail->getNext();
    keyDownEventListenListnerListTail->setNext( new LinkedListNode<void*>(listner) );
    keyDownEventListenListnerListTail = keyDownEventListenListnerListTail->getNext();
    return;
};
void Window::listenToKeyUpEvent( void* listner , eventFunct_t funcptr ){
    if ( keyUpEventListenFuncList == nullptr ){
        keyUpEventListenFuncList = new LinkedListNode<eventFunct_t>(funcptr);
        keyUpEventListenFuncListTail = keyUpEventListenFuncList;
        keyUpEventListenListnerList = new LinkedListNode<void*>(listner);
        keyUpEventListenListnerListTail = keyUpEventListenListnerList;
        return;
    };
    keyUpEventListenFuncListTail->setNext( new LinkedListNode<eventFunct_t>(funcptr) );
    keyUpEventListenFuncListTail = keyUpEventListenFuncListTail->getNext();
    keyUpEventListenListnerListTail->setNext( new LinkedListNode<void*>(listner) );
    keyUpEventListenListnerListTail = keyUpEventListenListnerListTail->getNext();
    return;
};