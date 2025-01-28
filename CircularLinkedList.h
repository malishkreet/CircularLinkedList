#pragma once
#include <ostream>
#include <istream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

struct ListNode
{
    std::string value_;
    ListNode* next_ = this;
    ListNode* prev_ = this;

    ListNode(const std::string& value) : value_(value) {}
};

using NodePtr = ListNode*;

struct CircularLinkedList
{
public:
    CircularLinkedList() = default;
    CircularLinkedList(const CircularLinkedList&);
    CircularLinkedList(CircularLinkedList&&);
    CircularLinkedList& operator=(const CircularLinkedList&);
    CircularLinkedList& operator=(CircularLinkedList&&);

    bool empty() const;

    void clear();
    void deleteNode(NodePtr node);

    void push_back(const std::string&);
    void pop_back();
    std::string& back();
    const std::string& back() const;

    void push_front(const std::string&);
    void pop_front();
    std::string& front();
    const std::string& front() const;

    NodePtr forwardSearch(const std::string&) const;
    NodePtr backwardSearch(const std::string&) const;

    void sort();

    std::vector<std::string> toVector() const;

    ~CircularLinkedList();

    friend std::ostream& operator<< (std::ostream&, const CircularLinkedList&);
    friend std::ofstream& operator<< (std::ofstream&, const CircularLinkedList&);
    friend std::istream& operator>> (std::istream&, CircularLinkedList&);

private:
    bool hasExactlyOne() const;
    void insertAfter(NodePtr, NodePtr);

    void swap(NodePtr, NodePtr);
    NodePtr partition(NodePtr, NodePtr);
    void quickSort(NodePtr, NodePtr);

private:
    NodePtr first_ = nullptr;
};
