

#include<bits/stdc++.h>
using namespace std;

class Player{
    public:
    string Name;
    int position;
    Player(string name):Name(name),position(0){}
};

class Ladder{
    public:
    int size;
    vector<int> board;
    set<Player *> st;

    Ladder(int size){
        this->size = size;
        for (int i = 0; i <= size;i++){
            board.push_back(i);
        }
    }

    void addLadderAndSnake(int start,int end,string type){
        if(type == "snake"){
            board[start] = end;
        }else{
            board[start] = end;
        }

    }

    void addPlayer(Player* p){
        st.insert(p);
    }

    int forword(Player* p,int move){

        if(st.find(p) == st.end()){
            cout << "Player " << p->Name << "not exist\n";
            return 0;
        }

        if(p->position + move > 100){
            return 0;
        }
        //forwrd the player with move
        p->position = p->position + move;
        p->position = board[p->position];

        if(p->position == 100){
            cout << p->Name << " won the first Position\n";
            return 1;
        }

        return 0;
    }

    void showLadder(){
        cout << "________________________________________________________________\n";
        for (int i = 1; i <= size;i++){
            bool found = false;
            string name;
            for(auto player :st){
                if(player->position == i){
                    // cout << " "<<player->Name[0]<<" ";
                    name = player->Name[0];
                    found = true;
                }

            }
            if(found)
                cout <<name<<"\t";
            else{
                cout << board[i] << "\t";
            }
            if(i%10==0)
                cout << endl;
        }
        cout << "________________________________________________________________\n";

    }


};

int main(){

    Ladder *L = new Ladder(100);

    L->addLadderAndSnake(1, 7, "lad");
    L->addLadderAndSnake(14, 67, "lad");
    L->addLadderAndSnake(51, 75, "lad");
    L->addLadderAndSnake(19, 97, "lad");
    L->addLadderAndSnake(33, 88, "lad");
    L->addLadderAndSnake(30, 8, "snake");
    L->addLadderAndSnake(64, 23, "snake");
    L->addLadderAndSnake(83, 9, "snake");
    L->addLadderAndSnake(99, 2, "snake");

    Player *p1 = new Player("Xhubham");
    Player *p2 = new Player("Zatyam");
    // Player *p3 = new Player("ashis");
    // Player *p4 = new Player("mayank");

    L->addPlayer(p1);
    L->addPlayer(p2);

    L->showLadder();

    while(1){
        bool start = true;
        for (int i = 1; i <= 2; i++)
        {
            if(!start)break;
            srand(static_cast<unsigned>(time(0)));

            // Define the range
            int lower = 1;
            int upper = 6;

            // Generate a random number in the range [lower, upper]
            int move = lower + rand() % (upper - lower + 1);
            if( i%2 == 0 && L->forword(p1,move)){
                start = false;
            }else if(i%2 != 0 && L->forword(p2,move)){
                start = false;
            }
        }
        L->showLadder();
        if(!start){
            cout << "Game End \n";
            break;
        }
    }

    L->showLadder();
}