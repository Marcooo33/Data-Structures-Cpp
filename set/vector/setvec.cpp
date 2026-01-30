
namespace lasd {

    // Specific constructors

    template <typename Data>
    SetVec<Data>::SetVec(const TraversableContainer<Data>& con) {
        capacity = con.Size();
        Elements = new Data[capacity];
        con.Traverse(
            [this](const Data& dat) {
                this->Insert(dat);
            }
        );
    }


    template <typename Data>
    SetVec<Data>::SetVec(MappableContainer<Data>&& con) {
        capacity = con.Size();
        Elements = new Data[capacity];
        con.Map(
            [this](Data& dat) {
                this->Insert(std::move(dat));
            }
        );
    }

    /* ************************************************************************ */

    // Copy constructor

    template <typename Data>
    SetVec<Data>::SetVec(const SetVec& svec) {
        size = svec.size;
        capacity = svec.size;
        Head = svec.Head;
        Elements = new Data[capacity];

        for (ulong i = 0; i < size; i++)
            Elements[i] = svec.Elements[i];
    }


    // Move constructor

    template <typename Data>
    SetVec<Data>::SetVec(SetVec&& svec) noexcept {
        std::swap(size, svec.size);
        std::swap(capacity, svec.capacity);
        std::swap(Head, svec.Head);
        std::swap(Elements, svec.Elements);
    }

    /* ************************************************************************ */

    // Copy assignment

    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(const SetVec& svec) {
        SetVec<Data> tmp(svec);
        std::swap(size, tmp.size);
        std::swap(capacity, tmp.capacity);
        std::swap(Head, tmp.Head);
        std::swap(Elements, tmp.Elements);

        return *this;
    }


    // Move assignment

    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(SetVec&& svec) noexcept {
        std::swap(size, svec.size);
        std::swap(capacity, svec.capacity);
        std::swap(Head, svec.Head);
        std::swap(Elements, svec.Elements);

        return *this;
    }

    /* ************************************************************************ */

    // Comparison operator

    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec& svec) const noexcept {
        if (size != svec.size)
            return false;

        else {
            for (ulong i = 0; i < size; i++)
                if ((*this)[i] != svec[i])
                    return false;

            return true;
        }
    }

    template <typename Data>
    bool SetVec<Data>::operator!=(const SetVec& svec) const noexcept {
        return !(*this == svec);
    }


    /* ************************************************************************ */

    // Specific member functions (inherited from OrderedDictionaryContainer)

    template <typename Data>
    const Data& SetVec<Data>::Min() const {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else
            return (*this)[0];
    }

    template <typename Data>
    Data SetVec<Data>::MinNRemove() {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else {
            Data min = (*this)[0];
            Head = Head + 1;
            size = size - 1;
            return min;
        }
    }

    template <typename Data>
    void SetVec<Data>::RemoveMin() {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else {
            Head = Head + 1;
            size = size - 1;
        }
    }



    template <typename Data>
    const Data& SetVec<Data>::Max() const {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else
            return (*this)[size - 1];
    }

    template <typename Data>
    Data SetVec<Data>::MaxNRemove() {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else {
            Data max = (*this)[size - 1];
            size = size - 1;
            return max;
        }
    }

    template <typename Data>
    void SetVec<Data>::RemoveMax() {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else
            size = size - 1;
    }




    template <typename Data>
    const Data& SetVec<Data>::Predecessor(const Data& dat) const {
        if (size == 0)
            throw std::length_error("Predecessor not found");

        ulong idx = BinarySearch(0, size - 1, dat);
        if (idx == 0)
            throw std::length_error("Predecessor not found");

        else
            return (*this)[idx - 1];
    }

    template <typename Data>
    Data SetVec<Data>::PredecessorNRemove(const Data& dat) {
        if (size == 0)
            throw std::length_error("Predecessor not found");

        ulong idx = BinarySearch(0, size - 1, dat);
        if (idx == 0)
            throw std::length_error("Predecessor not found");

        else {
            Data pred = (*this)[idx - 1];
            Remove_at(idx - 1);
            return pred;
        }
    }

    template <typename Data>
    void SetVec<Data>::RemovePredecessor(const Data& dat) {
        if (size == 0)
            throw std::length_error("Predecessor not found");

        ulong idx = BinarySearch(0, size - 1, dat);
        if (idx == 0)
            throw std::length_error("Predecessor not found");

        else
            Remove_at(idx - 1);

    }


    template <typename Data>
    const Data& SetVec<Data>::Successor(const Data& dat) const {
        if (size == 0)
            throw std::length_error("Successor not found");

        ulong idx = BinarySearch(0, size - 1, dat);

        if (idx >= size)
            throw std::length_error("Successor not found");

        else {
            if ((*this)[idx] == dat)
                return (*this)[idx + 1];

            else
                return (*this)[idx];
        }
    }

    template <typename Data>
    Data SetVec<Data>::SuccessorNRemove(const Data& dat) {
        if (size == 0)
            throw std::length_error("Successor not found");

        ulong idx = BinarySearch(0, size - 1, dat);
        if (idx >= size)
            throw std::length_error("Successor not found");

        else {
            Data succ;

            if ((*this)[idx] == dat) {
                succ = (*this)[idx + 1];
                Remove_at(idx + 1);
            }

            else {
                succ = (*this)[idx];
                Remove_at(idx);
            }

            return succ;
        }
    }

    template <typename Data>
    void SetVec<Data>::RemoveSuccessor(const Data& dat) {
        if (size == 0)
            throw std::length_error("Successor not found");

        ulong idx = BinarySearch(0, size - 1, dat);
        if (idx >= size)
            throw std::length_error("Successor not found");

        else
            Remove_at(idx - 1);
    }


    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    template <typename Data>
    bool SetVec<Data>::Insert(const Data& dat) {    //Copy of the value
        if (capacity == 0) {
            Expand(5);
            Elements[0] = dat;
            size = 1;
            return true;
        }

        if (size == 0) {
            Elements[0] = dat;
            size = 1;
            return true;
        }

        if (size == capacity)
            Expand(capacity * 2);

        ulong idx = BinarySearch(0, size - 1, dat);

        if (idx >= size || (*this)[idx] != dat) {
            if (idx < size / 2)
                Shift_sx(idx);

            else
                Shift_dx(idx);

            AccessNonConst_at(idx) = dat;
            size = size + 1;
            return true;
        }

        else
            return false;
    }


    template <typename Data>
    bool SetVec<Data>::Insert(Data&& dat) {    //Move of the value
        if (capacity == 0) {
            Expand(5);
            Elements[0] = std::move(dat);
            size = 1;
            return true;
        }

        if (size == 0) {
            Elements[0] = std::move(dat);
            size = 1;
            return true;
        }

        if (size == capacity)
            Expand(capacity * 2);

        ulong idx = BinarySearch(0, size - 1, dat);

        if (idx >= size || (*this)[idx] != dat) {
            if (idx < size / 2)
                Shift_sx(idx);

            else
                Shift_dx(idx);

            AccessNonConst_at(idx) = std::move(dat);
            size = size + 1;
            return true;
        }

        else
            return false;
    }


    template <typename Data>
    bool SetVec<Data>::Remove(const Data& dat) {
        if (size == 0)
            return false;

        else {
            ulong idx = BinarySearch(0, size - 1, dat);

            if (idx < size && (*this)[idx] == dat) {
                if (idx < size / 2)
                    Shift_sx_to_dx(idx);

                else
                    Shift_dx_to_sx(idx);

                size = size - 1;

                if (size < capacity / 2)
                    Reduce(capacity / 2);

                return true;
            }

            else
                return false;
        }
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    template <typename Data>
    const Data& SetVec<Data>::operator[](ulong i) const {
        if (i >= size)
            throw std::out_of_range("Index " + std::to_string(i) + " out of range");

        else
            return Elements[(Head + i) % capacity];
    }

    /* ************************************************************************ */

    // Specific member function (inherited from TestableContainer)

    template <typename Data>
    bool SetVec<Data>::Exists(const Data& dat) const noexcept {
        if (size == 0)
            return false;

        ulong idx = BinarySearch(0, size - 1, dat);

        if (idx < size && (*this)[idx] == dat)
            return true;

        else
            return false;
    }


    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    template <typename Data>
    void SetVec<Data>::Clear() {
        Vector<Data>::Clear();
        capacity = 0;
        Head = 0;
    }

    /* ************************************************************************ */

    // Auxiliary functions

    template <typename Data>
    ulong SetVec<Data>::BinarySearch(ulong i, ulong j, const Data& dat) const noexcept {
        if (i <= j) {
            ulong mid = i + (j - i) / 2;

            if ((*this)[mid] == dat)
                return mid;

            //Search in the right half
            else if ((*this)[mid] < dat)
                return BinarySearch(mid + 1, j, dat);


            //Search in the left half
            else {
                //prevent underflow (searching a data smaller than the minimum)
                if (mid == 0)
                    return 0;

                return BinarySearch(i, mid - 1, dat);
            }
        }

        else
            return i;
    }

    template<typename Data>
    void SetVec<Data>::Shift_sx(ulong idx) noexcept {
        Head = (Head == 0) ? capacity - 1 : Head - 1;
        for (ulong i = 0; i < idx; i++)
            AccessNonConst_at(i) = std::move((*this)[i + 1]);
    }

    template<typename Data>
    void SetVec<Data>::Shift_dx(ulong idx) noexcept {
        for (ulong i = size; i > idx; i--)
            AccessNonConst_at(i) = std::move((*this)[i - 1]);
    }


    template<typename Data>
    void SetVec<Data>::Shift_sx_to_dx(ulong idx) noexcept {
        for (ulong i = idx; i > 0; i--)
            AccessNonConst_at(i) = std::move((*this)[i - 1]);

        Head = Head + 1;

    }

    template<typename Data>
    void SetVec<Data>::Shift_dx_to_sx(ulong idx) noexcept {
        for (ulong i = idx; i < size - 1; i++)
            AccessNonConst_at(i) = std::move((*this)[i + 1]);
    }


    template<typename Data>
    void SetVec<Data>::Remove_at(ulong idx) {
        if (idx < size / 2)
            Shift_sx_to_dx(idx);

        else
            Shift_dx_to_sx(idx);

        size = size - 1;
    }


    template <typename Data>
    void SetVec<Data>::Expand(ulong new_capacity) {
        Data* new_Elements = new Data[new_capacity];

        for (ulong i = 0; i < size; i++)
            std::swap(new_Elements[i], AccessNonConst_at(i));

        delete[] Elements;
        Elements = new_Elements;
        capacity = new_capacity;
        Head = 0;
    }


    template <typename Data>
    void SetVec<Data>::Reduce(ulong new_capacity) {
        Data* new_Elements = new Data[new_capacity];

        ulong tmp_size = (size < new_capacity) ? size : new_capacity;
        for (ulong i = 0; i < tmp_size; i++)
            std::swap(new_Elements[i], AccessNonConst_at(i));

        delete[] Elements;
        Elements = new_Elements;
        capacity = new_capacity;
        size = tmp_size;
        Head = 0;
    }


}




