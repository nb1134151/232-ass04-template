#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif
#include <stdlib.h>

// ============================================================
// Forward declarations — implemented in code.c
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

void  initNode    (Node *nodePtr, int value);
Node* createNode  (int value);
void  destroyNode (Node **nodePtrPtr);
void  destroyList (Node **headPtrPtr);
int   addFirst    (Node **headPtrPtr, Node *newNodePtr);
int   addLast     (Node **headPtrPtr, Node *newNodePtr);
Node* detachFirst (Node **headPtrPtr);
Node* detachLast  (Node **headPtrPtr);
Node* detachValue (Node **headPtrPtr, int value);
int   deleteFirst (Node **headPtrPtr);
int   deleteLast  (Node **headPtrPtr);
int   deleteValue (Node **headPtrPtr, int value);
void  destroyList (Node **headPtrPtr);
int   printList   (Node *headPtr);
int   listLength  (Node *headPtr);


// ============================================================
//  UNIT TESTS
//
//  Rules:
//  - Use TEST_ASSERT_TRUE_MESSAGE for every assertion.
//  - Do NOT use TEST_ASSERT_EQUAL — it reveals expected values.
//  - Heap tests: use createNode / destroyList.
//  - Stack tests: declare Node variables on the stack.
//  - Do NOT modify function names or signatures.
// ============================================================


// ============================================================
// test_initNode_sets_value
//
// Declare a Node on the stack.
// Call initNode with a known value.
// Verify that the value field contains that value.
// ============================================================

void test_initNode_sets_value(void)
{
        Node newNode;
        initNode(&newNode, 5);
        TEST_ASSERT_TRUE_MESSAGE(newNode.value == 5, "Expected 5.");
    
}


// ============================================================
// test_initNode_sets_next_null
//
// Declare a Node on the stack.
// Call initNode.
// Verify that nextPtr is NULL after the call.
// ============================================================

void test_initNode_sets_next_null(void)
{
    Node newNode;
    initNode(&newNode, 6);
    TEST_ASSERT_TRUE_MESSAGE(newNode.nextPtr == NULL, "nextPtr not null.");
}


// ============================================================
// test_initNode_null_guard
//
// Call initNode with NULL as the nodePtr.
// Verify the program does not crash.
// ============================================================

void test_initNode_null_guard(void)
{
    // TODO
    initNode(NULL, 42);
    TEST_ASSERT_TRUE_MESSAGE(1 == 1,
        "Error: initNode must handle NULL without crashing.");
}


// ============================================================
// test_createNode_not_null
//
// Call createNode with a known value.
// Verify the returned pointer is NOT NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_not_null(void)
{
    Node *newNode = createNode(5);
    TEST_ASSERT_TRUE_MESSAGE(newNode != NULL, "Error: Node cannot be null");
    destroyNode(&newNode);
}


// ============================================================
// test_createNode_value
//
// Call createNode with a known value.
// Verify that the value field of the returned node
// contains the correct value.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_value(void)
{
    Node *newNode = createNode(5);
    TEST_ASSERT_TRUE_MESSAGE(newNode->value == 5, "Error: expected value was 5.");
    destroyNode(&newNode);
}


// ============================================================
// test_createNode_next_null
//
// Call createNode.
// Verify that nextPtr of the returned node is NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_next_null(void)
{
    Node *newNode = createNode(5);
    TEST_ASSERT_TRUE_MESSAGE(newNode->nextPtr == NULL, "Error: nextPtr must be null");
    destroyNode(&newNode);
}


// ============================================================
// test_destroyNode_sets_null
//
// Call createNode to allocate a node.
// Call destroyNode.
// Verify that the pointer is NULL after the call.
// ============================================================

void test_destroyNode_sets_null(void)
{
    Node *newNode = createNode(5);
    destroyNode(&newNode);
    TEST_ASSERT_TRUE_MESSAGE(newNode == NULL, "Error: pointer is not null");
}


// ============================================================
// test_addFirst_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addFirst.
// Verify that headPtr now points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addFirst_empty_list(void)
{
    Node *headPtr = NULL;
    Node *newNode = createNode(6);

    addFirst(&headPtr, newNode);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == newNode, "Error: headPtr does not point to new node.");
    destroyList(&headPtr);
}


// ============================================================
// test_addFirst_non_empty
//
// Add two nodes using addFirst.
// Verify that headPtr points to the SECOND node added
// (the most recently added node is at the front).
// Verify the first node is reachable via nextPtr.
// Clean up with destroyList.
// ============================================================

void test_addFirst_non_empty(void)
{   

    Node *newNodeFirst = createNode(5);
    Node *newNodeSecond = createNode(6);
    Node *headPtr = NULL;

    addFirst(&headPtr, newNodeFirst);
    addFirst(&headPtr, newNodeSecond);

    TEST_ASSERT_TRUE_MESSAGE(headPtr == newNodeSecond, "Error: HeadPtr does not point to second node.");
    TEST_ASSERT_TRUE_MESSAGE(headPtr->nextPtr == newNodeFirst, "Error: nextPtr does not point to first node.");
    destroyList(&headPtr);
}


// ============================================================
// test_addFirst_null_headptr
//
// Call addFirst with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addFirst_null_headptr(void)
{
    Node *newNode = createNode(4);
    int status = addFirst(NULL, newNode);
    TEST_ASSERT_TRUE_MESSAGE(status == -1, "Error: Function does not return -1");
}


// ============================================================
// test_addLast_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addLast.
// Verify that headPtr points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addLast_empty_list(void)
{
    Node *headPtr = NULL;
    Node *newNode = createNode(7);
    addLast(&headPtr, newNode);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == newNode, "Error: headPtr does not point to new node");
    destroyList(&headPtr);
}


// ============================================================
// test_addLast_non_empty
//
// Add two nodes using addLast.
// Verify that headPtr points to the FIRST node added.
// Verify the second node is reachable via nextPtr.
// Verify the second node's nextPtr is NULL.
// Clean up with destroyList.
// ============================================================

void test_addLast_non_empty(void)
{
    Node *a = createNode(2);
    Node *b = createNode(2);
    
    a->nextPtr = b;
    b->nextPtr = NULL;

    Node *headPtr = a;
    addLast(&headPtr, b);

    TEST_ASSERT_TRUE_MESSAGE(headPtr == a, "Error: HeadPtr does not point to the first node added");
    TEST_ASSERT_TRUE_MESSAGE(headPtr->nextPtr == b, "Error: Second Node is not reachable by nextPTr");
    TEST_ASSERT_TRUE_MESSAGE(b->nextPtr == NULL, "Error: Second node's nextPtr is not NULL");
    destroyList(&headPtr);
}


// ============================================================
// test_addLast_null_guard
//
// Call addLast with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addLast_null_guard(void)
{
    Node* a;
    int status = addLast(NULL, a);
    TEST_ASSERT_TRUE_MESSAGE(status == -1, "Error: status returned values other than -1");
}


// ============================================================
// test_detachFirst_returns_node
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify the returned pointer equals &a.
// ============================================================

void test_detachFirst_returns_node(void)
{
    Node * a = createNode(5);
    Node * b = createNode(7);

    a->nextPtr = b;
    b->nextPtr = NULL;
    Node *headPtr = a;

    Node *detached = detachFirst(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(detached == a, "Error: Returned pointer does not equal &a");
}


// ============================================================
// test_detachFirst_updates_head
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify that headPtr now points to b.
// ============================================================

void test_detachFirst_updates_head(void)
{
    Node * a = createNode(5);
    Node * b = createNode(7);
    Node *headPtr = a;

    a->nextPtr = b;
    b->nextPtr = NULL;

    Node *detached = detachFirst(&headPtr);

    TEST_ASSERT_TRUE_MESSAGE(headPtr == b, "Error: headPtr does not point to b");
}


// ============================================================
// test_detachFirst_empty_list
//
// Call detachFirst on an empty list (headPtr == NULL).
// Verify the function returns NULL without crashing.
// ============================================================

void test_detachFirst_empty_list(void)
{
    Node *headPtr = NULL;
    int status = detachFirst(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(status == NULL, "DetachFirst did not return NULL");
}


// ============================================================
// test_detachValue_found
//
// Build a stack chain: a(1) -> b(2) -> c(3) -> NULL
// Call detachValue for value 2 (middle node).
// Verify the returned pointer equals &b.
// Verify a->nextPtr now points to c.
// Verify b->nextPtr is NULL after detach.
// ============================================================

void test_detachValue_found(void)
{
    Node * nodeA = createNode(1);
    Node * nodeB = createNode(2);
    Node * nodeC = createNode(3);


    Node *headPtr = nodeA;

    nodeA->nextPtr = nodeB;
    nodeB->nextPtr = nodeC;
    nodeC->nextPtr = NULL;

    Node *detachedPtr = detachValue(&headPtr, 2);
    TEST_ASSERT_TRUE_MESSAGE(detachedPtr == nodeB, "Error: Returned pointer does not point to b.");
    TEST_ASSERT_TRUE_MESSAGE(nodeA->nextPtr == nodeC, "Error: a->nextPTr does not point to c.");
    TEST_ASSERT_TRUE_MESSAGE(nodeB->nextPtr == NULL, "Error: b->nextPtr is not NULL.");

}


// ============================================================
// test_detachValue_head
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for value 1 (head node).
// Verify the returned pointer equals &a.
// Verify headPtr now points to b.
// ============================================================

void test_detachValue_head(void)
{
    Node * a = createNode(1);
    Node * b = createNode(2);
    Node * c = createNode(3);


    Node *headPtr = a;

    a->nextPtr = b;
    b->nextPtr = c;
    c->nextPtr = NULL;

    Node *detachedPtr = detachValue(&headPtr,1);



    TEST_ASSERT_TRUE_MESSAGE(detachedPtr == a, "Error: Returned pointer does not equal the address of a.");
    TEST_ASSERT_TRUE_MESSAGE(headPtr == b, "Error: headPtr does not point to b.");

}


// ============================================================
// test_detachValue_not_found
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for a value that does not exist (e.g. 99).
// Verify the function returns NULL.
// ============================================================

void test_detachValue_not_found(void)
{
    Node *a = createNode(1);
    Node *b = createNode(2);

    Node *headPtr = a;

    a->nextPtr = b;
    b->nextPtr = NULL;

    Node *status = detachValue(&headPtr, 99);

    TEST_ASSERT_TRUE_MESSAGE(status == NULL, "detachValue did not return NULL.");
}


// ============================================================
// test_deleteFirst_removes_node
//
// Create two heap nodes and build a list.
// Call deleteFirst.
// Verify the function returns 0.
// Verify headPtr now points to the second node.
// Clean up with destroyList.
// ============================================================

void test_deleteFirst_removes_node(void)
{
    Node *nodeA = createNode(5);
    Node *nodeB = createNode(10);

    nodeA->nextPtr = nodeB;
    nodeB->nextPtr = NULL;

    Node *headPtr = nodeA;



    int status = deleteFirst(&headPtr);

    TEST_ASSERT_TRUE_MESSAGE(status == 0, "Error: status not 0");
    TEST_ASSERT_TRUE_MESSAGE(headPtr == nodeB , "Error: headPtr does not point to second node");
    destroyList(&headPtr);
}


// ============================================================
// test_deleteFirst_empty_list
//
// Call deleteFirst on an empty list.
// Verify the function returns -1 without crashing.
// ============================================================

void test_deleteFirst_empty_list(void)
{
    int status = deleteFirst(NULL);
    TEST_ASSERT_TRUE_MESSAGE(status == -1, "Error: status returned a value other than -1");
}


// ============================================================
// test_deleteValue_found
//
// Create three heap nodes: 10 -> 20 -> 30
// Call deleteValue for 20.
// Verify the function returns 0.
// Verify listLength is now 2.
// Verify 20 is no longer in the list.
// Clean up with destroyList.
// ============================================================

void test_deleteValue_found(void)
{
    Node * nodeA = createNode(10);
    Node * nodeB = createNode(20);
    Node * nodeC = createNode(30);


    Node *headPtr = nodeA;

    nodeA->nextPtr = nodeB;
    nodeB->nextPtr = nodeC;
    nodeC->nextPtr = NULL;

    int status = deleteValue(&headPtr, 20);
    TEST_ASSERT_TRUE_MESSAGE(status == 0, "Error: return status not zero");
    status = listLength(headPtr);
    TEST_ASSERT_TRUE_MESSAGE(status = 2, "Error: List length not 2");
    status = deleteValue(&headPtr, 20);
    TEST_ASSERT_TRUE_MESSAGE(status == -1, "Error: 20 still in list");
    destroyList(&headPtr);

}


// ============================================================
// test_deleteValue_not_found
//
// Create two heap nodes: 10 -> 20
// Call deleteValue for 99.
// Verify the function returns -1.
// Verify the list is unchanged (length still 2).
// Clean up with destroyList.
// ============================================================

void test_deleteValue_not_found(void)
{
    Node * nodeA = createNode(10);
    Node * nodeB = createNode(20);

    Node *headPtr = nodeA;

    nodeA->nextPtr = nodeB;
    nodeB->nextPtr = NULL;

    int status = deleteValue(&headPtr, 99);
    TEST_ASSERT_TRUE_MESSAGE(status == -1, "Error: Return status is not -1");
    status = listLength(headPtr);
    TEST_ASSERT_TRUE_MESSAGE(status == 2, "Error: Return status is not -1");
    destroyList(&headPtr);
}


// ============================================================
// test_destroyList_empties_list
//
// Create three heap nodes and build a list.
// Call destroyList.
// Verify headPtr is NULL after the call.
// ============================================================

void test_destroyList_empties_list(void)
{
    Node * nodeA = createNode(1);
    Node * nodeB = createNode(2);
    Node * nodeC = createNode(3);

    Node * headPtr = nodeA;
    nodeA->nextPtr = nodeB;
    nodeB->nextPtr = nodeC;
    nodeC->nextPtr = NULL;


    destroyList(&headPtr);

    TEST_ASSERT_TRUE_MESSAGE(headPtr == NULL, "Error: headPtr is not null");
}


// ============================================================
// test_listLength_empty
//
// Call listLength with NULL.
// Verify the function returns 0.
// ============================================================

void test_listLength_empty(void)
{
    int status = listLength(NULL);
    TEST_ASSERT_TRUE_MESSAGE(status == 0, "Error: Return value is not 0");
}


// ============================================================
// test_listLength_three
//
// Create three heap nodes and build a list.
// Call listLength.
// Verify the function returns 3.
// Clean up with destroyList.
// ============================================================

void test_listLength_three(void)
{
    Node * nodeA = createNode(1);
    Node * nodeB = createNode(2);
    Node * nodeC = createNode(3);
    nodeA->nextPtr = nodeB;
    nodeB->nextPtr = nodeC;
    nodeC->nextPtr = NULL;

    Node *headPtr = nodeA;

    int status = listLength(headPtr);

    TEST_ASSERT_TRUE_MESSAGE(status == 3, "Error: return value is not 3");
    destroyList(&headPtr);
}


// ============================================================
// test_printList_empty
//
// Call printList with NULL.
// Verify the function returns -1 without crashing.
// ============================================================

void test_printList_empty(void)
{
    int status = printList(NULL);
    TEST_ASSERT_TRUE_MESSAGE(status == -1, "TODO: implement this test.");
}