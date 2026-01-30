namespace lasd {

    // Specific constructors (Vector)

    template <typename Data>
    Vector<Data>::Vector(const unsigned long dim) {
        size = dim;
        Elements = new Data[dim];
    }


    template <typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data>& con) {
        size = con.Size();
        Elements = new Data[size];

        unsigned long i = 0;
        con.Traverse(
            [this, &i](const Data& dat) {
                Elements[i] = dat;
                i++;
            }
        );
    }

    template<typename Data>
    Vector<Data>::Vector(MappableContainer<Data>&& con) {
        size = con.Size();
        Elements = new Data[size];

        unsigned long i = 0;
        con.Map(
            [this, &i](Data& dat) {
                Elements[i] = std::move(dat);
                i++;
            }
        );
    }


    // Copy constructor (Vector)

    template <typename Data>
    Vector<Data>::Vector(const Vector& vec) {
        size = vec.size;
        Elements = new Data[size];
        for (unsigned int i = 0; i < size; i++)
            Elements[i] = vec.Elements[i];
    }


    // Move constructor (Vector)

    template <typename Data>
    Vector<Data>::Vector(Vector&& vec) noexcept {
        std::swap(size, vec.size);
        std::swap(Elements, vec.Elements);
    }


    // Destructor (Vector)

    template <typename Data>
    Vector<Data>::~Vector() {
        delete[] Elements;
        Elements = nullptr;
    }


    /* ************************************************************************ */


    // Copy assignment (Vector)

    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector& vec) {
        Vector<Data> tmp(vec);
        std::swap(size, tmp.size);
        std::swap(Elements, tmp.Elements);

        return *this;
    }

    // Move assignment (Vector)

    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector&& vec) noexcept {
        std::swap(size, vec.size);
        std::swap(Elements, vec.Elements);

        return *this;
    }

    /* ************************************************************************ */


    // Comparison operators (Vector)

    template <typename Data>
    bool Vector<Data>::operator==(const Vector& vec) const noexcept {
        if (this == &vec)
            return true;

        else if (size != vec.size)
            return false;

        else {
            for (unsigned int i = 0; i < size; i++)
                if (Elements[i] != vec.Elements[i])
                    return false;

            return true;
        }
    }

    template <typename Data>
    bool Vector<Data>::operator!=(const Vector& vec) const noexcept {
        return !(*this == vec);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    template <typename Data>
    const Data& Vector<Data>::operator[](unsigned long i) const {
        if (i >= size)
            throw std::out_of_range("Index " + std::to_string(i) + " out of range");

        else
            return Elements[i];
    }


    template <typename Data>
    const Data& Vector<Data>::Front() const {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else
            return Elements[0];
    }

    template <typename Data>
    const Data& Vector<Data>::Back() const {
        if (size == 0)
            throw std::length_error("Vector is empty");

        else
            return Elements[size - 1];
    }

    /* ************************************************************************ */

     // Specific member functions (inherited from MutableLinearContainer)

    template <typename Data>
    Data& Vector<Data>::operator[](unsigned long i) {
        return const_cast<Data&>(static_cast<const Vector<Data>*> (this)->operator[](i));
    }

    template <typename Data>
    Data& Vector<Data>::Front() {
        return const_cast<Data&>(static_cast<const Vector<Data>*> (this)->Front());
    }

    template <typename Data>
    Data& Vector<Data>::Back() {
        return const_cast<Data&>(static_cast<const Vector<Data>*> (this)->Back());
    }

    /* ************************************************************************ */


    // Specific member function (inherited from ResizableContainer)

    template <typename Data>
    void Vector<Data>::Resize(unsigned long new_size) {
        if (new_size == 0)
            Clear();

        else if (size == new_size)
            return;

        else {
            Data* tmp_elements = new Data[new_size];

            unsigned long tmp_size = (size < new_size) ? size : new_size;
            for (unsigned long i = 0; i < tmp_size; i++)
                std::swap(Elements[i], tmp_elements[i]);

            delete[] Elements;
            Elements = tmp_elements;
            size = new_size;
        }
    }

    template <typename Data>
    void Vector<Data>::Clear() {
        delete[] Elements;
        Elements = nullptr;
        size = 0;
    }


    /* ************************************************************************ */

    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector& sort_vec) {
        Vector<Data>::operator=(sort_vec);
        return *this;
    }

    // Move assignment (Sortable Vector)

    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector&& sort_vec) noexcept {
        Vector<Data>::operator=(std::move(sort_vec));
        return *this;
    }

}