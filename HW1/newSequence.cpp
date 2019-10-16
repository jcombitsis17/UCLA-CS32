#include "newSequence.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Sequence::Sequence()
: m_size(0), m_maxItems(DEFAULT_MAX_ITEMS)
{
    m_array = new ItemType[DEFAULT_MAX_ITEMS];
}
// Create a default Sequence

Sequence::Sequence(const int maxSize)
: m_size(0)
{
    if (maxSize < 0)
    {
        cout << "Max size of Sequence must be non-negative" << endl;
        exit(1);
    }
    m_maxItems = maxSize;
    m_array = new ItemType[maxSize];
}
// Create a Sequence of size maxSize

Sequence::Sequence(const Sequence& other)
: m_size(other.m_size), m_maxItems(other.m_maxItems)
{
    m_array = new ItemType[m_maxItems];
    for (int i = 0; i < m_maxItems; i++)
    {
        m_array[i] = other.m_array[i];
    }
}
// Copy Constructor

Sequence::~Sequence()
{
    delete [] m_array;
}
// Destructor

Sequence& Sequence::operator=(const Sequence& other)
{
    if (this != &other)
    {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}
// Operator Overload =

bool Sequence::empty() const
{
    return (m_size == 0);
}
// Return true if the sequence is empty, otherwise false.

int Sequence::size() const
{
    return m_size;
}
// Return the number of items in the sequence.

bool Sequence::insert(int pos, const ItemType& value)
{
    if (m_size >= m_maxItems || pos < 0 || pos > m_size)
        return false;
    for (int i = (m_size - 1); i >= pos; i--)
        m_array[i+1] = m_array[i];
    m_array[pos] = value;
    m_size++;
    return true;
}
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return false.  Notice that
// if pos is equal to size(), the value is inserted at the end.

int Sequence::insert(const ItemType& value)
{
    if (m_size >= m_maxItems)
        return -1;
    int p = 0;
    for (int i = 0; i < m_size; i++)
    {
        if (value <= m_array[i])
        {
            p = i;
            break;
        }
        p = m_size;
    }
    insert(p, value);
    return p;
}
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).

bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= m_size || m_size == 0)
        return false;
    for (int i = pos; i < (m_size - 1); i++)
    {
        m_array[i] = m_array[i+1];
    }
    m_size--;
    return true;
}
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.

int Sequence::remove(const ItemType& value)
{
    if (m_size == 0)
        return 0;
    int count = 0;
    for (int i = 0; i < m_size; i++)
    {
        if (m_array[i] == value)
        {
            erase(i);
            count++;
            i--;
        }
    }
    return count;
}
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= m_size)
        return false;
    value = m_array[pos];
    return true;
}
// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= m_size || m_size == 0)
        return false;
    m_array[pos] = value;
    return true;
}
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value) const
{
    int p = -1;
    for (int i = 0; i < m_size; i++)
    {
        if (m_array[i] == value)
        {
            p = i;
            break;
        }
    }
    return p;
}
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.

void Sequence::swap(Sequence& other)
{
    int tempSize = other.m_size;
    int tempMax = other.m_maxItems;
    ItemType* temp = other.m_array;
    
    other.m_size = m_size;
    m_size = tempSize;
    
    other.m_maxItems = m_maxItems;
    m_maxItems = tempMax;
    
    other.m_array = m_array;
    m_array = temp;
}
// Exchange the contents of this sequence with the other one.

void Sequence::dump() const
{
    cerr << endl << "Contents of this Sequence (size " << m_size << "): " << endl;
    for (int i = 0; i < m_size; i++)
    {
        cerr << "m_array[" << i << "] = " << m_array[i] << endl;
    }
    cerr << endl;
}
