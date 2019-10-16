/*#include <string>
using namespace std;
    // delete ^^

bool somePredicate(string s)
{
    return s.empty();
}*/
    // delete ^^



// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if (n <= 0)
        return true;
    if (!somePredicate(a[0]))
        return false;
    return allTrue(a + 1, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    if (n <= 0)
        return 0;
    
    if (n == 1)
    {
        if (!somePredicate(a[0]))
            return 1;
        else
            return 0;
    }
    if (!somePredicate(a[0]))
        return 1 + countFalse(a + 1, n - 1);
    else
        return countFalse(a + 1, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    if (n <= 0)
        return -1;
    if (!somePredicate(a[0]))
        return 0;
    else
    {
        if (firstFalse(a + 1, n - 1) == -1)
            return -1;
        return 1 + firstFalse(a + 1, n - 1);
    }
}

// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int indexOfLeast(const string a[], int n)
{
    if (n <= 0)
        return -1;
    int index = 1 + indexOfLeast(a + 1, n - 1);
    if (a[0] <= a[index])
        return 0;
    else
        return index;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1)
        return false;
    if (n1 == 0 || n2 == 0)
        return true;
    
    if (a1[0] == a2[0])
        return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    else
        return includes(a1 + 1, n1 - 1, a2, n2);
}


// ------------- vvv DELETE vvv --------------

/*#include <cassert>
#include <iostream>
int main()
{
    // test allTrue()
    string arr[10] = {"", "", "", "", "", "", "", "", "", ""};
    assert(allTrue(arr, 10));
    arr[7] = "Hi";
    assert(allTrue(arr, 7));
    assert(!allTrue(arr, 10));
    arr[0] = "Hello";
    assert(!allTrue(arr, 10) && !allTrue(arr, 1));
    
    // test countFalse()
    assert(countFalse(arr, 10) == 2);
    assert(countFalse(arr + 1, 5) == 0);
    arr[8] = "AH"; arr[9] = "AHH";
    assert(countFalse(arr, 10) == 4);
    
    // test firstFalse()
    assert(firstFalse(arr, 10) == 0);
    assert(firstFalse(arr + 1, 8) == 6);
    arr[0] = "";
    assert(firstFalse(arr, 10) == 7);
    assert(firstFalse(arr, 4) == -1 && firstFalse(arr, 7) == -1);
    
    // test indexOfLeast()
    assert(indexOfLeast(arr, 10) == 0);
    arr[0] = "Hello";
    assert(indexOfLeast(arr, 10) == 1);
    string arr2[5] = {"cat", "dog", "aardvark", "elephant", "matt"};
    assert(indexOfLeast(arr2, 5) == 2);
    arr2[0] = arr2[2];
    assert(indexOfLeast(arr2, 5) == 0);
    assert(indexOfLeast(arr, 0) == -1);
    
    // test includes()
    string a1[7] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
    string a2[3] = {"kyle", "kenny", "butters"};
    string a3[3] = {"kyle", "cartman", "cartman"};
    string a4[3] = {"kyle", "butters", "kenny"};
    string a5[3] = {"stan", "kenny", "kenny"};
    assert(includes(a1, 7, a2, 3) && includes(a1, 7, a3, 3));
    assert(!includes(a1, 7, a4, 3) && !includes(a1, 7, a5, 3));
    
    cout << "All tests passed!" << endl;
}*/
