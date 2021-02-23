/*******************************************************
 * Homework 1: Rasterization                           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method decribed in the handout.                     *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int radius;
bool** image;

// x1 and y1 are for the circle with radius 150 and x2 and y2 are for the circle with radius 100.
void renderPixel(int x1, int y1, int x2, int y2) {
    assert(x1 >= 0 && y1 >= 0 && x1 <= radius && y1 <= radius);
    // The addition and subtracion of radius / 2 is to account for the fact that
    // the (0,0) is at the bottom left corner.
    // Light up the pixels for the half circle with radius 150
    image[x1 + radius / 2][y1 + radius / 2] = 1;
    image[y1 + radius / 2][x1 + radius / 2] = 1;
    image[x1 + radius / 2][radius / 2 - y1] = 1;
    image[y1 + radius / 2][radius / 2 - x1] = 1;
    
    // Light up the pixels for the half circle with radius 100.
    image[x2 + radius / 2][y2 + radius / 2] = 1;
    image[y2 + radius / 2][x2 + radius / 2] = 1;
    image[radius / 2 - y2][x2 + radius / 2] = 1;
    image[radius / 2 - x2][y2 + radius / 2] = 1;

}

void rasterizeArc(int r) {
    // TODO:  rasterize the arc using renderPixel to light up pixels
    // Varaiables for half circle with radius 150.
    int x1 = 0;
    int y1 = r/2;
    int d1 = 1 - r/2;

    // Variables for half circle with radius 100.
    int x2 = 0;
    int y2 = (r - 50) / 2;
    int d2 = 1 - (r - 50) / 2;
    renderPixel(x1, y1, x2, y2);

    // Midpoint circle scan conversion algorithm for both half circles.
    while (y1 > x1 || y2 > x2) {
        if (y1 > x1) {
            if (d1 < 0)
                d1 += 2 * x1 + 3;
            else {
                d1 += 2 * (x1 - y1) + 5;
                y1--;
            }
            x1++;
        }
        if (y2 > x2) {
            if (d2 < 0)
                d2 += 2 * x2 + 3;
            else {
                d2 += 2 * (x2 - y2) + 5;
                y2--;
            }
            x2++;
        }
        renderPixel(x1, y1, x2, y2);
    }
}

// You shouldn't need to change anything below this point.

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " circleSize\n";
        return 0;
    }

#ifdef _WIN32
    sscanf_s(argv[1], "%d", &radius);
#else
    sscanf(argv[1], "%d", &radius);
#endif
    if (radius <= 0) {
        cout << "Image must be of positive size.\n";
        return 0;
    }

    // reserve image as 2d array
    image = new bool* [radius + 1];
    for (int i = 0; i <= radius; i++) image[i] = new bool[radius + 1]{ 0 };

    rasterizeArc(radius);

    char filename[50];
#ifdef _WIN32
    sprintf_s(filename, 50, "circle%d.ppm", radius);
#else
    sprintf(filename, "circle%d.ppm", radius);
#endif

    ofstream outfile(filename);
    outfile << "P3\n# " << filename << "\n";
    outfile << radius + 1 << ' ' << radius + 1 << ' ' << 1 << endl;

    for (int i = 0; i <= radius; i++)
        for (int j = 0; j <= radius; j++)
            outfile << image[radius - i][j] << " 0 0\n";

    // delete image data
    for (int i = 0; i <= radius; i++) delete[] image[i];
    delete[] image;

    return 0;
}
