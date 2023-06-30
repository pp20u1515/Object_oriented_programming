#pragma once

#include <memory>
#include <concepts>

namespace MyBSTree {

    template <typename T>
    concept Comparable = std::totally_ordered<T>;

    template <typename T>
    concept Constructible = std::copy_constructible<T>;

    template<typename T>
    concept TreeElem = Comparable<T> && Constructible<T>;

    template <typename From, typename To>
    concept Convertible = std::convertible_to<From, To>;

    template <typename From, typename To>
    concept Assignable = requires (From fm, To to) {
        to = fm;
    };

    template <typename T>
    concept ContainerT = requires (T t) {

        typename T::value_type;
        
        { t.size() } -> std::same_as<typename T::size_type>;
        { t.empty() } -> std::same_as<bool>;
        { t.begin() } -> std::same_as<typename T::iterator>;
        { t.end() } -> std::same_as<typename T::iterator>;
    };

    template <typename T> 
    concept IteratorT = requires (T t, T p) {   
        
        typename T::value_type;

        { ++t } -> std::same_as<T&>;
        { t++ } -> std::same_as<T>;

        { *t } -> std::same_as<typename T::value_type const&>;
        
        { t != p } -> std::same_as<bool>;
        { t == p } -> std::same_as<bool>;
    };
}