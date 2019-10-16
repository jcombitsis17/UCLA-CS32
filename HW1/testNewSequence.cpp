#include "newSequence.h"
#include <iostream>
#include <cassert>

int main()
{
    // TESTING FOR SUCCESS
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
    
    // *** NEW TESTS ***

    Sequence empty(0);
    assert(empty.insert(1) == -1 && !empty.insert(0, 12));
    
    Sequence a(10);     // a can hold at most 10 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c(20);         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 1000;
    
    // No failures inserting items up to max size
    for (int i = 1; i <= 5; i++)
        assert(b.insert(i) != -1); // b filled with 5 items (max)
    b.dump(); b.dump(); b.dump(); b.dump(); b.dump();
    for (int j = 1; j <= 10; j++)
        assert(a.insert(j) != -1); // a filled with 10 items (max)
    b.dump();

    // Failure if we try to insert an extra item
    assert(b.insert(v) == -1);
    assert(a.insert(v) == -1);

    // Test operator=
    c = a;
    assert(c.insert(v) == -1);
    
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    c.dump();   // 1,2,3,4,5,6,7,8,9,10
    b.dump();   // 1,2,3,4,5
    c.swap(b); std::cerr << "***SWAP***" << std::endl;
    assert(c.insert(v) == -1  &&  b.insert(v) == -1);
    c.dump();   // 1,2,3,4,5
    b.dump();   // 1,2,3,4,5,6,7,8,9,10

    std::cerr << "----------" << std::endl;
    Sequence d(1000);
    d.insert(12345);    d.insert(67890);    assert(a.remove(10) == 1);
    a.dump();   // 1,2,3,4,5,6,7,8,9
    d.dump();   // 12345,67890
    d.swap(a);
    d.insert(9, 100);   // now that we've swapped, d is FULL, and a isn't (lots of space via d max items)
    assert(d.insert(v) == -1 && a.insert(101) != -1);
    std::cerr << "***FINAL VALUES OF A AND D***" << std::endl;
    a.dump();   // 101,12345,67890
    d.dump();   // 1,2,3,4,5,6,7,8,9,100
    
    std::cerr << "All tests passed!" << std::endl;
}
