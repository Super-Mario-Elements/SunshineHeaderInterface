#pragma once

#include <Dolphin/types.h>
#include <Dolphin/math.h>

#include <SMS/assert.h>

#include <JSystem/config.hxx>
#include <JSystem/initializer_list.hxx>
#include <JSystem/utility.hxx>
#include <JSystem/JGadget/Allocator.hxx>
#include <JSystem/JGadget/Node.hxx>

namespace JGadget {
    template <class _T, class _Alloc = TAllocator<_T>> class TVector {
    public:
        typedef typename _T value_type;
        typedef typename _Alloc allocator_type;
        typedef typename size_t size_type;
        typedef typename ptrdiff_t difference_type;
        typedef typename value_type &reference;
        typedef typename const value_type &const_reference;
        typedef typename _Alloc::pointer pointer;
        typedef typename _Alloc::const_pointer const_pointer;

        struct iterator {
            iterator(pointer node) : mCurrent(node) {}
            iterator(const iterator &iter) : mCurrent(iter.mCurrent) {}

            bool operator==(const iterator &rhs) const { return mCurrent == rhs.mCurrent; }
            bool operator!=(const iterator &rhs) const { return mCurrent != rhs.mCurrent; }

            iterator operator+(int i) {
                iterator temp{mCurrent};
                temp->mCurrent += i;
                return temp;
            }

            iterator &operator+=(int i) {
                mCurrent += i;
                return *this;
            }

            iterator &operator++() {
                ++mCurrent;
                return *this; 
            }

            iterator operator++(int) {
                iterator temp{mCurrent};
                ++mCurrent;
                return temp;
            }

            iterator operator-(int i) {
                iterator temp{mCurrent};
                temp->mCurrent -= i;
                return temp;
            }

            iterator &operator-=(int i) {
                mCurrent -= i;
                return *this;
            }

            iterator &operator--() {
                --mCurrent;
                return *this;
            }

            iterator operator--(int) {
                iterator temp{mCurrent};
                --mCurrent;
                return temp;
            }

            pointer operator->() const { return *mCurrent; }
            reference operator*() const { return *mCurrent; }

        private:
            pointer mCurrent;
        };

        _GLIBCXX20_CONSTEXPR TVector() _GLIBCXX_NOEXCEPT_IF(_GLIBCXX_NOEXCEPT_IF(allocator_type()))
            : mAllocator(), mStart(nullptr), mEnd(nullptr), mCapacity(0), _10(2.0f), _14(0) {}

        explicit _GLIBCXX20_CONSTEXPR TVector(const allocator_type &allocator) _GLIBCXX_NOEXCEPT
            : mAllocator(allocator), mStart(nullptr), mEnd(nullptr), mCapacity(0), _10(2.0f), _14(0) {}

        _GLIBCXX20_CONSTEXPR TVector(size_type count, const value_type &value,
                                     const allocator_type &allocator = allocator_type())
            : mAllocator(allocator), mStart(nullptr), mEnd(nullptr), mCapacity(0), _10(2.0f),
              _14(0) {
            insert(end(), count, value);
        }

#if __cplusplus >= 201402L
        explicit _GLIBCXX20_CONSTEXPR TVector(size_type count,
                                              const allocator_type &allocator = allocator_type())
            : mAllocator(allocator), mStart(nullptr), mEnd(nullptr), mCapacity(0), _10(2.0f),
              _14(0) {
            insert(end(), count, value_type());
        }
#else
        explicit TVector(size_type count)
            : mAllocator(), mStart(nullptr), mEnd(nullptr), mCapacity(0), _10(2.0f),
              _14(0) {
            insert(end(), count, value_type());
        }
#endif

        _GLIBCXX20_CONSTEXPR TVector(const TVector &other)
            : mAllocator(other.mAllocator), _10(other._10), _14(other._14) {
            for (auto &i : other) {
                insert(end(), i);
            }
        }

        _GLIBCXX20_CONSTEXPR TVector(const TVector &other, const allocator_type &allocator)
            : mAllocator(allocator), _10(other._10), _14(other._14) {
            for (auto &i : other) {
                insert(end(), i);
            }
        }

#if __cplusplus >= 201103L
        _GLIBCXX20_CONSTEXPR TVector(TVector &&other)
            : mAllocator(other.mAllocator), _10(other._10), _14(other._14) {
            for (auto &i : other) {
                insert(end(), i);
            }
        }

        _GLIBCXX20_CONSTEXPR TVector(TVector &&other, const allocator_type &allocator)
            : mAllocator(allocator), _10(other._10), _14(other._14) {
            for (auto &i : other) {
                insert(end(), i);
            }
        }

        _GLIBCXX20_CONSTEXPR TVector(JSystem::initializer_list<value_type> list,
                                     const allocator_type &allocator = allocator_type())
            : mAllocator(allocator), mStart(nullptr), mEnd(nullptr), mCapacity(0), _10(2.0f),
            _14(0) {
            for (auto &i : list) {
                insert(end(), i);
            }
        }
#endif

        _GLIBCXX20_CONSTEXPR ~TVector() { erase(begin(), end()); }

        _GLIBCXX20_CONSTEXPR TVector &operator=(const TVector &other) { 
            clear();
            for (auto &i : other) {
                insert(end(), i);
            }
            return *this;
        }

        _GLIBCXX20_CONSTEXPR reference operator[](size_type index) { return mStart[index]; }
        _GLIBCXX20_CONSTEXPR const_reference operator[](size_type index) const {
            return mStart[index];
        }

        _GLIBCXX20_CONSTEXPR allocator_type get_allocator() const { return mAllocator; }

        _GLIBCXX20_CONSTEXPR reference at(size_type index) {
            if (index >= size()) {
                /*OSReport("Attempted to access OOB item (%lu) of Vector (size %lu)!", index, size());
                while (true) {
                    __asm volatile("");
                }*/
            }
            return mStart[index];
        }

        _GLIBCXX20_CONSTEXPR const_reference at(size_type index) const {
            if (index >= size()) {
                /*OSReport("Attempted to access OOB item (%lu) of Vector (size %lu)!", index, size());
                while (true) {
                    __asm volatile("");
                }*/
            }
            return mStart[index];
        }

        _GLIBCXX20_CONSTEXPR reference front() { return *mBegin; }
        _GLIBCXX20_CONSTEXPR const_reference front() const { return *mBegin; }

        _GLIBCXX20_CONSTEXPR reference back() { return *(mEnd - 1); }
        _GLIBCXX20_CONSTEXPR const_reference back() const { return *(mEnd - 1); }

        void assign(size_type count, const_reference value) {
            clear();
            insert(begin(), count, value);
        }

        void assign(size_type count, value_type &&value) {
            clear();
            insert(begin(), count, value);
        }

        _GLIBCXX_NODISCARD _GLIBCXX20_CONSTEXPR bool empty() const _GLIBCXX_NOEXCEPT { return mBegin == mEnd; }
        _GLIBCXX20_CONSTEXPR void clear() _GLIBCXX_NOEXCEPT { erase(*begin(), *end()); }

        size_type capacity() { return mCapacity; }
        _GLIBCXX20_CONSTEXPR size_type size() const _GLIBCXX_NOEXCEPT {
            return mStart ? mEnd - mStart : 0;
        }

        _GLIBCXX20_CONSTEXPR iterator begin() _GLIBCXX_NOEXCEPT { return {mStart}; }
        _GLIBCXX20_CONSTEXPR iterator end() _GLIBCXX_NOEXCEPT { return {mEnd}; }

        _GLIBCXX20_CONSTEXPR iterator erase(iterator a) {
            return erase(*a, *(a + 1));
        }
        _GLIBCXX20_CONSTEXPR iterator erase(iterator a, iterator b) {
            return erase(*a, *b);
        }
        _GLIBCXX20_CONSTEXPR iterator erase(pointer a, pointer b) {
            pointer e = copy(b, mEnd, a);
            for (pointer i = e; i != mEnd; ++i) {
                mAllocator.destroy(i);
                mAllocator.deallocate(i, 1);
            }
            mEnd = e;
            return a;
        }

        _GLIBCXX20_CONSTEXPR iterator insert(iterator at, value_type &&item) {
            return insert(*at, 1, item);
        }
        _GLIBCXX20_CONSTEXPR iterator insert(iterator at, const_reference item) {
            return insert(*at, 1, item);
        }
        _GLIBCXX20_CONSTEXPR iterator insert(iterator at, size_type count, const_reference item) {
            return insert(*at, count, item);
        }
        _GLIBCXX20_CONSTEXPR iterator insert(iterator at, size_type count, value_type &&item) {
            value_type tmp = item;
            return insert(*at, count, tmp);
        }
        _GLIBCXX20_CONSTEXPR iterator insert(pointer at, size_type count, const_reference item) {
            auto *ofs  = at - mStart;
            auto *data = InsertRaw(at, count);
            if (data != end()) {
                uninitialized_fill_n(data, count, item);
            }
            return mStart + ofs;
        }

#if __cplusplus >= 201103L
        _GLIBCXX20_CONSTEXPR iterator insert(iterator at, JSystem::initializer_list<value_type> list) {
            for (auto i : list) {
                at = insert(at, i);
            }
        }
#endif

#if __cplusplus >= 201103L
        template <class... _Args>
        _GLIBCXX20_CONSTEXPR iterator emplace(iterator at, _Args &&...args) {
            auto *ofs  = at - mStart;
            auto *data = InsertRaw(at, 1);
            if (data != end()) {
#if __cplusplus <= 201703L
                mAllocator.construct(data, JSystem::forward<_Args>(args)...);
#else
                mAllocator.construct_at(data, JSystem::forward<_Args>(args)...);
#endif
            }
            return mStart + ofs;
        }
#endif

        _GLIBCXX20_CONSTEXPR void push_back(const_reference item) { insert(end(), item); }
        _GLIBCXX20_CONSTEXPR void pop_back() { erase(end()); }

#if __cplusplus >= 201103L
        template <class... _Args>
        _GLIBCXX20_CONSTEXPR void emplace_back(_Args &&...args) {
            emplace(end(), JSystem::forward<_Args>(args)...);
        }
#endif

        _GLIBCXX20_CONSTEXPR void reserve(size_type capacity) {
            if (mCapacity >= capacity)
                return;

            pointer reservedBuf = mAllocator.allocate(capacity);
            if (!reservedBuf)
                return;

            pointer b          = mStart;
            pointer e          = mEnd;
            size_type size = e - b;

            auto resBufIter = reservedBuf;
            for (pointer i = b; i != e; ++i) {
                *resBufIter++ = *i;
            }

            DestroyElement_(b, e);

            mEnd      = reservedBuf + size;
            mStart    = reservedBuf;
            mCapacity = capacity;

            mAllocator.deallocate(b, 1);
        }

        _GLIBCXX20_CONSTEXPR void resize(size_type s) {
            const size_type currentSize = size();
            if (s == currentSize)
                return;

            if (s < currentSize) {
                erase(*begin() + s, *end());
            } else {
                insert(*end(), s - currentSize, value_type());
            }
        }

    private:
        _GLIBCXX20_CONSTEXPR void DestroyElement_(pointer a, pointer b) {
            for (; a != b; ++a) {
                mAllocator.destroy(a);
            }
        }

        _GLIBCXX20_CONSTEXPR pointer InsertRaw(pointer at, size_type count) {
            if (count == 0)
                return at;

            size_type vsize = size();
            size_type vcapacity = capacity();

            if (vcapacity < count + vsize) {
                size_type ncapacity = Max(_14 + _10, count + vsize);

                // Allocate the new buffer since we maxxed the capacity
                pointer nbuffer = mAllocator.allocate(ncapacity);
                if (!nbuffer)
                    return mEnd;

                // Copy construct the values before the insertion
                pointer nbiter = nbuffer;
                for (pointer i = mStart; i != at; ++i) {
                    mAllocator.construct(nbiter++, *i);
                }

                // Copy construct the values after the insertion
                pointer naiter = nbiter + count;
                for (pointer i = at; i != mEnd; ++i) {
                    mAllocator.construct(naiter++, *i);
                }

                // Destroy old buffer
                DestroyElement_(mStart, mEnd);

                pointer vbegin = mStart;

                mEnd      = nbuffer + count + vsize;
                mStart    = nbuffer;
                mCapacity = ncapacity;

                mAllocator.deallocate(vbegin, 1);
                return nbiter;
            }

            pointer ieiter = at + count;
            if (ieiter < mEnd) {
                // Copy construct the values after the end
                pointer newiter = mEnd;
                for (pointer i = mEnd - count; i != mEnd; ++i) {
                    mAllocator.construct(newiter++, *i);
                }

                // Copy new values into inserted space? (Makes no sense)
                pointer insertIter = mEnd;
                for (pointer i = mEnd - count; i > at; --i) {
                    *insertIter = *i;
                }

                for (pointer i = at; i != mEnd - count; ++i) {
                    mAllocator.destroy(*i);
                }
            } else {
                pointer insertIter = ieiter;
                for (pointer i = at; i != mEnd; ++i) {
                    mAllocator.construct(insertIter++, *i);
                }

                // Destroy old elements
                DestroyElement_(at, mEnd);
            }

            mEnd += count;
            return at;
        }

        allocator_type mAllocator;
        pointer mStart;
        pointer mEnd;
        size_type mCapacity;
        f32 _10;
        size_type _14;
    };

    template <class _T, class _Alloc>
    _GLIBCXX20_CONSTEXPR bool operator==(const TVector<_T, _Alloc>& lhs,
        const TVector<_T, _Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return false;

        for (auto i = lhs.begin(), auto j = rhs.begin(); i != lhs.end() && j != rhs.end(); ++i, ++j) {
            if (i != j)
                return false;
        }

        return true;
    }

#if __cplusplus <= 201703L
    template <class _T, class _Alloc>
    bool operator!=(const TVector<_T, _Alloc> &lhs,
                                         const TVector<_T, _Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return true;

        for (auto i = lhs.begin(), auto j = rhs.begin(); i != lhs.end() && j != rhs.end();
             ++i, ++j) {
            if (i != j)
                return true;
        }

        return false;
    }
#endif

    class TVector_pointer_void : public TVector<void *> {
        TVector_pointer_void();
        ~TVector_pointer_void();

        iterator insert(void **a, void **b);
        void reserve(size_type capacity);
    };

}  // namespace JGadget