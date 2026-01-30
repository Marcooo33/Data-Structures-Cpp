
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class SetLst : virtual public Set<Data>, virtual protected List<Data> {
    // Must extend Set<Data>,
    //             List<Data>

  private:

    // ...

  protected:

    using Container::size;
    using typename List<Data>::Node;
    using List<Data>::Head;
    using List<Data>::Tail;

    // ...

  public:

    using List<Data>::Traverse;
    using List<Data>::PreOrderTraverse;
    using List<Data>::PostOrderTraverse;


    // Default constructor
    SetLst() = default;

    /* ************************************************************************ */

    // Specific constructors
    SetLst(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
    SetLst(MappableContainer<Data>&&); // A set obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    inline SetLst(const SetLst& slst) : List<Data>(slst) {};

    // Move constructor
    inline SetLst(SetLst&& slst) noexcept : List<Data>(std::move(slst)) {};

    /* ************************************************************************ */

    // Destructor
    ~SetLst() = default;

    /* ************************************************************************ */

    // Copy assignment
    SetLst& operator=(const SetLst&);

    // Move assignment
    SetLst& operator=(SetLst&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const SetLst&) const noexcept;
    bool operator!=(const SetLst&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from OrderedDictionaryContainer)

    const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

    const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
    bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
    bool Remove(const Data&) override; // Override DictionaryContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    const Data& operator[](unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

    /* ************************************************************************** */

    // Specific member function (inherited from TestableContainer)

    bool Exists(const Data&) const noexcept override; // Override TestableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() override; // Override ClearableContainer member

  protected:

    // Auxiliary functions, if necessary!

    mutable Node* pred = nullptr;
    mutable Node* curr = Head;
    mutable Node* start = Head;
    mutable unsigned long idx_start = 0;

    void ResetReferences() const noexcept;
    void MoveNode(unsigned long) const;
    void BinarySearch(unsigned long, unsigned long, const Data&) const noexcept; // If data exists, curr points to the node containing the data, otherwise curr points to the node containing the data’s successor. pred always points to the node containing the data’s predecessor.
    void RemoveNode(Node*&);



  };

  /* ************************************************************************** */

}

#include "setlst.cpp"

#endif
