
App::App( Window* parentWindow ){
    this->canvas = SDL_CreateRGBSurface(0,OUTPUT_CANVAS_WIDTH,OUTPUT_CANVAS_HEIGHT,32,0,0,0,0);
    this->renderer = SDL_CreateSoftwareRenderer(canvas);
    this->parentWindow = parentWindow;

    this->parentWindow->listenToKeyDownEvent( (void*)this , (eventFunct_t)&(App::keyDownEvent) );
    this->parentWindow->listenToKeyUpEvent( (void*)this , (eventFunct_t)&(App::keyUpEvent) );

    this->cam.x = 0;
    this->cam.y = 0;
    this->cam.z = 0;

    for ( int i = 0; i < 256; i++ ){
        this->keys[i] = false;
    };

    this->points[0].x = 0; this->points[0].y = 0; this->points[0].z = 0;
    this->points[1].x = 0; this->points[1].y = 0; this->points[1].z = 10;
    this->points[2].x = 5; this->points[2].y = 2.5; this->points[2].z = 20;
    this->points[3].x = 45; this->points[3].y = 0; this->points[3].z = 0;
    this->points[4].x = 42.5; this->points[4].y = 2.5; this->points[4].z = 10;
    this->points[5].x = 37.5; this->points[5].y = 0; this->points[5].z = 10;
    this->points[6].x = 30; this->points[6].y = 2.5; this->points[6].z = 20;
    this->points[7].x = 0; this->points[7].y = 20; this->points[7].z = 0;
    this->points[8].x = 0; this->points[8].y = 20; this->points[8].z = 10;
    this->points[9].x = 5; this->points[9].y = 17.5; this->points[9].z = 20;
    this->points[10].x = 45; this->points[10].y = 20; this->points[10].z = 0;
    this->points[11].x = 42.5; this->points[11].y = 17.5; this->points[11].z = 10;
    this->points[12].x = 37.5; this->points[12].y = 20; this->points[12].z = 10;
    this->points[13].x = 30; this->points[13].y = 17.5; this->points[13].z = 20;

    this->triangles[0].color = SDL_Color{255,0,0,255};      this->triangles[0].p1 = 5; this->triangles[0].p2 = 0; this->triangles[0].p3 = 3;
    this->triangles[1].color = SDL_Color{255,10,10,255};    this->triangles[1].p1 = 4; this->triangles[1].p2 = 5; this->triangles[1].p3 = 3;
    this->triangles[2].color = SDL_Color{255,20,20,255};    this->triangles[2].p1 = 0; this->triangles[2].p2 = 5; this->triangles[2].p3 = 1;
    this->triangles[3].color = SDL_Color{255,30,30,255};    this->triangles[3].p1 = 5; this->triangles[3].p2 = 2; this->triangles[3].p3 = 1;
    this->triangles[4].color = SDL_Color{255,40,40,255};    this->triangles[4].p1 = 2; this->triangles[4].p2 = 5; this->triangles[4].p3 = 6;
    this->triangles[5].color = SDL_Color{255,50,50,255};    this->triangles[5].p1 = 7; this->triangles[5].p2 = 12; this->triangles[5].p3 = 10;
    this->triangles[6].color = SDL_Color{255,60,60,255};    this->triangles[6].p1 = 12; this->triangles[6].p2 = 11; this->triangles[6].p3 = 10;
    this->triangles[7].color = SDL_Color{255,70,70,255};    this->triangles[7].p1 = 12; this->triangles[7].p2 = 7; this->triangles[7].p3 = 8;
    this->triangles[8].color = SDL_Color{255,80,80,255};    this->triangles[8].p1 = 9; this->triangles[8].p2 = 12; this->triangles[8].p3 = 8;
    this->triangles[9].color = SDL_Color{255,90,90,255};    this->triangles[9].p1 = 12; this->triangles[9].p2 = 9; this->triangles[9].p3 = 13;
    this->triangles[10].color = SDL_Color{255,100,100,255}; this->triangles[10].p1 = 4; this->triangles[10].p2 = 11; this->triangles[10].p3 = 5;
    this->triangles[11].color = SDL_Color{255,110,110,255}; this->triangles[11].p1 = 11; this->triangles[11].p2 = 12; this->triangles[11].p3 = 5;
    this->triangles[12].color = SDL_Color{255,120,120,255}; this->triangles[12].p1 = 3; this->triangles[12].p2 = 10; this->triangles[12].p3 = 4;
    this->triangles[13].color = SDL_Color{255,130,130,255}; this->triangles[13].p1 = 10; this->triangles[13].p2 = 11; this->triangles[13].p3 = 4;
    this->triangles[14].color = SDL_Color{255,140,140,255}; this->triangles[14].p1 = 5; this->triangles[14].p2 = 12; this->triangles[14].p3 = 6;
    this->triangles[15].color = SDL_Color{255,150,150,255}; this->triangles[15].p1 = 12; this->triangles[15].p2 = 13; this->triangles[15].p3 = 6;
    this->triangles[16].color = SDL_Color{255,160,160,255}; this->triangles[16].p1 = 6; this->triangles[16].p2 = 13; this->triangles[16].p3 = 2;
    this->triangles[17].color = SDL_Color{255,170,170,255}; this->triangles[17].p1 = 13; this->triangles[17].p2 = 9; this->triangles[17].p3 = 2;
    this->triangles[18].color = SDL_Color{255,180,180,255}; this->triangles[18].p1 = 7; this->triangles[18].p2 = 0; this->triangles[18].p3 = 1;
    this->triangles[19].color = SDL_Color{255,190,190,255}; this->triangles[19].p1 = 8; this->triangles[19].p2 = 7; this->triangles[19].p3 = 1;
    this->triangles[20].color = SDL_Color{255,200,200,255}; this->triangles[20].p1 = 8; this->triangles[20].p2 = 1; this->triangles[20].p3 = 2;
    this->triangles[21].color = SDL_Color{255,210,210,255}; this->triangles[21].p1 = 9; this->triangles[21].p2 = 8; this->triangles[21].p3 = 2;
    for ( int i = 0; i < TRIANGLES_AMOUNT; i++ ){
        this->triangles[i].color = SDL_Color{30,20,180,255};
    };

    // calculating triangles' normals   using formula from: https://stackoverflow.com/questions/19350792/calculate-normal-of-a-single-triangle-in-3d-space
    for ( int i = 0; i < TRIANGLES_AMOUNT; i++ ){
        point_t A;
        A.x = this->points[this->triangles[i].p2].x - this->points[this->triangles[i].p1].x;
        A.y = this->points[this->triangles[i].p2].y - this->points[this->triangles[i].p1].y;
        A.z = this->points[this->triangles[i].p2].z - this->points[this->triangles[i].p1].z;
        point_t B;
        B.x = this->points[this->triangles[i].p3].x - this->points[this->triangles[i].p1].x;
        B.y = this->points[this->triangles[i].p3].y - this->points[this->triangles[i].p1].y;
        B.z = this->points[this->triangles[i].p3].z - this->points[this->triangles[i].p1].z;
        this->triangles[i].normal.x = A.y * B.z - A.z * B.y;
        this->triangles[i].normal.y = A.z * B.x - A.x * B.z;
        this->triangles[i].normal.z = A.x * B.y - A.y * B.x;
        {/* for drawing triangles' normals
            this->points[POINTS_AMOUNT+i].x = (this->points[this->triangles[i].p1].x+this->points[this->triangles[i].p2].x+this->points[this->triangles[i].p3].x)/3 + this->triangles[i].normal.x/20;
            this->points[POINTS_AMOUNT+i].y = (this->points[this->triangles[i].p1].y+this->points[this->triangles[i].p2].y+this->points[this->triangles[i].p3].y)/3 + this->triangles[i].normal.y/20;
            this->points[POINTS_AMOUNT+i].z = (this->points[this->triangles[i].p1].z+this->points[this->triangles[i].p2].z+this->points[this->triangles[i].p3].z)/3 + this->triangles[i].normal.z/20;
        */};

        if ( this->triangles[i].normal.x != 0 || this->triangles[i].normal.y != 0 ){
            long double a = atan(this->triangles[i].normal.y/this->triangles[i].normal.x);
            this->triangles[i].color.r = this->triangles[i].color.r/(M_PI_2+10)*(a+10);
            this->triangles[i].color.g = this->triangles[i].color.g/(M_PI_2+10)*(a+10);
            this->triangles[i].color.b = this->triangles[i].color.b/(M_PI_2+10)*(a+10);
        };

        long double a = atan(this->triangles[i].normal.z/sqrt(pow(this->triangles[i].normal.x,2)+pow(this->triangles[i].normal.y,2)));
        if ( this->triangles[i].normal.z == 0 ){
            a = 0;
        };
        this->triangles[i].color.r = this->triangles[i].color.r/(M_PI_2+10)*(a+10);
        this->triangles[i].color.g = this->triangles[i].color.g/(M_PI_2+10)*(a+10);
        this->triangles[i].color.b = this->triangles[i].color.b/(M_PI_2+10)*(a+10);
    };
    {/* for drawing triangles' normals
        for( int i = 0; i < TRIANGLES_AMOUNT; i++ ){
            this->triangles_colors[i] = this->triangles[i].color;
        };
    */};
    return;
};

App::~App(){
    return;
};

void App::Render(){
    SDL_SetRenderDrawColor( this->renderer , 61 , 61 , 61 , 255 );
    SDL_RenderClear(this->renderer);

    //SDL_SetRenderDrawColor( this->parentWindow->renderer , 255 , 0 , 0 , 255 );
    for ( int i = 0; i < POINTS_AMOUNT/*+TRIANGLES_AMOUNT*/; i++ ){
        //SDL_RenderDrawPoint( this->parentWindow->renderer , this->points[i].x , this->points[i].y );
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
            std::cout << "{" << linesColl->point.x << "," << linesColl->point.y << "," << linesColl->reason << "}\n";
            std::cout << "y=" << camLine->m << "x+" << camLine->b << " {" << camLine->minx << "<x<" << camLine->maxx << "," << camLine->miny << "<y<" << camLine->maxy << "}\n";
            std::cout << "y=" << pointLine->m << "x+" << pointLine->b << " {" << pointLine->minx << "<x<" << pointLine->maxx << "," << pointLine->miny << "<y<" << pointLine->maxy << "}\n";
            std::cout << "did not collide!!!\n";
        };
        free( linesColl );
        delete pointLine;
        delete camLine;
    };

    // calculating depth
    for ( int i = 0; i < TRIANGLES_AMOUNT; i++ ){
        //this->triangles[i].depth = std::max( std::max( this->pointsOnCanvas[this->triangles[i].p1].y+(this->points[this->triangles[i].p1].z/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT , this->pointsOnCanvas[this->triangles[i].p2].y+(this->points[this->triangles[i].p2].z/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT ) , this->pointsOnCanvas[this->triangles[i].p3].y+(this->points[this->triangles[i].p3].z/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT );
        //this->triangles[i].depth += (std::max( std::max( this->points[this->triangles[i].p1].z , this->points[this->triangles[i].p2].z ) , this->points[this->triangles[i].p3].z )/VIEWPORT_HEIGHT)*OUTPUT_CANVAS_HEIGHT;
        this->triangles[i].depth = sqrt(
            pow( (this->cam.x+cos(this->cam.z+M_PI_2)*1000) - (this->points[this->triangles[i].p1].x+this->points[this->triangles[i].p2].x+this->points[this->triangles[i].p3].x)/3 ,2) +
            pow( (this->cam.y+sin(this->cam.z+M_PI_2)*1000) - (this->points[this->triangles[i].p1].y+this->points[this->triangles[i].p2].y+this->points[this->triangles[i].p3].y)/3 ,2) +
            pow( 1000 - (this->points[this->triangles[i].p1].z+this->points[this->triangles[i].p2].z+this->points[this->triangles[i].p3].z)/3 ,2)
        );
    };
    // sort triangles
    for ( int i = TRIANGLES_AMOUNT-1; i >= 1; i-- ){
        for ( int j = 0; j < i; j++ ){
            if ( this->triangles[j].depth < this->triangles[j+1].depth ){
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

     //drawing points
    SDL_SetRenderDrawColor( this->renderer , 255 , 255 , 255 , 255 );
    for ( int i = 0; i < POINTS_AMOUNT; i++ ){
        SDL_RenderDrawPoint( this->renderer , this->pointsOnCanvas[i].x , this->pointsOnCanvas[i].y );
    };
    {/* for drawing triangles' normals
        for ( int i = 0; i < TRIANGLES_AMOUNT; i++ ){
            SDL_SetRenderDrawColor( this->renderer , this->triangles_colors[i].r , this->triangles_colors[i].g , this->triangles_colors[i].b , this->triangles_colors[i].a );
            SDL_RenderDrawPoint( this->renderer , this->pointsOnCanvas[POINTS_AMOUNT+i].x , this->pointsOnCanvas[POINTS_AMOUNT+i].y );
        };
    */};
    
    
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
    /*
    this->points[8] = this->cam;
    this->points[8].z = 0;
    //right
    this->points[9].x = this->cam.x+cos(this->cam.z)*VIEWPORT_HEIGHT/2+cos(this->cam.z);
    this->points[9].y = this->cam.y+sin(this->cam.z)*VIEWPORT_HEIGHT/2+sin(this->cam.z);
    //down
    this->points[10].x = this->cam.x+cos(this->cam.z+M_PI_2)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI_2);
    this->points[10].y = this->cam.y+sin(this->cam.z+M_PI_2)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI_2);
    //left
    this->points[11].x = this->cam.x+cos(this->cam.z+M_PI)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI);
    this->points[11].y = this->cam.y+sin(this->cam.z+M_PI)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI);
    //up
    this->points[12].x = this->cam.x+cos(this->cam.z+M_PI_2*3)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI_2*3);
    this->points[12].y = this->cam.y+sin(this->cam.z+M_PI_2*3)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI_2*3);
    //right down
    this->points[13].x = this->cam.x+cos(this->cam.z)*VIEWPORT_HEIGHT/2+cos(this->cam.z)+cos(this->cam.z+M_PI_2)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI_2);
    this->points[13].y = this->cam.y+sin(this->cam.z)*VIEWPORT_HEIGHT/2+sin(this->cam.z)+sin(this->cam.z+M_PI_2)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI_2);
    //left down
    this->points[14].x = this->cam.x+cos(this->cam.z+M_PI)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI)+cos(this->cam.z+M_PI_2)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI_2);
    this->points[14].y = this->cam.y+sin(this->cam.z+M_PI)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI)+sin(this->cam.z+M_PI_2)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI_2);
    //right up
    this->points[15].x = this->cam.x+cos(this->cam.z)*VIEWPORT_HEIGHT/2+cos(this->cam.z)+cos(this->cam.z+M_PI_2*3)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI_2*3);
    this->points[15].y = this->cam.y+sin(this->cam.z)*VIEWPORT_HEIGHT/2+sin(this->cam.z)+sin(this->cam.z+M_PI_2*3)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI_2*3);
    //left up
    this->points[16].x = this->cam.x+cos(this->cam.z+M_PI)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI)+cos(this->cam.z+M_PI_2*3)*VIEWPORT_HEIGHT/2+cos(this->cam.z+M_PI_2*3);
    this->points[16].y = this->cam.y+sin(this->cam.z+M_PI)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI)+sin(this->cam.z+M_PI_2*3)*VIEWPORT_HEIGHT/2+sin(this->cam.z+M_PI_2*3);
    */
    return;
};
