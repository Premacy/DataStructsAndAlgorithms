#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <initializer_list>

// попробуй концепты
// добавить аллокатор и делетер

template<typename T, bool Const>
class list_iterator;

template<typename T>
struct Node{
    T data;
    Node *next;

    Node(T data_): data(data_), next(nullptr){};
    Node(): data(T{}), next(nullptr){};
};

template<typename T>
class list{

    friend class list_iterator<T>;

    using node_ptr       = Node<T>*;
    using iterator       = list_iterator<T, false>;
    using const_iterator = list_iterator<T, true>;

public:
    list() = default;

    explicit list(std::initializer_list<T> &&l){
        for (auto element : l){
            if (head == nullptr){
                head = new Node<T>(element);
                curr = head;
            }else{
                curr->next = new Node<T>(element);
                curr = curr->next;
            }
            size_++;
        }
    }

    void push_back(T data){
        size_++;

        if (head == nullptr){
            head = new Node<T>(data);
            curr = head;
        }else{
            curr->next = new Node<T>(data); // это чтобы не пробегать весь список при добавлении элемента
            curr = curr->next;
        }
    }

    T at(std::size_t i){
        if ( i >= size_ ) throw std::out_of_range("at");

        Node<T> *p = head;
        for (std::size_t j = 0; j < i; j++){
            p = p->next;
        }

        return p->data;
    }

    inline std::size_t size() const{
        return size_;
    }

    iterator begin(){ return iterator(head); }
    iterator end()  { return iterator(nullptr); }

    const_iterator begin() const { return const_iterator(head); };
    const_iterator end()   const { return const_iterator(nullptr); }

private:
    node_ptr head = nullptr;
    node_ptr curr = nullptr;

    std::size_t size_ = 0;
};

template<typename T, bool Const>
class list_iterator{

    friend class list<T>;
    using pointer = std::conditional_t<Const, const Node<T>*, Node<T>>;

    list_iterator(pointer node_ptr){
        p = node_ptr;
    }

public:

    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T;
    using iterator_category = std::forward_iterator_tag;

    list_iterator operator++() {
        return list_iterator( p->next() );
    }

    inline T operator*() {
        return p->data;
    }

    list_iterator& operator =(list_iterator iter){
        p = iter->p;
        return (*this);
    }

    bool operator ==(list_iterator iter){
        return iter.p->data == p->data;
    }

    bool operator !=(list_iterator iter){
        return !( (*this) == iter );
    }

private:
    pointer *p;
};
