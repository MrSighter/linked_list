#ifndef DATA_STRUCTURES_LIST_HPP
#define DATA_STRUCTURES_LIST_HPP

#include <ostream>
#include <exception>

template<typename Key, typename Info>
class list {
private:
    //data class
    class node {
    private:        //data of a node
        Info info;
        Key key;
        node *next;
    public:

        //ctors and dtors
        node(const Key &key, const Info &info, node *nextNode) : key(key), info(info), next(nextNode) {}
        ~node() = default;
        node(const node &other) : key(other.key), info(other.info), next(nullptr) {}

        //getters
        Key &getKey() {
            return key;
        }
        Info &getInfo() {
            return info;
        }
        node *getNext() const {
            return next;
        }

        //setters
        void setNext(const Key &newKey, const Info &newInfo, node *nextNode) {
            next = new node(newKey, newInfo, nextNode);
        }
        void setNext(node *other) {
            next = other;
        }
        void setKey(const Key &newKey) {
            key = newKey;
        }
        void setInfo(const Info &newInfo) {
            info = newInfo;
        }

        //operators
        bool operator==(const node &other) {
            return key == other.key && info == other.info;
        }
        friend std::ostream &operator<<(std::ostream &os, const node &node) {
            os << node.key << "\t" << node.info;
            return os;
        }

        friend class list;
    };

    //private information of a class
    node *sentinel;
    int size;
    Key defKey;
    Info defInfo;
public:

    //iterator classes for ease of use
    class iterator {
    private:
        //node pointer for iteration and owner pointer for checking if iterator belongs to a sequence
        node *current;
        const list *owner;
    public:
        //ctor
        iterator(const list *own, node *c) : current(c), owner(own) {};
        iterator(const iterator &other) : current(other.current), owner(other.owner) {};

        //operators
        iterator &operator=(const iterator &other) {
            if (this == other) return *this;
            current = other.current;
            owner = other.owner;
            return *this;
        }
        std::pair<Key, Info> operator*() {
            return std::make_pair(current->key, current->info);
        }
        iterator &operator++() {
            current = current->getNext();
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        iterator &operator+(int reps) {
            for (int i = 0; i < reps; ++i) ++(*this);
            return *this;
        }
        bool operator==(const iterator &other) {
            return current == other.current && owner == other.owner;
        }
        bool operator!=(const iterator &other) {
            return !(*this == other);
        }

        //getters
        Key &getKey() {
            return current->getKey();
        }
        Info &getInfo() {
            return current->getInfo();
        }

        //setter
        void setInfo(const Info &newInfo) {
            current->setInfo(newInfo);
        }

        friend class list;
    };
    class const_iterator {
    private:
        //node pointer for iteration and owner pointer for checking if iterator belongs to a sequence
        node *current;
        const list *owner;
    public:
        //ctors
        const_iterator(const list *own, node *c) : current(c), owner(own) {};
        const_iterator(const const_iterator &other) : current(other.current), owner(other.owner) {};

        //operators
        const_iterator &operator=(const iterator &other) {
            if (this == other) return *this;
            current = other.current;
            owner = other.owner;
            return *this;
        }
        std::pair<Key, Info> operator*() const {
            return std::make_pair(current->key, current->info);
        }
        const_iterator &operator++() {
            current = current->getNext();
            return *this;
        }
        const_iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        const_iterator &operator+(int reps) {
            for (int i = 0; i < reps; ++i) ++(*this);
            return *this;
        }
        bool operator==(const const_iterator &other) {
            return current == other.current && owner == other.owner;
        }
        bool operator!=(const const_iterator &other) {
            return !(*this == other);
        }

        //getters
        const Key &getKey() const {
            return current->getKey();
        }
        const Info &getInfo() const {
            return current->getInfo();
        }

        friend class list;
    };

    //ctors and dtors
    list(const Key &defaultKey, const Info &defaultInfo) {
        defKey = defaultKey;
        defInfo = defaultInfo;
        sentinel = new node(defKey, defInfo, nullptr);
        sentinel->setNext(sentinel);
        size = 0;
    }
    list(const list &other) {
        sentinel = new node(defKey, defInfo);
        size = 0;
        if (other.isEmpty()) return;
        auto i = other.begin();
        pushFront(i);
        ++i;
        for (i; i != other.end(); ++i) {
            pushBack(i);
        }
    }
    ~list() {
        clear();
    }

    //utility functions and getters
    bool isEmpty() const {
        return sentinel->getNext() == sentinel;
    }
    int getLength() const {
        return size;
    }
    const Key &getDefaultKey() const {
        return defKey;
    }
    const Info &getDefaultInfo() const {
        return defInfo;
    }

    //functions used to iterate over a list
    iterator begin() {
        return iterator(this, sentinel->getNext());
    }
    const_iterator begin() const {
        return const_iterator(this, sentinel->getNext());
    }
    iterator end() {
        return iterator(this, sentinel);
    }
    const_iterator end() const {
        return const_iterator(this, sentinel);
    }

    //push/popFront
    iterator pushFront(const Key &newKey, const Info &newInfo) {
        size++;
        sentinel->setNext(new node(newKey, newInfo, sentinel->getNext()));
        return iterator(this, sentinel->getNext());
    }
    iterator pushBack(const Key &newKey, const Info &newInfo) {
        size++;
        sentinel->setNext(sentinel->getKey(), sentinel->getInfo(), sentinel->getNext());
        sentinel->setKey(newKey);
        sentinel->setInfo(newInfo);
        iterator a(this, sentinel);
        sentinel = sentinel->getNext();
        return a;

    }
    void popFront() {
        if (isEmpty())return;
        size--;
        node *toDel = sentinel->getNext();
        sentinel->setNext(sentinel->getNext()->getNext());
        delete toDel;
    }
    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }


    //used for finding how many nodes of a given key are present in a list
    int getNumberOfOccurrences(const Key &searchedKey) {
        int counter = 0;
        for (iterator i = begin(); i != end(); ++i) {
            if (i.getKey() == searchedKey)counter++;
        }
        return counter;
    }

    //find/insert/pop
    iterator find(const Key &searchedKey, unsigned int occurrence = 0) {
        if (isEmpty()) return iterator(this, sentinel);
        int occ = 0;
        for (auto i = begin(); i != end(); ++i) {
            if (searchedKey == i.getKey()) {
                if (occ == occurrence) return i;
                occ++;
            }
        }
        return iterator(this, sentinel);
    }
    const_iterator find(const Key &searchedKey, unsigned int occurrence = 0) const {
        if (isEmpty()) return const_iterator(this, sentinel);
        int occ = 0;
        for (auto i = begin(); i != end(); ++i) {
            if (searchedKey == i.getKey()) {
                if (occ == occurrence) return i;
                occ++;
            }
        }
        return const_iterator(this, sentinel);
    }
    iterator insert(const Key &newKey, const Info &newInfo, iterator position) {
        size++;
        position.current->setNext(
                new node(position.current->getKey(), position.current->getInfo(), position.current->getNext()));
        if (position.current == sentinel) sentinel = sentinel->getNext();
        position.current->setKey(newKey);
        position.current->setInfo(newInfo);
        return position;
    }
    iterator pop(iterator position) {
        if (position == end())
            throw std::out_of_range(
                    "Iterator is not pointing towards any element of the list. Cannot delete sentinel node.");
        size--;
        position.current->setKey(position.current->getNext()->getKey());
        position.current->setInfo(position.current->getNext()->getInfo());
        node *toDel = position.current->getNext();
        if (toDel == sentinel)sentinel = position.current;
        position.current->setNext(position.current->getNext()->getNext());
        delete toDel;
        return position;

    }

    //ostream operator
    friend std::ostream &operator<<(std::ostream &os, const list<Key, Info> &seq) {
        os << "Default: " << seq.getDefaultKey() << "\t" << seq.getDefaultInfo() << "\n";
        for (auto i = seq.begin(); i != seq.end(); ++i) {
            os << i.getKey() << "\t" << i.getInfo() << "\n";
        }
        return os;
    }
};

#endif //DATA_STRUCTURES_LIST_HPP