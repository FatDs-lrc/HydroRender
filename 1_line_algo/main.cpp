#include <eigen3/Eigen/Dense>
#include <iostream>
#include "tgaimage.h"

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

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    Point p11(0, 10), p12(10, 70), p21(90, 10);
    line(p11, p12, image, red);
    line(p21, p12, image, white);
    line(p21, p11, image, red);
    std::cout << image.write_tga_file("output.tga") << std::endl;
    return 0;
}