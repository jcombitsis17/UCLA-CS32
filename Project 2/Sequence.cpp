#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence() //NOTE: m_head->next is position 0 in Sequence (head is dummy node)
: m_size(0)
{
    m_head = new Node;
    m_head->prev = m_head;
    m_head->next = m_head;
}
// Create an empty sequence (i.e., one with no items)

Sequence::Sequence(const Sequence& other)
: m_size(0)
{
    Node* curr = other.m_head->next;
    m_head = new Node; // create new empty Sequence
    m_head->prev = m_head;
    m_head->next = m_head;
    while (curr != other.m_head)
    {
        Node* newNode = new Node; // create new Node
        newNode->data = curr->data;
        
        Node* lastNode = m_head->prev; // insert new Node at end of list
        lastNode->next = newNode;
        newNode->prev = lastNode;
        m_head->prev = newNode;
        newNode->next = m_head;
        
        curr = curr->next;
        m_size++;
    }
}
// Copy Constructor

Sequence::~Sequence()
{
    Node* curr = m_head->next;
    while (curr != m_head)
    {
        Node* temp = curr->next; // delete each Node in the Sequence
        delete curr;
        curr = temp;
    }
    delete m_head; // delete the head (dummy) Node
}
// Destructor

Sequence& Sequence::operator=(const Sequence& other)
{
    if (this == &other) // Do nothing if a Sequence is set equal to itself
        return *this;
    Sequence temp = other;
    swap(temp);
    
    return *this;
}
// Assignment Operator

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
    if (pos < 0 || pos > m_size)
        return false;
    m_size++;
    
    Node* newNode = new Node;             //introduce new Node
    newNode->data = value;
    
    Node* curr = m_head->next;            //go to correct position in list to insert newNode
    for (int i = 0; i < pos; i++)
        curr = curr->next;
    
    newNode->prev = curr->prev;           //insert newNode into list
    (curr->prev)->next = newNode;
    curr->prev = newNode;
    newNode->next = curr;
    
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
    int p = 0;
    Node* curr = m_head->next;
    while (curr != m_head)
    {
        if (value <= curr->data) // break loop if the correct position to insert is found
            break;
        p++;
        curr = curr->next;
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
    Node* select = m_head->next;
    for (int i = 0; i < pos; i++) // go to correct location in Sequence
        select = select->next;
    (select->next)->prev = select->prev; // adjust pointers around selected Node
    (select->prev)->next = select->next;
    delete select; // delete selected Node
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
    int index = 0;
    Node* curr = m_head->next;
    while (curr != m_head)
    {
        if (curr->data == value)
        {
            Node* temp = curr->next;
            erase(index); // remove Node at the index where data == value
            count++;
            index--;
            curr = temp;
        }
        else
            curr = curr->next;
        index++;
    }
    return count;
}
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= m_size)
        return false;
    Node* curr = m_head->next;
    for (int i = 0; i < pos; i++)
        curr = curr->next;
    value = curr->data;
    return true;
}
// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= m_size || m_size == 0)
        return false;
    Node* curr = m_head->next;
    for (int i = 0; i < pos; i++)
        curr = curr->next;
    curr->data = value;
    return true;
}
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value) const
{
    int p = -1;
    int count = 0;
    for (Node* curr = m_head->next; curr != m_head; curr = curr->next)
    {
        if (curr->data == value)
        {
            p = count;
            break;
        }
        count++;
    }
    return p;
}
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.

void Sequence::swap(Sequence& other)
{
    Node* temp = other.m_head;      // switch Nodes
    other.m_head = this->m_head;
    this->m_head = temp;
    
    int sizeTemp = other.m_size;    // switch sizes
    other.m_size = this->m_size;
    this->m_size = sizeTemp;
}
// Exchange the contents of this sequence with the other one.

void Sequence::dump() const
{
    cerr << endl << "Contents of this Sequence (size " << m_size << "): " << endl;
    for (Node* p = m_head->next; p != m_head; p = p->next)
        cerr << p->data << endl;
    cerr << endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    int index = -1;
    if (seq1.empty() || seq2.empty() || seq2.size() > seq1.size())
        return index;
    ItemType one;
    ItemType two;
    for (int i = 0; i < seq1.size(); i++)
    {
        seq1.get(i, one);
        seq2.get(0, two); // compare the first Node in seq2 to every Node in seq1 (until they're equal)
        if (one == two)
        {
            if (i + seq2.size() > seq1.size())
                return -1;
            index = i;
            int seq2Index = 1;
            for (int j = (i + 1); j < seq2.size() + i; j++) // check for equality in the rest of seq2
            {
                seq1.get(j, one);
                seq2.get(seq2Index, two);
                if (one != two)
                {
                    index = -1; // revert to default value, continue original for loop
                    break;
                }
                seq2Index++;
            }
        }
    }
    return index;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    if (seq1.empty())   // If one Sequence is empty, result is equal to the other Sequence
    {
        result = seq2;
        return;
    } else if (seq2.empty())
    {
        result = seq1;
        return;
    }
    
    int initialSizeSeq2 = seq2.size();
    int min;
    bool seq2bigger = false;
    if (seq1.size() <= seq2.size()) // Determine which Sequence is smaller
    {
        min = seq1.size();
        seq2bigger = true;
    }
    else
        min = seq2.size();
    
    result = seq1; // set initial result Sequence to seq1
    ItemType data;
    int index2 = 0;
    for (int i = 1; i < (min * 2); i = i + 2) // Insert a member of seq2 into result at every other slot (odd indeces)
    {
        seq2.get(index2, data);
        result.insert(i, data);
        index2++;
        
        if (initialSizeSeq2 != seq2.size()) // If seq2.size changes, i.e. seq2 and result refer to the same Sequence,
            return;                         // Do nothing, because I couldn't figure out how to implement this case
    }                                       // The return; is here to prevent an infinite loop and possible memory leak
    
    if (seq2bigger) // If seq2 was bigger, insert remaining items at end of result
    {
        for (int i = min; i < seq2.size(); i++)
        {
            seq2.get(i, data);
            result.insert(result.size(), data);
        }
    }
}
