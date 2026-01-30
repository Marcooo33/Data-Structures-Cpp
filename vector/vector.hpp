
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class Vector : virtual public MutableLinearContainer<Data>, virtual public ResizableContainer {
    // Must extend MutableLinearContainer<Data>,
    //             ResizableContainer

  private:

    // ...

  protected:

    using Container::size;
    Data* Elements = nullptr;

    // ...

  public:

    // Default constructor
    Vector() = default;

    /* ************************************************************************ */

    // Specific constructors
    Vector(const ulong); // A vector with a given initial dimension
    Vector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
    Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    Vector(const Vector&);

    // Move constructor
    Vector(Vector&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~Vector();

    /* ************************************************************************ */

    // Copy assignment
    Vector& operator=(const Vector&);

    // Move assignment
    Vector& operator=(Vector&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const Vector&) const noexcept;
    bool operator!=(const Vector&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from MutableLinearContainer)

    Data& operator[](ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

    Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

    Data& Back() override;// Override MutableLinearContainer member (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    const Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

    const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

    const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member function (inherited from ResizableContainer)

    void Resize(ulong) override; // Override ResizableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() override;// Override ClearableContainer member

  protected:

    // Auxiliary functions, if necessary!

  };

  /* ************************************************************************** */

  template <typename Data>
  class SortableVector : public Vector<Data>, virtual public SortableLinearContainer<Data> {
    // Must extend Vector<Data>,
    //             SortableLinearContainer<Data>

  private:

    // ...

  protected:

    // ...

  public:

    // Default constructor
    SortableVector() = default;

    /* ************************************************************************ */

    // Specific constructors
    inline SortableVector(const ulong dim) : Vector<Data>(dim) {}; // A vector with a given initial dimension
    inline SortableVector(const TraversableContainer<Data>& con) : Vector<Data>(con) {}; // A vector obtained from a TraversableContainer
    inline SortableVector(MappableContainer<Data>&& con) : Vector<Data>(std::move(con)) {}; // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    inline SortableVector(const SortableVector& sort_vec) : Vector<Data>(sort_vec) {};

    // Move constructor
    inline SortableVector(SortableVector&& sort_vec) noexcept : Vector<Data>(std::move(sort_vec)) {};

    /* ************************************************************************ */

    // Destructor
    ~SortableVector() = default;

    /* ************************************************************************ */

    // Copy assignment
    SortableVector& operator=(const SortableVector& sort_vec);

    // Move assignment
    SortableVector& operator=(SortableVector&&) noexcept;

  protected:

    // Auxiliary functions, if necessary! 

  };

  /* ************************************************************************** */

}

#include "vector.cpp"

#endif
