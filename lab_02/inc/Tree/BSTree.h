#pragma once

#include <iostream>
#include <memory>
#include <cstddef>

#include "Concepts.hpp"
#include "BaseTree.h"
#include "TreeIterator.h"
#include "RevTreeIterator.h"

namespace MyBSTree {

    template <TreeElem T>
    class BSTree: public BaseTree {
    public:
        friend class TreeIterator<T>;
        friend class RevTreeIterator<T>;

        using iterator = TreeIterator<T>;
        using reverse_iterator = RevTreeIterator<T>;

        using const_iterator = const TreeIterator<T>;
        using const_reverse_iterator = const RevTreeIterator<T>;

        using value_type = T;

    private:
        class Node;
        using BSTSharedPtr = typename std::shared_ptr<Node>;
        using BSTWeakPtr = typename std::weak_ptr<Node>;

    private:
        class Node : public std::enable_shared_from_this<Node> {
        public:
            Node() noexcept;
            explicit Node(const T &value);
            explicit Node(T &&value) noexcept;

            const T &getValue() const noexcept;
            const BSTSharedPtr &getLeft() const noexcept;
            const BSTSharedPtr &getRight() const noexcept;

            void setValue(const T &value) noexcept;
            void setLeft(const BSTSharedPtr &curNode) noexcept;
            void setRight(const BSTSharedPtr &curNode) noexcept;
            
            bool operator==(const Node &other) const;
            bool operator!=(const Node &other) const;

            BSTSharedPtr lookfor(const T &value) const;
            bool insert(const BSTSharedPtr &curNode);

            void setPath(std::stack<BSTWeakPtr> &curStack, const T &value) const;

            void setLeftPath(std::stack<BSTWeakPtr> &curStack) noexcept;
            void setRightPath(std::stack<BSTWeakPtr> &curStack) noexcept;
           
        private:
            BSTSharedPtr getThis();
        
        private:
            T value_;
            BSTSharedPtr left_;
            BSTSharedPtr right_;
        };

    public:
        BSTree() noexcept;
        explicit BSTree(std::initializer_list<T> list);
        explicit BSTree(const T *arr, const size_t size);
    
        explicit BSTree(const BSTree<T> &other);
        BSTree(BSTree<T> &&other) noexcept;

        template <IteratorT Iter>
        requires Assignable<typename Iter::value_type, T>
        explicit BSTree(Iter beg, Iter end);

        template <ContainerT Con>
        requires Convertible<typename Con::value_type, T> && Assignable<typename Con::value_type, T>
        explicit BSTree(const Con &container);

        BSTree<T> &operator=(const BSTree<T> &other);
        BSTree<T> &operator=(BSTree<T> &&other) noexcept;
        BSTree<T> &operator=(std::initializer_list<T> list);

        ~BSTree() noexcept = default;

        bool operator==(const BSTree<T> &other) const;
        bool operator!=(const BSTree<T> &other) const;

        bool insert(T &&value);
        bool insert(const T &value);

        bool contains(const T &value) const;
        iterator find(const T &value) const;

        template <IteratorT Iter>
        requires Assignable<typename Iter::value_type, T>
        bool remove(iterator pos);
        bool remove(const T &value);

        iterator begin() const noexcept;
        reverse_iterator rbegin() const noexcept;

        iterator end() const noexcept;
        reverse_iterator rend() const noexcept;

        BSTree intersection(const BSTree<T> &otherTree) const;
        BSTree &operator*=(const BSTree &otherTree);
        BSTree operator*(const BSTree &otherTree) const;

        BSTree unification(const BSTree<T> &otherTree) const;
        BSTree &operator+=(const BSTree &otherTree);
        BSTree operator+(const BSTree &otherTree) const;

        BSTree difference(const BSTree<T> &otherTree) const;
        BSTree &operator-=(const BSTree &otherTree);
        BSTree operator-(const BSTree &otherTree) const;

        BSTree symDifference(const BSTree<T> &otherTree) const;
        BSTree &operator^=(const BSTree &otherTree);
        BSTree operator^(const BSTree &otherTree) const;
        
        size_t size() const noexcept override;
        bool empty() const noexcept override;
        void clear() noexcept;

        template <typename P>
        friend std::ostream& operator<< (std::ostream &out, const BSTree<P> &tmpTree);

    protected:
        BSTSharedPtr deepCopy_(const BSTSharedPtr &tmpNode);

        BSTSharedPtr findMin_(const BSTSharedPtr &tmpNode);
        void replaceChild_(const BSTSharedPtr &parentNode);

        BSTSharedPtr find_(const T &value) const;
        BSTSharedPtr tryToMakeNode_(const T &value) const;
        
        void checkRoot_() const;

    private:
        BSTSharedPtr root_;
    };
}

#include "BSTree.hpp"