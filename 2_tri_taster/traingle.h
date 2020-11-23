#ifndef __TRAINGLE_H__
#define __TRAINGLE_H__

#include "tgaimage.h"
#include <vector>
#include <eigen3/Eigen/Dense>

using uint = unsigned int;
using Point = Eigen::Matrix<uint, 2, 1>;

struct Traingle{
    std::vector<Point> vertex;
    Traingle(){
        Point p0, p1, p2;
        p0 << 0, 0;
        p1 << 0, 0;
        p2 << 0, 0;
        vertex.push_back(p0);
        vertex.push_back(p1);
        vertex.push_back(p2);
    };
    Traingle(Point &x0, Point &x1, Point &x2){
        Point p0, p1, p2;
        p0 << x0.x(), x0.y();
        p1 << x1.x(), x1.y();
        p2 << x2.x(), x2.y();
        vertex.push_back(p0);
        vertex.push_back(p1);
        vertex.push_back(p2);
    };
    ~Traingle(){};
    bool inside(uint x, uint y) const{
        Point p0(this->vertex[0].x()-x, this->vertex[0].y()-y);
        Point p1(this->vertex[1].x()-x, this->vertex[1].y()-y);
        Point p2(this->vertex[2].x()-x, this->vertex[2].y()-y);
        int z0 = p0.x() * p1.y() - p0.y() * p1.x();
        int z1 = p1.x() * p2.y() - p1.y() * p2.x();
        int z2 = p2.x() * p0.y() - p2.y() * p0.x();
        if((z0<=0 && z1<=0 && z2<=0) || (z0>=0 && z1>=0 && z2>=0)) return true;
        else return false;
    };
};

struct bbox{
    uint left, right, top, bottom;
    bbox():left(0), right(0), top(0), bottom(0){};
    bbox(uint left, uint right, uint top, uint bottom){
        this->left = left;
        this->right = right;
        this->top = top;
        this->bottom = bottom;
    };
};

#endif