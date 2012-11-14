/* Created by Taylor Daw
 * Feb 19, 2012
 *
 *
 * This is the machine problem 1 assignment and I will be completing this using A* search. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <time.h>
#include <ctime>
#include <sys/time.h>

using namespace std;
using std::string;

struct node {
    int *board;//keeps locations on the board
    int blank;//empty space in board
    int traveled;//g
    int total;//f
    int cost;//h
};

struct timeval timer;
double curtime;
int i = 0, j, k = 0, rowsize, empty;
bool test;
struct node start, goal, tempnode;
node current;
string temp;
bool pushopen = true;
int nindex;
int lowscore, lowindex;
vector<char> ans;
vector<int> input;
vector<node> openlist;
vector<node> closedlist;

void copier(struct node *first, struct node *second) {
    for(i = 0; i < rowsize * rowsize; i++)
        second->board[i] = first->board[i];
    second->blank = first->blank;
    second->total = second->total;
    second->traveled = first-> traveled;
    second->cost = first->cost;
}


//gets manhattan distance
int manhattan(int a, int b) {
    int disa, disb = 0;
    disa = abs(a + 1 - b);
    while ((disa < rowsize) > 0) 
    {
        disa -= rowsize;
        disb++;
    }
    while ((disa - 1) > 0) 
    {
        disa -= rowsize;
        disb++;
    }
    return disb;
}
    //maps the score by adding together the manhattan of each square on board

int findscore(struct node *n) {
    int total = 0;

    for (int i = 0; i < rowsize * rowsize; i++) {

        total += manhattan(i, n->board[i]);

    }
    return total;

}

bool up() {
    if (tempnode.blank < rowsize)
        return false;

    int temp;
    temp = tempnode.board[tempnode.blank - rowsize];
    tempnode.board[tempnode.blank] = temp;
    tempnode.board[tempnode.blank - rowsize] = 0;

    tempnode.blank -= rowsize;

    tempnode.cost = findscore(&tempnode); //h
    tempnode.traveled += 1; //g
    tempnode.total = tempnode.traveled + tempnode.cost; //f
    //printf("returned true \n");
    return true;
}

bool down() {
    if (tempnode.blank >= (rowsize * (rowsize - 1)))
        return false;

    int temp;
    temp = tempnode.board[tempnode.blank + rowsize];
    tempnode.board[tempnode.blank] = temp;
    tempnode.board[tempnode.blank + rowsize] = 0;

    tempnode.blank += rowsize;

    tempnode.cost = findscore(&tempnode);
    tempnode.traveled += 1;
    tempnode.total = tempnode.traveled + tempnode.cost;

    return true;
}

bool left() {
    if ((tempnode.blank % rowsize) == 0)
        return false;

    int temp;
    temp = tempnode.board[tempnode.blank - 1];
    tempnode.board[tempnode.blank] = temp;
    tempnode.board[tempnode.blank - 1] = 0;

    tempnode.blank -= 1;

    tempnode.cost = findscore(&tempnode);
    tempnode.traveled += 1;
    tempnode.total = tempnode.traveled + tempnode.cost;

    return true;
}

bool right() {
    if ((tempnode.blank % rowsize) == (rowsize - 1))
        return false;

    int temp;
    temp = tempnode.board[tempnode.blank + 1];
    tempnode.board[tempnode.blank] = temp;
    tempnode.board[tempnode.blank + 1] = 0;

    tempnode.blank += 1;

    tempnode.cost = findscore(&tempnode);
    tempnode.traveled += 1;
    tempnode.total = tempnode.traveled + tempnode.cost;

    return true;
}

/*void doStuff() {
    bool goahead = true;
    for (i = 0; i < closed.size(); i++) {
        for (int z = 0; z < size * size; z++) {
            printf("temp board: %d \n closed.board: %d \n", tempnode.board[z], closed[i].board[z]);
            if (!(tempnode.board[z] == closed[i].board[z]))
                goahead = false;
        }
    }
    //if (compare(&tempnode, &(closed[i])) == true)
    //    goahead = false;

    if (!goahead) {
        for (i = 0; i < open.size(); i++) {
            for (int z = 0; z < size * size; z++) {
                if (!(tempnode.board[z] == open[i].board[z])) {
                    nindex = z;
                    pushopen = false;
                }
            }
            /*if (compare(&tempnode, &(open[i]))) {
                pushopen = false;
                nindex = i;
            }*/
       /* }
        if (!pushopen)//push into open
        {
            printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
            open.push_back(tempnode);
        }
        if (pushopen)//there is a match, check which is cheaper
            if (tempnode.traveled < open[nindex].traveled) {
                open.erase(open.begin() + nindex);
                open.push_back(tempnode);
            }
    }
}*/

int main(int argc, char** argv) {
    
    int readin = 0;
    bool row = true;
    //read input into vector
    while(cin)
    {
        
        cin >> temp;
        /*if(((temp == "\n") || (temp == "\0")) && (row = true))
        {
            rowsize = input.size();
            row = false;
        }*/
        if ((temp == "X") || (temp == "x"))
        {
            input.push_back(0);
            readin++;
        }
        
        else
        {
            input.push_back(atoi(temp.c_str()));
            readin++;
        }
        
        //if(readin == (rowsize * rowsize))
            //break;
    }
    
    //rowsize is going to be important for shifting the blank space effectively.
    rowsize = sqrt(input.size());
    //initialize start and goal state.
        start.cost = 0;
    start.blank = 0;
    start.total = 0;
    start.traveled = 0;
    start.board = new int[rowsize * rowsize];
    goal.cost = 0;
    goal.blank = 0;
    goal.total = 0;
    goal.traveled = 0;
    goal.board = new int[rowsize * rowsize];

    //initialize start state
    for (i = 0; i < rowsize * rowsize; i++) {

        if (input[k] == 0)
            start.blank = i;

        start.board[i] = input[k];
        k++;
    }

    //initialize goal state
    for (i = 0; i < rowsize * rowsize; i++)
        goal.board[i] = i + 1;
    goal.board[rowsize * rowsize - 1] = 0;
    goal.cost = 0;
    goal.blank = rowsize * rowsize - 1;

    start.cost = findscore(&start);
    start.traveled = 0;
    
    current.board = new int[rowsize * rowsize];
    tempnode.board = new int[rowsize * rowsize];

    openlist.push_back(start);


        gettimeofday(&timer, NULL);
    curtime = timer.tv_sec ;
    //A* 
    while (timer.tv_sec - curtime < 1800) {
        //node current;
        node temp;
        temp.board = new int[rowsize* rowsize];
        //temp.cost = 0;
        //temp.empty = 0;
        //temp.total = 0;
        //temp.traveled = 0;
        node temp2;
        temp2.board = new int[rowsize * rowsize];
        //temp2.cost = 0;
        //temp2.empty = 0;
        //temp2.total = 0;
        //temp2.traveled = 0;
        node temp3;
        temp3.board = new int[rowsize * rowsize];
        //temp3.cost = 0;
        //temp3.empty = 0;
        //temp3.traveled = 0;
        //temp3.total = 0;
        node temp4;
        temp4.board = new int[rowsize * rowsize];
        //temp4.cost = 0;
        //temp4.empty =0;
        //temp4.total = 0;
        //temp4.traveled = 0;
        if (openlist.size() == 0) {
            printf( "can't solve problem, open list is empty ");
            exit(1);
        }
        node comp;
        lowscore = openlist[0].total;
        //cout << "working here \n";
        //find lowest score

        for (i = 0; i < openlist.size(); i++) 
        {
            //copy(&(open[i]), &comp);
            if (openlist[i].total < lowscore) {
                lowindex = i;
                lowscore = openlist[i].total;
            }
        }
        //printf("lowscore: %d \n", lowscore);

        copier(&(openlist[lowindex]), &current);
        bool path = true;
        for (i = 0; i < rowsize * rowsize; i++) {
            //printf("current board: %d \n goal.board: %d \n", current.board[i], goal.board[i]);
            if (!(current.board[i] == goal.board[i]))
                path = false;
        }
        if (path) {
            printf( "found path");
            exit(1);
        }

        closedlist.push_back(current);
        openlist.erase(openlist.begin() + lowindex);
        copier(&current, &tempnode);
        copier(&tempnode, &temp);
        if (up()) 
        {
            printf("u \n");
            bool goahead = true;
            for (i = 0; i < closedlist.size(); i++) {
                for (int z = 0; z < rowsize * rowsize; z++) {
                    //printf("temp board: %d \n closed.board: %d \n", tempnode.board[z], closed[i].board[z]);
                    if (!(tempnode.board[z] == closedlist[i].board[z]))
                        goahead = false;
                }
            }
            if (!goahead) {
                for (i = 0; i < openlist.size(); i++) {
                    for (int z = 0; z < rowsize * rowsize; z++) {
                        if (!(tempnode.board[z] == openlist[i].board[z])) {
                            nindex = z;
                            pushopen = false;
                        }
                    }
                }
                if (!pushopen)//push into open
                {
                    //printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
                    openlist.push_back(temp);
                }
                else if((pushopen) && (openlist.size() == 0))
                {
                    //printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
                    openlist.push_back(temp);
                }
                else if ((pushopen) && (openlist.size() > 0))//there is a match, check which is cheaper
                    if (tempnode.traveled <= openlist[nindex].traveled) {
                        openlist.erase(openlist.begin() + nindex);
                        openlist.push_back(temp);
                    }
            }
        }
        //MOVE DOWN
        copier(&current, &tempnode);
        copier(&tempnode, &temp2);
        if (down()) 
        {
            copier(&tempnode, &temp2);

            printf("d \n");
            bool goahead = true;
            for (i = 0; i < closedlist.size(); i++) {
                for (int z = 0; z < rowsize * rowsize; z++) {
                    //printf("temp board: %d \n closed.board: %d \n", tempnode.board[z], closed[i].board[z]);
                    if (!(tempnode.board[z] == closedlist[i].board[z]))
                        goahead = false;
                }
            }
            if (!goahead) {
                for (i = 0; i < openlist.size(); i++) {
                    for (int z = 0; z < rowsize * rowsize; z++) {
                        if (!(tempnode.board[z] == openlist[i].board[z])) {
                            nindex = z;
                            pushopen = false;
                        }
                    }
                }
                if (!pushopen)//push into open
                {
                    //printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
                    openlist.push_back(temp2);
                }
                else if((pushopen) && (openlist.size() == 0))
                {
                    //printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
                    openlist.push_back(temp2);
                }
                else if ((pushopen) && (openlist.size() > 0))//there is a match, check which is cheaper
                    if (tempnode.traveled <= openlist[nindex].traveled) {
                        openlist.erase(openlist.begin() + nindex);
                        openlist.push_back(temp2);
                    }
            }
        
        }
        //MOVE RIGHT
        copier(&current, &tempnode);
        copier(&tempnode, &temp3);
        if (right())        
        {
            printf("r \n");
            bool goahead = true;
            for (i = 0; i < closedlist.size(); i++) {
                for (int z = 0; z < rowsize * rowsize; z++) {
                    //printf("temp board: %d \n closed.board: %d \n", tempnode.board[z], closed[i].board[z]);
                    if (!(tempnode.board[z] == closedlist[i].board[z]))
                        goahead = false;
                }
            }
            if (!goahead) {
                for (i = 0; i < openlist.size(); i++) {
                    for (int z = 0; z < rowsize * rowsize; z++) {
                        if (!(tempnode.board[z] == openlist[i].board[z])) {
                            nindex = z;
                            pushopen = false;
                        }
                    }
                }
                if (!pushopen)//push into open
                {
                    //printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
                    openlist.push_back(temp3);
                }
                else if((pushopen) && (openlist.size() == 0))
                {
                    //printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
                    openlist.push_back(temp3);
                }
                else if ((pushopen) && (openlist.size() > 0))//there is a match, check which is cheaper
                    if (tempnode.traveled <= openlist[nindex].traveled) {
                        openlist.erase(openlist.begin() + nindex);
                        openlist.push_back(temp3);
                    }
            }
        }
        //MOVE LEFT
        copier(&current, &tempnode);
        copier(&tempnode, &temp4);
        if (left())         
        {
            //copy(&tempnode, &temp4);
            printf("l \n");
            bool goahead = true;
            for (i = 0; i < closedlist.size(); i++) {
                for (int z = 0; z < rowsize * rowsize; z++) {
                    //printf("temp board: %d \n closed.board: %d \n", tempnode.board[z], closed[i].board[z]);
                    if (!(tempnode.board[z] == closedlist[i].board[z]))
                        goahead = false;
                }
            }
            if (!goahead) {
                for (i = 0; i < openlist.size(); i++) {
                    for (int z = 0; z < rowsize * rowsize; z++) {
                        if (!(tempnode.board[z] == openlist[i].board[z])) {
                            nindex = z;
                            pushopen = false;
                        }
                    }
                }
                if (!pushopen)//push into open
                {
                    //printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
                    openlist.push_back(temp4);
                }
                else if((pushopen) && (openlist.size() == 0))
                {
                    //printf("tempnode: %d %d %d %d \n", tempnode.cost, tempnode.empty, tempnode.total, tempnode.traveled);
                    openlist.push_back(temp4);
                }
                else if ((pushopen) && (openlist.size() > 0))//there is a match, check which is cheaper
                    if (tempnode.traveled <= openlist[nindex].traveled) {
                        openlist.erase(openlist.begin() + nindex);
                        openlist.push_back(temp4);
                    }
            }
        }

    gettimeofday(&timer, NULL);
    }
}