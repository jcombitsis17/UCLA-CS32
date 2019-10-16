#include "ScoreList.h"
#include <cassert>
#include <iostream>

int main()
{
    ScoreList test;
    assert(test.size() == 0);
    assert(test.minimum() == NO_SCORE && test.maximum() == NO_SCORE);
    assert(!test.remove(100));
    assert(!test.add(101) && !test.add(-1));
    test.add(95);
    assert(!test.remove(96));
    assert(test.size() == 1 && test.maximum() == 95 && test.minimum() == 95);
    test.remove(95);
    test.add(70);   test.add(90);   test.add(80);   test.add(90);   test.add(100);
    assert(test.size() == 5);
    assert(test.minimum() == 70 && test.maximum() == 100);
    test.remove(70);    test.remove(100);
    test.add(95);
    assert(test.minimum() == 80 && test.maximum() == 95);
    
    std::cerr << "All tests passed!" << std::endl;
}
