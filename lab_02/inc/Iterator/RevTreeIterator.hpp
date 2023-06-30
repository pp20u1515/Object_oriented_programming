#pragma once

#include "RevTreeIterator.h"
#include "IteratorError.h"

namespace MyBSTree {
    
    template <TreeElem T>
    RevTreeIterator<T>::RevTreeIterator() noexcept :
        stack_()
    {}

    template <TreeElem T>
    RevTreeIterator<T>::RevTreeIterator(const BSTSharedPtr &rootNode, bool last) {

        if (!rootNode) 
            stack_.emplace();
        else if (!last)
            rootNode->setRightPath(stack_);
        else {   
            rootNode->setLeftPath(stack_);
            stack_.emplace();
        }
    }

    template <TreeElem T>
    RevTreeIterator<T>::RevTreeIterator(const BSTSharedPtr &rootNode, const BSTSharedPtr &tmpNode) {
        
        if (tmpNode) 
            rootNode->setPath(stack_, tmpNode->getValue());
        else {   
            rootNode->setLeftPath(stack_);
            stack_.emplace(tmpNode);
        }
    }

    template <TreeElem T>
    RevTreeIterator<T>::RevTreeIterator(const RevTreeIterator<T> &other) :
        stack_(other.stack_)
    {}

    template <TreeElem T>
    RevTreeIterator<T>::RevTreeIterator(RevTreeIterator<T> &&other) :
        stack_(std::move(other.stack_))
    {}

    template <TreeElem T>
    RevTreeIterator<T> &RevTreeIterator<T>::operator=(const RevTreeIterator<T> &other) {
        other.checkValidity_(__LINE__);
        
        stack_ = other.stack_;
        return *this;
    }

    template <TreeElem T>
    RevTreeIterator<T> &RevTreeIterator<T>::operator=(RevTreeIterator<T> &&other) {
        other.checkValidity_(__LINE__);

        stack_ = std::move(other.stack_);
        return *this;
    }

    template <TreeElem T>
    RevTreeIterator<T>::operator bool() const {
        return !stack_.empty() && !stack_.top().expired();
    }

    template <TreeElem T>
    const T &RevTreeIterator<T>::operator*() const {
        checkValidity_(__LINE__);
        checkInRange_(__LINE__);
        
        return stack_.top().lock()->getValue();
    }

    template <TreeElem T>
    const T *RevTreeIterator<T>::operator->() const {
        checkValidity_(__LINE__);
        checkInRange_(__LINE__);

        return &(stack_.top().lock()->getValue());
    }

    template <TreeElem T>
    RevTreeIterator<T> &RevTreeIterator<T>::operator--() {
        
        if (stack_.empty())
            return *this;

        if (stack_.top().expired()) {
            stack_.pop();
            return *this;
        };

        BSTSharedPtr tmpNode = stack_.top().lock();

        if (tmpNode->getRight())
            tmpNode->getRight()->setLeftPath(stack_);
        else {
            stack_.pop();

            while (!stack_.empty() && stack_.top().lock()->getRight() == tmpNode) {
                
                BSTSharedPtr nextNode = stack_.top().lock();
                stack_.pop();

                tmpNode = nextNode;
            }

            if (stack_.empty()) 
                stack_.emplace();
        }

        return *this;
    }

    template <TreeElem T>
    RevTreeIterator<T> &RevTreeIterator<T>::operator++() {

        if (!(*this))
            return *this;

        BSTSharedPtr tmpNode = stack_.top().lock();

        if (tmpNode->getLeft())
            tmpNode->getLeft()->setRightPath(stack_);
        else {
            stack_.pop();

            while (!stack_.empty() && stack_.top().lock()->getLeft() == tmpNode) {
                
                BSTSharedPtr nextNode = stack_.top().lock();
                stack_.pop();

                tmpNode = nextNode;
            }

            if (stack_.empty())
                stack_.emplace();
        }
        
        return *this;
    }

    template <TreeElem T>
    RevTreeIterator<T> RevTreeIterator<T>::operator++(int) {
        RevTreeIterator<T> tempIter{*this};
        ++(*this);
        return tempIter;
    }

    template <TreeElem T>
    RevTreeIterator<T> RevTreeIterator<T>::operator--(int) {
        RevTreeIterator<T> tempIter{*this};
        --(*this);
        return tempIter;
    }

    template <TreeElem T>
    bool RevTreeIterator<T>::operator==(const RevTreeIterator<T> &other) const {

        if (!stack_.empty() && !other.stack_.empty()) {
            
            BSTSharedPtr Node1 = other.stack_.top().lock();
            BSTSharedPtr Node2 = stack_.top().lock();

            return Node1 == Node2;
        }

        return false;
    }

    template <TreeElem T>
    bool RevTreeIterator<T>::operator!=(const RevTreeIterator<T> &other) const {
        return !(*this == other);
    }

    template <TreeElem T>
    void RevTreeIterator<T>::reset_() {
        while (!stack_.empty())
            stack_.pop();
    }

    template <TreeElem T>
    void RevTreeIterator<T>::checkValidity_(int line) const {
        
        if (stack_.empty()) {
            time_t curTime = time(nullptr);
            auto curLoc = std::source_location::current();
            
            throw NotExpiredIteratorError(
                curLoc.file_name(),
                curLoc.function_name(),
                line,
                ctime(&curTime)
            );
        }
    }

    template <TreeElem T>
    void RevTreeIterator<T>::checkInRange_(int line) const {

        if (stack_.top().expired()) {
            time_t curTime = time(nullptr);
            auto curLoc = std::source_location::current();
            
            throw OutOfRangeIteratorError(
                curLoc.file_name(),
                curLoc.function_name(),
                line,
                ctime(&curTime)
            );
        }
    }
};
