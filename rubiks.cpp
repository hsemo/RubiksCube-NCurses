#include <iostream>
#include <conio.h>
#include <random>
#include <vector>
#include <fstream>
#include "rubiks.h"

// using namespace std;
using std::string; using std::random_device; using std::mt19937; using std::uniform_int_distribution;
using std::cout; using std::printf; using std::swap; using std::endl;

rubiks::rubiks()
{
    int moves = 20;
    string mvs = "";
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 27);
    for (int i = 0; i < moves; i++)
    {
        mvs += totalValidMoves[dist(mt) - 1] + " ";
    }
    mvs.pop_back();
    initialCube();
    executeMoves(mvs);
}

rubiks::rubiks(string moves)
{
    initialCube();
    executeMoves(moves);
}

rubiks::rubiks(rubiks *cube1)
{
    copy((*cube1).cube, true);
}

rubiks::rubiks(char (*cb)[3][3])
{
    copy(cb, true);
}

void rubiks::initialCube(void)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cube[i][j][k] = colors[i];
            }
        }
    }
}

void rubiks::copy(void)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cubecopy[i][j][k] = cube[i][j][k];
            }
        }
    }
}

void rubiks::copy(char (*cb)[3][3], bool givenTocurrent = true)
{
    char(*dst)[3][3] = cube, (*src)[3][3] = cb;

    // cout << "'copy(char (*cb)[3][3], bool givenTocurrent = true)' func is called\n";

    if (!givenTocurrent)
    {
        dst = cb;
        src = cube;
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                dst[i][j][k] = src[i][j][k];
                cubecopy[i][j][k] = src[i][j][k];
            }
        }
    }
}

void rubiks::copy(rubiks& tempCube){
    // cout << "\n'copy(rubiks& tempCube)' func called\n";
    copy(tempCube.cube, true);
}

int rubiks::getval(char key)
{
    // cout << "'getval(char key)' func is called!!\n";
    // cout << "getting value of KEY: " << key << endl;
    for (int i = 0; i < 6; i++)
    {
        if (keys[i] == key)
        {
            // cout << "\'" << vals[i] << "\' is returned, when 'i' is: " << i << endl;
            return vals[i];
        }
    }
    // cout << "'-1' is returned\n";
    return -1;
}

char rubiks::getkey(int val)
{
    for (int i = 0; i < 6; i++)
    {
        if (vals[i] == val)
        {
            return keys[i];
        }
    }
    return -1;
}

void rubiks::setval(char key, int val)
{
    for (int i = 0; i < 6; i++)
    {
        if (keys[i] == key)
        {
            vals[i] = val;
            return;
        }
    }
}

void rubiks::rotateside(char side, bool isclockwise = true)
{
    int sdindx, t = 2, j = 0;
    // cout << "inside rotateside func, rotating the side: " << side << endl;
    sdindx = getval(side);
    // cout << "sdindx is: " << sdindx << endl;
    copy();
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (!isclockwise)
            {
                cube[sdindx][2 - k][i] = cubecopy[sdindx][i][k];
            }
            else
            {
                cube[sdindx][k][2 - i] = cubecopy[sdindx][i][k];
            }
        }
    }
}

void rubiks::xrotate(bool isclockwise = true)
{
    char sds[5] = {'F', 'U', 'B', 'D', 'F'};
    if (!isclockwise)
    {
        // cout << "Applying X'" << endl;
        swap(sds[1], sds[3]);
    }
    else
    {
        // cout << "Applying X" << endl;
    }

    int i = 0;
    rotateside('R', isclockwise);
    rotateside('L', !isclockwise); // for anticlockwise rotation
    copy();
    while (i != 4)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (i == 1 || i == 2)
                {
                    cube[getval(sds[i + 1])][2 - j][2 - k] = cubecopy[getval(sds[i])][j][k];
                    // printf("cube[%d][%d][%d] = cubecopy[%d][%d][%d]: %c=%c\n",getval(sds[i + 1]),2 - j,2 - k,getval(sds[i]),j,k,cube[getval(sds[i + 1])][2 - j][2 - k],cubecopy[getval(sds[i])][j][k]);
                }
                else
                {
                    cube[getval(sds[i + 1])][j][k] = cubecopy[getval(sds[i])][j][k];
                    // printf("cube[%d][%d][%d] = cubecopy[%d][%d][%d]: %c=%c\n",getval(sds[i + 1]),j,k,getval(sds[i]),j,k,cube[getval(sds[i + 1])][j][k],cubecopy[getval(sds[i])][j][k]);
                }
            }
        }
        i++;
    }
}

void rubiks::yrotate(bool isclockwise = true)
{
    char sds[5] = {'F', 'L', 'B', 'R', 'F'};

    if (!isclockwise)
    {
        // cout << "Applying Y'...\n";
        swap(sds[1], sds[3]); // for anticlockwise rotation
    }
    else
    {
        // cout << "Applying Y...\n";
    }

    int i = 0;
    rotateside('U', isclockwise);
    // cout << "rotateside func is called in yrotate func!!\n";
    rotateside('D', !isclockwise); // for anticlockwise rotation
    // cout << "rotateside func is finished in yrotate func!!\n";
    // cout << "'copy' func is called in yrotate func!!\n";
    copy();
    // cout << "'copy' func is finished in yrotate func!!\n";
    while (i != 4)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cube[getval(sds[i + 1])][j][k] = cubecopy[getval(sds[i])][j][k];
            }
        }
        i++;
    }
}

void rubiks::zrotate(bool isclockwise = true)
{
    char sds[5] = {'U', 'R', 'D', 'L', 'U'};

    if (!isclockwise)
    {
        // cout << "Applying Z'...\n";
        swap(sds[1], sds[3]); // for anticlockwise rotation
    }
    else
    {
        // cout << "Applying Z...\n";
    }

    rotateside('F', isclockwise);
    rotateside('B', !isclockwise); // for anticlockwise rotation

    copy();
    int i = 0;
    while (i != 4)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cube[getval(sds[i + 1])][k][2 - j] = cubecopy[getval(sds[i])][j][k];
            }
        }
        i++;
    }
}

void rubiks::Frotat(bool isclockwise = true)
{
    // cout << "'rotateside' func is called!!\n";
    rotateside('F', isclockwise);
    // cout << "'rotateside' func is finished!!\n";

    int i = 0;
    // cout << "'copy()' func is called!!\n";
    copy();
    // cout << "'copy()' func is finished!!\n";

    if (!isclockwise)
    {
        // cout << "Applying F'...\n";
        for (int k = 0; k < 3; k++)
        {
            cube[1][2 - k][2 - i] = cubecopy[0][2 - i][k];
            cube[5][i][2 - k] = cubecopy[1][2 - k][2 - i];
            cube[4][k][i] = cubecopy[5][i][2 - k];
            cube[0][2 - i][k] = cubecopy[4][k][i];
        }
    }
    else
    {
        // cout << "Applying F...\n";
        for (int k = 0; k < 3; k++)
        {
            // cout << "k: " << k << endl;
            // printf("cube[%d][%d][%d] = cubecopy[%d][%d][%d]: %c = %c",getval('D'),i,2 - k,getval('R'),k,i,cube[getval('D')][i][2 - k],cubecopy[getval('R')][k][i]);
            cube[4][k][i] = cubecopy[0][2 - i][k];
            cube[5][i][2 - k] = cubecopy[4][k][i];
            cube[1][2 - k][2 - i] = cubecopy[5][i][2 - k];
            cube[0][2 - i][k] = cubecopy[1][2 - k][2 - i];
        }
    }
    // cout << "returning from 'Frotat' func\n";
}

void rubiks::Brotat(bool isclockwise = true)
{
    // cout << "yrotate is called!!\n";
    yrotate();
    // cout << "yrotate is finished!!\n";
    yrotate();
    Frotat(isclockwise);
    yrotate(false);
    yrotate(false);
}

void rubiks::Rrotat(bool isclockwise = true)
{
    yrotate();
    Frotat(isclockwise);
    yrotate(false);
}

void rubiks::Lrotat(bool isclockwise = true)
{
    yrotate(false);
    Frotat(isclockwise);
    yrotate();
}

void rubiks::Urotat(bool isclockwise = true)
{
    xrotate(false);
    Frotat(isclockwise);
    xrotate();
}

void rubiks::Drotat(bool isclockwise = true)
{
    xrotate();
    Frotat(isclockwise);
    xrotate(false);
}

void rubiks::Erotat(bool isclockwise = true)
{
    char sds[5] = {'F', 'R', 'B', 'L', 'F'};

    if (!isclockwise)
    {
        // cout << "Applying E'...\n";
        swap(sds[1], sds[3]); // for anticlockwise rotation
    }
    else
    {
        // cout << "Applying E...\n";
    }

    int i = 0;
    copy();

    while (i != 4)
    {
        for (int k = 0; k < 3; k++)
        {
            cube[getval(sds[i + 1])][1][k] = cubecopy[getval(sds[i])][1][k];
        }
        i++;
    }
}

void rubiks::Mrotat(bool isclockwise = true)
{
    zrotate(false);
    Erotat(isclockwise);
    zrotate();
}

void rubiks::Srotat(bool isclockwise = true)
{
    xrotate(false);
    Erotat(isclockwise);
    xrotate();
}

void rubiks::printCube(void)
{
    for (int i = 0; i < 6; i++)
    {
        cout << getkey(i) << " side:   ";
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                printf("%c ", cube[i][j][k]);
            }
            cout << endl;
            cout << "          ";
        }
        cout << "\n\n";
    }
    return;
}

void rubiks::performMove(const string move)
{
    // cout << "'performMove(const string move)' func is called\n";
    // cout << "performing " << move << "...\n";
    bool isclockwise = true;
    int time = 1, i = 0;

    if (move.length() > 1)
    {
        if (move[1] == '\'')
        {
            isclockwise = false;
        }
        else if (move[1] == '2')
        {
            time = 2;
        }
        else
        {
            cout << "invalid move!! exiting..." << endl;
            return;
        }
    }

    // adding move to performed moves VECTOR
    // performedMoves.push_back(move);
    // cout << "move: " << move << " is added to performedmoves vector!!\n";

    while (i < time)
    {
        // cout << "switched to move[0]: " << move[0] << endl;
        switch (move[0])
        {
        case 'F':
            // cout << "func Frotat is called\n";
            Frotat(isclockwise);
            // cout << "func Frotat is finished\n";
            break;
        case 'B':
            // cout << "func Brotat is called\n";
            Brotat(isclockwise);
            // cout << "func Brotat is finished\n";
            break;
        case 'L':
            Lrotat(isclockwise);
            break;
        case 'R':
            Rrotat(isclockwise);
            break;
        case 'U':
            Urotat(isclockwise);
            break;
        case 'D':
            Drotat(isclockwise);
            break;
        case 'E':
            Erotat(isclockwise);
            break;
        case 'M':
            Mrotat(isclockwise);
            break;
        case 'S':
            Srotat(isclockwise);
            break;
        default:
            break;
        }
        i++;
    }
    return;
}

void rubiks::executeMoves(string moves)
{
    if (moves == ""){
        cout << "(in executeMoves func) moves is empty!! returning...\n";
        return;
    }
    string move = "";
    if (moves[moves.length()-1] != ' ')
    {
        moves += ' ';
    }

    for (int i = 0; i < moves.length(); i++)
    {
        if (moves[i] == ' ')
        {
            performMove(move);
            // cout << "Move performed: " << move << endl;
            move = "";
        }
        else
        {
            move += moves[i];
        }
    }
}

bool rubiks::issolved(void)
{
    if (isSolved)
    {
        return true;
    }
    
    char temp = '\0';
    for (int i = 0; i < 6; i++)
    {
        temp = cube[i][0][0];
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (temp != cube[i][j][k])
                {
                    return false;
                }
            }
        }
    }
    isSolved = true;
    return true;
}

void rubiks::inputFromFile(std::string fname){
    std::ifstream fin;
    std::string line;
    int k=0,l=0;
    fin.open(fname);
    for (int i = 0; i < 6; i++)
    {
        getline(fin, line);
        l = 0;
        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] != ' ')
            {
                cube[i][l][k] = line[j];
                cubecopy[i][l][k] = line[j];
                k++;
                if(k > 2){
                    k = 0;
                    l++;
                }
            }
            
        }
    }
    fin.close();
    return;
}

// void rubiks::solve(int depth = 20)
// {
//     vector<rubiks> cubes;
//     int sz = cubes.size();
//     for (int tmpDepth = 0; tmpDepth < depth; tmpDepth++)
//     {
//         sz = cubes.size();
//         for (int i = 0; i < cubes.size(); i++)
//         {
//             cubes[i].copy(cube);
//         }
//         rubiks x(cube);
//         cubes.push_back(x);

//         sz = cubes.size();
//         for (int i = 0; i < sz; i++)
//         {
//             for (int j = 0; j < 27; j++)
//             {
//                 cubes[sz].copy(cubes[sz - 1].cube);
//                 cubes[sz].performMove(totalValidMoves[i]);
//                 if (cubes[sz].issolved())
//                 {
//                 }
//             }
//         }
//     }
// }

