#include "CircularLinkedList.h"


CircularLinkedList::CircularLinkedList(const CircularLinkedList& other) {
    if (&other == this) {
        return;
    }

    *this = other;
}

CircularLinkedList::CircularLinkedList(CircularLinkedList&& other) {
    if (&other == this) {
        return;
    }

    first_ = other.first_;
    other.first_ = nullptr;
}

CircularLinkedList& CircularLinkedList::operator=(const CircularLinkedList& other) {
    if (&other == this) {
        return *this;
    }

    clear();
    if (other.empty()) {
        return *this;
    }

    if (other.hasExactlyOne()) {
        push_back(other.back());
        return *this;
    }

    NodePtr current = other.first_;
    do {
        push_back(current->value_);
        current = current->next_;
    } while (current != other.first_);

    return *this;
}

CircularLinkedList& CircularLinkedList::operator=(CircularLinkedList&& other) {
    if (&other == this) {
        return *this;
    }


    clear();
    first_ = other.first_;
    other.first_ = nullptr;

    return *this;
}

bool CircularLinkedList::empty() const {
    return first_ == nullptr;
}

void CircularLinkedList::clear() {
    if (empty()) {
        return;
    }

    NodePtr current = first_;
    do {
        NodePtr tmp = current->next_;
        delete current;
        current = tmp;
    } while (current != first_);
    first_ = nullptr;
}

void CircularLinkedList::push_back(const std::string& value) {
    NodePtr newNode = new ListNode(value);
    if (empty()) {
        first_ = newNode;
    } else {
        insertAfter(first_->prev_, newNode);
    }
}

void CircularLinkedList::pop_back() {
    if (empty()) {
        throw std::logic_error("Popping from empty CircularLinkedList");
    }

    if (hasExactlyOne()) {
        delete first_;
        first_ = nullptr;
    } else {
        deleteNode(first_->prev_);
    }
}

std::string& CircularLinkedList::back() {
    if (empty()) {
        throw std::logic_error("Getting value from empty CircularLinkedList");
    }

    return first_->prev_->value_;
}

const std::string& CircularLinkedList::back() const {
    if (empty()) {
        throw std::logic_error("Getting value from empty CircularLinkedList");
    }

    return first_->prev_->value_;
}

void CircularLinkedList::push_front(const std::string& value) {
    push_back(value);
    first_ = first_->prev_;
}

void CircularLinkedList::pop_front() {
    if (empty()) {
        throw std::logic_error("Popping from empty CircularLinkedList");
    }

    if (hasExactlyOne()) {
        delete first_;
        first_ = nullptr;
    } else {
        NodePtr next = first_->next_;
        deleteNode(first_);
        first_ = next;
    }
}

std::string& CircularLinkedList::front() {
    if (empty()) {
        throw std::logic_error("Getting value from empty CircularLinkedList");
    }

    return first_->value_;
}

const std::string& CircularLinkedList::front() const {
    if (empty()) {
        throw std::logic_error("Getting value from empty CircularLinkedList");
    }

    return first_->value_;
}

NodePtr CircularLinkedList::forwardSearch(const std::string& value) const {
    if (empty()) {
        return nullptr;
    }
    if (hasExactlyOne()) {
        return first_->value_ == value ? first_ : nullptr;
    }

    NodePtr current = first_;
    do {
        if (current->value_ == value) {
            return current;
        }
        current = current->next_;
    } while (current != first_);

    return nullptr;
}

NodePtr CircularLinkedList::backwardSearch(const std::string& value) const {
    if (empty()) {
        return nullptr;
    }
    if (hasExactlyOne()) {
        return first_->value_ == value ? first_ : nullptr;
    }

    NodePtr current = first_->prev_;
    do {
        if (current->value_ == value) {
            return current;
        }
        current = current->prev_;
    } while (current != first_);

    return nullptr;
}

void CircularLinkedList::deleteNode(NodePtr node) {
    if (node == nullptr) {
        throw std::logic_error("Deleting by null NodePtr");
    }

    if (empty()) {
        throw std::logic_error("Deleting from empty CircularLinkedList");
    }

    if (node == first_ && hasExactlyOne()) {
        delete first_;
        first_ = nullptr;
        return;
    }

    NodePtr next = node->next_;
    NodePtr prev = node->prev_;

    prev->next_ = next;
    next->prev_ = prev;

    delete node;
    if (node == first_) {
        first_ = next;
    }
}

void CircularLinkedList::sort() {
    if (empty() || hasExactlyOne()) {
        return;
    }
    NodePtr last = first_->prev_;
    first_->prev_ = nullptr;
    last->next_ = nullptr;
    quickSort(first_, last);
    first_->prev_ = last;
    last->next_ = first_;
}

std::vector<std::string> CircularLinkedList::toVector() const {
    if (empty()) {
        return {};
    }

    if (hasExactlyOne()) {
        return {back()};
    }

    std::vector<std::string> result;
    NodePtr current = first_;
    do {
        result.push_back(current->value_);
        current = current->next_;
    } while (current != first_);
    return result;
}

CircularLinkedList::~CircularLinkedList() {
    if (!empty()) {
        clear();
    }
}

bool CircularLinkedList::hasExactlyOne() const {
    return empty() ? false : first_->next_ == first_;
}

void CircularLinkedList::insertAfter(NodePtr location, NodePtr newNode) {
    newNode->prev_ = location;
    newNode->next_ = location->next_;

    location->next_->prev_ = newNode;
    location->next_ = newNode;
}

void CircularLinkedList::swap(NodePtr a, NodePtr b) {
    std::swap(a->value_, b->value_);
}

NodePtr CircularLinkedList::partition(NodePtr begin, NodePtr end) {
    std::string pivot = end->value_;
    NodePtr l = begin->prev_;

    for (NodePtr r = begin; r != end; r = r->next_) {
        if (r->value_ <= pivot) {
            l = (l == nullptr) ? begin : l->next_;
            swap(l, r);
        }
    }
    l = (l == nullptr) ? begin : l->next_;
    swap(l, end);
    return l;
}

void CircularLinkedList::quickSort(NodePtr begin, NodePtr end) {
    if (begin != nullptr && end != nullptr && begin != end && begin != end->next_) {
        NodePtr pivot = partition(begin, end);
        quickSort(begin, pivot->prev_);
        quickSort(pivot->next_, end);
    }
}

std::ostream& operator<< (std::ostream& stream, const CircularLinkedList& list) {
    if (list.empty()) {
        return stream;
    }

    if (list.hasExactlyOne()) {
        stream << " <-> \"" << list.first_->value_ << "\" <-> " << std::endl;
        return stream;
    }

    NodePtr current = list.first_;
    stream << " <-> ";
    do {
        stream << "\"" << current->value_ << "\" <-> ";
        current = current->next_;
    } while (current != list.first_);
    stream << std::endl;
    return stream;
}

std::ofstream& operator<< (std::ofstream& stream, const CircularLinkedList& list) {
    if (list.empty()) {
        return stream;
    }

    if (list.hasExactlyOne()) {
        stream << list.first_->value_ << std::endl;
        return stream;
    }

    NodePtr current = list.first_;
    do {
        stream << current->value_ << std::endl;
        current = current->next_;
    } while (current != list.first_);
    return stream;
}

std::istream& operator>> (std::istream& stream, CircularLinkedList& list) {
    while (!stream.eof()) {
        std::string line;
        stream >> line;
        if (!line.empty()) {
            list.push_back(line);
        }
    }
    return stream;
}