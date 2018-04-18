#ifndef __LINKED_LIST__
#define __LINKED_LIST__

template <typename T>
class LinkedList
{
protected:
    struct Node
    {
        T item;
        Node* next;
        Node* prev;
        Node() : next(nullptr), prev(nullptr) {}
        Node(const T& i) : item(i), next(nullptr), prev(nullptr) {}
    };

public:
    const T GetItemAt(int pos) const;

    void InsertAt(const T& elem, int pos);
    void PushFront(const T& elem);
    void PushBack(const T& elem);

    void RemoveAt(int pos);

    void Traverse(void (*visit)(const T&)) const;

private:
    Node * _head;
    Node * _tail;
    int    _size;
};

#endif
