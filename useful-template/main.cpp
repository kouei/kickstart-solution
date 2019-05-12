#include"useful_template.h"
using namespace std;

int main() {

    auto grid = _vector2d(0, -1, 0);
    for(auto & row : grid) _print(row, ", ");
    return 0;
}