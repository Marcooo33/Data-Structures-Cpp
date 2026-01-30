
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class PQHeap : virtual public PQ<Data>, protected HeapVec<Data> {
    // Must extend PQ<Data>,
    // Could extend HeapVec<Data>

  private:

    // ...

  protected:

    using Container::size;
    ulong capacity = 0;
    using Vector<Data>::Elements;


    // ...

  public:
    using LinearContainer<Data>::operator[];
    using LinearContainer<Data>::Front;
    using LinearContainer<Data>::Back;

    // Default constructor
    inline PQHeap() : capacity(5) {
      Elements = new Data[capacity];
    }

    /* ************************************************************************ */

    // Specific constructors
    inline PQHeap(const TraversableContainer<Data>& con) : HeapVec<Data>(con), capacity(con.Size()) {}; // A priority queue obtained from a TraversableContainer
    inline PQHeap(MappableContainer<Data>&& con) : HeapVec<Data>(std::move(con)), capacity(con.Size()) {}; // A priority queue obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    inline PQHeap(const PQHeap& pqheap) : HeapVec<Data>(pqheap) {};

    // Move constructor
    inline PQHeap(PQHeap&& pqheap) noexcept : HeapVec<Data>(std::move(pqheap)) {};

    /* ************************************************************************ */

    // Destructor
    virtual ~PQHeap() = default;

    /* ************************************************************************ */

    // Copy assignment
    PQHeap& operator=(const PQHeap&);

    // Move assignment
    PQHeap& operator=(PQHeap&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const PQHeap<Data>& pqheap) const noexcept { return Vector<Data>::operator==(pqheap); };
    inline bool operator!=(const PQHeap<Data>& pqheap) const noexcept { return !(*this == pqheap); };

    /* ************************************************************************ */

    // Specific member functions (inherited from ClearableContainer)

    void Clear() override; // Override ClearableContainer member

    /* ************************************************************************ */


    // Specific member functions (inherited from PQ)

    inline const Data& Tip() const override { return Vector<Data>::Front(); }; // Override PQ member (must throw std::length_error when empty)
    void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
    Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

    void Insert(const Data&) override; // Override PQ member (Copy of the value)
    void Insert(Data&&) override; // Override PQ member (Move of the value)

    void Change(ulong, const Data&) override; // Override PQ member (Copy of the value)
    void Change(ulong, Data&&) override; // Override PQ member (Move of the value)

  protected:

    // Auxiliary functions, if necessary!

    void Expand(ulong);
    void Reduce(ulong);

  };

  /* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
