#include <eigen3/Eigen/Dense>
#include <vector>
#include <algorithm>
#include <iostream>
#include "tgaimage.h"
#include "traingle.h"

using uint = unsigned int;
using Point = Eigen::Matrix<uint, 2, 1>;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

bool is_in_bound(TGAImage &image, const Point &p){
    uint width = image.get_width();
    uint height = image.get_height();
    auto ans = p.x() < width && p.y() < height ? true : false;
    return ans;
}

void line(const Point &p_start, const Point &p_end, TGAImage &image, const TGAColor &color) {
    uint x0, x1, y0, y1;
    x0 = p_start.x();
    y0 = p_start.y();
    x1 = p_end.x();
    y1 = p_end.y();
    if(!is_in_bound(image, p_start) || !is_in_bound(image, p_end)){
        fprintf(stderr, "Point out of bound");
        std::exit(-1);
    }
    bool flip = false;
    if(std::abs((int)(y1-y0)) > std::abs((int)(x1-x0))){
        std::swap(x0, y0);
        std::swap(x1, y1);
        flip = true;
    }
    if(x0 > x1){
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dy = y1 - y0;
    int dx = x1 - x0;
    int y = y0;
    int error = 0;
    int derror = 2 * std::abs((int)dy);
    for (int x=x0; x<=x1; x++) { 
        flip?image.set(y, x, color):image.set(x, y, color); 
        error += derror;
        if(error > dx){
            error -= 2 * dx;
            y += (y1>y0?1:-1);
        }
    } 
}

bbox get_bbox(Traingle t){
    std::vector<uint> x_lst{0, 0, 0};
    std::vector<uint> y_lst{0, 0, 0};
    std::transform(t.vertex.begin(), t.vertex.end(), x_lst.begin(), [](Point x)->uint {return x.x();});
    std::transform(t.vertex.begin(), t.vertex.end(), y_lst.begin(), [](Point x)->uint {return x.y();});
    uint x_max = *std::max_element(x_lst.begin(),x_lst.end()); 
    uint y_max = *std::max_element(y_lst.begin(),y_lst.end()); 
    uint x_min = *std::min_element(x_lst.begin(),x_lst.end()); 
    uint y_min = *std::min_element(y_lst.begin(),y_lst.end()); 
    return bbox(x_min, x_max, y_min, y_max);
}

void raster_triangle(const Traingle t, TGAImage &image, const TGAColor &color){
    bbox box = get_bbox(t);
    for(uint x=box.left; x<box.right; x++){
        for(uint y=box.top; y<box.bottom; y++){
            if(t.inside(x, y)){
                image.set(x, y, color);
            }
        }
    }
}

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    // Point p11(20, 13), p12(40, 80), p21(80, 40), p22(13, 20), p31(30, 15), p32(80, 40);
    Point p11(10, 10), p12(10, 70), p21(90, 10);
    Traingle t(p11, p12, p21);
    raster_triangle(t, image, red);
    line(p11, p12, image, white);
    line(p12, p21, image, white);
    line(p21, p11, image, white);
    image.write_tga_file("output.tga");
    return 0;
}