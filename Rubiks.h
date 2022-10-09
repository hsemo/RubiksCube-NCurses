#ifndef __RUBIKS__H
#define __RUBIKS__H

#include <iostream>
#include <vector>

class Rubiks
{
private:
    char cube[6][3][3];
    char cubecopy[6][3][3];

    // total valid moves that can be performed on a cube
    const std::string totalValidMoves[27] = {"F", "B", "L", "R", "U", "D", "E", "M", "S", "F'", "B'", "L'", "R'", "U'", "D'","E'", "M'", "S'", "F2", "B2", "L2", "R2", "U2", "D2", "E2", "M2", "S2"};

    // std::vector<std::string> performedMoves;

    // for getting value by KEY or key by VALUE
    const std::vector<char> keys = {'U', 'L', 'F', 'B', 'R', 'D'};
    const std::vector<int> vals = {0, 1, 2, 3, 4, 5};

    // default colours indexed sidewise
    const char colors[6] = {'w', 'g', 'r', 'o', 'b', 'y'};

public:
    // cube is solved or not
    bool isSolved = false;

    // copy the cube in cubecopy
    void copy(void);

    // create cube by random moves
    Rubiks();

    // create a cube by MOVES
    Rubiks(std::string);

    // create a cube by a given CUBE
    Rubiks(Rubiks *);

    // create a cube by a given 3D array of matching size
    Rubiks(char (*cb)[3][3]);

    // for getting the value of side KEY
    // return value of KEY if KEY was found else return -1
    int getval(char key);

    // for getting the key of VALUE
    // return key of VALUE if VALUE was found else return -1
    char getkey(int val);

    // set the value of KEY to VAL
    // void setval(char key, int val);

    // copy the given cube in current default cube
    void copy(char(*)[3][3], bool);

    // copy the cube from the given instance of Rubiks class
    void copy(Rubiks&);

    // char* getCube(void);

    // create's a initial solved cube by default colours
    void initialCube(void);

    void printCube(void);

    // check if the cube is solved or not
    bool issolved(void);

    // execute a string of moves seperated by spaces
    void executeMoves(const std::string);
    // perform a single move F, F', F2=F2'

    bool performMove(const std::string);

    // solve the cube and return the shortest solving moves string
    // void solve(int);

    // takes input from file
    void inputFromFile(std::string);

    // write the current cube, as it is, to the output file
    void outputToFile(std::string);

    // returns all the sides of the cube in a string array, without a separator
    std::string * getSidesString(void);

    // returns a single side of the cube in a string, without a separator
    std::string getSideString(int);

    void rotateside(char, bool);
    void xrotate(bool); // rotate the cube to the X axis
    void yrotate(bool); // rotate the cube to the Y axis
    void zrotate(bool); // rotate the cube to the Z axis

    void Frotat(bool); // for rotating Front layer
    void Lrotat(bool); // for rotating Left layer
    void Rrotat(bool); // for rotating Right layer
    void Urotat(bool); // for rotating Up layer
    void Drotat(bool); // for rotating Down layer
    void Brotat(bool); // for rotating Back layer

    void Erotat(bool); // for rotating Equator layer
    void Mrotat(bool); // for rotating Middle layer
    void Srotat(bool); // for rotating to Standing layer
};
#endif
