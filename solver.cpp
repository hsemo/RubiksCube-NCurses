#include "solver.h"
#include "rubiks.h"
#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>
// #include <mutex>
// #include <condition_variable>

using namespace std;
using std::cout;
// using std::endl;
// using std::printf;
// using std::string;
// using std::vector;
// using std::thread;
// using std::unique_lock;
// using std::mutex;

solver::solver(rubiks &tmpcube)
{
    tmpcube.copy(solverCube, false);
    solutionFound = false;
    allClear = false;
}

// void solver::setMvIndxs(void)
// {
//     // cout << "'setMvIndxs(void)' func is called\n";
//     vector<int> mvindxsCopy(mvindxs);
//     static int depth;
//     int prevDepth = depth;
//     mvindxsCopy.reserve(mvindxs.size());
//     // cout << "entering in loop of setMvIndxs func.\n";
//     for (int i = 0; i < length; i++)
//     {
//         // cout << "i: " << i << endl;
//         if (mvindxsCopy[i] < 27){
//             // cout << "in if condition.\n";
//             mvindxsCopy[i] += 1;
//             // if (mvindxsCopy[i] == mvindxsCopy[i+1]){
//             //     mvindxsCopy[i] += 1;
//             //     if (mvindxsCopy[i] == 28){
//             //         mvindxsCopy[i] = 27;
//             //         i--;
//             //         continue;
//             //     }
//             // }
//             if (i > depth){
//                 depth = i + 1;
//             }
//             // cout << "loop breaked!\n";
//             break;
//             // return;
//         }else if(mvindxsCopy[i] == 27){
//             // cout << "in else condition.\n";
//             mvindxsCopy[i] = 1;
//             // if (mvindxsCopy[i+1] == 0){
//             //     mvindxsCopy[i] = 2;
//             // }
//             // if (mvindxsCopy[i-1] == 1){
//             //     mvindxsCopy[i-1] = 2;
//             // }
//         }
//     }

//     if (depth != prevDepth){
//         // cout << "depth != prevDepth: true\n";
//         for (int i = depth-2; i >= 0; i--)
//         {
//             mvindxsCopy[i] = 2;
//             i--;
//             mvindxsCopy[i] = 1;
//         }
//     }
//     // cout << "\nreturning from setMvIndxs func.\n";
//     // cout << "\r";
//     // for (int z = 3; z >= 0; z--)
//     // {
//     //     printf("%d  ",mvindxs[z]);
//     // }
//     // cout << endl;
//     mvindxs = mvindxsCopy;
//     return;
//     // cout << "The cube is solved, string of moves is: \n\t" << mvs << endl;
// }

// void solver::analyseNprnt(void)
// {
//     int sz = solvedMoves.size();
//     int minLen = 1000, indx = 0;
//     cout << "All strings of Moves that can be solve the initial cube is: \n";
//     for (int j = 0; j < sz; j++)
//     {
//         printf("\t%d: %s", j + 1, solvedMoves[j]);
//         if (solvedMoves[j].size() < minLen)
//         {
//             minLen = solvedMoves.size();
//             indx = j;
//         }
//     }
//     cout << "\n\nThe shortest string of moves that can solve the cube is: \n";
//     cout << "\t\t" << solvedMoves[indx] << endl;
// }

// string solver::generateMovesStrng(void){
//     bool zeroFound = false;
//     string mvs = "";
//     // cout << "entering in the loop of generateMovesStrng func\n";
//     setMvIndxs();
//     vector<int> mvindxsCopy(mvindxs);
//     mvindxsCopy.push_back(0);
//     for (int i = 0; i < length;)
//     {
//         // cout << "'generateMovesStrng' of i: " << i << endl;
//         if (zeroFound){
//             i--;
//             mvs += totalValidMoves[mvindxsCopy[i]-1];
//             mvs += " ";
//             if (i == 0){
//                 // mvStrngs.push(mvs);
//                 // cout << "string generated: " << mvs << endl;
//                 // mvs.clear();
//                 // zeroFound = false;
//                 // break;
//                 return mvs;
//             }
//             continue;
//         }
//         if (mvindxsCopy[i] == 0){
//             zeroFound = true;
//             continue;
//         }
//         i++;
//     }
//     // cout << "\nreturning from 'generateMovesStrng' func.\n";
//     return mvs;
// }

void solver::tester(int strtFrom, int endTo)
{
    while(!allClear){
        Sleep(1000);
    }
    // cout << "tester thread is started...\n";
    string moves;
    rubiks myCube(solverCube);

    vector<int> mvindxsCopy(mvindxs);
    mvindxsCopy.reserve(mvindxs.size());
    mvindxsCopy[0] = strtFrom;

    static int depth;
    int i = 0;

    // generator func variables
    bool zeroFound = false;
    string mvs;

    while (!solutionFound)
    {
        // cout << "inside tester, while loop ran times: " << i << endl;

        // ################ setMyIndxs begins #################

        if (mvindxsCopy[0] < endTo){
            mvindxsCopy[0] += 1;
        }else if(mvindxsCopy[0] == endTo){
            mvindxsCopy[0] = strtFrom + 1;
            for (i = 1; i < length; i++)
            {
                if (mvindxsCopy[i] < 27){
                    mvindxsCopy[i] += 1;
                    break;
                }else if(mvindxsCopy[i] == 27){
                    mvindxsCopy[i] = 1;
                }
            }
            if (i > depth){depth = i;}
        }
        // ################ setMyIndxs ends #################

        // ################ generator begins #################
        mvindxsCopy.push_back(0);
        for (int i = 0; i < length;)
        {
            // cout << "'generateMovesStrng' of i: " << i << endl;
            if (zeroFound){
                i--;
                mvs += totalValidMoves[mvindxsCopy[i]-1];
                mvs += " ";
                if (i == 0){
                    moves.clear();
                    moves = mvs;
                    mvs.clear();
                    zeroFound = false;
                    break;
                }
                continue;
            }
            if (mvindxsCopy[i] == 0){
                zeroFound = true;
                continue;
            }
            i++;
        }
        mvindxs.pop_back();
        // ################ generator ends #################

        // cout << "\rgenerated moves string is: " + moves << "  que size: " << mvStrngs.size();
        // if (prntStrngs.size() < 100){
        // prntStrngs.push_back("\rgenerated moves string is: " + moves + "                                                                   ");
        // }
        // cout << "\rgenerated moves string is: " + moves + "                                                                   ";
        // cout << "executing moves\n";
        myCube.executeMoves(moves);
        if (solutionFound){
            // cout << "solution found returning...\n";
            return;
        }
        if (myCube.issolved()){
            solutionFound = true;
            cout << "\n(solve func) the cube is solved, Moves are: " << moves << endl;
            prom.set_value(moves);
            return;
        }
        // moves.assign(moves.length(), ' ');
        // cout << "\r                                                                                                   ";
        // cout << "making copy of solverCube inside myCube...\n";
        myCube.copy(solverCube, true);
        // cout << "\rdepth is: " << depth << "   ";
        // i++;
    }
}

// void solver::prntr(void){
//     // unique_lock<mutex> lck(mu);
//     // cout << "printer waiting...\n";
//     // while(!allClear){prntf.wait(lck);}
//     // cout << "printer waiting is over.\n";
//     string prnt;
//     while (!solutionFound)
//     {
//         if (!allClear){
//             continue;
//         }
//         if (!prntStrngs.empty()){
//             prnt = prntStrngs.front();
//             prntStrngs.pop_back();
//             cout << prnt;
//         }
//     }
// }

void solver::solve(int len, int thrds=2){
    string shortestSol;
    length = len;
    mvindxs.reserve(length);
    mvindxs.assign(length, 0);

    fu = prom.get_future();

    if (thrds != 2){
        cout << "\n\nTotal number of threads to be launched: " << thrds << endl;
    }else{cout << "\n\nTotal number of threads to be launched(default): " << thrds << endl;}

    int i=0, add;
    add = (int)(27/thrds);
    for (i = 0; i < add*(thrds-1); i += add)
    {
        testerThreads.push_back(thread(&tester, this, i, i+add));
    }
    if (testerThreads.size() < thrds){
    testerThreads.push_back(thread(&tester, this, i, 27));
    }
    // cout << thrds << " tester threads created.\n";

    for (i = 0; i < thrds; i++)
    {
        testerThreads[i].detach();
    }
    // cout << "all tester threads detached.\n";

    cout << "Finding Shortest Solution...\n";
    allClear = true;
    // gnrtr.notify_all();
    // tstrs.notify_all();
    // prntf.notify_all();
    // cout << "notification sent to all threads.\n";
    // string prnt;
    // while (!solutionFound)
    // {
    //     if (!prntStrngs.empty()){
    //         prnt = prntStrngs.back();
    //         prntStrngs.pop_front();
    //         cout << prnt << "  prntQue len: " << prntStrngs.size();
    //     }
    // }
    // cout << "waiting for solution...\n";
    shortestSol = fu.get();
    cout << "(main func) solution found, Moves are: " + shortestSol << endl;
    
    // prntThread.join();
    // cout << "prnt thread joined.\n";
}
