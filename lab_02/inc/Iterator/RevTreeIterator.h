#pragma once

#include <memory>
#include <iterator>
#include <iostream>
#include <stack>

#include "BaseIterator.h"
#include "BSTree.h"

namespace MyBSTree {
    
    template <TreeElem T>
    class BSTree;

    template <TreeElem T>
    class RevTreeIterator: public BaseIterator {
    private:
        friend class BSTree<T>;

        using BSTSharedPtr = typename BSTree<T>::BSTSharedPtr;
        using BSTWeakPtr = typename BSTree<T>::BSTWeakPtr;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        RevTreeIterator() noexcept;
        RevTreeIterator(const BSTSharedPtr &tmpNode, bool last = false);
        RevTreeIterator(const BSTSharedPtr &rootNode, const BSTSharedPtr &tmpNode);
        
        RevTreeIterator(const RevTreeIterator<T> &other);
        RevTreeIterator(RevTreeIterator<T> &&other);

        RevTreeIterator<T> &operator=(const RevTreeIterator<T> &other);
        RevTreeIterator<T> &operator=(RevTreeIterator<T> &&other);

        operator bool() const;

        const T &operator*() const;
        const T *operator->() const;

        // префиксный
        RevTreeIterator<T> &operator++(); 
        RevTreeIterator<T> &operator--();
        // постфиксный
        RevTreeIterator<T> operator++(int);
        RevTreeIterator<T> operator--(int);

        bool operator==(const RevTreeIterator<T> &other) const;
        bool operator!=(const RevTreeIterator<T> &other) const;

    protected:
        void checkValidity_(int line) const;
        void checkInRange_(int line) const;

        void reset_();
        
    private:
        std::stack<BSTWeakPtr> stack_;
    };
}

#include "RevTreeIterator.hpp"
