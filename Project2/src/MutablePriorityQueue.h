/*
 * MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * Created on: 17/03/2018
 *      Author: João Pascoal Faria
 */

#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

#include <vector>

/** @brief A generic priority queue that allows modification of its elements. */

template <class T>
class MutablePriorityQueue {

    /** @brief The heap itself, stored as a vector of pointers to elements of type T. */
	std::vector<T *> H;

	void heapifyUp(unsigned i);
	void heapifyDown(unsigned i);
	inline void set(unsigned i, T * x);
public:
	MutablePriorityQueue();
	void insert(T * x);
	T * extractMin();
	void decreaseKey(T * x);
	bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Constructor of an empty MutablePriorityQueue.
 * @details Time Complexity: O(1).
 * */

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
	H.push_back(nullptr);
	// indices will be used starting in 1
	// to facilitate parent/child calculations
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Checks if the MutablePriorityQueue is empty.
 * @details Time Complexity: O(1).
 * @return True if the queue is empty, false otherwise.
 * */

template <class T>
bool MutablePriorityQueue<T>::empty() {
	return H.size() == 1;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Extracts and removes the minimum element from the queue.
 * @details Time Complexity: O(log(n)).
 * @return Pointer to the minimum element.
 * */

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
	auto x = H[1];
	H[1] = H.back();
	H.pop_back();
	if(H.size() > 1) heapifyDown(1);
	x->queueIndex = 0;
	return x;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Inserts a new element into the priority queue.
 * @details Time Complexity: O(log(n)).
 * @param x Pointer to the element to be inserted.
 * */

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
	H.push_back(x);
	heapifyUp(H.size()-1);
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Decreases the key of a specific element making it more prioritized.
 * @details Time Complexity: O(log(n)).
 * @param x Pointer to the element for which the key is to be decreased.
 * */

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
	heapifyUp(x->queueIndex);
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Restores the heap property by moving an element up.
 * @details Time Complexity: O(log(n)).
 * @param i Index of element to move up.
 * */

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
	auto x = H[i];
	while (i > 1 && *x < *H[parent(i)]) {
		set(i, H[parent(i)]);
		i = parent(i);
	}
	set(i, x);
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Restores the heap property by moving an element down.
 * @details Time Complexity: O(log(n)).
 * @param i Index of element to move down.
 * */

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
	auto x = H[i];
	while (true) {
		unsigned k = leftChild(i);
		if (k >= H.size())
			break;
		if (k+1 < H.size() && *H[k+1] < *H[k])
			++k; // right child of i
		if ( ! (*H[k] < *x) )
			break;
		set(i, H[k]);
		i = k;
	}
	set(i, x);
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Sets the element at the specified index in the heap and updates its queueIndex.
 * @details Time Complexity: O(1).
 * @param i Index where the element is to be set.
 * @param x Pointer to the element to set.
 * */

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
	H[i] = x;
	x->queueIndex = i;
}

#endif /* DA_TP_CLASSES_MUTABLEPRIORITYQUEUE */
