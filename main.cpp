#include <iostream>
#include <conio.h>
#include <random>
#include <vector>
#include <bits/stdc++.h>
#include <thread>
#include <queue>
#include "rubiks.h"
#include "solver.h"

using namespace std;

int main(int argc, char const *argv[])
{
    rubiks cube;
    time_t start, end;
	
	int num;
	if (argc > 1){
		for (int n = 0; n < 2; n++)
		{
			if (argv[1][n] == 0){
				break;
			}
			num = (num*10) + (argv[1][n] - 48);
		}
	}else{num = 2;}

    // for (int i = 0; i < 6; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         for (int k = 0; k < 3; k++)
    //         {
    //             printf("\rEnter [%d][%d] of face %c: ",j,k, cube.getval(i));
    //             cin >> cb[i][j][k];
    //         }
    //     }
    // }
    // cube.copy(cb, true);
    // system("cls");
    // cout << "Inputting cube from file...\n";
    cube.inputFromFile("name.txt");

    cout << "After Inputing your cube is: \n";
    cube.printCube();
	
	cout << "\nEnter any key to start: ";
	getchar();
	system("cls");

    // cout << "creating solver obj...\n";
    solver solver1(cube);
    time(&start);
    // cout << "start time captured.\n";
    // cout << "calling solve function...\n";
    solver1.solve(20, num);
    time(&end);
    // cout << "end time captured.\n";
    // cout << "analysing and printing...\n";
    // solver1.analyseNprnt();

    // cout << "Applying moves...\n";
    // cube.executeMoves("M E' M' E");

    // cout << "After rotation moves: \n";
    // cube.printCube();

    // cout << "Checking cube is solved or not...\n";
    // if (cube.issolved())
    // {
    //     cout << "Congratulations cube is solved.\n";
    // }
    // else
    // {
    //     cout << "Sorry but the cube isn't solved yet!!\n";
    // }
    cout << "\nstart time of the programm by time function: " << start << setprecision(5) << endl;
    cout << "end time of the programm by time function: " << end << setprecision(5) << endl;
    double time_taken = double(end - start);
    cout << "total time taken by the programm is: " << time_taken << setprecision(5);
    return 0;
}