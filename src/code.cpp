// Robert Jackson
// CSCI 232 Fall 2026
// Programming Assignment #5
// I declare that I am the author of this work, take full responsibility for it, and have disclosed any material external assistance.
// I used Claude (Anthropic) to walk through each function and test step by step and explain the C++ concepts.
// I reviewed, tested, and verified the submitted implementation myself.

// ============================================================
// CSCI 232 Assignment 05 – Evolution of Data Structures
// Student Implementation
// ============================================================
// Author: Robert Jackson
// ============================================================

#include "code.hpp"
#include <iostream>
#include <format>

std::string AUTHOR_NAME       = "Robert Jackson";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
    "assignment independently, except where explicitly noted and referenced. "
    "Any collaboration or use of external resources has been properly cited. "
    "I am fully aware of the consequences of academic dishonesty and agree "
    "to abide by the university's academic integrity policy.";

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// Converts a LegacyData union to a formatted string.
/// Format specs:
/// 'i' -> integer value as string (e.g., "42")
/// 'd' -> double value formatted to 2 decimal places (e.g., "3.14")
/// 'c' -> string pointer content (or "nullptr" if cPtr is null)
/// default -> "unknown"

std::string printLegacyData(LegacyData data, char type) {
    switch (type) {
        case 'i':
            return std::to_string(data.i);
        case 'd':
            return std::format("{:.2f}", data.d);
        case 'c':
            if (data.cPtr == nullptr) {
                return "nullptr";
            }
            return std::string(data.cPtr);
        default:
            return "unknown";
    }
}

// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// Initializes a structNode with value, type indicator, and nullptr nextPtr.
void initStructNode(structNode* nPtr, LegacyData val, char type) {
    if (nPtr == nullptr) {
        return;
    }

    nPtr->value    = val;
    nPtr->typeData = type;
    nPtr->nextPtr  = nullptr;
}

/// Dynamically allocates two structNodes.
/// Node 1: int 5 ('i')
/// Node 2: double 3.14 ('d')
/// Links Node 1 -> Node 2 -> nullptr
/// Returns pointer to Node 1.
structNode* createTwoStructNodes() {
    structNode* firstPtr  = new structNode;
    structNode* secondPtr = new structNode;

    LegacyData firstVal;
    firstVal.i = 5;

    LegacyData secondVal;
    secondVal.d = 3.14;

    initStructNode(firstPtr, firstVal, 'i');
    initStructNode(secondPtr, secondVal, 'd');
    firstPtr->nextPtr = secondPtr;

    return firstPtr;
}

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// Constructor: Assign fields inside curly braces.
/// DO NOT use member initializer lists here!

classNode::classNode(LegacyData val, char type) {
    value    = val;
    typeData = type;
    nextPtr  = nullptr;
}

/// Dynamically allocates two classNodes (int 5, double 3.14) and links them.
classNode* createTwoClassNodes() {
    LegacyData firstVal;
    firstVal.i = 5;

    LegacyData secondVal;
    secondVal.d = 3.14;

    classNode* firstPtr  = new classNode(firstVal, 'i');
    classNode* secondPtr = new classNode(secondVal, 'd');
    firstPtr->nextPtr    = secondPtr;

    return firstPtr;
}

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// Dynamically allocates two classNodeT<int> objects (int 5, int 3) and links them.
classNodeT<int>* createTwoTemplateNodes() {
    classNodeT<int>* firstPtr  = new classNodeT<int>(5);
    classNodeT<int>* secondPtr = new classNodeT<int>(3);
    firstPtr->nextPtr          = secondPtr;

    return firstPtr;
}

// ============================================================
// STAGE 4: C++17 Variant and LinkedList Manager
// ============================================================

LinkedList::LinkedList() {
    headPtr = nullptr;
    counter = 0;
}

LinkedList::~LinkedList() {
    destroyList();
}

void LinkedList::destroyList() {
    classNodeVariant* currentPtr = headPtr;

    while (currentPtr != nullptr) {
        classNodeVariant* nextPtr = currentPtr->nextPtr;
        delete currentPtr;
        currentPtr = nextPtr;
    }

    headPtr = nullptr;
    counter = 0;
}

int LinkedList::addFirst(classNodeVariant* newNodePtr) {
    if (newNodePtr == nullptr) {
        return -1;
    }

    newNodePtr->nextPtr = headPtr;
    headPtr             = newNodePtr;
    counter++;

    return 0;
}

int LinkedList::addLast(classNodeVariant* newNodePtr) {
    if (newNodePtr == nullptr) {
        return -1;
    }

    newNodePtr->nextPtr = nullptr;

    if (headPtr == nullptr) {
        headPtr = newNodePtr;
    } else {
        classNodeVariant* currentPtr = headPtr;

        while (currentPtr->nextPtr != nullptr) {
            currentPtr = currentPtr->nextPtr;
        }

        currentPtr->nextPtr = newNodePtr;
    }

    counter++;

    return 0;
}

int LinkedList::deleteFirst() {
    if (headPtr == nullptr) {
        return -1;
    }

    classNodeVariant* oldHeadPtr = headPtr;
    headPtr                      = headPtr->nextPtr;

    delete oldHeadPtr;
    counter--;

    return 0;
}

int LinkedList::deleteLast() {
    if (headPtr == nullptr) {
        return -1;
    }

    if (headPtr->nextPtr == nullptr) {
        delete headPtr;
        headPtr = nullptr;
    } else {
        classNodeVariant* currentPtr = headPtr;

        while (currentPtr->nextPtr->nextPtr != nullptr) {
            currentPtr = currentPtr->nextPtr;
        }

        delete currentPtr->nextPtr;
        currentPtr->nextPtr = nullptr;
    }

    counter--;

    return 0;
}

int LinkedList::deleteValue(ModernData targetValue) {
    classNodeVariant* previousPtr = nullptr;
    classNodeVariant* currentPtr  = headPtr;

    while (currentPtr != nullptr) {
        if (currentPtr->value == targetValue) {
            if (previousPtr == nullptr) {
                headPtr = currentPtr->nextPtr;
            } else {
                previousPtr->nextPtr = currentPtr->nextPtr;
            }

            delete currentPtr;
            counter--;

            return 0;
        }

        previousPtr = currentPtr;
        currentPtr  = currentPtr->nextPtr;
    }

    return -1;
}

int LinkedList::printList() {
    if (headPtr == nullptr) {
        return -1;
    }

    classNodeVariant* currentPtr = headPtr;

    while (currentPtr != nullptr) {
        std::visit([](const auto& val) { std::cout << std::format("{} ", val); }, currentPtr->value);
        currentPtr = currentPtr->nextPtr;
    }

    std::cout << std::endl;

    return 0;
}

int LinkedList::listLength() {
    return counter;
}