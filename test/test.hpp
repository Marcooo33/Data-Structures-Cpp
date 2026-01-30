#ifndef MYTEST_HPP
#define MYTEST_HPP

namespace mytests {

    // HeapVec
    void test_HeapVec_Constructors_Int(unsigned int&);
    void test_HeapVec_MapTraverse_Int(unsigned int&);

    void test_HeapVec_Constructors_Double(unsigned int&);
    void test_HeapVec_MapTraverse_Double(unsigned int&);

    void test_HeapVec_Constructors_String(unsigned int&);
    void test_HeapVec_MapTraverse_String(unsigned int&);

    // PQHeap
    void test_PQHeap_Constructors_Int(unsigned int&);
    void test_PQHeap_Traverse_Int(unsigned int&);
    void test_PQHeap_InsertRemoveChange_Int(unsigned int&);

    void test_PQHeap_Constructors_Double(unsigned int&);
    void test_PQHeap_Traverse_Double(unsigned int&);
    void test_PQHeap_InsertRemoveChange_Double(unsigned int&);

    void test_PQHeap_Constructors_String(unsigned int&);
    void test_PQHeap_Traverse_String(unsigned int&);
    void test_PQHeap_InsertRemoveChange_String(unsigned int&);

    // Main
    void runAllTests();
}


void mytest();

#endif