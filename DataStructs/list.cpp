#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <initializer_list>

// попробуй концепты

class list_iterator{};

template<typename T>
class list{

    struct Node{
        T data;
        Node *next;

        Node(T data_): data(data_), next(nullptr){};
        Node(): data(T{}), next(nullptr){};
    };

    friend list_iterator;
    using iterator = list_iterator;

public:
    list(): head(nullptr) {};

    explicit list(std::initializer_list<T> &&l){
        for (auto element : l){
            if (head == nullptr){
                head = new Node(element);
                curr = head;
            }else{
                curr->next = new Node(element);
                curr = curr->next;
            }
            size_++;
        }
    }

    void push_back(T data){
        size_++;

        if (head == nullptr){
            head = new Node(data);
            curr = head;
        }else{
            curr->next = new Node(data); // это чтобы не пробегать весь список при добавлении элемента
            curr = curr->next;
        }
    }

    T at(std::size_t i){
        if ( i >= size_ ) throw std::out_of_range("at");

        Node *p = head;
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

private:
    Node *head = nullptr;
    Node *curr = nullptr;

    std::size_t size_ = 0;
};

template<typename T>
class list_iterator{
public:
    excplicit list_iterator(Node<T> *node) noexcept{
        p = node;
    }

    Node<T> operator++() noexcept{
        return list_iterator( p->next() );
    }

    inline T operator*() noexcept{
        return p->data;
    }

    list_iterator& operator =(list_iterator iter){
        p = iter->p;
        return (*this);
    }

    bool operator ==(list_of_doubles_iterator iter){
        return iter.p->data == p->data;
    }

    bool operator !=(list_of_doubles_iterator iter){
        return !( (*this) == iter );
    }

private:
    Node<T> *p;
};

template<class InputIterator>
void double_each_element(InputIterator begin, InputIterator end){
    for(auto itr = begin; itr != end; ++itr){
        (*itr) *= 2;
    }

    /*
    for(auto& val : container){
        val *= 2
    }
    */
}

template<class Containter>
void printContainer(const Containter &container, std::ostream &stream){
    for(const auto& val : container){
        stream << val << ", ";
    }
    stream << "\n";
}

int main(){
    
    list<int> l{1,2,3};
    double_each_element(l.begin(), l.end());
    printContainer(l);

    return 0;
}
