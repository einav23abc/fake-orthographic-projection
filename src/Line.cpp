
Line::Line(point_t p1,point_t p2){
    this->m = ((long double)p2.y-p1.y)/((long double)p2.x-p1.x);
    this->b = -this->m*p1.x+p1.y;
    this->isYparl = false;
    if ( (float)p2.x == (float)p1.x ){
        this->isYparl = true;
        this->x = p1.x;
    };
    this->minx = std::min(p1.x,p2.x);
    this->maxx = std::max(p1.x,p2.x);
    this->miny = std::min(p1.y,p2.y);
    this->maxy = std::max(p1.y,p2.y);
    this->infinite = false;
    return;
};
Line::Line(point_t p1,point_t p2,bool infinite){
    this->m = ((long double)p2.y-p1.y)/((long double)p2.x-p1.x);
    this->b = -this->m*p1.x+p1.y;
    this->isYparl = false;
    if ( (float)p2.x == (float)p1.x ){
        this->isYparl = true;
        this->x = p1.x;
        this->minx = std::min(p1.x,p2.x);
        this->maxx = std::max(p1.x,p2.x);
    };
    this->minx = std::min(p1.x,p2.x);
    this->maxx = std::max(p1.x,p2.x);
    this->miny = std::min(p1.y,p2.y);
    this->maxy = std::max(p1.y,p2.y);
    this->infinite = infinite;
    return;
};

Line::~Line(){
    return;
};

lineCollResult_t* Line::collision( Line* line1 , Line* line2 ){
    lineCollResult_t* res = (lineCollResult_t*)malloc( sizeof(lineCollResult_t) );
    if ( res == nullptr ){
        std::cout << "malloc failed at Line::collision\n";
    };
    res->collided = true;
    if( line1->isYparl && line2->isYparl ){
        res->collided = false;
        res->reason = 1;
    }else if( line1->isYparl ){
        res->point.x = line1->x;
        res->point.y = Line::getYatX( line2 , line1->x );
        if (
            ( line1->infinite == false && line2->infinite == false ) &&
            (
                res->point.y > line1->maxy || res->point.y < line1->miny
            )
        ){
            res->collided = false;
            res->reason = 2;
        };
    }else if( line2->isYparl ){
        res->point.x = line2->x;
        res->point.y = Line::getYatX( line1 , line2->x );
        if (
            ( line1->infinite == false && line2->infinite == false ) &&
            (
                res->point.y > line2->maxy || res->point.y < line2->miny
            )
        ){
            res->collided = false;
            res->reason = 3;
        };
    }else{
        res->point.x = (line2->b - line1->b)/(line1->m - line2->m);
        res->point.y = Line::getYatX( line1 , res->point.x );
        if (
            ( line1->infinite == false && line2->infinite == false ) &&
            (
                res->point.x > line1->maxx || res->point.x < line1->minx ||
                res->point.x > line2->maxx || res->point.x < line2->minx ||
                res->point.y > line1->maxy || res->point.y < line1->miny ||
                res->point.y > line2->maxy || res->point.y < line2->miny
            )
        ){
            res->collided = false;
            res->reason = 4;
        };
    };
    if (
        ( line1->infinite == false && line2->infinite == false ) &&
        (
            line1->minx > line2->maxx || line1->maxx < line2->minx || line1->miny > line2->maxy || line1->maxy < line2->miny
        )
    ){
        res->collided = false;
        res->reason = 5;
    };
    return res;
};
long double Line::getXatY( Line* line , long double y ){
    return ((y-line->b)/line->m);
};
long double Line::getYatX( Line* line , long double x ){
    return (line->m*x+line->b);
};