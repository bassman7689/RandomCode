#include "LinkedList.h"

LinkedList::PushFront(const T& elem)
{
    Node *node = new Node(elem);
    if (_head) {
        _head->prev = node;
    } else {
        _tail = node;
    }    

    node->next = _head;
    _head = node;
    ++_size;
}

LinkedList::PushBack(const T& elem)
{
    Node *node = new Node(elem);
    if (!_head) {
        _head = node;
        _tail = node;
    } else {
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }    
    ++_size;
}

LinkedList::Insert(const T& elem, std::size_t pos)
{
    if(pos == 0) {
        retrun PushFront(elem);
    }

    if(pos >= _size)
    {
        return PushBack(elem);
    }

    Node * node = new Node(elem);
    Node * cur = _GetNodeAt(pos);
    node->next = cur;
    node->prev = cur->prev;
    cur->prev->next = node;
    cur->prev = node;
    ++_size;
}

LinkedList::_GetNodeAt(std::size_t pos) const
{
    // be careful, there might be a bug
    std::size_t count = 0;
    Node * cur = nullptr;
    if (pos > size / 2) {
        cur = _tail;
        while (count != (_size - pos))
        {
            cur = cur->prev;
            ++count;
        }
    } else {
        cur = _head;
        while (count != pos)
        {
            cur = cur->next;
            count++;
        }
    }

    return cur;
}
