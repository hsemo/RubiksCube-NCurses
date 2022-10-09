#include <random>
#include <vector>
#include <fstream>
#include "Rubiks.h"

// using namespace std;
using std::string; using std::random_device; using std::mt19937; using std::uniform_int_distribution;
using std::cout; using std::printf; using std::swap; using std::endl;

Rubiks::Rubiks()
{
    int moves = 20;
    string mvs = "";
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 27);
    // random moves generator to initialize new cube 
    for (int i = 0; i < moves; i++)
    {
        mvs += totalValidMoves[dist(mt) - 1] + " ";
    }
    mvs.pop_back();
    initialCube();
    executeMoves(mvs);
}

Rubiks::Rubiks(string moves)
{
    initialCube();
    executeMoves(moves);
}

Rubiks::Rubiks(Rubiks *cube1)
{
    copy((*cube1).cube, true);
}

Rubiks::Rubiks(char (*cb)[3][3])
{
    copy(cb, true);
}

void Rubiks::initialCube(void)
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

void Rubiks::copy(void)
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

void Rubiks::copy(char (*cb)[3][3], bool givenTocurrent = true)
{
    char (*dst)[3][3] = cube, (*src)[3][3] = cb;

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

void Rubiks::copy(Rubiks& tempCube){
    copy(tempCube.cube, true);
}

int Rubiks::getval(char key)
{
    for (int i = 0; i < 6; i++)
    {
        if (keys[i] == key)
        {
            return vals[i];
        }
    }
    return -1;
}

char Rubiks::getkey(int val)
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


void Rubiks::rotateside(char side, bool isclockwise = true)
{
    int sdindx, t = 2, j = 0;
    sdindx = getval(side);
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

void Rubiks::xrotate(bool isclockwise = true)
{
    char sds[5] = {'F', 'U', 'B', 'D', 'F'};
    if (!isclockwise)
    {
        swap(sds[1], sds[3]);
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
                }
                else
                {
                    cube[getval(sds[i + 1])][j][k] = cubecopy[getval(sds[i])][j][k];
                }
            }
        }
        i++;
    }
}

void Rubiks::yrotate(bool isclockwise = true)
{
    char sds[5] = {'F', 'L', 'B', 'R', 'F'};

    if (!isclockwise)
    {
        // cout << "Applying Y'...\n";
        swap(sds[1], sds[3]); // for anticlockwise rotation
    }

    int i = 0;
    rotateside('U', isclockwise);
    rotateside('D', !isclockwise); // for anticlockwise rotation
    copy();
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

void Rubiks::zrotate(bool isclockwise = true)
{
    xrotate(false);
    yrotate(!isclockwise);
    xrotate();
}

void Rubiks::Frotat(bool isclockwise = true)
{
    rotateside('F', isclockwise);

    int i = 0;
    copy();

    if (!isclockwise)
    {
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
        for (int k = 0; k < 3; k++)
        {
            cube[4][k][i] = cubecopy[0][2 - i][k];
            cube[5][i][2 - k] = cubecopy[4][k][i];
            cube[1][2 - k][2 - i] = cubecopy[5][i][2 - k];
            cube[0][2 - i][k] = cubecopy[1][2 - k][2 - i];
        }
    }
}

void Rubiks::Brotat(bool isclockwise = true)
{
    yrotate();
    yrotate();
    Frotat(isclockwise);
    yrotate(false);
    yrotate(false);
}

void Rubiks::Rrotat(bool isclockwise = true)
{
    yrotate();
    Frotat(isclockwise);
    yrotate(false);
}

void Rubiks::Lrotat(bool isclockwise = true)
{
    yrotate(false);
    Frotat(isclockwise);
    yrotate();
}

void Rubiks::Urotat(bool isclockwise = true)
{
    xrotate(false);
    Frotat(isclockwise);
    xrotate();
}

void Rubiks::Drotat(bool isclockwise = true)
{
    xrotate();
    Frotat(isclockwise);
    xrotate(false);
}

void Rubiks::Erotat(bool isclockwise = true)
{
    char sds[5] = {'F', 'R', 'B', 'L', 'F'};

    if (!isclockwise)
    {
        swap(sds[1], sds[3]); // for anticlockwise rotation
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

void Rubiks::Mrotat(bool isclockwise = true)
{
    zrotate(false);
    Erotat(!isclockwise);
    zrotate();
}

void Rubiks::Srotat(bool isclockwise = true)
{
    xrotate(false);
    Erotat(isclockwise);
    xrotate();
}

void Rubiks::printCube(void)
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

bool Rubiks::performMove(const string move)
{
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
            return false;
        }
    }

    // adding move to performed moves VECTOR
    // performedMoves.push_back(move);

    while (i < time)
    {
        switch (move[0])
        {
        case 'F':
            Frotat(isclockwise);
            break;
        case 'B':
            Brotat(isclockwise);
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
        case 'X':
            xrotate(isclockwise);
            break;
        case 'Y':
            yrotate(isclockwise);
            break;
        case 'Z':
            zrotate(isclockwise);
            break;
        default:
            break;
        }
        i++;
    }
    return true;
}

void Rubiks::executeMoves(string moves)
{
    if (moves == ""){
        return;
    }

    for (int i = 0; i < moves.length(); i++)
    {
        if (i+1 < moves.length() && (moves[i+1] == '\'' || moves[i+1] == '2'))
        {
            // move += moves[i];
            // move += moves[i+1];
            performMove(moves.substr(i, 2));
            // move = "";
            i++;
            continue;
        }
        performMove(moves.substr(i, 1));
    }
}

bool Rubiks::issolved(void)
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

void Rubiks::inputFromFile(std::string fname){
    std::ifstream fin;
    std::string line;
    int col=0,row=0;
    fin.open(fname);
    for (int side = 0; side < 6; side++)
    {
        getline(fin, line);
        col=0;row=0; // reset for next side
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != ' ')
            {
                cube[side][row][col] = line[i];
                cubecopy[side][row][col] = line[i];
                col++;
                if(col > 2){
                    col = 0;
                    row++;
                }
            }
            
        }
    }
    fin.close();
    return;
}

void Rubiks::outputToFile(std::string fname){
    std::ofstream fout;
    std::string line;
    int col=0,row=0;
    fout.open(fname);
    for (int side = 0; side < 6; side++)
    {
        col=0;row=0; // reset for next side
        line = "";
        for (int i = 0; i < 9; i++)
        {
            line += cube[side][row][col];
            line += ' ';
            col++;
            if(col > 2){
                col = 0;
                row++;
            }
        }
        line[line.length()-1] = '\n';
        fout << line;
    }
    fout.close();
    return;
}

// string * Rubiks::getSidesString(){
//     string sides[6];
//     for(int i=0; i<6; i++){
//         sides[i] = "";
//         for(int j=0;j<3;j++){
//             for(int k=0; k<3; k++){
//                 sides[i] += cube[i][j][k];
//             }
//         }
//     }
//     return sides;
// }

string Rubiks::getSideString(int side){
    char sides[] = {'U', 'L', 'F', 'B', 'R', 'D'};
    string s = "";
    for(int j=0;j<3;j++){
        for(int k=0; k<3; k++){
            s += cube[side][j][k];
        }
    }
    return s;
}
