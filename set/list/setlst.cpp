
namespace lasd {

    // Specific Constructors 

    template<typename Data>
    SetLst<Data>::SetLst(const TraversableContainer<Data>& con) : SetLst<Data>() {
        con.Traverse(
            [this](const Data& dat) {
                this->Insert(dat);
            }
        );
    }

    template<typename Data>
    SetLst<Data>::SetLst(MappableContainer<Data>&& con) {
        con.Map(
            [this](Data& dat) {
                this->Insert(std::move(dat));
            }
        );
    }

    //Copy assignment 

    template<typename Data>
    SetLst<Data>& SetLst<Data>::operator=(const SetLst& slst) {
        List<Data>::operator=(slst);
        return *this;
    }


    // Move assignment

    template<typename Data>
    SetLst<Data>& SetLst<Data>::operator=(SetLst&& slst) noexcept {
        List<Data>::operator=(std::move(slst));
        return *this;
    }

    // Comparison operators

    template<typename Data>
    bool SetLst<Data>::operator==(const SetLst& slst) const noexcept {
        return List<Data>::operator==(slst);
    }

    template<typename Data>
    bool SetLst<Data>::operator!=(const SetLst& slst) const noexcept {
        return List<Data>::operator!=(slst);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from OrderedDictionaryContainer)

    template<typename Data>
    const Data& SetLst<Data>::Min() const {
        return List<Data>::Front();
    }

    template<typename Data>
    Data SetLst<Data>::MinNRemove() {
        return List<Data>::FrontNRemove();
    }

    template<typename Data>
    void SetLst<Data>::RemoveMin() {
        return List<Data>::RemoveFromFront();
    }

    /* ************************************************************************ */

    template<typename Data>
    const Data& SetLst<Data>::Max() const {
        return List<Data>::Back();
    }

    template<typename Data>
    Data SetLst<Data>::MaxNRemove() {
        return List<Data>::BackNRemove();
    }

    template<typename Data>
    void SetLst<Data>::RemoveMax() {
        return List<Data>::RemoveFromBack();
    }

    /* ************************************************************************ */

    template<typename Data>
    const Data& SetLst<Data>::Predecessor(const Data& dat) const {
        if (size == 0)
            throw std::length_error("Predecessor not found");

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (pred == nullptr)
            throw std::length_error("Predecessor not found");

        else
            return pred->Element;
    }

    template<typename Data>
    Data SetLst<Data>::PredecessorNRemove(const Data& dat) {
        if (size == 0)
            throw std::length_error("Predecessor not found");

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (pred == nullptr)
            throw std::length_error("Predecessor not found");

        else if (pred == Head)
            return List<Data>::FrontNRemove();

        else if (pred->next == nullptr)
            return List<Data>::BackNRemove();

        else {
            Data pred_elem = std::move(pred->Element);
            RemoveNode(pred);
            return pred_elem;
        }
    }


    template<typename Data>
    void SetLst<Data>::RemovePredecessor(const Data& dat) {
        if (size == 0)
            throw std::length_error("Predecessor not found");

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (pred == nullptr)
            throw std::length_error("Predecessor not found");

        else if (pred == Head)
            return List<Data>::RemoveFromFront();

        else if (pred->next == nullptr)
            return List<Data>::RemoveFromBack();

        else
            RemoveNode(pred);
    }

    /* ************************************************************************ */

    template<typename Data>
    const Data& SetLst<Data>::Successor(const Data& dat) const {
        if (size == 0)
            throw std::length_error("Successor not found");

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (curr == nullptr)
            throw std::length_error("Successor not found");

        //curr is the element found
        if (curr->Element == dat) {
            if (curr->next == nullptr)  //curr is the max element
                throw std::length_error("Successor not found");

            return curr->next->Element;
        }

        //curr is the successor
        else
            return curr->Element;
    }


    template<typename Data>
    Data SetLst<Data>::SuccessorNRemove(const Data& dat) {
        if (size == 0)
            throw std::length_error("Successor not found");

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (curr == nullptr)
            throw std::length_error("Successor not found");

        //curr is the element found
        if (curr->Element == dat) {
            if (curr->next == nullptr)  //curr is the max element
                throw std::length_error("Successor not found");

            Node* succ = curr->next;
            if (succ == Tail)
                return List<Data>::BackNRemove();

            else {
                Data succ_elem = succ->Element;
                RemoveNode(succ);
                return succ_elem;
            }

        }

        //curr is the successor
        else {
            if (curr == Head)
                return List<Data>::FrontNRemove();

            else if (curr == Tail)
                return List<Data>::BackNRemove();

            else {
                Data succ = curr->Element;
                RemoveNode(curr);
                return succ;
            }
        }
    }


    template<typename Data>
    void SetLst<Data>::RemoveSuccessor(const Data& dat) {
        if (size == 0)
            throw std::length_error("Successor not found");

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (curr == nullptr)
            throw std::length_error("Successor not found");

        //curr is the element found
        if (curr->Element == dat) {
            if (curr->next == nullptr)  // curr is the max element
                throw std::length_error("Successor not found");

            Node* succ = curr->next;
            if (succ == Tail)
                return List<Data>::RemoveFromBack();

            else
                RemoveNode(succ);

        }

        //curr is the successor
        else {
            if (curr == Head)
                return List<Data>::RemoveFromFront();

            else if (curr == Tail)
                return List<Data>::RemoveFromBack();

            else
                RemoveNode(curr);
        }
    }


    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    template<typename Data>
    bool SetLst<Data>::Insert(const Data& dat) {     // Copy of the value
        if (size == 0) {
            List<Data>::InsertAtFront(dat);
            return true;
        }

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (curr != nullptr && curr->Element == dat)
            return false;

        else if (pred == nullptr)
            List<Data>::InsertAtFront(dat);

        else if (curr == nullptr)
            List<Data>::InsertAtBack(dat);

        else {
            Node* new_node = new Node(dat);
            new_node->next = pred->next;
            pred->next = new_node;
            size++;
        }

        return true;
    }

    template<typename Data>
    bool SetLst<Data>::Insert(Data&& dat) {     // Move of the value
        if (size == 0) {
            List<Data>::InsertAtFront(std::move(dat));
            return true;
        }

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (curr != nullptr && curr->Element == dat)
            return false;

        else if (pred == nullptr)
            List<Data>::InsertAtFront(std::move(dat));

        else if (curr == nullptr)
            List<Data>::InsertAtBack(std::move(dat));

        else {
            Node* new_node = new Node(std::move(dat));
            new_node->next = pred->next;
            pred->next = new_node;
            size++;
        }

        return true;
    }


    template<typename Data>
    bool SetLst<Data>::Remove(const Data& dat) {
        if (size == 0)
            return false;

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (curr != nullptr && curr->Element == dat) {
            if (pred == nullptr)
                List<Data>::RemoveFromFront();

            else if (curr->next == nullptr)
                List<Data>::RemoveFromBack();

            else {
                pred->next = curr->next;
                delete curr;
                size--;
            }

            return true;
        }

        else
            return false;

    }


    /* ************************************************************************ */

    template<typename Data>
    const Data& SetLst<Data>::operator[](ulong i) const {
        return List<Data>::operator[](i);
    }

    template<typename Data>
    bool SetLst<Data>::Exists(const Data& dat) const noexcept {
        if (size == 0)
            return false;

        ResetReferences();
        BinarySearch(0, size - 1, dat);

        if (curr != nullptr && curr->Element == dat)
            return true;

        else
            return false;
    }


    template <typename Data>
    void SetLst<Data>::Clear() {
        return List<Data>::Clear();
    }


    /* ************************************************************************ */

    // Auxiliary functions, if necessary!

    template <typename Data>
    void SetLst<Data>::ResetReferences() const noexcept {
        pred = nullptr;
        curr = Head;
        start = Head;
        idx_start = 0;
    }

    template<typename Data>
    void SetLst<Data>::MoveNode(ulong idx_final) const {
        for (ulong i = idx_start; i < idx_final && curr != nullptr; i++) {
            pred = curr;
            curr = curr->next;
        }
    }


    template<typename Data>
    void SetLst<Data>::BinarySearch(ulong i, ulong j, const Data& dat) const noexcept {
        if (i <= j) {
            Node* temp_pred = pred;
            ulong mid = i + (j - i) / 2;
            MoveNode(mid);

            if (curr->Element == dat)
                return;

            // search in the right half
            else if (curr->Element < dat) {
                pred = curr;
                start = curr = curr->next;
                idx_start = mid + 1;
                return BinarySearch(mid + 1, j, dat);
            }

            // search in the left half
            else {
                // prevent underflow (searching a data smaller than the minimum)
                if (mid == 0) {
                    ResetReferences();
                    return;
                }

                pred = temp_pred;
                curr = start;
                idx_start = i;
                return BinarySearch(i, mid - 1, dat);
            }
        }

    }


    template<typename Data>
    void SetLst<Data>::RemoveNode(Node*& nodeToRemove) {
        Node* predecessor = Head;
        for (; predecessor != nullptr && predecessor->next != nodeToRemove; predecessor = predecessor->next) { ; }  // Reach the predecessor of the node to remove
        predecessor->next = nodeToRemove->next;

        delete nodeToRemove;
        size--;
    }


}
