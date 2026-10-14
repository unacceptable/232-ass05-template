// Robert Jackson
// CSCI 232 Fall 2026
// Programming Assignment #5
// I declare that I am the author of this work, take full responsibility for it, and have disclosed any material external assistance.
// I used Claude (Anthropic) to walk through each function and test step by step and explain the C++ concepts.
// I reviewed, tested, and verified the submitted implementation myself.

#ifndef CODE_HPP
#define CODE_HPP

#include <string>
#include <variant>

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// A union capable of storing an int, double, or char pointer.
/// YOUR TASK: Add three members:
/// - int member named 'i'
/// - double member named 'd'
/// - char pointer member named 'cPtr'
union LegacyData {
    int i;
    double d;
    char* cPtr;
};

/// Converts a LegacyData union to a formatted string based on the active type.
/// @param data The union to convert
/// @param type Character type indicator: 'i'=int, 'd'=double, 'c'=char*
/// @return Formatted string representation ("42", "3.14", string value, or "unknown")
std::string printLegacyData(LegacyData data, char type);

// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// A C-style linked list node containing a union and type indicator.
/// YOUR TASK: Add three members:
/// - LegacyData member named 'value'
/// - Pointer member named 'nextPtr' pointing to structNode
/// - char member named 'typeData' ('i', 'd', 'c')
struct structNode {
    LegacyData value;
    structNode* nextPtr;
    char typeData;
};

/// Manually initializes a structNode with the given data and type.
/// @param nPtr Pointer to the node to initialize
/// @param val The LegacyData union value
/// @param type Character type indicator ('i', 'd', 'c')
void initStructNode(structNode* nPtr, LegacyData val, char type);

/// Creates two dynamically allocated structNodes linked together.
/// Node 1 contains int 5, Node 2 contains double 3.14.
/// @return Pointer to the first node
structNode* createTwoStructNodes();

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// An early C++ class representing a linked list node.
/// IMPORTANT: Constructor MUST use field assignments inside curly braces (no init list).
/// YOUR TASK: Define public members (value, nextPtr, typeData) and constructor declaration.
class classNode {
public:
    LegacyData value;
    classNode* nextPtr;
    char typeData;

    classNode(LegacyData val, char type);
};

/// Creates two dynamically allocated classNode objects linked together.
/// Node 1 contains int 5, Node 2 contains double 3.14.
/// @return Pointer to the first node
classNode* createTwoClassNodes();

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// A template-based linked list node providing type-safe storage.
/// IMPORTANT: Constructor MUST use member initializer list syntax.
/// YOUR TASK: Define member 'value' of type T, 'nextPtr' of type classNodeT<T>*, and constructor.
template <typename T>
class classNodeT {
public:
    T value;
    classNodeT<T>* nextPtr;

    classNodeT(T d) : value(d), nextPtr(nullptr) {}
};

/// Creates two dynamically allocated classNodeT<int> objects linked together.
/// Node 1 contains int 5, Node 2 contains int 3.
/// @return Pointer to the first node
classNodeT<int>* createTwoTemplateNodes();

// ============================================================
// STAGE 4: C++17 Modern Variant and LinkedList Manager
// ============================================================

/// Type alias for modern C++17 variant supporting int, double, or std::string.
using ModernData = std::variant<int, double, std::string>;

/// A modern C++17 linked list node using std::variant for type-safe storage.
class classNodeVariant {
public:
    ModernData value;
    classNodeVariant* nextPtr;

    /// Constructor using member initializer list.
    classNodeVariant(ModernData d) : value(d), nextPtr(nullptr) {}
};

/// A fully encapsulated linked list manager for classNodeVariant objects.
/// YOUR TASK: Declare private members (headPtr, counter) and public methods.
class LinkedList {
private:
    classNodeVariant* headPtr;
    int counter;

public:
    LinkedList();
    ~LinkedList();

    void destroyList();
    int addFirst(classNodeVariant* newNodePtr);
    int addLast(classNodeVariant* newNodePtr);
    int deleteFirst();
    int deleteLast();
    int deleteValue(ModernData targetValue);
    int printList();
    int listLength();
};

#endif