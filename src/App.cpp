
App::App( Window* parentWindow ){
    this->canvas = SDL_CreateRGBSurface(0,OUTPUT_CANVAS_WIDTH,OUTPUT_CANVAS_HEIGHT,32,0,0,0,0);
    this->renderer = SDL_CreateSoftwareRenderer(canvas);
    this->parentWindow = parentWindow;

    this->parentWindow->listenToKeyDownEvent( (void*)this , (eventFunct_t)&(App::keyDownEvent) );
    this->parentWindow->listenToKeyUpEvent( (void*)this , (eventFunct_t)&(App::keyUpEvent) );

    this->cam.x = 150;
    this->cam.y = 100;

    this->points[0].x = 100; this->points[0].y = 100; this->points[0].z = 0;
    this->points[1].x = 100; this->points[1].y = 150; this->points[1].z = 0;
    this->points[2].x = 150; this->points[2].y = 100; this->points[2].z = 0;
    this->points[3].x = 150; this->points[3].y = 150; this->points[3].z = 0;
    this->points[4].x = 100; this->points[4].y = 100; this->points[4].z = 50;
    this->points[5].x = 100; this->points[5].y = 150; this->points[5].z = 50;
    this->points[6].x = 150; this->points[6].y = 100; this->points[6].z = 50;
    this->points[7].x = 150; this->points[7].y = 150; this->points[7].z = 50;

    this->triangles[0].color = SDL_Color{15,15,15,255};    this->triangles[0].p1 = 2; this->triangles[0].p2 = 1; this->triangles[0].p3 = 0; // 0 v
    this->triangles[1].color = SDL_Color{30,30,30,255};    this->triangles[1].p1 = 2; this->triangles[1].p2 = 1; this->triangles[1].p3 = 3; // 1 v
    this->triangles[2].color = SDL_Color{45,45,45,255};    this->triangles[2].p1 = 4; this->triangles[2].p2 = 1; this->triangles[2].p3 = 0; // 2
    this->triangles[3].color = SDL_Color{60,60,60,255};    this->triangles[3].p1 = 4; this->triangles[3].p2 = 1; this->triangles[3].p3 = 5; // 8
    this->triangles[4].color = SDL_Color{75,75,75,255};    this->triangles[4].p1 = 7; this->triangles[4].p2 = 1; this->triangles[4].p3 = 5; // 9
    this->triangles[5].color = SDL_Color{90,90,90,255};    this->triangles[5].p1 = 7; this->triangles[5].p2 = 1; this->triangles[5].p3 = 3; // 5
    this->triangles[6].color = SDL_Color{105,105,105,255}; this->triangles[6].p1 = 7; this->triangles[6].p2 = 2; this->triangles[6].p3 = 3; // 6
    this->triangles[7].color = SDL_Color{120,120,120,255}; this->triangles[7].p1 = 7; this->triangles[7].p2 = 2; this->triangles[7].p3 = 6; // 7
    this->triangles[8].color = SDL_Color{135,135,135,255}; this->triangles[8].p1 = 4; this->triangles[8].p2 = 2; this->triangles[8].p3 = 6; // 4
    this->triangles[9].color = SDL_Color{150,150,150,255}; this->triangles[9].p1 = 4; this->triangles[9].p2 = 2; this->triangles[9].p3 = 0; // 3
    return;
};

App::~App(){
    return;
};

void App::Render(){
    SDL_SetRenderDrawColor( this->renderer , 61 , 61 , 61 , 255 );
    SDL_RenderClear(this->renderer);
    
    for ( int i = 0; i < POINTS_AMOUNT; i++ ){
        point_t down;
        down.x = this->cam.x+cos(this->cam.z+M_PI_2)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI_2)*this->points[i].z;
        down.y = this->cam.y+sin(this->cam.z+M_PI_2)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI_2)*this->points[i].z;
        point_t up;
        up.x = this->cam.x+cos(this->cam.z-M_PI_2)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI_2)*this->points[i].z;
        up.y = this->cam.y+sin(this->cam.z-M_PI_2)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI_2)*this->points[i].z;
        Line* camLine = new Line( down , up , true );
        point_t pointRight;
        pointRight.x = this->points[i].x+cos(this->cam.z)*VIEWPORT_WIDTH/2;
        pointRight.y = this->points[i].y+sin(this->cam.z)*VIEWPORT_WIDTH/2;
        point_t pointLeft;
        pointLeft.x = this->points[i].x+cos(this->cam.z+M_PI)*VIEWPORT_WIDTH/2;
        pointLeft.y = this->points[i].y+sin(this->cam.z+M_PI)*VIEWPORT_WIDTH/2;
        Line* pointLine = new Line( pointRight , pointLeft , true );
        lineCollResult_t* linesColl = Line::collision( camLine , pointLine );
        if ( linesColl->collided == true ){
            long double xOnCanvas;
            long double yOnCanvas;
            if ( this->cam.z-M_PI <= 0.0001 && this->cam.z-M_PI >= -0.0001 ){
                xOnCanvas = (linesColl->point.x - this->points[i].x)+VIEWPORT_WIDTH/2;
                yOnCanvas = (this->cam.y - linesColl->point.y)+VIEWPORT_HEIGHT/2-this->points[i].z;
            }else if ( this->cam.z-M_PI_2 <= 0.0001 && this->cam.z-M_PI_2 >= -0.0001 ){
                xOnCanvas = (this->points[i].y - this->cam.y)+VIEWPORT_WIDTH/2;
                yOnCanvas = (this->cam.x - linesColl->point.x)+VIEWPORT_HEIGHT/2-this->points[i].z;
            }else if ( this->cam.z-M_PI_2*3 <= 0.0001 && this->cam.z-M_PI_2*3 >= -0.0001 ){
                xOnCanvas = (this->cam.y - this->points[i].y)+VIEWPORT_WIDTH/2;
                yOnCanvas = (linesColl->point.x - this->cam.x)+VIEWPORT_HEIGHT/2-this->points[i].z;
            }else{
                xOnCanvas = (this->points[i].x - linesColl->point.x)/cos(this->cam.z)+VIEWPORT_WIDTH/2;
                yOnCanvas = (linesColl->point.y - this->cam.y)/cos(this->cam.z)+VIEWPORT_HEIGHT/2-this->points[i].z;
            };
            this->pointsOnCanvas[i].x = (xOnCanvas/VIEWPORT_WIDTH)*OUTPUT_CANVAS_WIDTH;
            this->pointsOnCanvas[i].y = (yOnCanvas/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT;
        }else{
            std::cout << "did not collide!!!\n";
        };
        free( linesColl );
        delete pointLine;
        delete camLine;
    };

    // sort triangles
    for ( int i = 0; i < TRIANGLES_AMOUNT; i++ ){
        this->triangles[i].depth = std::max( std::max( this->pointsOnCanvas[this->triangles[i].p1].y+(this->points[this->triangles[i].p1].z/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT , this->pointsOnCanvas[this->triangles[i].p2].y+(this->points[this->triangles[i].p2].z/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT ) , this->pointsOnCanvas[this->triangles[i].p3].y+(this->points[this->triangles[i].p3].z/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT );
        this->triangles[i].depth += (std::max( std::max( this->points[this->triangles[i].p1].z , this->points[this->triangles[i].p2].z ) , this->points[this->triangles[i].p3].z )/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT;
    };
    for ( int i = TRIANGLES_AMOUNT-1; i >= 1; i-- ){
        for ( int j = 0; j < i; j++ ){
            if ( this->triangles[j].depth > this->triangles[j+1].depth ){
                triangle_t tmp1 = (this->triangles[j]);
                triangle_t tmp2 = (this->triangles[j+1]);
                this->triangles[j] = tmp2;
                this->triangles[j+1] = tmp1;
            };
        };
    };
    {/* print this->triangles
        for ( int i = 0; i < TRIANGLES_AMOUNT; i++ ){
            std::cout << "{p1:" << this->triangles[i].p1 << ",p2:" << this->triangles[i].p2 << ",p3:" << this->triangles[i].p3 << ",depth:" << this->triangles[i].depth << ",color:" << this->triangles[i].color.r%255 << "}\n";
        };
        std::cout << "\n";
    */};
    // drawing triangles
    for ( int i = 0; i < TRIANGLES_AMOUNT; i++ ){
        SDL_Vertex verts[3] = {
            SDL_FPoint{ (float)(this->pointsOnCanvas[this->triangles[i].p1].x), (float)(this->pointsOnCanvas[this->triangles[i].p1].y) }, this->triangles[i].color, SDL_FPoint{ 0 , 0 },
            SDL_FPoint{ (float)(this->pointsOnCanvas[this->triangles[i].p2].x), (float)(this->pointsOnCanvas[this->triangles[i].p2].y) }, this->triangles[i].color, SDL_FPoint{ 0 , 0 },
            SDL_FPoint{ (float)(this->pointsOnCanvas[this->triangles[i].p3].x), (float)(this->pointsOnCanvas[this->triangles[i].p3].y) }, this->triangles[i].color, SDL_FPoint{ 0 , 0 },
        };
        SDL_RenderGeometry( this->renderer, nullptr, verts, 3, nullptr, 0 );
    };

    // drawing points
    SDL_SetRenderDrawColor( this->renderer , 255 , 255 , 255 , 255 );
    for ( int i = 0; i < POINTS_AMOUNT; i++ ){
        SDL_RenderDrawPoint( this->renderer , this->pointsOnCanvas[i].x , this->pointsOnCanvas[i].y );
    };

    
    int pixelSize = std::min( this->parentWindow->width/OUTPUT_CANVAS_WIDTH , this->parentWindow->height/OUTPUT_CANVAS_HEIGHT );
    int topLeftX = ( this->parentWindow->width - pixelSize*OUTPUT_CANVAS_WIDTH )/2;
    int topLeftY = ( this->parentWindow->height - pixelSize*OUTPUT_CANVAS_HEIGHT )/2;
    SDL_Rect destRect;
    destRect.x = topLeftX;
    destRect.y = topLeftY;
    destRect.w = OUTPUT_CANVAS_WIDTH*pixelSize;
    destRect.h = OUTPUT_CANVAS_HEIGHT*pixelSize;

    SDL_Texture* canvasTexture = SDL_CreateTextureFromSurface(this->parentWindow->renderer, this->canvas);
    SDL_RenderCopy(this->parentWindow->renderer, canvasTexture, NULL, &destRect);
    SDL_DestroyTexture(canvasTexture);
    return;
};

void App::Update(){
    if ( this->keys['A'] == true || this->keys['a'] == true ){
        this->cam.x += cos(this->cam.z+M_PI);
        this->cam.y += sin(this->cam.z+M_PI);
    };
    if ( this->keys['D'] == true || this->keys['d'] == true ){
        this->cam.x += cos(this->cam.z);
        this->cam.y += sin(this->cam.z);
    };
    if ( this->keys['W'] == true || this->keys['w'] == true ){
        this->cam.x += cos(this->cam.z-M_PI_2);
        this->cam.y += sin(this->cam.z-M_PI_2);
    };
    if ( this->keys['S'] == true || this->keys['s'] == true ){
        this->cam.x += cos(this->cam.z+M_PI_2);
        this->cam.y += sin(this->cam.z+M_PI_2);
    };
    if ( this->right == true ){
        this->cam.z -= M_PI/180;
        if ( this->cam.z < 0 ){ this->cam.z += M_PI*2; };
    };
    if ( this->left == true ){
        this->cam.z += M_PI/180;
        if ( this->cam.z >= M_PI*2 ){ this->cam.z -= M_PI*2; };
    };
    this->points[8] = this->cam; this->points[8].z = 0;
    return;
};
