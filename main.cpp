#include <iostream>
#include <vector>

#define P(X) std::cout << #X << ":" << X << std::endl

template <typename Item>
class MyVector: public std::vector<Item> {
private:
public:
    MyVector() = default;
    MyVector(std::initializer_list<Item> il): std::vector<Item>(il) {}
    class MyIterator {
    private:
        typename MyVector<Item>::iterator _currentIterator;
        MyVector<Item>* _pointerToParent;
    public:
        MyIterator() = default;
        MyIterator(const MyIterator& iterator) = default;
        explicit MyIterator(const typename MyVector<Item>::iterator& iterator, MyVector<Item>* pointerToParent):
            _currentIterator(iterator), _pointerToParent(pointerToParent) {
        }
        MyIterator& operator++() {
            auto i = _currentIterator;
            for(++i; i != _pointerToParent->end(); ++i) {
                if(*i == *_currentIterator) {
                    _currentIterator = i;
                    return *this;
                }
            }
            for(auto j = _pointerToParent->begin(); j != _pointerToParent->end(); ++j) {
                if(*j > *_currentIterator) {
                    _currentIterator = j;
                    return *this;
                }
            }
            _currentIterator = _pointerToParent->end();
            return *this;
        }
        Item operator*() {
            return *_currentIterator;
        }
        bool operator!=(const MyIterator& iterator) {
            return !(_currentIterator == iterator._currentIterator && _pointerToParent == iterator._pointerToParent);
        }
    };
    MyIterator myBegin() {
        auto theSmallest = MyVector<Item>::begin();
        for(auto i = MyVector<Item>::begin(); i != MyVector<Item>::end(); ++i) {
            if(*i < *theSmallest) theSmallest = i;
        }
        return MyIterator(theSmallest, this);
    }
    MyIterator myEnd() {
        return MyIterator(MyVector<Item>::end(), this);
    }
};

int main() {
    MyVector<int> myVector{3, 5, 6, 1, 3, 4, 6, 8, 10};
    for(auto myIterator = myVector.myBegin(); myIterator != myVector.myEnd(); ++myIterator) {
        P(*myIterator);
    }

    return 0;
}