#pragma once
#include "CircularLinkedList.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

#define EXPECT_TRUE(EXPRESSION) if (!EXPRESSION) throw std::logic_error("EXPECT_TRUE FAILED, LINE: " + std::to_string(__LINE__))
#define EXPECT_FALSE(EXPRESSION) if (EXPRESSION) throw std::logic_error("EXPECT_FALSE FAILED, LINE: " + std::to_string(__LINE__))
#define EXPECT_EQUAL(A, B) if (!(A == B)) throw std::logic_error("EXPECT_EQUAL FAILED, LINE: " + std::to_string(__LINE__))
#define EXPECT_NOT_EQUAL(A, B) if (A == B) throw std::logic_error("EXPECT_NOT_EQUAL FAILED, LINE: " + std::to_string(__LINE__))
#define EXPECT_STRING(A, B) if (!(A == B)) throw std::logic_error("EXPECT_EQUAL FAILED, LINE: " + std::to_string(__LINE__) + "\nA: " + A + "\nB: " + B)

#define EXPECT_EXCEPTION(EXPRESSION, EXCEPTION_TYPE, MESSAGE) {                                                     \
                                                                bool catched = false;                               \
                                                                try {                                               \
                                                                    EXPRESSION;                                     \
                                                                } catch (const EXCEPTION_TYPE& e) {                 \
                                                                    catched = e.what() == std::string(MESSAGE);     \
                                                                }                                       \
                                                                if (!catched) {                         \
                                                                    throw std::logic_error("EXPECT_EXCEPTION FAILED, LINE: " + std::to_string(__LINE__)); \
                                                                }                                       \
                                                            }

void emptyListTest() {
    CircularLinkedList list;
    EXPECT_TRUE(list.empty());
    std::cout << "Completed emptyListTest!" << std::endl;
}

void pushBackTests() {
    CircularLinkedList list;
    list.push_back("a");
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "a");

    list.push_back("b");
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "b");
    auto aPtr = list.forwardSearch("a");
    auto bPtr = list.forwardSearch("b");
    EXPECT_EQUAL(aPtr->next_, bPtr);
    EXPECT_EQUAL(bPtr->prev_, aPtr);
    EXPECT_EQUAL(bPtr->next_, aPtr);
    EXPECT_EQUAL(aPtr->prev_, bPtr);

    list.push_back("c");
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "c");
    aPtr = list.forwardSearch("a");
    bPtr = list.forwardSearch("b");
    auto cPtr = list.forwardSearch("c");
    EXPECT_EQUAL(aPtr->next_, bPtr);
    EXPECT_EQUAL(bPtr->prev_, aPtr);
    EXPECT_EQUAL(bPtr->next_, cPtr);
    EXPECT_EQUAL(cPtr->prev_, bPtr);
    EXPECT_EQUAL(cPtr->next_, aPtr);
    EXPECT_EQUAL(aPtr->prev_, cPtr);
    std::cout << "Completed pushBackTests!" << std::endl;
}

void pushFrontTests() {
    CircularLinkedList list;
    list.push_front("a");
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "a");

    list.push_front("b");
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "b");
    EXPECT_EQUAL(list.back(), "a");
    auto aPtr = list.forwardSearch("a");
    auto bPtr = list.forwardSearch("b");
    EXPECT_EQUAL(aPtr->next_, bPtr);
    EXPECT_EQUAL(bPtr->prev_, aPtr);
    EXPECT_EQUAL(bPtr->next_, aPtr);
    EXPECT_EQUAL(aPtr->prev_, bPtr);

    list.push_front("c");
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "c");
    EXPECT_EQUAL(list.back(), "a");
    aPtr = list.forwardSearch("a");
    bPtr = list.forwardSearch("b");
    auto cPtr = list.forwardSearch("c");
    EXPECT_EQUAL(cPtr->next_, bPtr);
    EXPECT_EQUAL(bPtr->prev_, cPtr);
    EXPECT_EQUAL(bPtr->next_, aPtr);
    EXPECT_EQUAL(aPtr->prev_, bPtr);
    EXPECT_EQUAL(aPtr->next_, cPtr);
    EXPECT_EQUAL(cPtr->prev_, aPtr);
    std::cout << "Completed pushFrontTests!" << std::endl;
}

void clearTests() {
    CircularLinkedList list;
    list.push_back("a");
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());

    list.push_front("a");
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());

    list.push_back("a");
    list.push_back("b");
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());

    list.push_front("a");
    list.push_front("b");
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());

    list.clear();
    EXPECT_TRUE(list.empty());
    std::cout << "Completed clearTests!" << std::endl;
}

void popBackTests() {
    CircularLinkedList list;
    list.push_back("a");
    list.pop_back();
    EXPECT_TRUE(list.empty());

    list.push_back("a");
    list.push_back("b");
    list.pop_back();
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "a");

    list.clear();
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    list.pop_back();
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "b");
    auto aPtr = list.forwardSearch("a");
    auto bPtr = list.forwardSearch("b");
    EXPECT_EQUAL(aPtr->next_, bPtr);
    EXPECT_EQUAL(bPtr->prev_, aPtr);
    EXPECT_EQUAL(bPtr->next_, aPtr);
    EXPECT_EQUAL(aPtr->prev_, bPtr);
    list.pop_back();
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "a");


    list.clear();
    EXPECT_EXCEPTION(list.pop_back(), std::logic_error, "Popping from empty CircularLinkedList");
    std::cout << "Completed popBackTests!" << std::endl;
}

void popFrontTests() {
    CircularLinkedList list;
    list.push_back("a");
    list.pop_front();
    EXPECT_TRUE(list.empty());

    list.push_back("a");
    list.push_back("b");
    list.pop_front();
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "b");
    EXPECT_EQUAL(list.back(), "b");

    list.clear();
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    list.pop_front();
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "b");
    EXPECT_EQUAL(list.back(), "c");
    auto bPtr = list.forwardSearch("b");
    auto cPtr = list.forwardSearch("c");
    EXPECT_EQUAL(bPtr->next_, cPtr);
    EXPECT_EQUAL(cPtr->prev_, bPtr);
    EXPECT_EQUAL(cPtr->next_, bPtr);
    EXPECT_EQUAL(bPtr->prev_, cPtr);
    list.pop_front();
    EXPECT_FALSE(list.empty());
    EXPECT_EQUAL(list.front(), "c");
    EXPECT_EQUAL(list.back(), "c");


    list.clear();
    EXPECT_EXCEPTION(list.pop_front(), std::logic_error, "Popping from empty CircularLinkedList");
    std::cout << "Completed popFrontTests!" << std::endl;
}

void toVectorTests() {
    CircularLinkedList list;
    EXPECT_EQUAL(list.toVector(), std::vector<std::string>());

    std::vector<std::string> vec;
    list.push_back("a");
    vec.push_back("a");
    EXPECT_EQUAL(list.toVector(), vec);

    list.push_back("b");
    vec.push_back("b");
    EXPECT_EQUAL(list.toVector(), vec);

    list.push_back("c");
    vec.push_back("c");
    EXPECT_EQUAL(list.toVector(), vec);

    list.pop_back();
    vec.pop_back();
    EXPECT_EQUAL(list.toVector(), vec);
    std::cout << "Completed toVectorTests!" << std::endl;
}

void deleteNodeTests() {
    CircularLinkedList list;
    list.push_back("a");
    auto aPtr = list.forwardSearch("a");
    list.deleteNode(aPtr);
    EXPECT_TRUE(list.empty());

    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    aPtr = list.forwardSearch("a");
    list.deleteNode(aPtr);
    EXPECT_EQUAL(list.front(), "b");
    EXPECT_EQUAL(list.back(), "c");
    auto bPtr = list.forwardSearch("b");
    auto cPtr = list.forwardSearch("c");
    EXPECT_EQUAL(bPtr->next_, cPtr);
    EXPECT_EQUAL(cPtr->prev_, bPtr);
    EXPECT_EQUAL(cPtr->next_, bPtr);
    EXPECT_EQUAL(bPtr->prev_, cPtr);
    list.clear();

    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    bPtr = list.forwardSearch("b");
    list.deleteNode(bPtr);
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "c");
    aPtr = list.forwardSearch("a");
    cPtr = list.forwardSearch("c");
    EXPECT_EQUAL(aPtr->next_, cPtr);
    EXPECT_EQUAL(cPtr->prev_, aPtr);
    EXPECT_EQUAL(cPtr->next_, aPtr);
    EXPECT_EQUAL(aPtr->prev_, cPtr);
    list.clear();

    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    cPtr = list.forwardSearch("c");
    list.deleteNode(cPtr);
    EXPECT_EQUAL(list.front(), "a");
    EXPECT_EQUAL(list.back(), "b");
    aPtr = list.forwardSearch("a");
    bPtr = list.forwardSearch("b");
    EXPECT_EQUAL(aPtr->next_, bPtr);
    EXPECT_EQUAL(bPtr->prev_, aPtr);
    EXPECT_EQUAL(bPtr->next_, aPtr);
    EXPECT_EQUAL(aPtr->prev_, bPtr);
    list.clear();

    EXPECT_EXCEPTION(list.deleteNode(aPtr), std::logic_error, "Deleting from empty CircularLinkedList");
    EXPECT_EXCEPTION(list.deleteNode(nullptr), std::logic_error, "Deleting by null NodePtr");

    std::cout << "Completed deleteNodeTests!" << std::endl;
}

void searchTests() {
    CircularLinkedList list;
    EXPECT_EQUAL(list.forwardSearch("a"), nullptr);
    EXPECT_EQUAL(list.backwardSearch("a"), nullptr);

    list.push_back("a");
    EXPECT_EQUAL(list.forwardSearch("b"), nullptr);
    EXPECT_EQUAL(list.backwardSearch("b"), nullptr);
    EXPECT_NOT_EQUAL(list.forwardSearch("a"), nullptr);
    EXPECT_NOT_EQUAL(list.backwardSearch("a"), nullptr);
    EXPECT_EQUAL(list.forwardSearch("a"), list.backwardSearch("a"));

    list.push_back("b");
    list.push_back("a");
    EXPECT_NOT_EQUAL(list.forwardSearch("b"), nullptr);
    EXPECT_NOT_EQUAL(list.backwardSearch("b"), nullptr);
    EXPECT_EQUAL(list.forwardSearch("b"), list.backwardSearch("b"));
    EXPECT_NOT_EQUAL(list.forwardSearch("a"), nullptr);
    EXPECT_NOT_EQUAL(list.backwardSearch("a"), nullptr);
    EXPECT_NOT_EQUAL(list.forwardSearch("a"), list.backwardSearch("a"));
    EXPECT_EQUAL(list.forwardSearch("a")->next_, list.forwardSearch("b"));
    EXPECT_EQUAL(list.forwardSearch("a"), list.forwardSearch("b")->prev_);
    EXPECT_EQUAL(list.backwardSearch("a")->prev_, list.forwardSearch("b"));
    EXPECT_EQUAL(list.backwardSearch("a"), list.forwardSearch("b")->next_);

    std::cout << "Completed searchTests!" << std::endl;
}

void sortTests() {
    CircularLinkedList list;
    std::vector<std::string> vec = {"y", "a", "x", "b", "w", "c", "q", "aa", "ab", "c", "wa", "ww"};
    for (const auto& v : vec) {
        list.push_back(v);
    }

    list.sort();
    std::sort(vec.begin(), vec.end());
    EXPECT_EQUAL(list.toVector(), vec);

    list.clear();
    list.push_back("a");
    list.sort();
    EXPECT_EQUAL(list.front(), "a");

    list.clear();
    list.sort();
    EXPECT_TRUE(list.empty());

    std::cout << "Completed sortTests!" << std::endl;
}

void ostreamTests() {
    {
        CircularLinkedList list;
        std::ostringstream ss;

        ss << list;
        EXPECT_STRING(ss.str(), "");
    }

    {
        CircularLinkedList list;
        std::ostringstream ss;

        list.push_back("a");
        ss << list;
        EXPECT_STRING(ss.str(), " <-> \"a\" <-> \n");
    }

    {
        CircularLinkedList list;
        std::ostringstream ss;

        list.push_back("a");
        list.push_back("b");
        ss << list;
        EXPECT_STRING(ss.str(), " <-> \"a\" <-> \"b\" <-> \n");
    }

    std::cout << "Completed ostreamTests!" << std::endl;
}

void istreamTests() {
    {
        CircularLinkedList list;
        std::istringstream ss("");

        ss >> list;
        EXPECT_TRUE(list.empty());
    }

    {
        CircularLinkedList list;
        std::istringstream ss("a");

        ss >> list;
        EXPECT_FALSE(list.empty());
        EXPECT_EQUAL(list.front(), "a");
        EXPECT_EQUAL(list.back(), "a");
    }

    {
        CircularLinkedList list;
        std::istringstream ss("a\nb");

        ss >> list;
        EXPECT_FALSE(list.empty());
        EXPECT_EQUAL(list.front(), "a");
        EXPECT_EQUAL(list.back(), "b");
        auto aPtr = list.forwardSearch("a");
        auto bPtr = list.forwardSearch("b");
        EXPECT_EQUAL(aPtr->next_, bPtr);
        EXPECT_EQUAL(bPtr->prev_, aPtr);
        EXPECT_EQUAL(bPtr->next_, aPtr);
        EXPECT_EQUAL(aPtr->prev_, bPtr);
    }
    std::cout << "Completed istreamTests!" << std::endl;
}

void runAllTests() {
    try {
        emptyListTest();
        pushBackTests();
        pushFrontTests();
        clearTests();
        popBackTests();
        popFrontTests();
        toVectorTests();
        deleteNodeTests();
        searchTests();
        sortTests();
        ostreamTests();
        istreamTests();
    } catch (const std::logic_error& exception) {
        std::cout << "Failed tests!" << std::endl;
        std::cout << exception.what() << std::endl;
        return;
    }
    std::cout << "All tests passed!" << std::endl;
}