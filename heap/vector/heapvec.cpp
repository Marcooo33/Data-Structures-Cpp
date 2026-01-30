
namespace lasd {

    // Copy assignment

    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec& heap) {
        Vector<Data>::operator=(heap);
        return *this;
    }

    // Move assignment

    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(HeapVec&& heap) noexcept {
        Vector<Data>::operator=(std::move(heap));
        return *this;
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Heap)

    template <typename Data>
    bool HeapVec<Data>::IsHeap() const noexcept {
        if (size <= 1)
            return true;

        for (unsigned long i = 0; i <= (size - 2) / 2; i++) {
            unsigned long left = (2 * i) + 1;
            unsigned long right = (2 * i) + 2;

            if (left < size && Elements[left] > Elements[i])
                return false;

            if (right < size && Elements[right] > Elements[i])
                return false;
        }

        return true;
    }


    template <typename Data>
    void HeapVec<Data>::Heapify() noexcept {
        for (unsigned long i = size / 2; i > 0; i--)
            HeapifyToDown(i - 1);
    }


    /* ************************************************************************ */

    // Specific member function (inherited from SortableLinearContainer)

    //Heap Sort
    template <typename Data>
    void HeapVec<Data>::Sort() noexcept {
        Heapify();
        unsigned long tmp_size = size;
        for (unsigned long i = size - 1; i > 0; i--) {
            std::swap(Elements[0], Elements[i]);
            size--;
            HeapifyToDown(0);
        }

        size = tmp_size;
    }


    /* ************************************************************************ */

    // Auxiliary functions, if necessary!

    template <typename Data>
    void HeapVec<Data>::HeapifyToDown(unsigned long i) noexcept {
        unsigned long max = i;
        unsigned long left = (2 * i) + 1;
        unsigned long right = (2 * i) + 2;

        if (left < size && Elements[left] > Elements[max])
            max = left;

        if (right < size && Elements[right] > Elements[max])
            max = right;

        if (i != max) {
            std::swap(Elements[i], Elements[max]);
            HeapifyToDown(max);
        }
    }


    template <typename Data>
    void HeapVec<Data>::HeapifyToUp(unsigned long i) noexcept {
        if (i == 0)
            return;

        unsigned long parent = (i - 1) / 2;
        if (Elements[i] > Elements[parent]) {
            std::swap(Elements[i], Elements[parent]);
            HeapifyToUp(parent);
        }
    }

}