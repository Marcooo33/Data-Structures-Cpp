
namespace lasd {

    // LINEAR CONTAINER Comparison operators

    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer<Data>& con) const noexcept {
        if (this == &con) {
            return true;
        }

        if (size != con.size) {
            return false;
        }


        for (ulong i = 0; i < con.size; i++) {
            if (this->operator[](i) != con.operator[](i))
                return false;
        }
        return true;
    }


    template <typename Data>
    bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& con) const noexcept {
        return  !(*this == con);
    }

    /* ************************************************************************** */

    // LINEAR CONTAINER Functions

    template <typename Data>
    void LinearContainer<Data>::Traverse(TraverseFun fun) const {
        PreOrderTraverse(fun);
    }

    template <typename Data>
    void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
        for (ulong i = 0; i < size; i++)
            fun(operator[](i));
    }

    template <typename Data>
    void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
        for (ulong i = size; i > 0; i--)
            fun(operator[](i - 1));
    }

    template <typename Data>
    const Data& LinearContainer<Data>::Front() const {
        if (size == 0)
            throw std::length_error("Container is empty");

        else
            return operator[](0);
    }

    template <typename Data>
    const Data& LinearContainer<Data>::Back() const {
        if (size == 0)
            throw std::length_error("Container is empty");

        else
            return operator[](size - 1);
    }

    /* ************************************************************************** */


    //MUTABLE LINEAR CONTAINER Functions

    template <typename Data>
    void MutableLinearContainer<Data>::Map(MapFun fun) {
        PreOrderMap(fun);
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
        for (ulong i = 0; i < size; i++)
            fun(operator[](i));
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
        for (ulong i = size; i > 0; i--)
            fun(operator[](i - 1));
    }

    template <typename Data>
    Data& MutableLinearContainer<Data>::Front() {
        if (size == 0)
            throw std::length_error("Container is empty");

        else
            return operator[](0);
    }

    template <typename Data>
    Data& MutableLinearContainer<Data>::Back() {
        if (size == 0)
            throw std::length_error("Container is empty");
        else
            return operator[](size - 1);
    }

    /* ************************************************************************** */

    //SORTABLE LINEAR CONTAINER Functions

    //Insertion Sort  
    template <typename Data>
    void SortableLinearContainer<Data>::Sort() noexcept {
        for (ulong i = 1; i < size; i++) {
            Data key = this->operator[](i);
            ulong j = i;

            while (j > 0 && this->operator[](j - 1) > key) {
                this->operator[](j) = this->operator[](j - 1);
                j--;
            }
            this->operator[](j) = key;
        }
    }


}

