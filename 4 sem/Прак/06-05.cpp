#include <iostream>
#include <map>
#include <vector>

class D
{
public:
    int x, y, z;
    D() {}
    D(int a, int b, int c) : x{a}, y{b}, z{c} {}

    D & operator+= (D a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    friend bool operator< (D a, D b) {
        if (a.x < b.x || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z < b.z))
            return true;
        else 
            return false;
    }
    friend bool operator> (D a, D b) {
        if (a.x > b.x || (a.x == b.x && a.y > b.y) || (a.x == b.x && a.y == b.y && a.z > b.z))
            return true;
        else 
            return false;
    }

    friend D operator+ (D a, D b);
};

D operator+ (D a, D b) {
    a += b;
    return a;
}

D check1 (char & step, char & side, std::map <char, D> & dir) {
    char out;
    if (side == 'F') {
        out = 'B';
    } else if (side == 'B') {
        out = 'F';
    } else if (side == 'L') {
        out = 'R';
    } else if (side == 'R') {
        out = 'L';
    }
    side = step;
    step = out;
    return dir[step];
}

D check2 (char & step, char & side, std::map <char, D> & dir) {
    char out;
    if (side == 'F') {
        out = 'B';
    } else if (side == 'B') {
        out = 'F';
    } else if (side == 'U') {
        out = 'D';
    } else if (side == 'D') {
        out = 'U';
    }
    side = step;
    step = out;
    return dir[step];
}

D check3 (char & step, char & side, std::map <char, D> & dir) {
    char out;
    if (side == 'L') {
        out = 'R';
    } else if (side == 'R') {
        out = 'L';
    } else if (side == 'U') {
        out = 'D';
    } else if (side == 'D') {
        out = 'U';
    }
    side = step;
    step = out;
    return dir[step];
}

void checkL (char & st, char si) {
    if ((st == 'U' && si == 'F') || (st == 'B' && si == 'U')
            || (st == 'D' && si == 'B') || (st == 'F' && si == 'D')) {
        st = 'L';
    } else if ((st == 'R' && si == 'F') || (st == 'B' && si == 'R')
            || (st == 'L' && si == 'B') || (st == 'F' && si == 'L')) {
        st = 'U';
    } else if ((st == 'D' && si == 'F') || (st == 'F' && si == 'U')
            || (st == 'U' && si == 'B') || (st == 'B' && si == 'D')) {
        st = 'R';
    } else if ((st == 'L' && si == 'F') || (st == 'B' && si == 'L')
            || (st == 'R' && si == 'B') || (st == 'F' && si == 'R')) {
        st = 'D';
    } else if ((st == 'U' && si == 'R') || (st == 'L' && si == 'U')
            || (st == 'D' && si == 'L') || (st == 'R' && si == 'D')) {
        st = 'F';
    } else if ((st == 'U' && si == 'L') || (st == 'L' && si == 'D')
            || (st == 'D' && si == 'B') || (st == 'R' && si == 'U')) {
        st = 'B';
    }
}

void checkR (char & st, char si) {
    if ((st == 'U' && si == 'B') || (st == 'B' && si == 'D')
            || (st == 'D' && si == 'F') || (st == 'F' && si == 'U')) {
        st = 'L';
    } else if ((st == 'L' && si == 'F') || (st == 'F' && si == 'R')
            || (st == 'R' && si == 'B') || (st == 'B' && si == 'L')) {
        st = 'U';
    } else if ((st == 'U' && si == 'F') || (st == 'B' && si == 'U')
            || (st == 'D' && si == 'B') || (st == 'F' && si == 'D')) {
        st = 'R';
    } else if ((st == 'R' && si == 'F') || (st == 'F' && si == 'L')
            || (st == 'L' && si == 'B') || (st == 'B' && si == 'R')) {
        st = 'D';
    } else if ((st == 'U' && si == 'R') || (st == 'L' && si == 'U')
            || (st == 'D' && si == 'L') || (st == 'R' && si == 'D')) {
        st = 'B';
    } else if ((st == 'U' && si == 'L') || (st == 'L' && si == 'D')
            || (st == 'D' && si == 'B') || (st == 'R' && si == 'U')) {
        st = 'F';
    }
}

int main()
{
    std::map <char, D> dir;
    std::map <D, int> cube = {};
    
    char side = 'F';

    D r = {1, 1, 0};
    dir['U'] = {-1, 0, 0};
    dir['D'] = {1, 0, 0};
    dir['L'] = {0, -1, 0};
    dir['R'] = {0, 1, 0};
    dir['F'] = {0, 0, -1};
    dir['B'] = {0, 0, 1};

    cube[r] = 1;
    char in, step = 'U';
    D way = dir['U'];
    while (std::cin >> in) {
        if (in == 'S') {
            break;
        }
        if (in == 'F') {
            if ((step == 'U' && r.x == 0) || (step == 'D' && r.x == 2)) {
                way = check1(step, side, dir);
            } else if ((step == 'L' && r.y == 0) || (step == 'R' && r.y == 2)) {
                way = check2(step, side, dir);
            } else if ((step == 'F' && r.z == 0) || (step == 'B' && r.z == 2)) {
                way = check3(step, side, dir);
            } else {
                r += way;
            }
        } else if (in == 'L') {
            checkL(step, side);
            way = dir[step];
        } else if (in == 'R') {
            checkR(step, side);
            way = dir[step];
        }
        cube[r] = 1;
    }
    int cnt = 0;
    for (auto & i : cube) {
        cnt += i.second;
    }
    std::cout << cnt << std::endl;
}