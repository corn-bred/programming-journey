#include "linedrawer.h"
#include <vector>
#include <cmath>
#include <algorithm>

void LineManager::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, std::vector<uint32_t> *input) {
    //bitshift oh no
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return; // to not core dump or somehitng
    //input[y * WIDTH + x] = (0xFF << 24) | (r << 16) | (g << 8) | b; 
    // because
    //00000000 00000000 00000000 00000000
    //alpha    red      green    blue
    //EXAMPLE
    //so alpha is first
    //00000000 00000000 00000000 11111111
    //but then is shifted 24 to the left soo
    //11111111 00000000 00000000 00000000
    //then do the rest, now it's
    //11111111 00000000 00000000 00000000
    //00000000 00010000 00000000 00000000
    //00000000 00000000 11111111 00000000
    //00000000 00000000 00000000 00010000
    //but HOW DO YOU COMBINE IT???
    //easy: the OR operator ( | )
    //basically: it compares the bits and per bit it asks:
    //if (a = 1 || b = 1) then output = 1
    //so if any bit is 1 then the output is 1
    //so output is:
    //11111111 00010000 11111111 00010000
    //easy B)

}

LineManager::LineManager(int w, int h) :WIDTH(w), HEIGHT(h){
    pixels.resize(w * h);
}//oh god what do i fricking put here

void LineManager::drawLine2D(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x2 - x1 < 0) ? -1 : 1;
    int sy = (y2 - y1 < 0) ? -1 : 1;
    int error = 0;

    if (dx < dy)
    {
        int x = x1;

        for (int y = y1; y != y2 + sy; y += sy)
        {
            setPixel(x, y, 255, 255, 255, &this->pixels);

            error += abs(dx);

            if (error * 2 >= abs(dy))
            {
                error -= abs(dy);
                x += sx;
            }
        }
    }
    else
    {

        int y = y1;

        for (int x = x1; x != x2 + sx; x += sx)
        {
            setPixel(x, y, 255, 255, 255, &this->pixels);

            error += abs(dy);

            if (error * 2 >= abs(dx))
            {
                error -= abs(dx);
                y += sy;
            }
        }
    }
}

void LineManager::drawLine2D(int x1, int y1, int x2, int y2, std::vector<uint32_t> *output)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x2 - x1 < 0) ? -1 : 1;
    int sy = (y2 - y1 < 0) ? -1 : 1;
    int error = 0;

    if (dx < dy)
    {
        int x = x1;

        for (int y = y1; y != y2 + sy; y += sy)
        {
            setPixel(x, y, 255, 255, 255, output);

            error += abs(dx);

            if (error * 2 >= abs(dy))
            {
                error -= abs(dy);
                x += sx;
            }
        }
    }
    else
    {

        int y = y1;

        for (int x = x1; x != x2 + sx; x += sx)
        {
            setPixel(x, y, 255, 255, 255, output);

            error += abs(dy);

            if (error * 2 >= abs(dx))
            {
                error -= abs(dx);
                y += sy;
            }
        }
    }
}

void LineManager::drawTriangleFilled(int triangleX[3], int triangleY[3]) {
    drawLine2D(triangleX[0], triangleY[0], triangleX[1], triangleY[1]);
    drawLine2D(triangleX[1], triangleY[1], triangleX[2], triangleY[2]);
    drawLine2D(triangleX[2], triangleY[2], triangleX[0], triangleY[0]);
    
    int xmin = triangleX[0];
    int xmax = triangleX[0];
    for (int i = 0; i < 3; i++) {
        if (triangleX[i] > xmax) xmax = triangleX[i]; 
        if (triangleX[i] < xmin) xmin = triangleX[i]; 
    }

    int ymin = triangleY[0];
    int ymax = triangleY[0];
    for (int i = 0; i < 3; i++) {
        if (triangleY[i] > ymax) ymax = triangleY[i]; 
        if (triangleY[i] < ymin) ymin = triangleY[i]; 
    }
    int linemin;
    int linemax;
    for (int i = ymin; i <= ymax; i++) {
        linemin = 0;
        linemax = 0;
        std::vector<int> onlinebits;
        for (int j = xmin; j <= xmax; j++) {
            if (pixels[i*WIDTH+j] != 0xFF000000) {
                onlinebits.push_back(j);
                
                
                
            }
            
            
        }
        linemax = onlinebits.back();
        linemin = onlinebits.front();
        drawLine2D(linemin, i, linemax, i);
    }
}



void LineManager::drawLine2DGradient(int x1, int y1, uint8_t a1, uint8_t r1, uint8_t g1, uint8_t b1, int x2, int y2, uint8_t a2, uint8_t r2, uint8_t g2, uint8_t b2, void (*operation)(int x, int y, uint8_t r, uint8_t g, uint8_t b)) {

}