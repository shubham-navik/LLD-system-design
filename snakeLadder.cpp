#include <bits/stdc++.h>
using namespace std;

class Player {
public:
    string Name;
    int position;
    Player(string name) : Name(name), position(0) {}
};

class Ladder {
public:
    int size;
    vector<int> board;
    set<Player *> st;

    Ladder(int size) {
        this->size = size;
        for (int i = 0; i <= size; i++) {
            board.push_back(i);
        }
    }

    void addLadderAndSnake(int start, int end, string type) {
        if (type == "snake") {
            board[start] = end;
        } else {
            board[start] = end;
        }
    }

    void addPlayer(Player *p) {
        st.insert(p);
    }

    int forward(Player *p, int move) {
        if (st.find(p) == st.end()) {
            cout << "Player " << p->Name << " does not exist\n";
            return 0;
        }

        if (p->position + move > 100) {
            return 0;
        }

        // Move the player
        p->position = p->position + move;
        p->position = board[p->position];

        if (p->position == 100) {
            cout << p->Name << " won the first Position\n";
            return 1;
        }

        return 0;
    }

    void showLadder() {
        cout << "________________________________________________________________\n";
        for (int i = 1; i <= size; i++) {
            bool found = false;
            string name;
            for (auto player : st) {
                if (player->position == i) {
                    name = player->Name;
                    found = true;
                }
            }
            if (found)
                cout << name << "\t";
            else {
                cout << board[i] << "\t";
            }
            if (i % 10 == 0)
                cout << endl;
        }
        cout << "________________________________________________________________\n";
    }
};

int main() {
    Ladder *L = new Ladder(100);

    // Add ladders and snakes
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
    Player *p3 = new Player("Matyam");

    L->addPlayer(p1);
    L->addPlayer(p2);

    L->showLadder();

    srand(static_cast<unsigned>(time(0))); // Seed the random number generator once outside the loop

    while (1) {
        bool start = true;
        for (int i = 1; i <= 2; i++) {
            if (!start) break;

            int lower = 1;
            int upper = 6;

            // Generate a random move
            int move = lower + rand() % (upper - lower + 1);
            cout << "Move: " << move << endl;

            if (i % 2 != 0 && L->forward(p1, move)) {  // Player 1 moves on odd turns
                start = false;
            } else if (i % 2 == 0 && L->forward(p2, move)) {  // Player 2 moves on even turns
                start = false;
            }
        }
        L->showLadder();
        if (!start) {
            cout << "Game End \n";
            break;
        }
    }

    L->showLadder();
}
