#ifndef Line_HPP
#define Line_HPP
#include <cmath>

typedef struct point {
    long double x;
    long double y;
    long double z;
} point_t;
typedef struct {
    bool collided;
    int reason;
    point_t point;
} lineCollResult_t;

class Line {
    public:
        Line(point_t p1,point_t p2);
        Line(point_t p1,point_t p2,bool infinite);
        ~Line();
        double b,m,x;
        double minx,maxx,miny,maxy;
        bool isYparl;
        bool infinite;
        static lineCollResult_t* collision( Line* line1 , Line* line2 );
        static long double getXatY( Line* line , long double y );
        static long double getYatX( Line* line , long double x );
    private:
        
};

#include "Line.cpp"
#endif