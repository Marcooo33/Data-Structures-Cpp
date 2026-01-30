namespace lasd {

    // Traversable Container Functions

    template <typename Data>
    template <typename Accumulator>
    Accumulator TraversableContainer<Data>::Fold(FoldFun<Data> fun, Accumulator acc) const {
        Traverse(
            [fun, &acc](const Data& dat) {
                acc = fun(dat, acc);
            }
        );

        return acc;
    }

    template <typename Data>
    bool TraversableContainer<Data>::Exists(const Data& val) const noexcept {
        bool res = false;
        Traverse(
            [val, &res](const Data& dat) {
                res |= (dat == val);
            }
        );
        return res;
    }


    /* ************************************************************************ */

    // Preorder Traversable Container Functions

    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Data> fun, Accumulator acc) const {
        PreOrderTraverse(
            [fun, &acc](const Data& dat) {
                acc = fun(dat, acc);
            }
        );

        return acc;
    }

    template <typename Data>
    void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
        PreOrderTraverse(fun);
    }

    /* ************************************************************************ */

    // Postorder Traversable Container Functions

    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Data> fun, Accumulator acc) const {
        PostOrderTraverse(
            [fun, &acc](const Data& dat) {
                acc = fun(dat, acc);
            }
        );

        return acc;
    }

    template <typename Data>
    void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
        PostOrderTraverse(fun);
    }

}
