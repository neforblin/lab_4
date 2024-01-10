#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class DequeBasedOnArray {
public:
    DequeBasedOnArray();
    explicit DequeBasedOnArray(unsigned size);
    DequeBasedOnArray(const DequeBasedOnArray& other);
    DequeBasedOnArray(DequeBasedOnArray&& other);
    DequeBasedOnArray(std::initializer_list<T> ilist);
    ~DequeBasedOnArray();

    unsigned GetSize() const;

    // Методы для добавления, удаления и просмотра элементов
    bool PushFront(const T& element);
    bool PopFront(T& element);
    bool PushBack(const T& element);
    bool PopBack(T& element);
    bool PeekFront(T& element) const;
    bool PeekBack(T& element) const;

    // Перегруженные операции
    const T& operator[](int index) const;
    T& operator[](int index);
    DequeBasedOnArray& operator=(const DequeBasedOnArray& other);
    DequeBasedOnArray& operator=(DequeBasedOnArray&& other);
    DequeBasedOnArray& operator=(std::initializer_list<T> ilist);

private:
    T* array;
    unsigned capacity;
    unsigned front;
    unsigned back;
    unsigned count;
};

template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray() : capacity(10), front(0), back(0), count(0) {
    array = new T[capacity];
}

template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(unsigned size) : front(0), back(0), count(size) {
    if (size > 0) {
        capacity = size * 2;
        array = new T[capacity];
    }
    else {
        capacity = 10;
        array = new T[capacity];
    }
}

template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(const DequeBasedOnArray& other) : front(0), back(0), count(other.count) {
    capacity = other.capacity;
    array = new T[capacity];

    for (unsigned i = 0; i < other.count; ++i) {
        array[i] = other.array[i];
    }
}

template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(DequeBasedOnArray&& other) {
    capacity = other.capacity;
    front = other.front;
    back = other.back;
    count = other.count;
    array = other.array;

    other.capacity = 0;
    other.front = 0;
    other.back = 0;
    other.count = 0;
    other.array = nullptr;
}

template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(std::initializer_list<T> ilist) : front(0), back(0), count(ilist.size()) {
    capacity = count * 2;
    array = new T[capacity];

    for (const auto& element : ilist) {
        array[back] = element;
        back = (back + 1) % capacity;
    }
}

template <typename T>
DequeBasedOnArray<T>::~DequeBasedOnArray() {
    delete[] array;
}

template <typename T>
unsigned DequeBasedOnArray<T>::GetSize() const {
    return count;
}

template <typename T>
bool DequeBasedOnArray<T>::PushFront(const T& element) {
    if (count == capacity - 1) {
        std::cerr << "Deque is full, cannot push to front." << std::endl;
        return false;
    }

    front = (front - 1 + capacity) % capacity;
    array[front] = element;
    ++count;
    return true;
}

template <typename T>
bool DequeBasedOnArray<T>::PopFront(T& element) {
    if (count == 0) {
        std::cerr << "Deque is empty, cannot pop from front." << std::endl;
        return false;
    }

    element = array[front];
    front = (front + 1) % capacity;
    --count;
    return true;
}

template <typename T>
bool DequeBasedOnArray<T>::PushBack(const T& element) {
    if (count == capacity - 1) {
        std::cerr << "Deque is full, cannot push to back." << std::endl;
        return false;
    }

    array[back] = element;
    back = (back + 1) % capacity;
    ++count;
    return true;
}

template <typename T>
bool DequeBasedOnArray<T>::PopBack(T& element) {
    if (count == 0) {
        std::cerr << "Deque is empty, cannot pop from back." << std::endl;
        return false;
    }

    back = (back - 1 + capacity) % capacity;
    element = array[back];
    --count;
    return true;
}

template <typename T>
bool DequeBasedOnArray<T>::PeekFront(T& element) const {
    if (count == 0) {
        std::cerr << "Deque is empty, cannot peek from front." << std::endl;
        return false;
    }

    element = array[front];
    return true;
}

template <typename T>
bool DequeBasedOnArray<T>::PeekBack(T& element) const {
    if (count == 0) {
        std::cerr << "Deque is empty, cannot peek from back." << std::endl;
        return false;
    }

    element = array[(back - 1 + capacity) % capacity];
    return true;
}

template <typename T>
const T& DequeBasedOnArray<T>::operator[](int index) const {
    if (index < 0 || index >= static_cast<int>(count)) {
        std::cerr << "Index out of bounds." << std::endl;
        throw std::out_of_range("Index out of bounds");
    }

    return array[(front + index) % capacity];
}

template <typename T>
T& DequeBasedOnArray<T>::operator[](int index) {
    if (index < 0 || index >= static_cast<int>(count)) {
        std::cerr << "Index out of bounds." << std::endl;
        throw std::out_of_range("Index out of bounds");
    }

    return array[(front + index) % capacity];
}

template <typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(const DequeBasedOnArray& other) {
    if (this != &other) {
        delete[] array;

        capacity = other.capacity;
        front = other.front;
        back = other.back;
        count = other.count;
        array = new T[capacity];

        for (unsigned i = 0; i < other.count; ++i) {
            array[i] = other.array[i];
        }
    }
    return *this;
}

template <typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(DequeBasedOnArray&& other) {
    if (this != &other) {
        delete[] array;

        capacity = other.capacity;
        front = other.front;
        back = other.back;
        count = other.count;
        array = other.array;

        other.capacity = 0;
        other.front = 0;
        other.back = 0;
        other.count = 0;
        other.array = nullptr;
    }
    return *this;
}

template <typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(std::initializer_list<T> ilist) {
    delete[] array;

    count = ilist.size();
    capacity = count * 2;
    array = new T[capacity];

    back = 0;
    for (const auto& element : ilist) {
        array[back] = element;
        back = (back + 1) % capacity;
    }

    return *this;
}

int main() {
    DequeBasedOnArray<int> deque1;
    DequeBasedOnArray<int> deque2(5);
    DequeBasedOnArray<int> deque3 = { 1, 2,3,4,5 };

    deque1 = { 10, 20, 30 };
    // Тестирование методов Push, Pop, Peek
    deque1.PushBack(100);
    deque1.PushBack(200);
    deque1.PushBack(300);

    int poppedElement;
    if (deque1.PopFront(poppedElement))
        std::cout << "Popped element from front: " << poppedElement << std::endl;
    else
        std::cout << "Deque is empty, cannot pop." << std::endl;

    if (deque1.PopBack(poppedElement))
        std::cout << "Popped element from back: " << poppedElement << std::endl;
    else
        std::cout << "Deque is empty, cannot pop." << std::endl;

    int peekedElement;
    if (deque3.PeekFront(peekedElement))
        std::cout << "Peeked element from front: " << peekedElement << std::endl;
    else
        std::cout << "Deque is empty, cannot peek." << std::endl;

    if (deque3.PeekBack(peekedElement))
        std::cout << "Peeked element from back: " << peekedElement << std::endl;
    else
        std::cout << "Deque is empty, cannot peek." << std::endl;

    std::cout << "Size of deque1: " << deque1.GetSize() << std::endl;
    std::cout << "Size of deque2: " << deque2.GetSize() << std::endl;
    std::cout << "Size of deque3: " << deque3.GetSize() << std::endl;

    std::cout << "Elements of deque1: ";
    for (unsigned i = 0; i < deque1.GetSize(); ++i) {
        std::cout << deque1[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Elements of deque2: ";
    for (unsigned i = 0; i < deque2.GetSize(); ++i) {
        std::cout << deque2[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Elements of deque3: ";
    for (unsigned i = 0; i < deque3.GetSize(); ++i) {
        std::cout << deque3[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
