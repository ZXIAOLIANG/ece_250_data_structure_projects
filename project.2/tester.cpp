#include <iostream>
#include "Resizable_deque.h"

int main() {
    Resizable_deque<int> deque;
    deque.push_front(1);
    deque.push_back(2);
    deque.pop_back();
    deque.pop_back();
    deque.push_back(15);
    deque.push_front(14);
    std::cout << "front: " << deque.front() << std::endl;
    std::cout << "back: " << deque.back() << std::endl;
    deque.clear();
    deque.push_back(0);
    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    deque.push_back(4);
    deque.push_back(5);
    deque.push_back(6);
    deque.push_back(7);
    deque.push_back(8);
    deque.push_back(9);
    deque.push_back(10);
    deque.push_back(11);
    deque.push_back(12);
    deque.push_back(13);
    deque.push_back(14);
    deque.push_back(15);
    deque.push_back(16);
    std::cout << "front: " << deque.front() << std::endl;
    std::cout << "back: " << deque.back() << std::endl;
    deque.clear();
    std::cout << "cap: " << deque.capacity() << std::endl;
    std::cout << "empty: " << deque.empty() << std::endl;
}