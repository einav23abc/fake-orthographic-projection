
App::App( Window* parentWindow ){
    this->canvas = SDL_CreateRGBSurface(0,OUTPUT_CANVAS_WIDTH,OUTPUT_CANVAS_HEIGHT,32,0,0,0,0);
    this->renderer = SDL_CreateSoftwareRenderer(canvas);
    this->parentWindow = parentWindow;

    this->parentWindow->listenToKeyDownEvent( (void*)this , (eventFunct_t)&(App::keyDownEvent) );
    this->parentWindow->listenToKeyUpEvent( (void*)this , (eventFunct_t)&(App::keyUpEvent) );
    this->parentWindow->listenToMousePressEvent( (void*)this , (eventFunct_t)&(App::mousePressEvent) );
    this->parentWindow->listenToMouseReleaseEvent( (void*)this , (eventFunct_t)&(App::mouseReleaseEvent) );

    for ( int i = 0; i < 256; i++ ){
        this->keys[i] = false;
    };

    this->cam.rotation = 0;
    this->cam.zoom = 5;
    this->cam.rot_pos.x = 0;
    this->cam.rot_pos.y = 0;
    this->cam.rot_pos.z = 0;
    this->cam.pos_rot_pos_dist = 100;

    // model_t floor;
    // floor.points_amount = 8;
    // floor.points = (f3point_t*)calloc( floor.points_amount , sizeof(f3point_t) );
    // floor.points[0] = f3point_t{ 0 , 0 , 0 };
    // floor.points[1] = f3point_t{ 10 , 0 , 0 };
    // floor.points[2] = f3point_t{ 0 , 10 , 0 };
    // floor.points[3] = f3point_t{ 10 , 10 , 0 };
    // floor.points[4] = f3point_t{ 0 , 0 , 10 };
    // floor.points[5] = f3point_t{ 10 , 0 , 10 };
    // floor.points[6] = f3point_t{ 0 , 10 , 10 };
    // floor.points[7] = f3point_t{ 10 , 10 , 10 };
    // floor.triangles_amount = 12;
    // floor.triangles = (triangle_t*)calloc( floor.triangles_amount , sizeof(triangle_t) );
    // floor.triangles[0] = triangle_t{ 0 , 1 , 5 , 1 };
    // floor.triangles[1] = triangle_t{ 0 , 5 , 4 , 1 };
    // floor.triangles[2] = triangle_t{ 2 , 0 , 6 , 1 };
    // floor.triangles[3] = triangle_t{ 6 , 0 , 4 , 1 };
    // floor.triangles[4] = triangle_t{ 1 , 3 , 5 , 1 };
    // floor.triangles[5] = triangle_t{ 5 , 3 , 7 , 1 };
    // floor.triangles[6] = triangle_t{ 3 , 2 , 6 , 1 };
    // floor.triangles[7] = triangle_t{ 3 , 6 , 7 , 1 };
    // floor.triangles[8] = triangle_t{ 1 , 0 , 2 , 1 };
    // floor.triangles[9] = triangle_t{ 3 , 1 , 2 , 1 };
    // floor.triangles[10]= triangle_t{ 4 , 5 , 6 , 1 };
    // floor.triangles[11]= triangle_t{ 5 , 7 , 6 , 1 };
    // models = new LinkedListNode<model_t>( floor );

    srand(1);

    model_t floor;
    const int floor_size = 30;
    floor.points_amount = floor_size*floor_size;
    floor.points = (f3point_t*)calloc( floor.points_amount , sizeof(f3point_t) );
    for ( int y = 0; y < floor_size; y++ ){
        for ( int x = 0; x < floor_size; x++ ){
            floor.points[y*floor_size+x].x = x-floor_size*0.5;
            floor.points[y*floor_size+x].y = y-floor_size*0.5;
            floor.points[y*floor_size+x].z = ((float)(rand()%100))/60;
        };
    };
    floor.triangles_amount = (floor_size-1)*(floor_size-1)*2;
    floor.triangles = (triangle_t*)calloc( floor.triangles_amount , sizeof(triangle_t) );
    for ( int y = 0; y < (floor_size-1); y++ ){
        for ( int x = 0; x < (floor_size-1); x++ ){
            floor.triangles[y*(floor_size-1)+x] = triangle_t{ y*floor_size+x , y*floor_size+(x+1) , (y+1)*floor_size+x , 1 };
            floor.triangles[y*(floor_size-1)+x +(floor_size-1)*(floor_size-1)] = triangle_t{ (y+1)*floor_size+(x+1) , (y+1)*floor_size+x , y*floor_size+(x+1) , 1 };
            // floor.triangles[y*9+x +(floor_size-1)*(floor_size-1)*2] = triangle_t{ y*10+x , (y+1)*10+(x+1) , (y+1)*10+x , 1 };
            // floor.triangles[y*9+x +(floor_size-1)*(floor_size-1)*3] = triangle_t{ (y+1)*10+(x+1) , y*10+x , y*10+(x+1) , 1 };
        };
    };
    models = new LinkedListNode<model_t>( floor );


    return;
};

App::~App(){
    return;
};

void App::Render(){
    SDL_SetRenderDrawColor( this->renderer , 61 , 61 , 61 , 255 );
    SDL_RenderClear(this->renderer);
    SDL_SetRenderDrawColor( this->renderer , 255 , 255 , 255 , 255 );

    const float cosr_z = cos(this->cam.rotation)*this->cam.zoom;
    const float sinr_z = sin(this->cam.rotation)*this->cam.zoom;
    const float origin_x = OUTPUT_CANVAS_WIDTH/2 - ( cosr_z*this->cam.rot_pos.x - sinr_z*this->cam.rot_pos.y )*OUTPUT_X_MODIFIER;
    const float origin_y = OUTPUT_CANVAS_HEIGHT/2 - ( sinr_z*this->cam.rot_pos.x + cosr_z*this->cam.rot_pos.y -this->cam.zoom*this->cam.rot_pos.z )*OUTPUT_Y_MODIFIER;
    

    f3point_t i_cam_vec = f3point_t{ sin(this->cam.rotation) , cos(this->cam.rotation) , 1 };
    const float rsqrt_i_cam_vec = Q_rsqrt( i_cam_vec.x*i_cam_vec.x + i_cam_vec.y*i_cam_vec.y + i_cam_vec.z*i_cam_vec.z );
    i_cam_vec.x = i_cam_vec.x*rsqrt_i_cam_vec;
    i_cam_vec.y = i_cam_vec.y*rsqrt_i_cam_vec;
    i_cam_vec.z = i_cam_vec.z*rsqrt_i_cam_vec;
    this->cam.pos.x = this->cam.rot_pos.x + i_cam_vec.x*this->cam.pos_rot_pos_dist;
    this->cam.pos.y = this->cam.rot_pos.y + i_cam_vec.y*this->cam.pos_rot_pos_dist;
    this->cam.pos.z = this->cam.rot_pos.z + i_cam_vec.z*this->cam.pos_rot_pos_dist;

    f3point_t sun_vec = f3point_t{ 1.5 , 1 , -3.2 };
    const float rsqrt_sun_vec = Q_rsqrt( sun_vec.x*sun_vec.x + sun_vec.y*sun_vec.y + sun_vec.z*sun_vec.z );
    sun_vec.x = sun_vec.x*rsqrt_sun_vec;
    sun_vec.y = sun_vec.y*rsqrt_sun_vec;
    sun_vec.z = sun_vec.z*rsqrt_sun_vec;

    { //* triangles updating
        LinkedListNode<model_t>* current_model = this->models;
        while ( current_model != nullptr ){
            model_t _model = current_model->getValue();
            for ( int i = 0; i < _model.triangles_amount; i++ ){
                f3point_t A;
                A.x = _model.points[_model.triangles[i].p2].x - _model.points[_model.triangles[i].p1].x;
                A.y = _model.points[_model.triangles[i].p2].y - _model.points[_model.triangles[i].p1].y;
                A.z = _model.points[_model.triangles[i].p2].z - _model.points[_model.triangles[i].p1].z;
                f3point_t B;
                B.x = _model.points[_model.triangles[i].p3].x - _model.points[_model.triangles[i].p1].x;
                B.y = _model.points[_model.triangles[i].p3].y - _model.points[_model.triangles[i].p1].y;
                B.z = _model.points[_model.triangles[i].p3].z - _model.points[_model.triangles[i].p1].z;
                f3point_t triangle_normal;
                triangle_normal.x = A.y * B.z - A.z * B.y;
                triangle_normal.y = A.z * B.x - A.x * B.z;
                triangle_normal.z = A.x * B.y - A.y * B.x;
                float rsqrt_triangle_normal = Q_rsqrt( triangle_normal.x*triangle_normal.x + triangle_normal.y*triangle_normal.y + triangle_normal.z*triangle_normal.z );
                triangle_normal.x = triangle_normal.x*rsqrt_triangle_normal;
                triangle_normal.y = triangle_normal.y*rsqrt_triangle_normal;
                triangle_normal.z = triangle_normal.z*rsqrt_triangle_normal;

                _model.triangles[i].normal = triangle_normal;
                _model.triangles[i].cam_dotproduct = dot_product( &triangle_normal , &i_cam_vec );

                //std::cout << "dp:" << _model.triangles[i].cam_dotproduct << ", i_cam_vec:{" << i_cam_vec.x << "," << i_cam_vec.y << "," << i_cam_vec.z << "}, triangle_normal:{" << triangle_normal.x << "," << triangle_normal.y << "," << triangle_normal.z << "}\n";
                if ( _model.triangles[i].cam_dotproduct >= 0 ){
                    _model.triangles[i].shade_value = (-dot_product(&triangle_normal , &sun_vec)+1)*0.5;

                    // calculate distance to camera (without fisheye effect)
                    f3point_t delta_triangle_cam_vec;
                    delta_triangle_cam_vec.x = this->cam.pos.x-(_model.points[_model.triangles[i].p1].x+_model.points[_model.triangles[i].p2].x+_model.points[_model.triangles[i].p3].x)*0.3333;
                    delta_triangle_cam_vec.y = this->cam.pos.y-(_model.points[_model.triangles[i].p1].y+_model.points[_model.triangles[i].p2].y+_model.points[_model.triangles[i].p3].y)*0.3333;
                    delta_triangle_cam_vec.z = this->cam.pos.z-(_model.points[_model.triangles[i].p1].z+_model.points[_model.triangles[i].p2].z+_model.points[_model.triangles[i].p3].z)*0.3333;
                    // not changing size to 1
                    _model.triangles[i].cam_dist = dot_product( &delta_triangle_cam_vec , &i_cam_vec );

                    // sort this triangle
                    int t = i;
                    for ( int j = i-1; j >= 0; j-- ){
                        if ( _model.triangles[j].cam_dotproduct >= 0 && _model.triangles[j].cam_dist > 0 ){
                            if ( _model.triangles[t].cam_dist > _model.triangles[j].cam_dist ){
                                triangle_t tmp = _model.triangles[t];
                                _model.triangles[t] = _model.triangles[j];
                                _model.triangles[j] = tmp;
                                t = j;
                            }else{
                                j = -1;
                            };
                        };
                    };

                };
            };
            current_model = current_model->getNext();
        };
        //*/
    };
    { //* triangles drawing
        LinkedListNode<model_t>* current_model = this->models;
        while ( current_model != nullptr ){
            model_t _model = current_model->getValue();
            for ( int i = 0; i < _model.triangles_amount; i++ ){
                
                if ( _model.triangles[i].cam_dotproduct >= 0 && _model.triangles[i].cam_dist > 0 ){
                    short color = _model.triangles[i].color;
                    if ( _model.triangles[i].shade_value > 0.93 ){
                        color = pallete[color].lighter;
                    }else if( _model.triangles[i].shade_value < 0.71 ){
                        color = pallete[color].darker;
                    };
                    //std::cout << "t:" << i << ", shade:" << _model.triangles[i].shade_value << ", c:" << color << "\n";
                    SDL_Color triangle_color = pallete[color].color;
                    // triangle_color.r = triangle_color.r*_model.triangles[i].shade_value;
                    // triangle_color.g = triangle_color.g*_model.triangles[i].shade_value;
                    // triangle_color.b = triangle_color.b*_model.triangles[i].shade_value;

                    SDL_Vertex verts[3] = {
                        SDL_FPoint{
                            origin_x+ (cosr_z*_model.points[_model.triangles[i].p1].x - sinr_z*_model.points[_model.triangles[i].p1].y)*OUTPUT_X_MODIFIER ,
                            origin_y+ (sinr_z*_model.points[_model.triangles[i].p1].x + cosr_z*_model.points[_model.triangles[i].p1].y -this->cam.zoom*_model.points[_model.triangles[i].p1].z)*OUTPUT_Y_MODIFIER
                        }, triangle_color, SDL_FPoint{ 0 , 0 },
                        SDL_FPoint{
                            origin_x+ (cosr_z*_model.points[_model.triangles[i].p2].x - sinr_z*_model.points[_model.triangles[i].p2].y)*OUTPUT_X_MODIFIER ,
                            origin_y+ (sinr_z*_model.points[_model.triangles[i].p2].x + cosr_z*_model.points[_model.triangles[i].p2].y -this->cam.zoom*_model.points[_model.triangles[i].p2].z)*OUTPUT_Y_MODIFIER
                        }, triangle_color, SDL_FPoint{ 0 , 0 },
                        SDL_FPoint{
                            origin_x+ (cosr_z*_model.points[_model.triangles[i].p3].x - sinr_z*_model.points[_model.triangles[i].p3].y)*OUTPUT_X_MODIFIER ,
                            origin_y+ (sinr_z*_model.points[_model.triangles[i].p3].x + cosr_z*_model.points[_model.triangles[i].p3].y -this->cam.zoom*_model.points[_model.triangles[i].p3].z)*OUTPUT_Y_MODIFIER
                        }, triangle_color, SDL_FPoint{ 0 , 0 },
                    };
                    SDL_RenderGeometry( this->renderer, nullptr, verts, 3, nullptr, 0 );
                    
                    // draw triangle's normal
                    // SDL_RenderDrawLine(this->renderer,
                    //     (
                    //         origin_x+ (cosr_z*_model.points[_model.triangles[i].p1].x - sinr_z*_model.points[_model.triangles[i].p1].y)*OUTPUT_X_MODIFIER +
                    //         origin_x+ (cosr_z*_model.points[_model.triangles[i].p2].x - sinr_z*_model.points[_model.triangles[i].p2].y)*OUTPUT_X_MODIFIER +
                    //         origin_x+ (cosr_z*_model.points[_model.triangles[i].p3].x - sinr_z*_model.points[_model.triangles[i].p3].y)*OUTPUT_X_MODIFIER
                    //     )*0.333 ,
                    //     (
                    //         origin_y+ (sinr_z*_model.points[_model.triangles[i].p1].x + cosr_z*_model.points[_model.triangles[i].p1].y -this->cam.zoom*_model.points[_model.triangles[i].p1].z)*OUTPUT_Y_MODIFIER +
                    //         origin_y+ (sinr_z*_model.points[_model.triangles[i].p2].x + cosr_z*_model.points[_model.triangles[i].p2].y -this->cam.zoom*_model.points[_model.triangles[i].p2].z)*OUTPUT_Y_MODIFIER +
                    //         origin_y+ (sinr_z*_model.points[_model.triangles[i].p3].x + cosr_z*_model.points[_model.triangles[i].p3].y -this->cam.zoom*_model.points[_model.triangles[i].p3].z)*OUTPUT_Y_MODIFIER
                    //     )*0.333 ,
                    //     (
                    //         origin_x+ (cosr_z*_model.points[_model.triangles[i].p1].x - sinr_z*_model.points[_model.triangles[i].p1].y)*OUTPUT_X_MODIFIER +
                    //         origin_x+ (cosr_z*_model.points[_model.triangles[i].p2].x - sinr_z*_model.points[_model.triangles[i].p2].y)*OUTPUT_X_MODIFIER +
                    //         origin_x+ (cosr_z*_model.points[_model.triangles[i].p3].x - sinr_z*_model.points[_model.triangles[i].p3].y)*OUTPUT_X_MODIFIER
                    //     )*0.333 + (cosr_z*triangle_normal.x - sinr_z*triangle_normal.y)*OUTPUT_X_MODIFIER,
                    //     (
                    //         origin_y+ (sinr_z*_model.points[_model.triangles[i].p1].x + cosr_z*_model.points[_model.triangles[i].p1].y -this->cam.zoom*_model.points[_model.triangles[i].p1].z)*OUTPUT_Y_MODIFIER +
                    //         origin_y+ (sinr_z*_model.points[_model.triangles[i].p2].x + cosr_z*_model.points[_model.triangles[i].p2].y -this->cam.zoom*_model.points[_model.triangles[i].p2].z)*OUTPUT_Y_MODIFIER +
                    //         origin_y+ (sinr_z*_model.points[_model.triangles[i].p3].x + cosr_z*_model.points[_model.triangles[i].p3].y -this->cam.zoom*_model.points[_model.triangles[i].p3].z)*OUTPUT_Y_MODIFIER
                    //     )*0.333 + (sinr_z*triangle_normal.x + cosr_z*triangle_normal.y -this->cam.zoom*triangle_normal.z)*OUTPUT_Y_MODIFIER
                    // );
                };
            };
            current_model = current_model->getNext();
        };
        //*/
    };

    { /* drawing points
        SDL_SetRenderDrawColor( this->renderer , 255 , 255 , 255 , 255 );
        LinkedListNode<model_t>* current_model = this->models;
        while ( current_model != nullptr ){
            model_t _model = current_model->getValue();
            for ( int i = 0; i < _model.points_amount; i++ ){
                SDL_RenderDrawPoint(this->renderer,
                    origin_x+ (cosr_z*_model.points[i].x - sinr_z*_model.points[i].y)*OUTPUT_X_MODIFIER ,
                    origin_y+ (sinr_z*_model.points[i].x + cosr_z*_model.points[i].y -this->cam.zoom*_model.points[i].z)*OUTPUT_Y_MODIFIER
                );
            };
            current_model = current_model->getNext();
        };
        //*/
    };
    { /* how to draw points
        for ( int x = -10; x <= 10; x++ ){
            for ( int y = -10; y <= 10; y++ ){
                for ( int z = -10; z <= 10; z++ ){
                    SDL_RenderDrawPoint(this->renderer,
                        origin_x+ (cosr_z*x - sinr_z*y)*OUTPUT_X_MODIFIER ,
                        origin_y+ (sinr_z*x + cosr_z*y -this->cam.zoom*z)*OUTPUT_Y_MODIFIER
                    );
                };
            };
        };
        //*/
    };
    { /* draw axisses
        // x axis
        SDL_SetRenderDrawColor( this->renderer , 255 , 0 , 0 , 255 );
        SDL_RenderDrawLine(this->renderer,
            origin_x ,
            origin_y ,
            origin_x+ (cosr_z)*OUTPUT_X_MODIFIER ,
            origin_y+ (sinr_z)*OUTPUT_Y_MODIFIER
        );
        // y axis
        SDL_SetRenderDrawColor( this->renderer , 0 , 0 , 255 , 255 );
        SDL_RenderDrawLine(this->renderer,
            origin_x ,
            origin_y ,
            origin_x+ (-sinr_z)*OUTPUT_X_MODIFIER ,
            origin_y+ (cosr_z)*OUTPUT_Y_MODIFIER
        );
        // z axis
        SDL_SetRenderDrawColor( this->renderer , 0 , 255 , 0 , 255 );
        SDL_RenderDrawLine(this->renderer,
            origin_x ,
            origin_y ,
            origin_x ,
            origin_y+ (-this->cam.zoom)*OUTPUT_Y_MODIFIER
        );
        //*/
    };
    
    

    // drawing canvas to screen
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
    if ( this->key_space ){
        this->cam.rot_pos.z += 1/this->cam.zoom;
    };
    if ( this->key_lshift ){
        this->cam.rot_pos.z -= 1/this->cam.zoom;
    };
    if ( this->keys['a'] || this->keys['A'] ){
        this->cam.rot_pos.x += sin(this->cam.rotation+M_PI_2*3)/this->cam.zoom;
        this->cam.rot_pos.y += cos(this->cam.rotation+M_PI_2*3)/this->cam.zoom;
    };
    if ( this->keys['d'] || this->keys['D'] ){
        this->cam.rot_pos.x += sin(this->cam.rotation+M_PI_2)/this->cam.zoom;
        this->cam.rot_pos.y += cos(this->cam.rotation+M_PI_2)/this->cam.zoom;
    };
    if ( this->keys['w'] || this->keys['W'] ){
        this->cam.rot_pos.x += sin(this->cam.rotation+M_PI)/this->cam.zoom;
        this->cam.rot_pos.y += cos(this->cam.rotation+M_PI)/this->cam.zoom;
    };
    if ( this->keys['S'] || this->keys['S'] ){
        this->cam.rot_pos.x += sin(this->cam.rotation)/this->cam.zoom;
        this->cam.rot_pos.y += cos(this->cam.rotation)/this->cam.zoom;
    };
    if ( this->key_right ){
        this->cam.rotation -= M_PI/180;
        if ( this->cam.rotation < 0 ){ this->cam.rotation += M_PI*2; };
    };
    if ( this->key_left ){
        this->cam.rotation += M_PI/180;
        if ( this->cam.rotation >= M_PI*2 ){ this->cam.rotation -= M_PI*2; };
    };
    if ( this->key_up ){
        this->cam.zoom += this->cam.zoom*0.05;
        if ( this->cam.zoom > 10 ){ this->cam.zoom = 10; };
    };
    if ( this->key_down ){
        this->cam.zoom -= this->cam.zoom*0.05;
        if ( this->cam.zoom < 0.1 ){ this->cam.zoom = 0.1; };
    };
    return;
};
