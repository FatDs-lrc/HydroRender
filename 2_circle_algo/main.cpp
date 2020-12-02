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
    bool ans = p.x() < width && p.y() < height ? true : false;
    return ans;
}

void set_pixel(const Point &center, uint x, uint y, TGAImage &image, const TGAColor &color){
    image.set(center.x()+x, center.y()+y, color); 
    image.set(center.x()-x, center.y()+y, color); 
    image.set(center.x()+x, center.y()-y, color); 
    image.set(center.x()-x, center.y()-y, color); 
    image.set(center.x()+y, center.y()+x, color); 
    image.set(center.x()-y, center.y()+x, color); 
    image.set(center.x()+y, center.y()-x, color); 
    image.set(center.x()-y, center.y()-x, color); 
}

void draw_circle(const Point &center, uint R, TGAImage &image, const TGAColor &color) {
    uint x = 0, y = R;
    int d = 3 - 2*R;
    while(y>=x){
        set_pixel(center, x++, y, image, color);
        d += (d > 0 ? 4 * (x - y--) + 10 : 4 * x + 6); 
    }
}

int main(int argc, char** argv) {
    TGAImage image(300, 300, TGAImage::RGB);
    Point p(150, 150);
    draw_circle(p, 50, image, red);
    draw_circle(p, 100, image, white);
    draw_circle(p, 150, image, red);
    std::cout << image.write_tga_file("output.tga") << std::endl;
    return 0;
}