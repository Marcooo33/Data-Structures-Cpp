#include <iostream>

#include "../heap/heap.hpp"
#include "../heap/vec/heapvec.hpp"
#include "../priority_queue/pq.hpp"
#include "../priority_queue/heap/pqheap.hpp"
#include "../vector/vector.hpp"
#include "test.hpp"

#include "../set/set.hpp"
#include "../set/vector/setvec.hpp"
#include "../set/list/setlst.hpp"


using namespace std;
using namespace lasd;

namespace mytests {
  template <typename Data>
  void printElement(const Data& dat) { cout << dat << " "; }

  template <typename Data>
  Data foldFunction(const Data& dat, const Data& acc) { return acc + dat; }

  template <typename Data>
  void modifyElement(Data& dat) { dat += dat; }

  template <typename Data>
  bool IsSorted(const HeapVec<Data>& heap) {
    for (unsigned long i = 0; i < heap.Size() - 1; i++) {
      if (heap[i] > heap[i + 1])
        return false;
    }
    return true;
  }


  // HeapVec tests for int
  void test_HeapVec_Constructors_Int(unsigned int& failedTests) {
    cout << "\nTesting HeapVec<int> constructors...\n";
    HeapVec<int> heap1;
    if (!heap1.Empty())
      cout << "  Test 1: Default constructor - Error! (Empty: " << heap1.Empty() << ", Size: " << heap1.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Default constructor - Correct!\n";

    Vector<int> vec(10);
    vec[0] = 2; vec[1] = 4; vec[2] = 3; vec[3] = 3; vec[4] = 1; vec[5] = 9; vec[6] = 7; vec[7] = 6; vec[8] = 5; vec[9] = 8;
    HeapVec<int> heap2(vec);
    if (heap2.Size() != 10 || !heap2.IsHeap())
      cout << "  Test 2: Constructor from TraversableContainer - Error! (Size: " << heap2.Size() << ")\n", failedTests++;
    else {
      cout << "  Test 2: Constructor from TraversableContainer - Correct! (heap2: "; heap2.Traverse(printElement<int>); cout << ")\n";
    }

    Vector<int> vec2(10);
    vec[0] = 3; vec[1] = 1; vec[2] = 7; vec[3] = 9; vec[4] = 10; vec[5] = 9; vec[6] = 7; vec[7] = 2; vec[8] = 5; vec[9] = 8;
    HeapVec<int> heap3(move(vec2));
    if (heap3.Size() != 10 || !heap3.IsHeap())
      cout << "  Test 3: Constructor from MappableContainer - Error! (Size: " << heap3.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: Constructor from MappableContainer - Correct!\n";

    HeapVec<int> heap4(heap3);
    if (heap4.Size() != heap3.Size() || !heap4.IsHeap())
      cout << "  Test 4: Copy constructor - Error! (Size: " << heap4.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: Copy constructor - Correct!\n";

    HeapVec<int> heap5(move(heap4));
    if (heap5.Size() != 10 || !heap4.Empty())
      cout << "  Test 5: Move constructor - Error! (heap5 Size: " << heap5.Size() << ", heap4 Empty: " << heap4.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 5: Move constructor - Correct!\n";

    HeapVec<int> heap6;
    heap6 = heap3;
    if (heap6.Size() != heap3.Size() || !heap6.IsHeap())
      cout << "  Test 6: Copy assignment - Error! (Size: " << heap6.Size() << ")\n", failedTests++;
    else
      cout << "  Test 6: Copy assignment - Correct!\n";

    HeapVec<int> heap7;
    heap7 = move(heap6);
    if (heap7.Size() != 10 || !heap6.Empty())
      cout << "  Test 7: Move assignment - Error! (heap7 Size: " << heap7.Size() << ", heap6 Empty: " << heap6.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 7: Move assignment - Correct!\n";

    heap7.Clear();
    if (!heap7.Empty())
      cout << "  Test 8: Clear - Error! (heap7 Size: " << heap7.Size() << ")\n", failedTests++;
    else
      cout << "  Test 8: Clear - Correct!\n";


    heap2.Sort();
    if (!IsSorted(heap2)) {
      cout << "  Test 9: Sort - Error! (heap2 is not sorted "; heap2.Traverse(printElement<int>); cout << ")\n"; failedTests++;
    }
    else {
      cout << "  Test 9: Sort - Correct! (heap2 is sorted: "; heap2.Traverse(printElement<int>); cout << ")\n";
    }
  }

  void test_HeapVec_MapTraverse_Int(unsigned int& failedTests) {
    cout << "\nTesting HeapVec<int> map and traverse...\n";
    Vector<int> vec(5);
    vec[0] = 2; vec[1] = 4; vec[2] = 3; vec[3] = 3; vec[4] = 1;
    HeapVec<int> heap(vec);

    cout << "  Heap start: ";
    heap.Traverse(printElement<int>);
    cout << "\n";

    heap.PreOrderMap(modifyElement<int>);
    if (!heap.IsHeap())
      cout << "  Test 1: PreOrderMap - Error! (It's not heap anymore)\n", failedTests++;
    else
      cout << "  Test 1: PreOrderMap - Correct!\n";

    heap.PostOrderMap(modifyElement<int>);
    if (!heap.IsHeap())
      cout << "  Test 2: PostOrderMap - Error! (It's not heap anymore)\n", failedTests++;
    else
      cout << "  Test 2: PostOrderMap - Correct!\n";

    cout << "  Test 3: PreOrderTraverse output: ";
    heap.PreOrderTraverse(printElement<int>);
    cout << "- Correct!\n";

    cout << "  Test 4: PostOrderTraverse output: ";
    heap.PostOrderTraverse(printElement<int>);
    cout << "- Correct!\n";

    int sum = heap.Fold(foldFunction<int>, 0);
    if (sum != 52)
      cout << "  Test 5: Fold - Error! (Sum: " << sum << ", Expected: 52)\n", failedTests++;
    else
      cout << "  Test 5: Fold - Correct! (Sum: " << sum << ")\n";
  }


  // HeapVec tests for double
  void test_HeapVec_Constructors_Double(unsigned int& failedTests) {
    cout << "\nTesting HeapVec<double> constructors...\n";
    HeapVec<double> heap1;
    if (!heap1.Empty())
      cout << "  Test 1: Default constructor - Error! (Empty: " << heap1.Empty() << ", Size: " << heap1.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Default constructor - Correct!\n";

    Vector<double> vec(10);
    vec[0] = 4.4; vec[1] = 2.6; vec[2] = 2.3; vec[3] = 3.7; vec[4] = 1.1; vec[5] = 9.9; vec[6] = 7.5; vec[7] = 6.9; vec[8] = 5.2; vec[9] = 8.1;
    HeapVec<double> heap2(vec);
    if (heap2.Size() != 10 || !heap2.IsHeap())
      cout << "  Test 2: Constructor from TraversableContainer - Error! (Size: " << heap2.Size() << ")\n", failedTests++;
    else {
      cout << "  Test 2: Constructor from TraversableContainer - Correct! (heap2: "; heap2.Traverse(printElement<double>); cout << ")\n";
    }

    Vector<double> vec2(10);
    vec2[0] = 4.4; vec2[1] = 6.2; vec[2] = 3.2; vec[3] = 7.3; vec[4] = 1.1; vec[5] = 9.9; vec[6] = 5.7; vec[7] = 9.6; vec[8] = 2.5; vec[9] = 0.8;
    HeapVec<double> heap3(move(vec2));
    if (heap3.Size() != 10 || !heap3.IsHeap())
      cout << "  Test 3: Constructor from MappableContainer - Error! (Size: " << heap3.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: Constructor from MappableContainer - Correct!\n";

    HeapVec<double> heap4(heap3);
    if (heap4.Size() != heap3.Size() || !heap4.IsHeap())
      cout << "  Test 4: Copy constructor - Error! (Size: " << heap4.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: Copy constructor - Correct!\n";

    HeapVec<double> heap5;
    heap5 = heap3;
    if (heap5.Size() != heap3.Size() || !heap5.IsHeap())
      cout << "  Test 5: Copy assignment - Error! (Size: " << heap5.Size() << ")\n", failedTests++;
    else
      cout << "  Test 5: Copy assignment - Correct!\n";

    HeapVec<double> heap6;
    heap6 = move(heap5);
    if (heap6.Size() != 10 || !heap5.Empty())
      cout << "  Test 6: Move assignment - Erorre! (heap6 Size: " << heap6.Size() << ", heap5 Empty: " << heap5.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 6: Move assignment - Correct!\n";

    HeapVec<double> heap7(move(heap4));
    if (heap7.Size() != 10 || !heap4.Empty())
      cout << "  Test 7: Move constructor - Error! (heap7 Size: " << heap7.Size() << ", heap4 Empty: " << heap4.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 7: Move constructor - Correct!\n";

    heap7.Clear();
    if (!heap7.Empty())
      cout << "  Test 8: Clear - Error! (heap7 Size: " << heap7.Size() << ")\n", failedTests++;
    else
      cout << "  Test 8: Clear - Correct!\n";

    heap2.Sort();
    if (!IsSorted(heap2)) {
      cout << "  Test 9: Sort - Error! (heap2 is not sorted "; heap2.Traverse(printElement<double>); cout << ")\n"; failedTests++;
    }
    else {
      cout << "  Test 9: Sort - Correct! (heap2 is sorted: "; heap2.Traverse(printElement<double>); cout << ")\n";
    }
  }

  void test_HeapVec_MapTraverse_Double(unsigned int& failedTests) {
    cout << "\nTesting HeapVec<double> map and traverse...\n";
    Vector<double> vec(5);
    vec[0] = 2.5; vec[1] = 4.1; vec[2] = 3.7; vec[3] = 7.7; vec[4] = 1.2;
    HeapVec<double> heap(vec);

    cout << "  Heap start: ";
    heap.Traverse(printElement<double>);
    cout << "\n";

    heap.PreOrderMap(modifyElement<double>);
    if (!heap.IsHeap())
      cout << "  Test 1: PreOrderMap - Error! (It's not heap anymore)\n", failedTests++;
    else
      cout << "  Test 1: PreOrderMap - Correct!\n";

    heap.PostOrderMap(modifyElement<double>);
    if (!heap.IsHeap())
      cout << "  Test 2: PostOrderMap - Error! (It's not heap anymore)\n", failedTests++;
    else
      cout << "  Test 2: PostOrderMap - Correct!\n";


    cout << "  Test 3: PreOrderTraverse output: ";
    heap.PreOrderTraverse(printElement<double>);
    cout << "- Correct!\n";

    cout << "  Test 4: PostOrderTraverse output: ";
    heap.PostOrderTraverse(printElement<double>);
    cout << "- Correct!\n";

    double sum = heap.Fold(foldFunction<double>, 0.0);
    if (sum != 76.8)
      cout << "  Test 5: Fold - Error! (Sum: " << sum << ", Expected: 76.8)\n", failedTests++;
    else
      cout << "  Test 5: Fold - Correct! (Sum: " << sum << ")\n";
  }


  // HeapVec tests for string
  void test_HeapVec_Constructors_String(unsigned int& failedTests) {
    cout << "\nTesting HeapVec<string> constructors...\n";
    HeapVec<string> heap1;
    if (!heap1.Empty())
      cout << "  Test 1: Default constructor - Error! (Empty: " << heap1.Empty() << ", Size: " << heap1.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Default constructor - Correct!\n";

    Vector<string> vec(10);
    vec[0] = "D"; vec[1] = "B"; vec[2] = "J"; vec[3] = "C"; vec[4] = "A"; vec[5] = "F"; vec[6] = "G"; vec[7] = "E"; vec[8] = "H"; vec[9] = "I";
    HeapVec<string> heap2(vec);
    if (heap2.Size() != 10 || !heap2.IsHeap())
      cout << "  Test 2: Constructor from TraversableContainer - Error! (Size: " << heap2.Size() << ")\n", failedTests++;
    else {
      cout << "  Test 2: Constructor from TraversableContainer - Correct! (heap2: "; heap2.Traverse(printElement<string>); cout << ")\n";
    }

    Vector<string> vec2(10);
    vec[0] = "B"; vec[1] = "J"; vec[2] = "I"; vec[3] = "D"; vec[4] = "H"; vec[5] = "A"; vec[6] = "E"; vec[7] = "F"; vec[8] = "C"; vec[9] = "G";
    HeapVec<string> heap3(move(vec2));
    if (heap3.Size() != 10 || !heap3.IsHeap())
      cout << "  Test 3: Constructor from MappableContainer - Error! (Size: " << heap3.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: Constructor from MappableContainer - Correct!\n";

    HeapVec<string> heap4(heap3);
    if (heap4.Size() != heap3.Size() || !heap4.IsHeap())
      cout << "  Test 4: Copy constructor - Error! (Size: " << heap4.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: Copy constructor - Correct!\n";

    HeapVec<string> heap5(move(heap4));
    if (heap5.Size() != 10 || !heap4.Empty())
      cout << "  Test 5: Move constructor - Error! (heap5 Size: " << heap5.Size() << ", heap4 Empty: " << heap4.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 5: Move constructor - Correct!\n";

    HeapVec<string> heap6;
    heap6 = heap3;
    if (heap6.Size() != heap3.Size() || !heap6.IsHeap())
      cout << "  Test 6: Copy assignment - Error! (Size: " << heap6.Size() << ")\n", failedTests++;
    else
      cout << "  Test 6: Copy assignment - Correct!\n";

    HeapVec<string> heap7;
    heap7 = move(heap6);
    if (heap7.Size() != 10 || !heap6.Empty())
      cout << "  Test 7: Move assignment - Error! (heap7 Size: " << heap7.Size() << ", heap6 Empty: " << heap6.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 7: Move assignment - Correct!\n";

    heap7.Clear();
    if (!heap7.Empty())
      cout << "  Test 8: Clear - Error! (heap7 Size: " << heap7.Size() << ")\n", failedTests++;
    else
      cout << "  Test 8: Clear - Correct!\n";

    heap2.Sort();
    if (!IsSorted(heap2)) {
      cout << "  Test 9: Sort - Error! (heap2 is not sorted "; heap2.Traverse(printElement<string>); cout << ")\n"; failedTests++;
    }
    else {
      cout << "  Test 9: Sort - Correct! (heap2 is sorted: "; heap2.Traverse(printElement<string>); cout << ")\n";
    }
  }

  void test_HeapVec_MapTraverse_String(unsigned int& failedTests) {
    cout << "\nTesting HeapVec<string> map and traverse...\n";
    Vector<string> vec(3);
    vec[0] = "A"; vec[1] = "B"; vec[2] = "C";
    HeapVec<string> heap(vec);

    cout << "  Heap start: ";
    heap.PreOrderTraverse(printElement<string>);
    cout << "\n";

    heap.PreOrderMap(modifyElement<string>);
    if (!heap.IsHeap())
      cout << "  Test 1: PreOrderMap - Error! (It's not heap anymore)\n", failedTests++;
    else
      cout << "  Test 1: PreOrderMap - Correct!\n";

    heap.PostOrderMap(modifyElement<string>);
    if (!heap.IsHeap())
      cout << "  Test 2: PostOrderMap - Error! (It's not heap anymore)\n", failedTests++;
    else
      cout << "  Test 2: PostOrderMap - Correct!\n";

    string sum = heap.Fold(foldFunction<string>, string(""));
    if (sum != "CCCCBBBBAAAA" && sum != "CCCCAAAABBBB")
      cout << "  Test 3: Fold - Error! (Sum: " << sum << ", Expected: CCCCBBBBAAAA or CCCCAAAABBBB)\n", failedTests++;
    else
      cout << "  Test 3: Fold - Correct! (Sum: " << sum << ")\n";

    cout << "  Test 4: PreOrderTraverse output: ";
    heap.PreOrderTraverse(printElement<string>);
    cout << "- Correct!\n";

    cout << "  Test 5: PostOrderTraverse output: ";
    heap.PostOrderTraverse(printElement<string>);
    cout << "- Correct!\n";
  }


  // PQHeap tests for int
  void test_PQHeap_Constructors_Int(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<int> constructors...\n";
    PQHeap<int> pq1;
    if (!pq1.Empty())
      cout << "  Test 1: Default constructor - Error! (Empty: " << pq1.Empty() << ", Size: " << pq1.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Default constructor - Correct!\n";

    Vector<int> vec(10);
    vec[0] = 2; vec[1] = 4; vec[2] = 3; vec[3] = 3; vec[4] = 1; vec[5] = 9; vec[6] = 7; vec[7] = 6; vec[8] = 5; vec[9] = 8;
    PQHeap<int> pq2(vec);
    if (pq2.Size() != 10)
      cout << "  Test 2: Constructor from TraversableContainer - Error! (Size: " << pq2.Size() << ")\n", failedTests++;
    else {
      cout << "  Test 2: Constructor from TraversableContainer - Correct!\n";
    }

    Vector<int> vec2(10);
    vec[0] = 3; vec[1] = 1; vec[2] = 7; vec[3] = 9; vec[4] = 10; vec[5] = 9; vec[6] = 7; vec[7] = 2; vec[8] = 5; vec[9] = 8;
    PQHeap<int> pq3(move(vec2));
    if (pq3.Size() != 10)
      cout << "  Test 3: Constructor from MappableContainer - Error! (Size: " << pq3.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: Constructor from MappableContainer - Correct!\n";

    PQHeap<int> pq4(pq3);
    if (pq4.Size() != pq3.Size())
      cout << "  Test 4: Copy constructor - Error! (Size: " << pq4.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: Copy constructor - Correct!\n";

    PQHeap<int> pq5(move(pq4));
    if (pq5.Size() != 10 || !pq4.Empty())
      cout << "  Test 5: Move constructor - Error! (pq5 Size: " << pq5.Size() << ", pq4 Empty: " << pq4.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 5: Move constructor - Correct!\n";

    PQHeap<int> pq6;
    pq6 = pq3;
    if (pq6.Size() != pq3.Size())
      cout << "  Test 6: Copy assignment - Error! (Size: " << pq6.Size() << ")\n", failedTests++;
    else
      cout << "  Test 6: Copy assignment - Correct!\n";

    PQHeap<int> pq7;
    pq7 = move(pq6);
    if (pq7.Size() != 10 || !pq6.Empty())
      cout << "  Test 7: Move assignment - Error! (pq7 Size: " << pq7.Size() << ", pq6 Empty: " << pq6.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 7: Move assignment - Correct!\n";

    pq7.Clear();
    if (!pq7.Empty())
      cout << "  Test 8: Clear - Error! (pq7 Size: " << pq7.Size() << ")\n", failedTests++;
    else
      cout << "  Test 8: Clear - Correct!\n";
  }

  void test_PQHeap_Traverse_Int(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<int> traverse and fold...\n";
    PQHeap<int> pq;
    pq.Insert(2); pq.Insert(4); pq.Insert(3); pq.Insert(3); pq.Insert(1);

    cout << "  PQ start: ";
    pq.Traverse(printElement<int>);
    cout << "\n";

    cout << "  Test 1: PreOrderTraverse output: ";
    pq.PreOrderTraverse(printElement<int>);
    cout << "- Correct!\n";

    cout << "  Test 2: PostOrderTraverse output: ";
    pq.PostOrderTraverse(printElement<int>);
    cout << "- Correct!\n";

    int sum = pq.Fold(foldFunction<int>, 0);
    if (sum != 13)
      cout << "  Test 3: Fold - Error! (Sum: " << sum << ", Expected: 13)\n", failedTests++;
    else
      cout << "  Test 3: Fold - Correct! (Sum: " << sum << ")\n";
  }

  void test_PQHeap_InsertRemoveChange_Int(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<int> insert, remove, and change...\n";
    PQHeap<int> pq;
    pq.Insert(4); pq.Insert(2); pq.Insert(3);
    if (pq.Size() != 3 || pq.Tip() != 4)
      cout << "  Test 1: Insert - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Insert - Correct!\n";

    int tip = pq.Tip();
    if (tip != 4 || pq.Size() != 3)
      cout << "  Test 2: Tip - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 2: Tip: " << tip << " - Correct!\n";

    pq.RemoveTip();
    if (pq.Size() != 2)
      cout << "  Test 3: RemoveTip - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: RemoveTip - Correct!\n";

    tip = pq.TipNRemove();
    if (tip != 3 || pq.Size() != 1)
      cout << "  Test 4: TipNRemove - Error! (Tip: " << tip << ", Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: TipNRemove - Correct! (Tip: " << tip << ")\n";

    pq.Clear();
    try {
      pq.RemoveTip();
      cout << "  Test 5: RemoveTip on empty PQ - Error! (No exception thrown)\n", failedTests++;
    }
    catch (length_error& err) {
      cout << "  Test 5: RemoveTip on empty PQ (Exception thrown: \"" << err.what() << "\") - Correct!\n";
    }

    pq.Insert(3); pq.Insert(1); pq.Insert(7); pq.Insert(4); pq.Insert(9);
    cout << "  Heap before change : ";
    pq.Traverse(printElement<int>);
    cout << endl;

    pq.Change(3, 15);
    if (pq.Tip() != 15)
      cout << "  Test 6: Change idx 3 with element 15 - Error! (It's not heap anymore after Change)\n", failedTests++;
    else
      cout << "  Test 6: Change idx 3 with element 15 - Correct!\n";

    cout << "  Heap after change: ";
    pq.Traverse(printElement<int>);
    cout << endl;
  }


  // PQHeap tests for double
  void test_PQHeap_Constructors_Double(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<double> constructors...\n";
    PQHeap<double> pq1;
    if (!pq1.Empty())
      cout << "  Test 1: Default constructor - Error! (Empty: " << pq1.Empty() << ", Size: " << pq1.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Default constructor - Correct!\n";

    Vector<double> vec(10);
    vec[0] = 4.4; vec[1] = 2.6; vec[2] = 2.3; vec[3] = 3.7; vec[4] = 1.1; vec[5] = 9.9; vec[6] = 7.5; vec[7] = 6.9; vec[8] = 5.2; vec[9] = 8.1;
    PQHeap<double> pq2(vec);
    if (pq2.Size() != 10)
      cout << "  Test 2: Constructor from TraversableContainer - Error! (Size: " << pq2.Size() << ")\n", failedTests++;
    else {
      cout << "  Test 2: Constructor from TraversableContainer - Correct!\n";
    }

    Vector<double> vec2(10);
    vec2[0] = 4.4; vec2[1] = 6.2; vec[2] = 3.2; vec[3] = 7.3; vec[4] = 1.1; vec[5] = 9.9; vec[6] = 5.7; vec[7] = 9.6; vec[8] = 2.5; vec[9] = 0.8;
    PQHeap<double> pq3(move(vec2));
    if (pq3.Size() != 10)
      cout << "  Test 3: Constructor from MappableContainer - Error! (Size: " << pq3.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: Constructor from MappableContainer - Correct!\n";

    PQHeap<double> pq4(pq3);
    if (pq4.Size() != pq3.Size())
      cout << "  Test 4: Copy constructor - Error! (Size: " << pq4.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: Copy constructor - Correct!\n";

    PQHeap<double> pq5(move(pq4));
    if (pq5.Size() != 10 || !pq4.Empty())
      cout << "  Test 5: Move constructor - Error! (pq5 Size: " << pq5.Size() << ", pq4 Empty: " << pq4.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 5: Move constructor - Correct!\n";

    PQHeap<double> pq6;
    pq6 = pq3;
    if (pq6.Size() != pq3.Size())
      cout << "  Test 6: Copy assignment - Error! (Size: " << pq6.Size() << ")\n", failedTests++;
    else
      cout << "  Test 6 : Copy assignment - Correct!\n";

    PQHeap<double> pq7;
    pq7 = move(pq6);
    if (pq7.Size() != 10 || !pq6.Empty())
      cout << "  Test 7: Move assignment - Error! (pq7 Size: " << pq7.Size() << ", pq6 Empty: " << pq6.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 7: Move assignment - Correct!\n";

    pq7.Clear();
    if (!pq7.Empty())
      cout << "  Test 8: Clear - Error! (pq7 Size: " << pq7.Size() << ")\n", failedTests++;
    else
      cout << "  Test 8: Clear - Correct!\n";
  }

  void test_PQHeap_Traverse_Double(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<double> traverse and fold...\n";
    PQHeap<double> pq;
    pq.Insert(2.5); pq.Insert(4.1); pq.Insert(3.7); pq.Insert(7.7); pq.Insert(1.2);

    cout << "  PQ start: ";
    pq.PreOrderTraverse(printElement<double>);
    cout << "\n";

    cout << "  Test 1: PreOrderTraverse output: ";
    pq.PreOrderTraverse(printElement<double>);
    cout << "- Correct!\n";

    cout << "  Test 2: PostOrderTraverse output: ";
    pq.PostOrderTraverse(printElement<double>);
    cout << "- Correct!\n";

    double sum = pq.Fold(foldFunction<double>, 0.0);
    if (sum != 19.2)
      cout << "  Test 3: Fold - Error! (Sum: " << sum << ", Expected: 19.2)\n", failedTests++;
    else
      cout << "  Test 3: Fold - Correct! (Sum: " << sum << ")\n";
  }

  void test_PQHeap_InsertRemoveChange_Double(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<double> insert, remove, and change...\n";
    PQHeap<double> pq;
    pq.Insert(4.4); pq.Insert(2.2); pq.Insert(3.3);
    if (pq.Size() != 3 || pq.Tip() != 4.4)
      cout << "  Test 1: Insert - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Insert - Correct!\n";

    double tip = pq.Tip();
    if (tip != 4.4 || pq.Size() != 3)
      cout << "  Test 2: Tip - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 2: Tip " << tip << " - Correct!\n";

    pq.RemoveTip();
    if (pq.Size() != 2)
      cout << "  Test 3: RemoveTip - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: RemoveTip - Correct!\n";

    tip = pq.TipNRemove();
    if (tip != 3.3 || pq.Size() != 1)
      cout << "  Test 4: TipNRemove - Error! (Tip: " << tip << ", Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: TipNRemove - Correct! (Tip: " << tip << ")\n";

    pq.Clear();
    try {
      pq.RemoveTip();
      cout << "  Test 5: RemoveTip on empty PQ - Error! (No exception thrown)\n", failedTests++;
    }
    catch (length_error& err) {
      cout << "  Test 5: RemoveTip on empty PQ (Exception thrown: \"" << err.what() << "\") - Correct!\n";
    }

    pq.Insert(3.3); pq.Insert(1.6); pq.Insert(7.5); pq.Insert(4.5); pq.Insert(9.2);
    cout << "  Heap before change : ";
    pq.Traverse(printElement<double>);
    cout << endl;

    pq.Change(3, 15.8);
    if (pq.Tip() != 15.8)
      cout << "  Test 6: Change idx 3 with element 15.8 - Error! (It's not heap anymore after Change)\n", failedTests++;
    else
      cout << "  Test 6: Change idx 3 with element 15.8 - Correct!\n";

    cout << "  Heap after change: ";
    pq.Traverse(printElement<double>);
    cout << endl;
  }


  // PQHeap tests for string
  void test_PQHeap_Constructors_String(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<string> constructors...\n";
    PQHeap<string> pq1;
    if (!pq1.Empty())
      cout << "  Test 1: Default constructor - Error! (Empty: " << pq1.Empty() << ", Size: " << pq1.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Default constructor - Correct!\n";

    Vector<string> vec(10);
    vec[0] = "D"; vec[1] = "B"; vec[2] = "I"; vec[3] = "C"; vec[4] = "A"; vec[5] = "F"; vec[6] = "G"; vec[7] = "E"; vec[8] = "H"; vec[9] = "J";
    PQHeap<string> pq2(vec);
    if (pq2.Size() != 10)
      cout << "  Test 2: Constructor from TraversableContainer - Error! (Size: " << pq2.Size() << ")\n", failedTests++;
    else {
      cout << "  Test 2: Constructor from TraversableContainer - Correct!\n";
    }

    Vector<string> vec2(10);
    vec2[0] = "K"; vec2[1] = "T"; vec2[2] = "L"; vec2[3] = "S"; vec2[4] = "R"; vec2[5] = "M"; vec2[6] = "N"; vec2[7] = "Q"; vec2[8] = "O"; vec2[9] = "P";
    PQHeap<string> pq3(move(vec2));
    if (pq3.Size() != 10)
      cout << "  Test 3: Constructor from MappableContainer - Error! (Size: " << pq3.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: Constructor from MappableContainer - Correct!\n";

    PQHeap<string> pq4(pq3);
    if (pq4.Size() != pq3.Size())
      cout << "  Test 4: Copy constructor - Error! (Spq2ize: " << pq4.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: Copy constructor - Correct!\n";

    PQHeap<string> pq5(move(pq4));
    if (pq5.Size() != 10 || !pq4.Empty())
      cout << "  Test 5: Move constructor - Error! (pq5 Size: " << pq5.Size() << ", pq4 Empty: " << pq4.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 5: Move constructor - Correct!\n";

    PQHeap<string> pq6;
    pq6 = pq3;
    if (pq6.Size() != pq3.Size())
      cout << "  Test 6: Copy assignment - Error! (Size: " << pq6.Size() << ")\n", failedTests++;
    else
      cout << "  Test 6: Copy assignment - Correct!\n";

    PQHeap<string> pq7;
    pq7 = move(pq6);
    if (pq7.Size() != 10 || !pq6.Empty())
      cout << "  Test 7: Move assignment - Error! (pq7 Size: " << pq7.Size() << ", pq6 Empty: " << pq6.Empty() << ")\n", failedTests++;
    else
      cout << "  Test 7: Move assignment - Correct!\n";

    pq7.Clear();
    if (!pq7.Empty())
      cout << "  Test 8: Clear - Error! (pq7 Size: " << pq7.Size() << ")\n", failedTests++;
    else
      cout << "  Test 8: Clear - Correct!\n";
  }

  void test_PQHeap_Traverse_String(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<string> traverse and fold...\n";
    PQHeap<string> pq;
    pq.Insert("A"); pq.Insert("B"); pq.Insert("C");

    cout << "  PQ start: ";
    pq.PreOrderTraverse(printElement<string>);
    cout << "\n";

    string sum = pq.Fold(foldFunction<string>, string(""));
    if (sum != "CBA" && sum != "CAB")
      cout << "  Test 1: Fold - Error! (Sum: " << sum << ", Expected: CBA or CAB)\n", failedTests++;
    else
      cout << "  Test 1: Fold - Correct! (Sum: " << sum << ")\n";

    cout << "  Test 2: PreOrderTraverse output: ";
    pq.PreOrderTraverse(printElement<string>);
    cout << "- Correct!\n";

    cout << "  Test 3: PostOrderTraverse output: ";
    pq.PostOrderTraverse(printElement<string>);
    cout << "- Correct!\n";
  }

  void test_PQHeap_InsertRemoveChange_String(unsigned int& failedTests) {
    cout << "\nTesting PQHeap<string> insert, remove, and change...\n";
    PQHeap<string> pq;
    pq.Insert("D"); pq.Insert("B"); pq.Insert("C");
    if (pq.Size() != 3 || pq.Tip() != "D")
      cout << "  Test 1: Insert - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 1: Insert - Correct!\n";

    string tip = pq.Tip();
    if (tip != "D" || pq.Size() != 3)
      cout << "  Test 2: Tip - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 2: Tip: " << tip << " - Correct!\n";

    pq.RemoveTip();
    if (pq.Size() != 2)
      cout << "  Test 3: RemoveTip - Error! (Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 3: RemoveTip - Correct!\n";

    tip = pq.TipNRemove();
    if (tip != "C" || pq.Size() != 1)
      cout << "  Test 4: TipNRemove - Error! (Tip: " << tip << ", Size: " << pq.Size() << ")\n", failedTests++;
    else
      cout << "  Test 4: TipNRemove - Correct! (Tip: " << tip << ")\n";

    pq.Clear();
    try {
      pq.RemoveTip();
      cout << "  Test 5: RemoveTip on empty PQ - Error! (No exception thrown)\n", failedTests++;
    }
    catch (length_error& err) {
      cout << "  Test 5: RemoveTip on empty PQ (Exception thrown: \"" << err.what() << "\") - Correct!\n";
    }

    pq.Insert("C"); pq.Insert("D"); pq.Insert("A"); pq.Insert("B"); pq.Insert("E");
    cout << "  Heap before change : ";
    pq.Traverse(printElement<string>);
    cout << endl;

    pq.Change(3, "Z");
    if (pq.Tip() != "Z")
      cout << "  Test 6: Change idx 3 with element Z - Error! (It's not heap anymore after Change)\n", failedTests++;
    else
      cout << "  Test 6: Change idx 3 with element Z - Correct!\n";

    cout << "  Heap after change: ";
    pq.Traverse(printElement<string>);
    cout << endl;
  }


  void runAllTests() {
    unsigned int failedTests = 0;

    test_HeapVec_Constructors_Int(failedTests);
    test_HeapVec_MapTraverse_Int(failedTests);

    test_HeapVec_Constructors_Double(failedTests);
    test_HeapVec_MapTraverse_Double(failedTests);

    test_HeapVec_Constructors_String(failedTests);
    test_HeapVec_MapTraverse_String(failedTests);

    test_PQHeap_Constructors_Int(failedTests);
    test_PQHeap_Traverse_Int(failedTests);
    test_PQHeap_InsertRemoveChange_Int(failedTests);

    test_PQHeap_Constructors_Double(failedTests);
    test_PQHeap_Traverse_Double(failedTests);
    test_PQHeap_InsertRemoveChange_Double(failedTests);

    test_PQHeap_Constructors_String(failedTests);
    test_PQHeap_Traverse_String(failedTests);
    test_PQHeap_InsertRemoveChange_String(failedTests);


    cout << endl;
    if (failedTests == 0)
      cout << "All tests correct! \n";

    else
      cout << failedTests << " test(s) Error!" << "\n";
  }


}


void mytest() {
  cout << "###### Start of mytest ######" << endl;
  mytests::runAllTests();
}

