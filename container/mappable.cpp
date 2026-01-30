namespace lasd {

    // Preorder Mappable Container functions
    template <typename Data>
    void PreOrderMappableContainer<Data>::Map(MapFun fun) {
        PreOrderMap(fun);
    }

    /* ************************************************************************** */

    // Postorder Mappable Container functions
    template <typename Data>
    void PostOrderMappableContainer<Data>::Map(MapFun fun) {
        PostOrderMap(fun);
    }


}
