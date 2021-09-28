#include <iostream>
#include "matrix.h"
int main() {

    Matrix<int> m = {{1 , 2} , {3 , 4}};

    std::cout << m << std::endl;

    std::cout << !m << std::endl;

    std::cout << m - m << std::endl;

    // And many great things !

    return 0;
}
