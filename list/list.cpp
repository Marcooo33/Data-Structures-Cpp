
namespace lasd {

    //Constructors (List)

    template<typename Data>
    List<Data>::List(const TraversableContainer<Data>& con) {
        con.Traverse(
            [this](const Data& dat) {
                this->InsertAtBack(dat);
            }
        );
    }


    template<typename Data>
    List<Data>::List(MappableContainer<Data>&& con) {
        con.Map(
            [this](Data& dat) {
                this->InsertAtBack(std::move(dat));
            }
        );
    }


    // Copy Constructor (List)

    template<typename Data>
    List<Data>::List(const List& list) {
        if (list.size != 0) {
            size = list.size;
            Head = new Node(*list.Head);
            Tail = Head;

            Node* curr = list.Head->next;
            for (ulong i = 1; i < list.size; i++, curr = curr->next) {
                Tail->next = new Node(*curr);
                Tail = Tail->next;
            }
        }

        else {
            size = 0;
            Head = Tail = nullptr;
        }
    }

    // Move Constructor (List)

    template<typename Data>
    List<Data>::List(List&& list) noexcept {
        std::swap(size, list.size);
        std::swap(Head, list.Head);
        std::swap(Tail, list.Tail);
    }


    //Destructor (List)

    template<typename Data>
    List<Data>::~List() {
        Node* curr = Head;
        for (ulong i = 0; i < size; i++) {
            Node* next_node = curr->next;
            delete curr;
            curr = next_node;
        }

        Head = Tail = nullptr;
    }


    // Copy assignment (List)   

    template<typename Data>
    List<Data>& List<Data>::operator=(const List& list) {
        Node* curr = Head;
        Node* other_curr = list.Head;
        ulong i;

        if (size == list.size) {
            for (i = 0; i < size; i++, curr = curr->next, other_curr = other_curr->next)
                curr->Element = other_curr->Element;
        }

        else if (size == 0) {
            Head = Tail = new Node(other_curr->Element);
            for (i = 1; i < list.size; i++) {
                other_curr = other_curr->next;
                Tail->next = new Node(other_curr->Element);
                Tail = Tail->next;
            }
        }

        else if (list.size == 0)
            Clear();

        else if (size < list.size) {
            for (i = 0; i < size; i++, curr = curr->next, other_curr = other_curr->next)
                curr->Element = other_curr->Element;

            for (i = 0; i < list.size - size; i++, other_curr = other_curr->next) {
                Node* new_node = new Node(other_curr->Element);
                Tail->next = new_node;
                Tail = new_node;
            }
        }

        else { // size > list.size
            for (i = 0; i < list.size; i++, Tail = curr, curr = curr->next, other_curr = other_curr->next)
                curr->Element = other_curr->Element;

            Tail->next = nullptr;

            for (i = 0; i < size - list.size; i++) {
                Node* next_node = curr->next;
                delete curr;
                curr = next_node;
            }
        }

        size = list.size;
        return *this;
    }


    //Move assignment (List)

    template<typename Data>
    List<Data>& List<Data>::operator=(List&& list) noexcept {
        std::swap(size, list.size);
        std::swap(Head, list.Head);
        std::swap(Tail, list.Tail);
        return *this;
    }


    // Comparison operators (List)

    template<typename Data>
    bool List<Data>::operator==(const List& list) const noexcept {
        if (this == &list)
            return true;

        else if (size != list.size)
            return false;

        else {
            Node* curr = Head;
            Node* other_curr = list.Head;
            for (ulong i = 0; i < size; i++, curr = curr->next, other_curr = other_curr->next) {
                if (curr->Element != other_curr->Element)
                    return false;
            }

            return true;
        }
    }

    template<typename Data>
    bool List<Data>::operator!=(const List& list) const noexcept {
        return !(*this == list);
    }


    /* ************************************************************************ */

     // Specific member functions (List)

    template<typename Data>
    void List<Data>::InsertAtFront(const Data& dat) {    // Copy of the value
        if (size == 0) {
            Node* new_node = new Node(dat);
            Head = Tail = new_node;
        }

        else {
            Node* new_node = new Node(dat);
            new_node->next = Head;
            Head = new_node;
        }

        size++;
    }

    template<typename Data>
    void List<Data>::InsertAtFront(Data&& dat) {    // Move of the value
        if (size == 0) {
            Node* new_node = new Node(std::move(dat));
            Head = Tail = new_node;
        }

        else {
            Node* new_node = new Node(std::move(dat));
            new_node->next = Head;
            Head = new_node;
        }

        size++;
    }

    template<typename Data>
    void List<Data>::RemoveFromFront() {
        if (size == 0)
            throw std::length_error("List is empty");

        else if (size == 1) {
            delete Head;
            Head = Tail = nullptr;
        }

        else {
            Node* new_head = Head->next;
            delete Head;
            Head = new_head;
        }

        size--;
    }


    template<typename Data>
    Data List<Data>::FrontNRemove() {
        if (size == 0)
            throw std::length_error("List is empty");

        else {
            Data elem = std::move(Head->Element);

            if (size == 1) {
                delete Head;
                Head = Tail = nullptr;
            }

            else {
                Node* new_head = Head->next;
                delete Head;
                Head = new_head;
            }

            size--;
            return elem;
        }
    }


    template<typename Data>
    void List<Data>::InsertAtBack(const Data& dat) {    // Copy of the value
        if (size == 0) {
            Node* new_node = new Node(dat);
            Head = Tail = new_node;
        }

        else {
            Node* new_node = new Node(dat);
            Tail->next = new_node;
            Tail = Tail->next;
        }

        size++;
    }

    template<typename Data>
    void List<Data>::InsertAtBack(Data&& dat) {     // Move of the value
        if (size == 0) {
            Node* new_node = new Node(std::move(dat));
            Head = Tail = new_node;
        }

        else {
            Node* new_node = new Node(std::move(dat));
            Tail->next = new_node;
            Tail = Tail->next;
        }

        size++;
    }


    template<typename Data>
    void List<Data>::RemoveFromBack() {
        if (size == 0)
            throw std::length_error("List is empty");

        else if (size == 1) {
            delete Tail;
            Head = Tail = nullptr;
        }

        else {
            delete Tail;
            Node* curr = Head;
            for (ulong i = 0; i < size - 2; i++, curr = curr->next) { ; }   //Reach the element before the tail
            curr->next = nullptr;
            Tail = curr;
        }

        size--;
    }

    template<typename Data>
    Data List<Data>::BackNRemove() {
        if (size == 0)
            throw std::length_error("List is empty");

        else {
            Data elem = std::move(Tail->Element);

            if (size == 1) {
                delete Tail;
                Head = Tail = nullptr;
            }

            else {
                delete Tail;
                Node* curr = Head;
                for (ulong i = 0; i < size - 2; i++, curr = curr->next) { ; }   //Reach the element before the tail
                curr->next = nullptr;
                Tail = curr;
            }

            size--;
            return elem;
        }
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)
    template<typename Data>
    const Data& List<Data>::operator[](ulong idx) const {
        if (idx >= size)
            throw std::out_of_range("Index " + std::to_string(idx) + " out of range");

        else {
            Node* curr = Head;
            for (ulong i = 0; i < idx; i++, curr = curr->next) { ; }     //Reach the element at index idx
            return curr->Element;
        }
    }

    template<typename Data>
    const Data& List<Data>::Front() const {
        if (size == 0)
            throw std::length_error("List is empty");

        else
            return Head->Element;
    }

    template<typename Data>
    const Data& List<Data>::Back() const {
        if (size == 0)
            throw std::length_error("List is empty");

        else
            return Tail->Element;
    }


    /* ************************************************************************ */

   // Specific member functions (inherited from MutableLinearContainer)

    template<typename Data>
    Data& List<Data>::operator[](ulong idx) {
        return const_cast<Data&>(static_cast<const List<Data> *> (this)->operator[](idx));
    }

    template <typename Data>
    Data& List<Data>::Front() {
        return const_cast<Data&>(static_cast<const List<Data> *> (this)->Front());
    }

    template <typename Data>
    Data& List<Data>::Back() {
        return const_cast<Data&>(static_cast<const List<Data> *> (this)->Back());
    }

    /* ************************************************************************ */

      // Specific member function (inherited from TraversableContainer)

    template <typename Data>
    void List<Data>::Traverse(TraverseFun fun) const {
        PreOrderTraverse(fun, Head);
    }

    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const {
        PreOrderTraverse(fun, Head);
    }

    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const {
        PostOrderTraverse(fun, Head);
    }

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    template <typename Data>
    void List<Data>::Map(MapFun fun) {
        PreOrderMap(fun, Head);
    }

    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun) {
        PreOrderMap(fun, Head);
    }

    template <typename Data>
    void List<Data>::PostOrderMap(MapFun fun) {
        PostOrderMap(fun, Head);
    }

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    template <typename Data>
    void List<Data>::Clear() {
        Node* curr = Head;
        for (ulong i = 0; i < size; i++) {
            Node* next_node = curr->next;
            delete curr;
            curr = next_node;
        }

        Head = Tail = nullptr;
        size = 0;
    }

    /* ************************************************************************ */

    // Auxiliary functions

    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun, const Node* curr) const {
        for (ulong i = 0; i < size; i++, curr = curr->next)
            fun(curr->Element);
    }

    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun, const Node* curr) const {
        if (curr != nullptr) {
            PostOrderTraverse(fun, curr->next);
            fun(curr->Element);
        }
    }

    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun, Node* curr) {
        for (ulong i = 0; i < size; i++, curr = curr->next)
            fun(curr->Element);
    }

    template <typename Data>
    void List<Data>::PostOrderMap(MapFun fun, Node* curr) {
        if (curr != nullptr) {
            PostOrderMap(fun, curr->next);
            fun(curr->Element);
        }
    }


}
