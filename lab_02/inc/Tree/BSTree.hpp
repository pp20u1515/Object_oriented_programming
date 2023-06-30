#pragma once

#include <iostream>
#include <cstddef>
#include <stack>

#include "TreeError.h"
#include "BSTree.h"

namespace MyBSTree {

    template <TreeElem T> 
    BSTree<T>::BSTree() noexcept : 
        root_(nullptr) 
    {}

    template <TreeElem T>
    BSTree<T>::BSTree(std::initializer_list<T> list) {

        for (auto val: list) 
            insert(std::move(val));
    }

    template <TreeElem T>
    BSTree<T>::BSTree(const BSTree<T> &other) : 
        root_(deepCopy_(other.root_))
    {}

    template <TreeElem T>
    BSTree<T>::BSTree(BSTree<T> &&other) noexcept:
        root_(std::exchange(other.root_, nullptr))
    {}

    template <TreeElem T>
    template <IteratorT Iter>
    requires Assignable<typename Iter::value_type, T>
    BSTree<T>::BSTree(Iter beg, Iter end) {

        for (Iter curIter = beg; curIter != end; ++curIter)
            insert(*curIter);
    }

    template <TreeElem T>
    template <ContainerT Con>
    requires Convertible<typename Con::value_type, T> && Assignable<typename Con::value_type, T>
    BSTree<T>::BSTree(const Con &container) {

        for (const auto &elem: container)
            insert(elem);
    }

    template <TreeElem T>
    BSTree<T>::BSTree(const T *arr, const size_t size) {

        for (size_t i = 0; i != size; ++i)
            insert(arr[i]);
    }

    template <TreeElem T>
    BSTree<T> &BSTree<T>::operator=(const BSTree<T> &other) {
        root_ = deepCopy_(other.root_);
        return *this;
    }

    template <TreeElem T>
    BSTree<T> &BSTree<T>::operator=(BSTree<T> &&other) noexcept {
        root_ = std::exchange(other.root_, nullptr);
        return *this;
    }

    template <TreeElem T>
    BSTree<T> &BSTree<T>::operator=(std::initializer_list<T> list) {
        
        for (const auto &elem: list)
            insert(elem);

        return *this;
    }

    template <TreeElem T>
    typename BSTree<T>::BSTSharedPtr BSTree<T>::deepCopy_(const BSTSharedPtr &tmpNode) {

        if (!tmpNode)
            return nullptr;

        std::stack<BSTSharedPtr> curStack;
        BSTSharedPtr newNode = tryToMakeNode_(tmpNode->getValue());

        curStack.emplace(newNode);
        curStack.emplace(tmpNode);

        while(!curStack.empty()) {

            BSTSharedPtr copyNode = curStack.top();
            curStack.pop();
            BSTSharedPtr newNode = curStack.top();
            curStack.pop();

            if (copyNode->getLeft()) {
                const T& curValue = copyNode->getLeft()->getValue();
                BSTSharedPtr curNode = tryToMakeNode_(curValue);

                newNode->setLeft(curNode);

                curStack.emplace(newNode->getLeft());
                curStack.emplace(copyNode->getLeft());
            }
            
            if (copyNode->getRight()) {
                const T& curValue = copyNode->getRight()->getValue();
                BSTSharedPtr curNode = tryToMakeNode_(curValue);

                newNode->setRight(curNode);

                curStack.emplace(newNode->getRight());
                curStack.emplace(copyNode->getRight());
            }
        }

        return newNode;
    }

    template <TreeElem T>
    typename BSTree<T>::BSTSharedPtr BSTree<T>::tryToMakeNode_(const T &value) const {
        
        BSTSharedPtr tmpNode;

        try {
            tmpNode = std::make_shared<Node>(value);
        }
        catch (const std::bad_alloc &e) {
            time_t curTime = time(nullptr);
            auto curLoc = std::source_location::current();
            
            throw TreeMemoryError(
                curLoc.file_name(),
                curLoc.function_name(),
                __LINE__,
                ctime(&curTime)
            );
        }

        return tmpNode;
    }

    template <TreeElem T>
    void BSTree<T>::checkRoot_() const {
        
        if (!root_) {
            time_t curTime = time(nullptr);
            auto curLoc = std::source_location::current();
            
            throw TreeInvalidRootError(
                curLoc.file_name(),
                curLoc.function_name(),
                __LINE__,
                ctime(&curTime)
            );
        }
    }

    template <TreeElem T>
    bool BSTree<T>::insert(const T &value) {

        BSTSharedPtr curNode = tryToMakeNode_(value);

        if (!root_) {
            root_ = curNode;
            return true;
        }

        return root_->insert(curNode);
    }

    template <TreeElem T>
    bool BSTree<T>::insert(T &&value) {
       
       BSTSharedPtr curNode = tryToMakeNode_(value);

        if (!root_) {
            root_ = curNode;
            return true;
        }

        return root_->insert(curNode);
    }

    template <TreeElem T>
    BSTree<T>::iterator BSTree<T>::find(const T &value) const {
        auto tmpNode = find_(value);
        return {root_, tmpNode};
    }

    template <TreeElem T>
    bool BSTree<T>::contains(const T &value) const {
        return nullptr != find_(value);
    }

    template <TreeElem T>
    typename BSTree<T>::BSTSharedPtr BSTree<T>::find_(const T &value) const {
    
        checkRoot_();

        BSTSharedPtr curNode = root_;
        return curNode->lookfor(value);
    }

    template <TreeElem T>
    typename BSTree<T>::BSTSharedPtr BSTree<T>::findMin_(const BSTSharedPtr &nodeTmp) {
        
        BSTSharedPtr curNode = nodeTmp;

        while (curNode->getLeft())
            curNode = curNode->getLeft();
        
        return curNode;
    }

    template <TreeElem T>
    bool BSTree<T>::remove(const T &value) {

        BSTSharedPtr curNode = root_, prevNode = root_;

        while (curNode && curNode->getValue() != value) {
            prevNode = curNode;

            if (curNode->getValue() < value)
                curNode = curNode->getRight();
            else
                curNode = curNode->getLeft();
        }

        if (!curNode)
            return false;

        if (curNode->getLeft() && curNode->getRight()) {
            BSTSharedPtr minNode = findMin_(curNode->getRight());

            if (curNode->getRight() != minNode) {
                replaceChild_(curNode->getRight());

                minNode->setRight(curNode->getRight());
            }

            minNode->setLeft(curNode->getLeft());

            if (prevNode == root_)
                root_ = minNode;
            else {
                if (prevNode->getValue() > value)
                    prevNode->setLeft(minNode);
                else    
                    prevNode->setRight(minNode);
            }
        }
        else {
            BSTSharedPtr childNode = curNode->getLeft() ? curNode->getLeft() : curNode->getRight();
            
            // replaceChild_(curNode);

            if (curNode == root_)
                root_ = childNode;
            else 
                if (prevNode->getValue() > value)
                    prevNode->setLeft(childNode);
                else    
                    prevNode->setRight(childNode);
        } 

        curNode.reset();

        return true;
    }


    template <TreeElem T>
    BSTree<T> BSTree<T>::intersection(const BSTree<T> &otherTree) const {

        BSTree curTree;

        for (auto &elem: *this) {

            if (otherTree.contains(elem))
                curTree.insert(elem);
        }

        return curTree;
    }

    template <TreeElem T>
    BSTree<T> BSTree<T>::unification(const BSTree<T> &otherTree) const {

        BSTree curTree;

        for (auto &elem: *this)
            curTree.insert(elem);

        for (auto &elem: otherTree)
            curTree.insert(elem);

        return curTree;
    }

    template <TreeElem T>
    BSTree<T> BSTree<T>::difference(const BSTree<T> &otherTree) const {

        BSTree curTree;

        for (auto &elem: *this) {

            if (!otherTree.contains(elem))
                curTree.insert(elem);
        }

        return curTree;
    }

    template <TreeElem T>
    BSTree<T> BSTree<T>::symDifference(const BSTree<T> &otherTree) const {

        BSTree curTree;

        for (auto &elem: *this) {

            if (!otherTree.contains(elem))
                curTree.insert(elem);
        }

        for (auto &elem: otherTree) {

            if (!contains(elem))
                curTree.insert(elem);
        }

        return curTree;
    }

    template <TreeElem T>
    BSTree<T> &BSTree<T>::operator+=(const BSTree<T> &otherTree) {

        for (auto &val: otherTree)
            insert(val);

        return *this;
    }

    template <TreeElem T>
    BSTree<T> &BSTree<T>::operator-=(const BSTree<T> &otherTree) {

        for (auto &val: otherTree)
            remove(val);

        return *this;
    }

    template <TreeElem T>
    BSTree<T> &BSTree<T>::operator*=(const BSTree<T> &otherTree) {

        std::stack<T> curStack;

        for (auto &val: *this) {
            
            if (!(otherTree.contains(val)))
                curStack.emplace(val);
        }

        while (!curStack.empty()) {
            remove(curStack.top());
            curStack.pop();
        }

        return *this;
    }

    template <TreeElem T>
    BSTree<T> &BSTree<T>::operator^=(const BSTree<T> &otherTree) {

        for (auto &val: otherTree) {
            if (contains(val))
                insert(val);
            else    
                remove(val);
        }

        return *this;
    }

    template <TreeElem T>
    BSTree<T> BSTree<T>::operator+(const BSTree<T> &otherTree) const {
        return unification(otherTree);
    }

    template <TreeElem T>
    BSTree<T> BSTree<T>::operator-(const BSTree<T> &otherTree) const {
        return difference(otherTree);
    }

    template <TreeElem T>
    BSTree<T> BSTree<T>::operator*(const BSTree<T> &otherTree) const {
        return intersection(otherTree);
    }

    template <TreeElem T>
    BSTree<T> BSTree<T>::operator^(const BSTree<T> &otherTree) const {
        return symDifference(otherTree);
    }

    template <TreeElem T>
    template <IteratorT Iter>
    requires Assignable<typename Iter::value_type, T>
    bool BSTree<T>::remove(iterator pos) {
        return remove(*pos);
    }

    template <TreeElem T>
    bool BSTree<T>::operator!=(const BSTree<T> &other) const {
        
        for (auto it1 = begin(), it2 = other.end(); it1 != end() && it2 != other.end(); ++it1, ++it2) {
            
            if (*it1 != *it2)
                return false;
        }

        return true;
    }

    template <TreeElem T>
    bool BSTree<T>::operator==(const BSTree<T> &other) const {
        return !(*this == other);
    }

    template <TreeElem T>
    void BSTree<T>::replaceChild_(const BSTSharedPtr &curNode) {

        BSTSharedPtr tmpNode = curNode, prevNode = curNode;

        while (tmpNode->getLeft()) {
            prevNode = tmpNode;
            tmpNode = tmpNode->getLeft();
        }

        prevNode->setLeft(tmpNode->getRight());
    }

    template <TreeElem T>
    BSTree<T>::iterator BSTree<T>::begin() const noexcept {
        return {root_};
    }

    template <TreeElem T>
    BSTree<T>::iterator BSTree<T>::end() const noexcept {
        return {root_, true};
    }

    template <TreeElem T>
    BSTree<T>::reverse_iterator BSTree<T>::rbegin() const noexcept {
        return {root_};
    }

    template <TreeElem T>
    BSTree<T>::reverse_iterator BSTree<T>::rend() const noexcept {
        return {root_, true};
    }

    template <TreeElem T>
    void BSTree<T>::Node::setValue(const T &value) noexcept {
        value_ = value;
    }

    template <TreeElem T>
    void BSTree<T>::Node::setLeft(const BSTSharedPtr &curNode) noexcept {
        left_= curNode;
    }

    template <TreeElem T>
    void BSTree<T>::Node::setRight(const BSTSharedPtr &curNode) noexcept {
        right_ = curNode;
    }

    template <TreeElem T>
    const T &BSTree<T>::Node::getValue() const noexcept {
        return value_;
    }

    template <TreeElem T>
    const BSTree<T>::BSTSharedPtr &BSTree<T>::Node::getLeft() const noexcept {
        return left_;
    }

    template <TreeElem T>
    const BSTree<T>::BSTSharedPtr &BSTree<T>::Node::getRight() const noexcept {
        return right_;
    }

    template <TreeElem T>
    BSTree<T>::Node::Node() noexcept : 
        value_{},
        left_(nullptr), 
        right_(nullptr)
    {} 

    template <TreeElem T>
    BSTree<T>::Node::Node(const T &value) : 
        value_(value),
        left_(nullptr), 
        right_(nullptr)
    {} 

    template <TreeElem T>
    BSTree<T>::Node::Node(T &&value) noexcept: 
        value_(value),
        left_(nullptr), 
        right_(nullptr)
    {} 

    template <TreeElem T> 
    bool BSTree<T>::Node::operator!=(const Node &other) const {
        return getValue() != other.getValue();
    }

    template <TreeElem T> 
    bool BSTree<T>::Node::operator==(const Node &other) const {
        return getValue() == other.getValue();
    }

    template <TreeElem T> 
    size_t BSTree<T>::size() const noexcept{
        
        size_t size = 0;

        for (const auto &elem : *this)
            ++size;

        return size;
    }

    template <TreeElem T> 
    bool BSTree<T>::empty() const noexcept {
        return root_ == nullptr;
    }

    template <TreeElem T> 
    void BSTree<T>::clear() noexcept {
        root_ == nullptr;
    }

    template <typename P>
    std::ostream& operator<< (std::ostream &out, const BSTree<P> &tmpTree) {
        
        out << "[";
        
        if (!tmpTree.root_)
            out << " empty tree! ";
        else {
            for (const auto &elem : tmpTree)
                out << elem << ", ";
        }

        out << "]";

        return out;
    }

    template <TreeElem T> 
    BSTree<T>::BSTSharedPtr BSTree<T>::Node::lookfor(const T &value) const {

        auto curNode = this->shared_from_this();

        while (curNode && curNode->value_ != value) {
            if (curNode->value_ < value)
                curNode = curNode->right_;
            else
                curNode = curNode->left_;
        }

        return std::const_pointer_cast<BSTree<T>::Node>(curNode);
    }

    template <TreeElem T> 
    bool BSTree<T>::Node::insert(const BSTSharedPtr &curNode) {

        BSTSharedPtr tmpNode = std::const_pointer_cast<BSTree<T>::Node>(getThis());
        BSTSharedPtr prevNode = tmpNode;

        while (tmpNode) {

            prevNode = tmpNode;
            if (tmpNode->getValue() < curNode->getValue())
                tmpNode = tmpNode->getRight();
            else if (tmpNode->getValue() > curNode->getValue())
                tmpNode = tmpNode->getLeft();
            else
                return false;
        }

        if (prevNode->getValue() < curNode->getValue())
            prevNode->setRight(curNode);
        else
            prevNode->setLeft(curNode);

        return true;
    }

    template <TreeElem T>
    void BSTree<T>::Node::setPath(std::stack<BSTWeakPtr> &curStack, const T &value) const {
        
        BSTSharedPtr curNode = std::const_pointer_cast<BSTree<T>::Node>(this->shared_from_this());

        while (curNode && curNode->getValue() != value) {

            curStack.emplace(curNode);

            if (curNode->getValue() < value)
                curNode = curNode->getRight();
            else
                curNode = curNode->getLeft();
        }

        if (curNode)
            curStack.emplace(curNode);
        else
            curStack.emplace();
    }

    template <TreeElem T>
    void BSTree<T>::Node::setLeftPath(std::stack<BSTWeakPtr> &curStack) noexcept {

        curStack.emplace(getThis());
        BSTree<T>::BSTSharedPtr curNode = left_;

        while (curNode) {
            curStack.emplace(curNode);
            curNode = curNode->left_;
        } 
    }

    template <TreeElem T>
    void BSTree<T>::Node::setRightPath(std::stack<BSTWeakPtr> &curStack) noexcept {
        
        curStack.emplace(getThis());
        BSTree<T>::BSTSharedPtr curNode = right_;

        while (curNode) {
            curStack.emplace(curNode);
            curNode = curNode->right_;
        }
    }

    template <TreeElem T>
    inline BSTree<T>::BSTSharedPtr BSTree<T>::Node::getThis() {
        return this->shared_from_this();
    }
};
