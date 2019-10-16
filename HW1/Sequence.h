#ifndef SEQUENCE_H
#define SEQUENCE_H

using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 200;

class Sequence
{
public:
    Sequence();
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
private:
    int m_size;
    ItemType m_array[DEFAULT_MAX_ITEMS];
};

#endif
