
namespace lasd {

    /* ************************************************************************** */

    // Copy assignment
    template <typename Data>
    PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap& pqheap) {
        Vector<Data>::operator=(pqheap);
        capacity = pqheap.capacity;
        return *this;
    }


    // Move assignment
    template <typename Data>
    PQHeap<Data>& PQHeap<Data>::operator=(PQHeap&& pqheap) noexcept {
        Vector<Data>::operator=(std::move(pqheap));
        std::swap(capacity, pqheap.capacity);
        return *this;
    }


    /* ************************************************************************** */

    // Specific member functions (inherited from ClearableContainer)

    template <typename Data>
    void PQHeap<Data>::Clear() {
        Vector<Data>::Clear();
        capacity = 0;
    }


    /* ************************************************************************** */

    // Specific member functions (inherited from PQ)

    template <typename Data>
    void PQHeap<Data>::RemoveTip() {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else {
            size--;
            std::swap(Elements[0], Elements[size]);
            if (size < capacity / 2)
                Reduce(capacity / 2);

            HeapVec<Data>::HeapifyToDown(0);
        }
    }


    template <typename Data>
    Data PQHeap<Data>::TipNRemove() {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else {
            size--;
            Data max = Elements[0];
            std::swap(Elements[0], Elements[size]);
            if (size < capacity / 2)
                Reduce(capacity / 2);

            HeapVec<Data>::HeapifyToDown(0);

            return max;
        }
    }


    template <typename Data>
    void PQHeap<Data>::Insert(const Data& dat) {  // Copy of the value
        if (size == capacity)
            (capacity == 0) ? Expand(5) : Expand(capacity * 2);

        Elements[size] = dat;
        size++;
        HeapVec<Data>::HeapifyToUp(size - 1);
    }


    template <typename Data>
    void PQHeap<Data>::Insert(Data&& dat) {  // Move of the value
        if (size == capacity)
            (capacity == 0) ? Expand(5) : Expand(capacity * 2);

        Elements[size] = std::move(dat);
        size++;
        HeapVec<Data>::HeapifyToUp(size - 1);
    }


    template <typename Data>
    void PQHeap<Data>::Change(ulong idx, const Data& dat) {
        if (idx >= size)
            throw std::out_of_range("Index " + std::to_string(idx) + " out of range");

        else {
            Elements[idx] = dat;
            if (idx > 0 && Elements[idx] > Elements[(idx - 1) / 2])
                HeapVec<Data>::HeapifyToUp(idx);

            else
                HeapVec<Data>::HeapifyToDown(idx);
        }
    }


    template <typename Data>
    void PQHeap<Data>::Change(ulong idx, Data&& dat) {
        if (idx >= size)
            throw std::out_of_range("Index " + std::to_string(idx) + " out of range");

        else {
            Elements[idx] = std::move(dat);
            if (idx > 0 && Elements[idx] > Elements[(idx - 1) / 2])
                HeapVec<Data>::HeapifyToUp(idx);

            else
                HeapVec<Data>::HeapifyToDown(idx);
        }
    }

    /* ************************************************************************** */

      // Auxiliary functions, if necessary!

    template <typename Data>
    void PQHeap<Data>::Expand(ulong new_capacity) {
        Data* new_Elements = new Data[new_capacity];

        for (ulong i = 0; i < size; i++)
            std::swap(new_Elements[i], Elements[i]);

        delete[] Elements;
        Elements = new_Elements;
        capacity = new_capacity;
    }


    template <typename Data>
    void PQHeap<Data>::Reduce(ulong new_capacity) {
        Data* new_Elements = new Data[new_capacity];

        for (ulong i = 0; i < size; i++)
            std::swap(new_Elements[i], Elements[i]);

        delete[] Elements;
        Elements = new_Elements;
        capacity = new_capacity;
    }


}
