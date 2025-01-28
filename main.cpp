#include "CircularLinkedList.h"
#include "CircularLinkedListTests.h"

#include <iostream>
#include <fstream>

void printOptions() {
    std::cout << "1. View list;" << std::endl;
    std::cout << "2. Push back;" << std::endl;
    std::cout << "3. Push front;" << std::endl;
    std::cout << "4. Pop back;" << std::endl;
    std::cout << "5. Pop front;" << std::endl;
    std::cout << "6. Erase;" << std::endl;
    std::cout << "7. Convert to array;" << std::endl;
    std::cout << "8. Sort;" << std::endl;
    std::cout << "9. Forward search;" << std::endl;
    std::cout << "10. Backward search;" << std::endl;
    std::cout << "11. Save to file and exit;" << std::endl;
}

void printList(const CircularLinkedList& list) {
    if (list.empty()) {
        std::cout << "List is empty now!" << std::endl;
        return;
    }
    std::cout << "Current state of list: " << std::endl;
    std::cout << list;
}

void pushBack(CircularLinkedList& list) {
    std::string s;
    std::cout << "Enter new string to push back: ";
    std::cin >> s;
    list.push_back(s);
    std::cout << "String " << s << " successfully pushed!" << std::endl;
    printList(list);
}

void pushFront(CircularLinkedList& list) {
    std::string s;
    std::cout << "Enter new string to push front: ";
    std::cin >> s;
    list.push_front(s);
    std::cout << "String " << s << " successfully pushed!" << std::endl;
    printList(list);
}

void popBack(CircularLinkedList& list) {
    if (list.empty()) {
        std::cout << "Trying to pop back from empty list!" << std::endl;
        return;
    }
    list.pop_back();
    std::cout << "Successfully executed pop back!" << std::endl;
    printList(list);
}

void popFront(CircularLinkedList& list) {
    if (list.empty()) {
        std::cout << "Trying to pop front from empty list!" << std::endl;
        return;
    }
    list.pop_front();
    std::cout << "Successfully executed pop front" << std::endl;
    printList(list);
}

void erase(CircularLinkedList& list) {
    std::string s;
    std::cout << "Enter string to erase: ";
    std::cin >> s;
    NodePtr pointer = list.forwardSearch(s);
    if (pointer == nullptr) {
        std::cout << "String " << s << " not fond in list!" << std::endl;
        return;
    }
    list.deleteNode(pointer);
    std::cout << "Successfully erased string " << s << std::endl;
    printList(list);
}

void toArray(const CircularLinkedList& list) {
    std::vector<std::string> vec = list.toVector();
    std::cout << "Successfully converted list to vector!" << std::endl;
    std::cout << "Result: [";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void sort(CircularLinkedList& list) {
    if (list.empty()) {
        std::cout << "No need to sort empty list!" << std::endl;
        return;
    }
    list.sort();
    std::cout << "List was successfully sorted!" << std::endl;
    printList(list);
}

void forwardSearch(CircularLinkedList& list) {
    std::string s;
    std::cout << "Enter string for forward search: ";
    std::cin >> s;
    NodePtr pointer = list.forwardSearch(s);
    if (pointer == nullptr) {
        std::cout << "String " << s << " not found in list!" << std::endl;
        return;
    }

    std::cout << "String " << s << " found in list!" << std::endl;
    std::cout << "Addres of node: " << pointer << std::endl;
}

void backwardSearch(CircularLinkedList& list) {
    std::string s;
    std::cout << "Enter string for backward search: ";
    std::cin >> s;
    NodePtr pointer = list.backwardSearch(s);
    if (pointer == nullptr) {
        std::cout << "String " << s << " not found in list!" << std::endl;
        return;
    }

    std::cout << "String " << s << " found in list!" << std::endl;
    std::cout << "Addres of node: " << pointer << std::endl;
}

void saveToFile(CircularLinkedList& list) {
    std::ofstream fout("out.txt");
    fout << list;
    std::cout << "List successfully saved!" << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Only one command line argument expected: <filename>" << std::endl;
        return -1;
    }

    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        std::cout << "Cannot open file " << argv[1] << std::endl;
        return -1;
    }

    CircularLinkedList list;
    fin >> list;

    bool exitRequested = false;

    while (!exitRequested) {
        int command;
        printOptions();
        std::cout << "-----------------------------------------------------" << std::endl;
        std::cout << "Please, select operation (enter index of operation): ";
        std::cin >> command;

        switch (command) {
        case 1:
            printList(list);
            break;
        case 2:
            pushBack(list);
            break;
        case 3:
            pushFront(list);
            break;
        case 4:
            popBack(list);
            break;
        case 5:
            popFront(list);
            break;
        case 6:
            erase(list);
            break;
        case 7:
            toArray(list);
            break;
        case 8:
            sort(list);
            break;
        case 9:
            forwardSearch(list);
            break;
        case 10:
            backwardSearch(list);
            break;
        case 11:
            saveToFile(list);
            exitRequested = true;
            break;
        default:
            std::cout << "Unexpected option!" << std::endl;
            break;
        }
        std::cout << "-----------------------------------------------------" << std::endl;
    }
}