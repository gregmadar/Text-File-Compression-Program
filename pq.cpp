// pq.cpp

// These 3 constructors just call the corresponding MinHeap constructors.  That's all.
template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue() : MinHeap<KeyType>()
{
}

// construct mpq with capacity
// Precond: n >= 0
// Postcond: return a min priority queue with capacity n
template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(int n) : MinHeap<KeyType>(n)
{
}

// copy constructor
// Precond: input a min priority queue
// Postcond:  return new object min priority queue = input min priority queue
template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(const MinPriorityQueue<KeyType> &pq) : MinHeap<KeyType>(pq)
{
}

// function to get the pointer to the current minimum value
// Precond: input a non-empty min priority queue
// Postcond: return the pointer which points to the current minimum value
template <class KeyType>
KeyType *MinPriorityQueue<KeyType>::minimum() const
{
    if (this->empty())
    {
        throw EmptyError();
    }
    return A[0];
}

// function to extract the element with minimum priority
// Precond: input a non-empty min priority queue
// Postcond: return the minimum element
template <class KeyType>
KeyType *MinPriorityQueue<KeyType>::extractMin()
{
    if (this->empty())
    {
        throw EmptyError();
    }
    KeyType *min = A[0];
    A[0] = A[heapSize - 1];
    heapSize--;
    heapify(0);
    return min;
}

// function to decrease priority of an element with given index
// Precond: array A must be a min heap, the priority of the element >= than the key
// Postcond: maintain min heap property
template <class KeyType>
void MinPriorityQueue<KeyType>::decreaseKey(int index, KeyType *key)
{
    if (key > A[index])
    {
        throw KeyError();
    }
    A[index] = key;
    while ((index > 0) && (*(A[index]) < *(A[parent(index)])))
    {
        swap(index, parent(index));
        index = parent(index);
    }
}

// function to insert a new element to the min heap
// Precond: array A must be a min heap
// Postcond: maintain min heap property after inserting new element
template <class KeyType>
void MinPriorityQueue<KeyType>::insert(KeyType *key)
{
    if (heapSize == capacity)
    {
        throw FullError();
    }
    heapSize++;
    A[heapSize - 1] = key;
    decreaseKey(heapSize - 1, key);
}

// boolean fuction to check if the heap is empty or not
// Postcond: true if the heap is empty, false if the heap is not empty
template <class KeyType>
bool MinPriorityQueue<KeyType>::empty() const
{
    if (heapSize == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// function to get the size of the heap
// Postcond: return an interger that indicates the size of the heap
template <class KeyType>
int MinPriorityQueue<KeyType>::length() const
{
    return heapSize;
}

template <class KeyType>
std::string MinPriorityQueue<KeyType>::toString() const
{
    std::stringstream ss;

    if (heapSize == 0)
    {
        ss << "[ ]";
    }
    else
    {
        ss << "[";
        for (int index = 0; index < heapSize - 1; index++)
            ss << *(A[index]) << ", ";
        ss << *(A[heapSize - 1]) << "]";
    }
    return ss.str();
}

template <class KeyType>
std::ostream &operator<<(std::ostream &stream, const MinPriorityQueue<KeyType> &pq)
{
    stream << pq.toString();

    return stream;
}
