
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class HeapVec : virtual public Heap<Data>, protected SortableVector<Data> {
    // Must extend Heap<Data>,
    // Could extend Vector<Data>

  private:

    // ...

  protected:

    using Container::size;
    using Vector<Data>::Elements;

    // ...

  public:

    using LinearContainer<Data>::operator[];
    using LinearContainer<Data>::Front;
    using LinearContainer<Data>::Back;
    using Vector<Data>::Clear;


    // Default constructor
    HeapVec() = default;

    /* ************************************************************************ */

    // Specific constructors
    inline HeapVec(const TraversableContainer<Data>& con) : SortableVector<Data>(con) { Heapify(); };    // A heap obtained from a TraversableContainer
    inline HeapVec(MappableContainer<Data>&& con) : SortableVector<Data>(std::move(con)) { Heapify(); };    // A heap obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    inline HeapVec(const HeapVec<Data>& heap) : SortableVector<Data>(heap) {};

    // Move constructor
    inline HeapVec(HeapVec<Data>&& heap) : SortableVector<Data>(std::move(heap)) {};

    /* ************************************************************************ */

    // Destructor
    virtual ~HeapVec() = default;

    /* ************************************************************************ */

    // Copy assignment
    HeapVec<Data>& operator=(const HeapVec<Data>&);

    // Move assignment
    HeapVec<Data>& operator=(HeapVec<Data>&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const HeapVec<Data>& heap) const noexcept { return Vector<Data>::operator==(heap); };
    inline  bool operator!=(const HeapVec<Data>& heap) const noexcept { return !(*this == heap); };

    /* ************************************************************************ */

    // Specific member functions (inherited from Heap)

    bool IsHeap() const noexcept override; // Override Heap member

    void Heapify() noexcept override; // Override Heap member  

    /* ************************************************************************ */

    // Specific member function (inherited from SortableLinearContainer)

    void Sort() noexcept override; // Override SortableLinearContainer member


  protected:

    // Auxiliary functions, if necessary!

    void HeapifyToDown(ulong) noexcept;
    void HeapifyToUp(ulong) noexcept;

  };

  /* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
