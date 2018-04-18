#include <iostream>

template <typename T>
struct Node
{
    public:
        T item;
        Node* next;
        Node* prev;
        Node() : next(nullptr), prev(nullptr) {}
        Node(const T& i) : item(i), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList
{
    public:
        LinkedList() {}
        ~LinkedList() {
            Node<T> *curr = _head;
            while(curr != nullptr) {
                Node<T> *tmp = curr->next;
                free(curr);
                curr = tmp;
            } 
        }

        void PushFront(const T& elem)
        {
            Node<T> *node = new Node<T>(elem);
            if (_head) {
                _head->prev = node;
            } else {
                _tail = node;
            }    

            node->next = _head;
            _head = node;
            ++_size;
        }

        T PopFront()
        {
            Node<T> *cur = _head;
            _head->next->prev = nullptr;
            _head = _head->next;
            cur->next = nullptr;
            T curItem =  cur->item;
            free(cur);
            return curItem;
        }

        void PushBack(const T& elem)
        {
            Node<T> *node = new Node<T>(elem);
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

        T PopBack()
        {
            Node<T> *cur = _tail;
            _tail->prev->next = nullptr;
            _tail = _tail->prev;
            cur->prev = nullptr;
            T curItem =  cur->item;
            free(cur);
            return curItem;
        }

        void InsertAt(const T& elem, std::size_t pos)
        {
            if(pos == 0) {
                return PushFront(elem);
            }

            if(pos >= _size)
            {
                return PushBack(elem);
            }

            Node<T> * node = new Node<T>(elem);
            Node<T> * cur = GetNodeAt(pos);
            node->next = cur;
            node->prev = cur->prev;
            cur->prev->next = node;
            cur->prev = node;
            ++_size;
        }

        T PopAt(std::size_t pos)
        {
            if(pos == 0) {
                return PopFront();
            }

            if(pos >= _size) {
                return PopBack();
            }

            Node<T> *cur = GetNodeAt(pos);
            Node<T> *prev = cur->prev;
            Node<T> *next = cur->next;
            prev->next = next;
            next->prev = prev;
            cur->next = nullptr;
            cur->prev = nullptr;
            T curItem =  cur->item;
            free(cur);
            return curItem;
        }

        Node<T> *GetNodeAt(std::size_t pos) const
        {
            // be careful, there might be a bug
            std::size_t count = 0;
            Node<T> * cur = nullptr;
            if (pos > _size / 2) {
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

        class iterator
        {
            public:
                iterator(Node<T> *ptr) : _ptr(ptr) {}
                iterator operator++() { iterator cur = *this; _ptr = _ptr->next; return cur; }
                iterator operator++(int junk) { iterator cur = *this; _ptr = _ptr->next; return cur; }
                T &operator*() { return _ptr->item; }
                T *operator->() { return _ptr->item; }
                bool operator==(const iterator& rhs) { return _ptr == rhs._ptr; }
                bool operator!=(const iterator& rhs) { return _ptr != rhs._ptr; }

            private:
                Node<T> *_ptr;
        };

        iterator begin() {
            return iterator(_head);
        }

        iterator end() {
            return iterator(_tail->next);
        }


    private:
        Node<T> * _head;
        Node<T> * _tail;
        int    _size;
};

int main(int argc, char **argv)
{
    LinkedList<std::string> list;
    list.PushBack("a");
    list.PushBack("b");
    list.PushBack("b");
    list.PushBack("b");
    list.PushBack("b");
    list.PushBack("b");
    list.PushBack("b");
    list.PushBack("b");
    list.PushFront("a");
    list.PushFront("a");
    list.PushFront("a");
    list.PushFront("a");
    list.PushFront("a");
    list.PushFront("a");
    list.PushFront("a");
    list.PushFront("a");
    list.PushFront("a");
    list.InsertAt("1", 0);
    list.InsertAt("1", 0);
    list.InsertAt("1", 0);

    std::cout << "Before PopFront:" << std::endl;
    for (auto& i : list) {
        std::cout << i << std::endl;
    }

    list.PopFront();
    list.PopFront();
    list.PopFront();

    std::cout << "After PopFront:" << std::endl;
    for (auto& i : list) {
        std::cout << i << std::endl;
    }

    std::cout << "Before PopBack:" << std::endl;
    for (auto& i : list) {
        std::cout << i << std::endl;
    }

    list.PopBack();
    list.PopBack();
    list.PopBack();
    list.PopBack();
    list.PopBack();
    list.PopBack();
    list.PopBack();
    list.PopBack();

    std::cout << "After PopBack:" << std::endl;
    for (auto& i : list) {
        std::cout << i << std::endl;
    }

    list.InsertAt("1", 0);
    list.InsertAt("1", 0);
    list.InsertAt("1", 0);

    std::cout << "Before PopAt:" << std::endl;
    for (auto& i : list) {
        std::cout << i << std::endl;
    }

    list.PopAt(3);
    list.PopAt(2);
    list.PopAt(1);

    std::cout << "After PopAt:" << std::endl;
    for (auto& i : list) {
        std::cout << i << std::endl;
    }
}
