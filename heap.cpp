// heap.cpp

#include <sstream>
#include <iostream>
using namespace std;

// Implement heap methods here.

//Default constructor
template <class KeyType>
MinHeap<KeyType>::MinHeap(int n) {
	//Post-condition: Heap is constructed
	capacity = n;
	heapSize = 0;
	A = new KeyType*[capacity];
}

//Construct heap from an array
template <class KeyType>
MinHeap<KeyType>::MinHeap(KeyType * initA[], int n) {
	//Post-condition: Heap is constructed
	capacity = n;
	heapSize = n;
	A = new KeyType*[n];
	for (int i = 0; i < n; i++) {
		A[i] = initA[i];
	}
	buildHeap(); //calls build-heap so it is not needed to be called in heapSort
}

//Copy Constrcutor
template <class KeyType>
MinHeap<KeyType>::MinHeap(const MinHeap<KeyType>& heap) {
	//Post-condition: Heap is constructed
	copy(heap);
}

//Destructor
template <class KeyType>
MinHeap<KeyType>::~MinHeap() {
	//Post-condition: Heap is destructed
	destroy();
}

// heapsort, return result in sorted[]
template <class KeyType>
void MinHeap<KeyType>::heapSort(KeyType * sorted[]) {
	//Precondition: the instance variable A is already a min heap
	//Post-condition: the passed-in parameter array sorted[] is sorted in ascending order
	for (int i = (capacity - 1); i >= 1; i--) {
		swap(0, i); //swaps first and last element in the heap
		heapSize--; //decreases heap size by 1 since that last position is already sorted
		heapify(0); //runs heapify rooted on that newly swapped element
	}
	for (int j = 0; j < capacity; j++) {
		sorted[j] = A[capacity - j - 1]; //change from descending to ascending order
	}
}

//Assignment =operator
template <class KeyType>
MinHeap<KeyType>& MinHeap<KeyType>::operator=(const MinHeap<KeyType>& heap) {
	//Post-condition: Heap is reassigned based on another heap
	if (this != &heap) {
		destroy(); //deallocates any past heap array
		copy(heap); //copys new heap array into this heap
	}
	return *this;
}

//Heapify subheap rooted at index
template <class KeyType>
void MinHeap<KeyType>::heapify(int index) {
	//Precondition: 2 subtrees of node index are both valid heaps
	//Post-condition: the resulting subtree rooted at the index is a min-heap
	heapifyR(index); //calls recursive heap
}

//Build heap
template <class KeyType>
void MinHeap<KeyType>::buildHeap() {
	//Post-condition: the resulting array is a min-heap after build-heap is ran
	heapSize = capacity;
	for (int i = (capacity / 2); i >= 0; i--) {
		heapify(i); //only the front half of array is needed to run heapify on because leaves are already heaps
	}
}

//Recursive heapify
template <class KeyType>
void MinHeap<KeyType>::heapifyR(int index) {
	//Precondition: 2 subtrees of node index are both valid heaps
	//Post-condition: the resulting subtree rooted at the index is a min-heap
	int left = leftChild(index); //setting left child
	int right = rightChild(index); //setting right child
	int smallest;

	if ((left < heapSize) && (*(A[left]) < *(A[index]))) {
		smallest = left; //checking if left is smallest element
	}
	else {
		smallest = index; //if not the root still is
	}

	if ((right < heapSize) && (*(A[right]) < *(A[smallest]))) {
		smallest = right; //checking if right is smallest element
	}

	if (smallest != index) {
		swap(index, smallest);
		heapifyR(smallest); //recursively calls itself until its in the right position
	}
}

//Iterative heapify
template <class KeyType>
void MinHeap<KeyType>::heapifyI(int index) {
	//Precondition: 2 subtrees of node index are both valid heaps
	//Post-condition: the resulting subtree rooted at the index is a min-heap
	int i = index;
	while (i <= heapSize) {
		int left = leftChild(i); //setting left child
		int right = rightChild(i); //setting right child
		int smallest;

		if ((left < heapSize) && (*(A[left]) < *(A[i]))) {
			smallest = left; //checking if left is smallest element
		}
		else {
			smallest = index; //if not the root still is
		}

		if ((right < heapSize) && (*(A[right]) < *(A[smallest]))) {
			smallest = right; //checking if right is smallest element
		}

		if (smallest != i) {
			swap(i, smallest);
			i = smallest;
		}
		else {
			break; //iterates through the tree until its in the right position
		}
	}
}

//Swap elements in A
template <class KeyType>
void MinHeap<KeyType>::swap(int index1, int index2) {
	KeyType * temp = A[index1]; //use temporary variable to swap
	A[index1] = A[index2];
	A[index2] = temp;
}

//Copy heap to this heap
template <class KeyType>
void MinHeap<KeyType>::copy(const MinHeap<KeyType>& heap) {
	capacity = heap.capacity;
	heapSize = heap.heapSize;
	A = new KeyType*[capacity];
	for (int i = 0; i < heapSize; i++) {
		A[i] = heap.A[i];
	}
}

//Deallocate heap
template <class KeyType>
void MinHeap<KeyType>::destroy() {
	delete [] A; //deallocating array
	heapSize = 0;
	capacity = 0;
}

// Use the following toString() for testing purposes.

template <class KeyType>
std::string MinHeap<KeyType>::toString() const
{
	std::stringstream ss;
	
	if (capacity == 0)
		ss << "[ ]";
	else
	{
		ss << "[";
		if (heapSize > 0)
		{
			for (int index = 0; index < heapSize - 1; index++)
				ss << *(A[index]) << ", ";
			ss << *(A[heapSize - 1]);
		}
		ss << " | ";
		if (capacity > heapSize)
		{
			for (int index = heapSize; index < capacity - 1; index++)
				ss << *(A[index]) << ", ";
			ss << *(A[capacity - 1]);
		}
		ss << "]";
	}
	return ss.str();
}

template <class KeyType>
std::ostream& operator<<(std::ostream& stream, const MinHeap<KeyType>& heap)
{
	return stream << heap.toString();
}