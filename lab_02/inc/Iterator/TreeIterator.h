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
    class TreeIterator: public BaseIterator {
    private:
        friend class BSTree<T>;

        using BSTSharedPtr = typename BSTree<T>::BSTSharedPtr;
        using BSTWeakPtr = typename BSTree<T>::BSTWeakPtr;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        TreeIterator() noexcept;
        TreeIterator(const BSTSharedPtr &tmpNode, bool last = false);
        TreeIterator(const BSTSharedPtr &rootNode, const BSTSharedPtr &tmpNode);
        
        TreeIterator(const TreeIterator<T> &other);
        TreeIterator(TreeIterator<T> &&other);

        TreeIterator<T> &operator=(const TreeIterator<T> &other);
        TreeIterator<T> &operator=(TreeIterator<T> &&other);

        operator bool() const;

        const T &operator*() const;
        const T *operator->() const;

        // префиксный
        TreeIterator<T> &operator++(); 
        TreeIterator<T> &operator--();
        // постфиксный
        TreeIterator<T> operator++(int);
        TreeIterator<T> operator--(int);

        bool operator==(const TreeIterator<T> &other) const;
        bool operator!=(const TreeIterator<T> &other) const;
        
    protected:
        void checkValidity_(int line) const;
        void checkInRange_(int line) const;

        void reset_();
    private:
        std::stack<BSTWeakPtr> stack_;
    };
}

#include "TreeIterator.hpp"

