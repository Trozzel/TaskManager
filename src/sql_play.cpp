#include <cassert>
#include <array>
#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>

namespace gaf {
    // ITERATOR TAGS
    struct output_iterator_tag {};
    struct input_iterator_tag {};
    struct forward_iterator_tag : public std::input_iterator_tag {};
    struct bidirectional_iterator_tag : public std::forward_iterator_tag {};
    struct random_access_iterator_tag : public std::bidirectional_iterator_tag {};
    struct contiguous_iterator_tag : public std::random_access_iterator_tag {};

    // BASE ITERATOR TRAITS
    template <typename Iterator> struct iterator_traits {
        using difference_type = typename Iterator::difference_type;
        using value_type = typename Iterator::value_type;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;
        using iterator_category = typename Iterator::iterator_category;
    };

    template <typename T> struct iterator_traits<T *> {
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;
    };

    template <class Iterator>
        void advance_impl(Iterator &it, std::size_t n, random_access_iterator_tag) {
            it += n;
        }

    template <class Iterator>
        void advance_impl(Iterator &it, size_t n, bidirectional_iterator_tag) {
            if (n < 0) {
                for (; n; n--) {
                    ++it;
                }
            } else {
                for (; n; n++) {
                    --it;
                }
            }
        }

    template <class Iterator> void advance(Iterator &it, size_t n) {
        advance_impl(it, n, typename iterator_traits<Iterator>::iterator_category{});
    }

    template <class Iterator>
        using Category = typename iterator_traits<Iterator>::iterator_category;

    template <class Iterator>
        using Difference_t = typename iterator_traits<Iterator>::difference_type;

    template <class Iter>
        Difference_t<Iter> dist_imp(Iter i1, Iter i2, random_access_iterator_tag) {
            return i1 - i2;
        }

    template <class Iter>
        Difference_t<Iter> dist_imp(Iter i1, Iter i2, bidirectional_iterator_tag) {
            Difference_t<Iter> diff = 0;
            while (i1 != i2) {
                ++i1;
                ++diff;
            }
            return diff;
        }

    template <class Iter> Difference_t<Iter> dist(Iter i1, Iter i2) {
        using Category = typename iterator_traits<Iter>::iterator_category;
        return dist_imp(i1, i2, Category{});
    }

    const unsigned STACK_SZ = 50;
    const unsigned CAPACITY_INCR = 2;
    template <typename T> class Vector {
        private:
            size_t _sz = 0;
            size_t _capacity = STACK_SZ;
            union {
                T *_heap = nullptr;
                T _stack[STACK_SZ];
            };

        public:
            Vector() = default;

            // CTOR WITH ITERATORS
            template <class Iter> Vector(Iter start, Iter finish) {
                _sz = finish - start;
                if (_sz >= STACK_SZ) {
                    printf("Allocating %lu bytes on heap for Vector.\n", _sz * sizeof(T));
                    _capacity = CAPACITY_INCR * _sz;
                    _heap = (T *)calloc(_sz, _capacity);
                    if (_heap == nullptr) {
                        throw std::bad_alloc();
                    }
                    for (; start != finish; ++start) {
                        *_heap++ = *start;
                    }
                } else {
                    _heap = nullptr;
                    printf("Creating vector on the stack\n");
                    for (int i = 0; start != finish; ++start, ++i) {
                        _stack[i] = *start;
                    }
                }
            };

            // PUSH BACK
            void push_back(const T &val) {
                if (_sz >= _capacity - 1) {
                    _capacity *= CAPACITY_INCR;
                    printf("Capacity increased to %lu bytes.\n", sizeof(T) * _capacity);
                    _heap = (T *)realloc(_heap, _capacity);
                    if (_heap == nullptr) {
                        throw std::bad_alloc();
                    }
                } else if (_sz < STACK_SZ - 1) {
                    _heap = nullptr;
                    _stack[_sz++] = val;
                    return;
                }
                _heap[_sz++] = val;
                return;
            }

            ~Vector() {
                if (_heap) {
                    printf("Deleting heap from Vector\n");
                    delete[] _heap;
                }
            }
    };

    template <class T, size_t Sz> class Array {
        using Array_t = Array<T, Sz>;

        private:
        T _arr[Sz]{};

        public:
        Array() = default;
        Array(const std::initializer_list<int> &il) {
            std::cout << "IL CTOR\n";
            auto it = il.begin();
            for (size_t i{}; i < il.size(); ++i) {
                _arr[i] = *it++;
            }
        }
        Array(T arr[Sz]) {
            std::cout << "Normal array ctor\n";
            for (int i = 0; i < Sz; ++i)
                _arr[i] = arr[i];
        }
        Array(const Array &other) {
            std::cout << "Copy CTOR\n";
            for (size_t i = 0; i < Sz; ++i) {
                _arr[i] = other._arr[i];
            }
        }
        Array(Array &&other) {
            std::cout << "Move CTOR\n";
            _arr = move(other._arr);
        }
        Array &operator=(const T arr[Sz]) {
            std::cout << "Assign operator 1\n";
            for (size_t i = 0; i < Sz; ++i) {
                _arr[i] = arr[i];
            }
            return *this;
        }
        Array &operator=(const Array &other) {
            std::cout << "Assignment operator 2\n";
            for (size_t i{}; i < Sz; ++i) {
                _arr[i] = other._arr[i];
            }
            return *this;
        }
        Array &operator=(Array &&other) {
            std::cout << "Move operatorn 2\n";
            *this = move(other);
            return *this;
        }

        inline const T &operator[](size_t idx) const {
            static_assert(idx < Sz, "Out of bounds access prohibited");
            return _arr[idx];
        }
        inline T &operator[](size_t idx) { return _arr[idx]; }

        constexpr size_t size() { return Sz; }

        class Iter;
        Iter begin() { return Iter(0, *this); }
        Iter end() { return Iter(Sz, *this); }
        const Iter cbegin() const { return Iter(0, *this); }
        const Iter cend() const { return Iter(Sz, *this); }
    };
    template <typename T, size_t Sz> class Array<T, Sz>::Iter {
        private:
            size_t _pos;
            Array<T, Sz> &_arr;

        public:
            Iter(size_t pos, Array<T, Sz> &arr) : _pos(pos), _arr(arr) {}

            Iter &operator++() {
                ++_pos;
                return *this;
            }
            Iter operator++(int) {
                Iter tmp = *this;
                ++_pos;
                return tmp;
            }

            Iter &operator--() {
                --_pos;
                return *this;
            }
            Iter operator--(int) {
                Iter tmp = *this;
                --_pos;
                return *this;
            }
            Iter operator+(size_t n) {
                Iter newIt(_pos + n, _arr);
                return newIt;
            }
            T &operator*() { return _arr[_pos]; }
            bool operator!=(const Iter &other) {
                assert(Sz == other._arr.size());
                if (_pos != other._pos) {
                    return true;
                }
                for (size_t i{}; i < Sz; ++i) {
                    if (_arr[i] != other._arr[i]) {
                        return true;
                    }
                }
                return false;
            }
    };
    template<typename T, size_t Sz>
        std::ostream& operator<< (std::ostream& out, const Array<T, Sz>& arr) {
            out << "Array[0.." << Sz - 1 << "]: {";
            for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
                out << *it;
                if (it + 1 != arr.cend()) {
                    out << ", ";
                }
            }
            out << "}\n";
            return out;
        }
} // namespace gaf

int main() {
    int a[] = {1, 2, 3, 4, 5};
    gaf::Array<int, 5> arr = a;

    size_t i{0};
    for (auto &elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl << std::endl;
    std::cout << arr;
}
