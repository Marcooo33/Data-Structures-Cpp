
namespace lasd {

    // Dictionary container functions

    template <typename Data>
    bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& con) {  // Copy of container
        bool res = true;
        con.Traverse(
            [this, &res](const Data& dat) {
                res &= Insert(dat);
            }
        );

        return res;
    }


    template <typename Data>
    bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& con) {  //Move of container
        bool res = true;
        con.Map(
            [this, &res](Data& dat) {
                res &= Insert(std::move(dat));
            }
        );

        return res;
    }


    template <typename Data>
    bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& con) {
        bool res = true;
        con.Traverse(
            [this, &res](const Data& dat) {
                res &= Remove(dat);
            }
        );

        return res;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& con) {
        bool res = false;
        con.Traverse(
            [this, &res](const Data& dat) {
                res |= Insert(dat);
            }
        );

        return res;
    }


    template <typename Data>
    bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& con) {
        bool res = false;
        con.Traverse(
            [this, &res](const Data& dat) {
                res |= Insert(std::move(dat));
            }
        );

        return res;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& con) {
        bool res = false;
        con.Traverse(
            [this, &res](const Data& dat) {
                res |= Remove(dat);
            }
        );

        return res;

    }

}
