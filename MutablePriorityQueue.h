//
// Created by andre on 03-04-2023.
//

#ifndef RAILWAY_MUTABLEPRIORITYQUEUE_H
#define RAILWAY_MUTABLEPRIORITYQUEUE_H


#include <vector>

template <class T>
class MutablePriorityQueue {
public:
    /**
     *
     */
    MutablePriorityQueue();

    /**
     *
     * @param x
     */
    void insert(T * x);

    /**
     *
     * @return
     */
    T * extractMin();

    /**
     *
     * @param x
     */
    void decreaseKey(T * x);

    /**
     *
     * @return
     */
    bool empty();

private:
    std::vector<T *> H;

    /**
     *
     * @param i
     */
    void heapifyUp(unsigned i);

    /**
     *
     * @param i
     */
    void heapifyDown(unsigned i);

    /**
     *
     * @param i
     * @param x
     */
    inline void set(unsigned i, T * x);
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1 to facilitate parent/child calculations
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size() - 1);
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if (H.size() > 1)
        heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k + 1 < H.size() && *H[k + 1] < *H[k])
            ++k; // right child of i
        if (!(*H[k] < *x))
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}


#endif //RAILWAY_MUTABLEPRIORITYQUEUE_H
