#include<fstream>
#include<iostream>

using namespace std;

//--------------------------------------- STRUCTURES
struct Color {
    int red, green, blue;
};

struct Rectangle {
    int x, y, dx, dy;
    Color color;
};

//--------------------------------------- FUNCTION DECLARATION
void draw(Rectangle rect, Color drawing[]); // add rectangle layer on top of a colorful drawing

//--------------------------------------- MAIN
static const int DRAWING_SIZE = 100;

int main() {

    //--------------------------------------- READ INPUT DATA
    int n; // number of rectangles
    int i; // used for loops' index
    int rightColumn = 0, bottomRow = 0; // to remove empty space on the right and bottom
    ifstream inputFile("U2.txt"); // open task's input file
    inputFile >> n; // read number of rectangles from input file
    Rectangle rectangles[n]; // allocate memory for n rectangles' information

    for (i = 0; i < n; i++) {
        inputFile >> rectangles[i].x >> rectangles[i].y >> rectangles[i].dx >> rectangles[i].dy;
        inputFile >> rectangles[i].color.red >> rectangles[i].color.green >> rectangles[i].color.blue;


        //--------------------------------------- ADJUST BOTTOM RIGHT CORNER IF NEEDED
        int xx = rectangles[i].x + rectangles[i].dx;
        int yy = rectangles[i].y + rectangles[i].dy;

        if (rightColumn < xx) {
            rightColumn = xx;
        }
        // Alternatives:
        //        rightColumn = (rightColumn < xx) ? xx : rightColumn; // Elvis expression
        //        rightColumn = max(rightColumn, xx);

        if (bottomRow < yy) {
            bottomRow = yy;
        }
    }
    inputFile.close();

    //--------------------------------------- INITIALIZE DRAWING
    Color drawing[DRAWING_SIZE * DRAWING_SIZE]; // allocate memory for colorful picture. Array size = ROWS * COLUMNS
    for (i = 0; i < DRAWING_SIZE * DRAWING_SIZE; i++) { // make all drawing cells white
        drawing[i].red = 255;
        drawing[i].green = 255;
        drawing[i].blue = 255;
    }

    //--------------------------------------- DRAW RECTANGLES
    for (i = 0; i < n; i++) {
        draw(rectangles[i], drawing);
    }

    //--------------------------------------- WRITE RESULT
    ofstream resultFile("U2rez.txt");
    resultFile << bottomRow << " " << rightColumn << endl;
    int column, row;
    for (row = 0; row < bottomRow; row++) {
        for (column = 0; column < rightColumn; column++) {
            i = DRAWING_SIZE * row + column;
            resultFile << drawing[i].red << " " << drawing[i].green << " " << drawing[i].blue << endl;
            cout << drawing[i].red << " " << drawing[i].green << " " << drawing[i].blue << endl;
        }
    }
    resultFile.close();
    return 0;
}

//--------------------------------------- FUNCTION IMPLEMENTATION
void draw(Rectangle rect, Color drawing[]) {
    int column, row, i;

    for (row = rect.y; row < rect.y + rect.dy; row++) { // Using < instead of <= so neighbour cells wouldn't be modified
        for (column = rect.x; column < rect.x + rect.dx; column++) {
            i = DRAWING_SIZE * row + column;
            drawing[i] = rect.color;
        }
    }
}
