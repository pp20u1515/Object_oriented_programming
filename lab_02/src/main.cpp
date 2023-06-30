#include <iostream>
#include "BSTree.h"

#include <vector>
#include <list>

using namespace MyBSTree;

int main() {

    std::cout << "__________CONSTRUCTORS__________" << std::endl << std::endl;
    {
        {
            std::cout << "1. Empty constructor" << std::endl;
            BSTree<int> tree;
            std::cout << tree << std::endl;
        }
        {
            std::cout << std::endl << "2. Initializer List constructor" << std::endl;
            BSTree<int> tree{1, 3, 2, 5, 4};
            std::cout << "Currrent Tree: " << tree << std::endl;
        }
        {
            std::cout << std::endl << "3. Constructor with movement" << std::endl;
            BSTree<int> tree1{1, 3, 2, 5, 4};
            std::cout << "Before:\nInitial Tree: " << tree1 << std::endl;
            BSTree<int> tree2(std::move(tree1));
            std::cout << "After:\nInitial Tree: " << tree1 << std::endl;
            std::cout << "New Tree: " << tree2 << std::endl;
        }
        {
            std::cout << std::endl << "4. Constructor with copy" << std::endl;
            BSTree<int> tree1{1, 3, 2, 5, 4};
            std::cout << "Before:\nInitial Tree: " << tree1 << std::endl;
            BSTree<int> tree2(tree1);
            std::cout << "After:\nInitial Tree: " << tree1 << std::endl;
            std::cout << "New Tree: " << tree2 << std::endl;
        }
        {
            std::cout << std::endl << "5. Operator= with movement" << std::endl;
            BSTree<int> tree1{1, 3, 2, 5, 4};
            BSTree<int> tree2;
            std::cout << "Before:\nFirst Tree: " << tree1 << std::endl;
            std::cout << "Second Tree: " << tree2 << std::endl;
            tree2 = std::move(tree1);
            std::cout << "After:\nFirst Tree: " << tree1 << std::endl;
            std::cout << "Second Tree: " << tree2 << std::endl;
        }
        {
            std::cout << std::endl << "6. Operator= with copy" << std::endl;
            BSTree<int> tree1{1, 3, 2, 5, 4};
            BSTree<int> tree2;
            std::cout << "Before:\nFirst Tree: " << tree1 << std::endl;
            std::cout << "Second Tree: " << tree2 << std::endl;
            tree2 = tree1;
            std::cout << "After:\nFirst Tree: " << tree1 << std::endl;
            std::cout << "Second Tree: " << tree2 << std::endl;
        }
        {
            std::cout << std::endl << "7. Constructor based on std::list" << std::endl;
            std::list<int> curList{10, 9, 8, 1, 11, 12};
            BSTree<int> tree1(curList);
            std::cout << "Current Tree: " << tree1 << std::endl;
        }
        {
            std::cout << std::endl << "8. Constructor based on std::list:iterator" << std::endl;
            const std::list<int> curList{10, 9, 8, 1, 11, 12};
            BSTree<int> tree1(curList.cbegin(), curList.end());
            std::cout << "Current Tree: " << tree1 << std::endl;
        }
    }
    std::cout << std::endl << "__________OPERATIONS WITH TREE__________" << std::endl << std::endl;
    {
        {
            std::cout << std::endl << "1. INSERT" << std::endl;
            BSTree<int> tree;
            int a[] = {9, 8, 7, 6, 5};

            for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
                tree.insert(a[i]);
                std::cout << "insert " << a[i] << ": " << tree << std::endl;
            }
        }
        {
            std::cout << std::endl << "1. INSERT" << std::endl;
            BSTree<int> tree;
            int a[] = {9, 8, -1, 7, 6, 5, 0};

            for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
                tree.insert(a[i]);
                std::cout << "insert " << a[i] << ": " << tree << std::endl;
            }
            std::cout << std::endl << "2. FIND" << std::endl;
            for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
                tree.insert(a[i]);
                std::cout << "find " << a[i] << ": " << tree.find(a[i]) << std::endl;
            }
            std::cout << std::endl << "3. REMOVE" << std::endl;
            std::cout << "Before: " << tree << std::endl;
            tree.remove(9);
            std::cout << "After remove 9: " << tree << std::endl;
            tree.remove(0);
            std::cout << "After remove 0: " << tree << std::endl;
            tree.remove(11);
            std::cout << "After remove 11: " << tree << std::endl;
        }
        {
            std::cout << std::endl << "4. THEORETICAL OPERATIONS" << std::endl;
            BSTree<int> a{1, 2, 3, 4, 5}, b{1, 2, 3, 10, 12};
            std::cout << "Tree a: " << a << std::endl;
            std::cout << "Tree b: " << b << std::endl;
            {
                BSTree aa(a), bb(b);
                std::cout << "Intersection: " << aa.intersection(bb) << std::endl;
            }
            {
                BSTree aa(a), bb(b);
                std::cout << "Unification: " << aa.unification(bb) << std::endl;
            }
            {
                BSTree aa(a), bb(b);
                std::cout << "Difference: " << aa.difference(bb) << std::endl;
            }
            {
                BSTree aa(a), bb(b);
                std::cout << "Sym difference: " << aa.symDifference(bb) << std::endl;
            }    
            std::cout << std::endl << "*overloaded operators" << std::endl;
            {
                BSTree aa(a), bb(b);
                aa += bb;
                std::cout << "a += b: a = " << aa << std::endl;
            }
            {
                BSTree aa(a), bb(b);
                aa -= bb;
                std::cout << "a -= b: a = " << aa << std::endl;
            }
            {
                BSTree aa(a), bb(b);
                aa *= bb;
                std::cout << "a *= b: a =" << aa << std::endl;
            }
            {
                BSTree aa(a), bb(b);
                aa ^= bb;
                std::cout << "a ^= b: a = " << aa << std::endl;
            }
            BSTree<int> c;
            {
                c = a + b;
                std::cout << "c = a + b: c = " << c << std::endl;
            }
            {
                c = a - b;
                std::cout << "c = a - b: c = " << c << std::endl;
            }
            {
                c = a * b;
                std::cout << "c = a * b: c = " << c << std::endl;
            }
            {
                c = a ^ b;
                std::cout << "c = a ^ b: c = " << c << std::endl;
            }
        }
        {
            std::cout << std::endl << "5. ITERATORS" << std::endl;
            {
                std::cout << std::endl << "1. Empty tree" << std::endl;
                BSTree<int> tree;
                std::cout << "begin() == end(): " << (tree.begin() == tree.end()) << std::endl;
            }
            {
                std::cout << "2. Not const tree" << std::endl;
                BSTree<int> tree{1, 5, 12, 3, -4, 0, 6, 8, 7};
                std::cout << "Init tree:" << tree << std::endl;

                std::cout << "\nFor loop with iterator\n";
                for (auto elem = tree.begin(); elem != tree.end(); ++elem)
                    std::cout << *elem << " ";
                std::cout << std::endl;

                std::cout << "\nFor each loop with const iterator&\n";
                for (const auto &elem : tree)
                    std::cout << elem << " ";
                std::cout << std::endl;

                std::cout << "\nFor loop with const reverse iterator&\n";
                for (auto elem = tree.rbegin(); elem != tree.rend(); ++elem)
                    std::cout << *elem << " ";
                std::cout << std::endl;
            }
            {
                std::cout << "3. Const tree" << std::endl;
                const BSTree<int> tree{1, 5, 12, 3, -4, 0, 6, 8, 7};
                std::cout << "Init tree:" << tree << std::endl;

                std::cout << "\nFor loop with iterator\n";
                for (auto elem = tree.begin(); elem != tree.end(); ++elem)
                    std::cout << *elem << " ";
                std::cout << std::endl;

                std::cout << "\nFor each loop with const iterator&\n";
                for (const auto &elem : tree)
                    std::cout << elem << " ";
                std::cout << std::endl;

                std::cout << "\nFor loop with const reverse iterator&\n";
                for (auto elem = tree.rbegin(); elem != tree.rend(); ++elem)
                    std::cout << *elem << " ";
                std::cout << std::endl;
            }
            {
                std::cout << "3. Iterators operations" << std::endl;
                const BSTree<int> tree{1, 5, 12, 3, -4, 0, 6, 8, 7};
                auto it = tree.begin();
                std::cout << "Tree begin() value: " << *it<<std::endl;

                it = tree.end();
                it--;
                std::cout << "Tree end() decrement value: " << *it <<std::endl;

                auto it1 = tree.rbegin();
                std::cout << "Tree rbegin() decrement value: " << *it1 <<std::endl;

                it1 = tree.rend();
                it1--;
                std::cout << "Tree rend() decrement value: " << *it1 <<std::endl;
            }
        }
        {
            std::cout << std::endl << "5. EXCEPTIONS" << std::endl;
            BSTree tree{1, 2, 3, 4, 5, 6};

            try {
                std::cout << "\n1. Tree begin() decrement\n";
                auto it = tree.begin();
                it--;
                std::cout << *it;
            }
            catch(const std::exception &e) {
                std::cout << e.what();
            }

            try {
                std::cout << "\n2. Tree end() increment\n";
                auto it = tree.begin();
                it--;
                std::cout << *it;
            }
            catch(const std::exception &e) {
                std::cout << e.what();
            }
            try {
                std::cout << "\n3. Tree end() dereference\n";
                auto it = tree.end();
                std::cout << *it;
            }
            catch(const std::exception &e) {
                std::cout << e.what();
            }
            try {
                std::cout << "\n4. Expired root\n";
                BSTree<int> a;
                auto it = a.begin();
                --it;
                std::cout << *it;
            }
            catch(const std::exception &e) {
                std::cout << e.what();
            }
        }
    }

    return 0;
}