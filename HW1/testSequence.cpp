#include <iostream>
#include <cassert>
#include "Sequence.h"

int main()
{
    //TESTING FOR SUCCESS
    Sequence test;
    assert(test.empty());
    assert(test.size() == 0);
    test.insert(1);
    assert(!test.empty());
    assert(test.size() == 1);
    test.insert(3);
    test.insert(5);
    test.insert(9);
    test.insert(3, 7);
    assert(test.size() == 5);
    test.dump(); // 1,3,5,7,9
    
    Sequence copy = test; // 1,3,5,7,9
    copy.dump();
    
    test.insert(2, 4);
    test.insert(6);
    assert(test.size() == 7);
    test.dump(); // 1,3,4,5,6,7,9
    
    assert(test.erase(2) && test.size() == 6);
    assert(test.insert(2) == 1);
    test.insert(test.size(), 10);
    assert(test.insert(6, 7) && test.insert(3, 7) && test.size() == 10);
    test.dump(); // 1,2,3,7,5,6,7,7,9,10
    assert(test.remove(7) == 3 && test.size() == 7);
    test.dump(); // 1,2,3,5,6,9,10
    
    ItemType num;
    assert(test.get(3, num) && num == 5);
    assert(test.set(3, 4) && test.set(4, 5));
    test.remove(9);
    test.remove(10);
    test.dump(); // 1,2,3,4,5
    
    test.insert(test.size(), 1);
    test.insert(3);
    assert(test.find(1) == 0);
    assert(test.find(3) == 2);
    test.erase(2);
    test.erase(5);
    test.dump(); // 1,2,3,4,5
    
    Sequence swapTest;
    swapTest.insert(6);
    swapTest.insert(7);
    swapTest.insert(9);
    swapTest.insert(8);
    swapTest.insert(4, 10);
    swapTest.insert(5, 11);
    swapTest.dump(); // 6,7,8,9,10,11
    
    std::cerr << std::endl << "***SWAP***" << std::endl;
    
    swapTest.swap(test);
    assert(test.size() == 6 && swapTest.size() == 5);
    swapTest.dump(); // 1,2,3,4,5
    test.dump(); // 6,7,8,9,10,11
    
    
    //TESTING FOR ERROR CASES
    Sequence bad;
    assert(!bad.insert(1, 718450));
    bad.insert(14);
    bad.insert(17);
    bad.insert(16);
    bad.insert(15);
    assert(!bad.insert(-50, 781354) && !bad.insert(5, 978543) && !bad.insert(200, 958034));
    assert(bad.insert(13) == 0);
    bad.dump(); // 13,14,15,16,17
    
    assert(!bad.erase(-1) && !bad.erase(5));
    assert(bad.remove(34567) == 0);
    assert(!bad.get(-1, num) && !bad.get(5, num));
    assert(!bad.set(-10, num) && !bad.set(50, num));
    assert(bad.find(num) == -1);
 
    std::cerr << "All tests passed!" << std::endl;
}
