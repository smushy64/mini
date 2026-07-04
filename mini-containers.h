#if !defined(MINI_CONTAINERS_H)
#define MINI_CONTAINERS_H
/**
 * @file   mini-containers.h
 * @brief  Mini: Containers.
 * @author Alicia D. Amarilla (smushyaa@gmail.com)
 * @date   July 01, 2026
*/
#include <stddef.h> // size_t
#include <stdint.h> // intptr_t
#include <stdlib.h> // calloc, realloc, free
#include <string.h> // memset, memcpy, memmove
#if defined(MINI_ENABLE_ASSERTIONS)
    #include <assert.h> // assert
    #define MINI_ASSERT(condition) assert(condition)
#else
    #define MINI_ASSERT(condition)
#endif

/// @brief Slice of items.
/// @tparam T Type of items.
template<typename T>
struct Slice;

/// @brief Buffer of items.
/// @tparam T Type of items.
template<typename T>
struct Buffer;

/// @brief Array of items.
/// @tparam T Type of items.
/// @tparam N Number of items in array.
template<typename T, size_t N>
struct Array;

/// @brief Nullable values.
/// @tparam T Type of item.
template<typename T>
struct Option;

/// @brief Multiple values together.
/// @tparam Ts Types of values.
template<typename... Ts>
struct Tuple;

/// @brief Comparison function result.
enum class CmpResult : int;

/// @brief Comparison function prototype.
/// @param[in] a, b   Values to be compared.
/// @param[in] params Optional parameters to this function.
/// @return Comparison result.
typedef CmpResult CmpFn(const void *a, const void *b, void *params);

/// @brief Get number of items in array.
/// @param[in] array Array to get length of.
/// @return Length of @c array.
template<typename T, size_t N> constexpr inline
size_t len(const T (&array)[N]);

/// @brief Sort items.
/// @param     len        Number of items.
/// @param[in] ptr        Pointer to items.
/// @param[in] cmpfn      Comparison function.
/// @param[in] params     Parameters to comparison function.
/// @param     is_reverse If should sort in reverse order.
template<typename T> inline
void quicksort(size_t len, T *ptr, CmpFn *cmpfn,
    void *params = nullptr, bool is_reverse = false);

/// @brief Standard comparison function.
/// @param[in] a, b   Pointers to items.
/// @param[in] params Unused.
/// @return Comparison result.
template<typename T, typename U = T> inline
CmpResult cmp_standard(const void *a, const void *b, void *params);

/// @brief Create a slice.
/// @param     len Number of items in slice.
/// @param[in] ptr Pointer to start of slice.
/// @return Slice.
template<typename T> constexpr inline
Slice<T> slice(size_t len, const T *ptr);

/// @brief Create a slice.
/// @param[in] ptr  Pointer to start of slice.
/// @param     from Start of slice, inclusive.
/// @param     to   End of slice, exclusive.
/// @return Slice.
template<typename T> constexpr inline
Slice<T> slice(const T *ptr, size_t from = 0, size_t to = 1);

/// @brief Create a slice.
/// @param[in] s    Slice.
/// @param     from Start of slice, inclusive.
/// @param     to   End of slice, exclusive.
/// @return Slice.
template<typename T> constexpr inline
Slice<T> slice(Slice<T> s, size_t from = 0, size_t to = 0);

/// @brief Create a slice.
/// @param[in] array Array.
/// @param     from  Start of slice, inclusive.
/// @param     to    End of slice, exclusive.
/// @return Slice.
template<typename T, size_t N> constexpr inline
Slice<T> slice(const Array<T,N>& array, size_t from = 0, size_t to = N);

/// @brief Advance slice.
/// @param s      Slice.
/// @param amount Number of items to advance by.
/// @return Slice.
template<typename T> constexpr inline
Slice<T> advance(Slice<T> s, size_t amount = 1);

/// @brief Set all items in slice to given value.
/// @param s     Slice to modify.
/// @param value Value to set items.
template<typename T> inline
void set(Slice<T>& s, const T& value);

/// @brief Sort items.
/// @param     s          Items.
/// @param[in] cmpfn      Comparison function.
/// @param[in] params     Parameters to comparison function.
/// @param     is_reverse If should sort in reverse order.
template<typename T> inline
void quicksort(Slice<T> s, CmpFn *cmpfn, void *params = nullptr, bool is_reverse = false);

/// @brief Allocate a new buffer.
/// @param amount Number of items in buffer.
/// @return Buffer.
template<typename T> inline
Buffer<T> buffer_alloc(size_t amount);

/// @brief Free allocated buffer.
/// @param[in] b Buffer to free.
template<typename T> inline
void buffer_free(Buffer<T>& b);

/// @brief Create buffer.
/// @param[in] ptr Base pointer.
/// @param     cap Number of items buffer can hold.
/// @param     len Initial length of buffer.
/// @return Buffer.
template<typename T> constexpr inline
Buffer<T> buffer(const T *ptr, size_t cap, size_t len = 0);

/// @brief Create buffer from slice.
/// @param s   Slice.
/// @param len Initial length of buffer.
/// @return Buffer.
template<typename T> constexpr inline
Buffer<T> buffer(Slice<T> s, size_t len = 0);

/// @brief Check how much empty space buffer has.
/// @param[in] b Buffer.
/// @return Number of empty spaces.
template<typename T> constexpr inline
size_t remaining(const Buffer<T>& b);

/// @brief Clear values from buffer.
/// @param[in] b Buffer to clear.
template<typename T> inline
void clear(Buffer<T>& b);

/// @brief Shrink buffer to current length.
/// @param[in] b Buffer to shrink.
template<typename T> inline
void shrink(Buffer<T>& b);

/// @brief Allocate additional space in buffer.
/// @param[in] b      Buffer to grow.
/// @param     amount Amount of additional capacity.
template<typename T> inline
void grow(Buffer<T>& b, size_t amount);

/// @brief Reserve minimum amount of free space in buffer.
/// @details
/// If buffer has less than @c minimum free space, reallocates.
/// Otherwise, does nothing.
/// @param[in] b       Buffer to grow.
/// @param     minimum Minimum amount of free space.
template<typename T> inline
void reserve(Buffer<T>& b, size_t minimum);

/// @brief Attempt to push item to end of buffer.
/// @param[in] b    Buffer.
/// @param[in] item Item to push.
/// @return
///     - @c true  : Pushed item.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_push(Buffer<T>& b, const T& item);

/// @brief Attempt to insert item in buffer.
/// @param[in] b     Buffer.
/// @param     index Index to insert at.
/// @param[in] item  Item to insert.
/// @return
///     - @c true  : Inserted item.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_insert(Buffer<T>& b, size_t index, const T& item);

/// @brief Attempt to prepend item to beginning of buffer.
/// @param[in] b    Buffer.
/// @param[in] item Item to prepend.
/// @return
///     - @c true  : Prepended item.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_prepend(Buffer<T>& b, const T& item);

/// @brief Attempt to append item to end of buffer.
/// @param[in] b    Buffer.
/// @param[in] item Item to prepend.
/// @return
///     - @c true  : Appended item.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_append(Buffer<T>& b, const T& item);

/// @brief Attempt to insert items into buffer.
/// @param[in] b     Buffer.
/// @param     index Index to insert at.
/// @param     count Number of items to insert.
/// @param[in] items Items to insert.
/// @return
///     - @c true  : Inserted items.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_insert(Buffer<T>& b, size_t index, size_t count, const T *items);

/// @brief Attempt to insert items at beginning of buffer.
/// @param[in] b     Buffer.
/// @param     count Number of items to insert.
/// @param[in] items Items to insert.
/// @return
///     - @c true  : Inserted items.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_prepend(Buffer<T>& b, size_t count, const T *items);

/// @brief Attempt to insert items at end of buffer.
/// @param[in] b     Buffer.
/// @param     count Number of items to insert.
/// @param[in] items Items to insert.
/// @return
///     - @c true  : Inserted items.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_append(Buffer<T>& b, size_t count, const T *items);

/// @brief Attempt to insert items in buffer.
/// @param[in] b     Buffer.
/// @param     index Index to insert at.
/// @param     items Items to insert.
/// @return
///     - @c true  : Inserted items.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_insert(Buffer<T>& b, size_t index, Slice<T> items);

/// @brief Attempt to insert items at beginning of buffer.
/// @param[in] b     Buffer.
/// @param     items Items to insert.
/// @return
///     - @c true  : Inserted items.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_prepend(Buffer<T>& b, Slice<T> items);

/// @brief Attempt to insert items at end of buffer.
/// @param[in] b     Buffer.
/// @param     items Items to insert.
/// @return
///     - @c true  : Inserted items.
///     - @c false : Buffer does not have required space.
template<typename T> inline
bool try_append(Buffer<T>& b, Slice<T> items);

/// @brief Push item to end of buffer.
/// @param[in] b    Buffer.
/// @param[in] item Item to push.
template<typename T> inline
void push(Buffer<T>& b, const T& item);

/// @brief Insert item in buffer.
/// @param[in] b     Buffer.
/// @param     index Index to insert at.
/// @param[in] item  Item to insert.
template<typename T> inline
void insert(Buffer<T>& b, size_t index, const T& item);

/// @brief Prepend item to beginning of buffer.
/// @param[in] b    Buffer.
/// @param[in] item Item to prepend.
template<typename T> inline
void prepend(Buffer<T>& b, const T& item);

/// @brief Append item to end of buffer.
/// @param[in] b    Buffer.
/// @param[in] item Item to prepend.
template<typename T> inline
void append(Buffer<T>& b, const T& item);

/// @brief Insert items into buffer.
/// @param[in] b     Buffer.
/// @param     index Index to insert at.
/// @param     count Number of items to insert.
/// @param[in] items Items to insert.
template<typename T> inline
void insert(Buffer<T>& b, size_t index, size_t count, const T *items);

/// @brief Insert items at beginning of buffer.
/// @param[in] b     Buffer.
/// @param     count Number of items to insert.
/// @param[in] items Items to insert.
template<typename T> inline
void prepend(Buffer<T>& b, size_t count, const T *items);

/// @brief Insert items at end of buffer.
/// @param[in] b     Buffer.
/// @param     count Number of items to insert.
/// @param[in] items Items to insert.
template<typename T> inline
void append(Buffer<T>& b, size_t count, const T *items);

/// @brief Insert items in buffer.
/// @param[in] b     Buffer.
/// @param     index Index to insert at.
/// @param     items Items to insert.
template<typename T> inline
void insert(Buffer<T>& b, size_t index, Slice<T> items);

/// @brief Insert items at beginning of buffer.
/// @param[in] b     Buffer.
/// @param     items Items to insert.
template<typename T> inline
void prepend(Buffer<T>& b, Slice<T> items);

/// @brief Insert items at end of buffer.
/// @param[in] b     Buffer.
/// @param     items Items to insert.
template<typename T> inline
void append(Buffer<T>& b, Slice<T> items);

/// @brief Attempt to remove last item from buffer.
/// @param[in] b Buffer to remove from.
/// @return
///     - @c some(T) : Buffer has item to remove, unwrap to use it.
///     - @c none    : Buffer is empty.
template<typename T> inline
Option<T> pop(Buffer<T>& b);

/// @brief Remove item from buffer.
/// @param[in] b     Buffer to remove from.
/// @param     index Index of item to remove.
template<typename T> inline
void remove(Buffer<T>& b, size_t index);

/// @brief Remove item from buffer by swapping with last item.
/// @param[in] b     Buffer to remove from.
/// @param     index Index of item to remove.
template<typename T> inline
void remove_swap(Buffer<T>& b, size_t index);

/// @brief Remove range of items.
/// @param[in] b    Buffer to remove from.
/// @param     from Start of range, inclusive.
/// @param     to   End of range, exclusive.
template<typename T> inline
void remove_range(Buffer<T>& b, size_t from, size_t to);

/// @brief Create valid option with value.
/// @param[in] value Value of option.
/// @return Option.
template<typename T> constexpr inline
Option<T> some(const T& value);

/// @brief Create empty option.
/// @return Option.
template<typename T> constexpr inline
Option<T> none();

/// @brief Get value from option.
/// @warning Only call this function if you're sure the option is valid!
/// @param[in] opt Option.
/// @return Value.
template<typename T> inline
T unwrap(Option<T>& opt);

/// @brief Create array.
/// @return Array.
template<typename T, size_t N> constexpr inline
Array<T,N> array();

/// @brief Create array.
/// @param first First value.
/// @param rest  Rest of values.
/// @return Array.
template<typename First, typename... Rest> constexpr inline
Array<First,(1 + sizeof...(Rest))> array(First first, Rest... rest);

/// @brief Create a tuple.
/// @return Tuple.
template<typename First, typename... Rest> constexpr inline
Tuple<First, Rest...> tuple();

/// @brief Create a tuple.
/// @param first First value.
/// @param rest  Rest of values.
/// @return Tuple.
template<typename First, typename... Rest> constexpr inline
Tuple<First, Rest...> tuple(First first, Rest... rest);

/// @brief Get value at given index.
/// @param t Tuple.
/// @return Value.
template<size_t Which, typename First, typename... Rest> constexpr inline
const auto& get(const Tuple<First, Rest...>& t);

/// @brief Get value at given index.
/// @param t Tuple.
/// @return Value.
template<size_t Which, typename First, typename... Rest> constexpr inline
auto& get(Tuple<First, Rest...>& t);

// NOTE(alicia): struct definitions

template<typename T>
struct Slice {
    /// @brief Type of items.
    typedef T Type;

    /// @brief Number of items.
    size_t len;
    /// @brief Items.
    Type     *ptr;

    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    const Type& operator[](size_t index) const;
    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    Type& operator[](size_t index);

    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator const Type *() const;
    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator Type *();

    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    const Type& operator*() const;
    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    Type& operator*();

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<Type> operator+(size_t adv) const;

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<Type>& operator+=(size_t adv);

    /// @brief Advance this slice by given number of items.
    /// @return Reference to self.
    constexpr inline
    Slice<Type>& operator++();

    /// @brief Advance this slice by given number of items.
    /// @return Reference to self.
    constexpr inline
    Slice<Type>& operator++(int);

    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    const Type *begin() const;
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    const Type *end() const;
    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    Type *begin();
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    Type *end();
};

template<>
struct Slice<char> {
    /// @brief Type of items.
    typedef char Type;

    /// @brief Number of items.
    size_t len;
    /// @brief Items.
    Type     *ptr;

    /// @brief Create empty slice.
    constexpr inline
    Slice();

    /// @brief Create slice from string.
    template<size_t N> constexpr inline
    Slice(const char (&cstring)[N]);

    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    const Type& operator[](size_t index) const;
    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    Type& operator[](size_t index);

    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator const Type *() const;
    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator Type *();

    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    const Type& operator*() const;
    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    Type& operator*();

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<Type> operator+(size_t adv) const;

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<Type>& operator+=(size_t adv);

    /// @brief Advance this slice by given number of items.
    /// @return Reference to self.
    constexpr inline
    Slice<Type>& operator++();

    /// @brief Advance this slice by given number of items.
    /// @return Reference to self.
    constexpr inline
    Slice<Type>& operator++(int);

    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    const Type *begin() const;
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    const Type *end() const;
    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    Type *begin();
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    Type *end();
};

template<>
struct Slice<wchar_t> {
    /// @brief Type of items.
    typedef wchar_t Type;

    /// @brief Number of items.
    size_t len;
    /// @brief Items.
    Type     *ptr;

    /// @brief Create empty slice.
    constexpr inline
    Slice();

    /// @brief Create slice from string.
    template<size_t N> constexpr inline
    Slice(const wchar_t (&cstring)[N]);

    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    const Type& operator[](size_t index) const;
    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    Type& operator[](size_t index);

    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator const Type *() const;
    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator Type *();

    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    const Type& operator*() const;
    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    Type& operator*();

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<Type> operator+(size_t adv) const;

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<Type>& operator+=(size_t adv);

    /// @brief Advance this slice by given number of items.
    /// @return Reference to self.
    constexpr inline
    Slice<Type>& operator++();

    /// @brief Advance this slice by given number of items.
    /// @return Reference to self.
    constexpr inline
    Slice<Type>& operator++(int);

    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    const Type *begin() const;
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    const Type *end() const;
    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    Type *begin();
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    Type *end();
};

template<>
struct Slice<char32_t> {
    /// @brief Type of items.
    typedef char32_t Type;

    /// @brief Number of items.
    size_t len;
    /// @brief Items.
    Type     *ptr;

    /// @brief Create empty slice.
    constexpr inline
    Slice();

    /// @brief Create slice from string.
    template<size_t N> constexpr inline
    Slice(const char32_t (&cstring)[N]);

    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    const Type& operator[](size_t index) const;
    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    Type& operator[](size_t index);

    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator const Type *() const;
    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator Type *();

    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    const Type& operator*() const;
    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    Type& operator*();

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<Type> operator+(size_t adv) const;

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<Type>& operator+=(size_t adv);

    /// @brief Advance this slice by given number of items.
    /// @return Reference to self.
    constexpr inline
    Slice<Type>& operator++();

    /// @brief Advance this slice by given number of items.
    /// @return Reference to self.
    constexpr inline
    Slice<Type>& operator++(int);

    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    const Type *begin() const;
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    const Type *end() const;
    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    Type *begin();
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    Type *end();
};

template<typename T>
struct Buffer {
    /// @brief Type of items.
    typedef T Type;

    /// @brief Number of items buffer can hold.
    size_t cap;
    /// @brief Number of items in buffer.
    size_t len;
    /// @brief Items.
    T     *ptr;

    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    const T& operator[](size_t index) const;
    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    T& operator[](size_t index);

    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator const T *() const;
    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator T *();

    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    const T& operator*() const;
    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    T& operator*();

    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    const T *begin() const;
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    const T *end() const;
    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    T *begin();
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    T *end();
};

template<typename T, size_t N>
struct Array {
    /// @brief Type of items.
    typedef T Type;

    /// @brief Number of items in array.
    constexpr const static size_t len = N;
    /// @brief Array of items.
    Type ptr[N];

    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    const T& operator[](size_t index) const;
    /// @brief Get item at index.
    /// @param index Index of item to get.
    /// @return Reference to item.
    constexpr inline
    T& operator[](size_t index);

    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator const T *() const;
    /// @brief Implicit conversion to pointer.
    /// @return Pointer.
    constexpr inline
    operator T *();

    /// @brief Implicit conversion to slice.
    /// @return Pointer.
    constexpr inline
    operator Slice<T>() const;
    /// @brief Implicit conversion to slice.
    /// @return Pointer.
    constexpr inline
    operator Slice<T>();

    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    const T& operator*() const;
    /// @brief Dereference first item.
    /// @return Reference to first item.
    constexpr inline
    T& operator*();

    /// @brief Advance by given number of items.
    /// @param adv Number of items to advance by.
    /// @return Slice.
    constexpr inline
    Slice<T> operator+(size_t adv) const;

    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    const T *begin() const;
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    const T *end() const;
    /// @brief Iterator begin.
    /// @return Pointer to first item.
    constexpr inline
    T *begin();
    /// @brief Iterator end.
    /// @return Pointer to last item.
    constexpr inline
    T *end();
};

template<typename T>
struct Option {
    /// @brief Type of items.
    typedef T Type;

    /// @brief True if option is valid.
    bool is_valid;
    /// @brief Value.
    Type value;

    /// @brief Implicitly convert to boolean.
    /// @return True if option is valid.
    constexpr inline
    operator bool() const;
};

template<typename First, typename... Rest>
struct Tuple<First, Rest...> {
    First          value;
    Tuple<Rest...> rest;
};

template<typename T>
struct Tuple<T> {
    T value;
};

enum class CmpResult : int {
    /// @brief @c a is less than @c b.
    LT = -1,
    /// @brief @c a is equal to @c b.
    EQ =  0,
    /// @brief @c a is greater than @c b.
    GT =  1,
};

// NOTE(alicia): implementation

template<typename T, size_t N> constexpr inline
size_t len(const T (&array)[N]) {
    (void)array;
    return N;
}

template<typename T> inline
intptr_t __quicksort_partition(
    intptr_t lo, intptr_t hi, T *ptr, CmpFn *cmpfn, void *params, bool is_reverse
) {
    T *pivot = ptr + hi;

    intptr_t i = lo - 1;

    for(intptr_t j = lo; j <= hi - 1; ++j) {
        T *at_j = ptr + j;

        CmpResult cmpres = cmpfn(pivot, at_j, params);

        if(is_reverse ? cmpres == CmpResult::LT : cmpres == CmpResult::GT) {
            T *at_i = ptr + ++i;

            T tmp = *at_j;
            *at_j = *at_i;
            *at_i = tmp;
        }
    }

    T tmp = *(ptr + (i + 1));
    *(ptr + (i + 1)) = *(ptr + hi);
    *(ptr + hi)      = tmp;

    return i + 1;
}

template<typename T> inline
void quicksort(size_t len, T *ptr, CmpFn *cmpfn, void *params, bool is_reverse) {
    if(!len) {
        return;
    }

    intptr_t from = 0;
    intptr_t to   = len - 1;

    while(from < to) {
        intptr_t part = __quicksort_partition(from, to, ptr, cmpfn, params, is_reverse);

        if((part - from) < (to - part)) {
            quicksort(part - from, ptr + from, cmpfn, params, is_reverse);
            from = part + 1;
        } else {
            quicksort(to - (part + 1), ptr + (part + 1), cmpfn, params, is_reverse);
            to = part - 1;
        }
    }
}

template<typename T, typename U> inline
CmpResult cmp_standard(const void *a, const void *b, void *params) {
    const T *_a = (const T *)a;
    const U *_b = (const U *)b;

    if(*_a < *_b) {
        return CmpResult::LT;
    } else if(*_a > *_b) {
        return CmpResult::GT;
    } else {
        return CmpResult::EQ;
    }
}

// NOTE(alicia): impl:Slice

template<typename T> constexpr inline
Slice<T> slice(size_t len, const T *ptr) {
    union {
        const T *cptr;
        T       *ptr;
    } remove_const = {.cptr=ptr};

    Slice<T> result;
    result.len = len;
    result.ptr = remove_const.ptr;
    return result;
}

template<typename T> constexpr inline
Slice<T> slice(const T *ptr, size_t from, size_t to) {
    MINI_ASSERT(to >= from);
    union {
        const T *cptr;
        T       *ptr;
    } remove_const = {.cptr=ptr};

    Slice<T> result;
    result.len = to - from;
    result.ptr = remove_const.ptr + from;
    return result;
}

template<typename T> constexpr inline
Slice<T> slice(Slice<T> s, size_t from, size_t to) {
    MINI_ASSERT(to >= from);
    MINI_ASSERT((from + to) <= s.len);

    if((from == to) && !from) {
        return s;
    } else {
        return slice(s.ptr, from, to);
    }
}

template<typename T, size_t N> constexpr inline
Slice<T> slice(const Array<T,N>& array, size_t from, size_t to) {
    MINI_ASSERT(to >= from);
    MINI_ASSERT((from + to) <= array.len);

    return slice(array.ptr, from, to);
}

template<typename T> constexpr inline
Slice<T> advance(Slice<T> s, size_t amount) {
    return s + amount;
}

template<typename T> constexpr inline
const T& Slice<T>::operator[](size_t index) const {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

template<typename T> constexpr inline
T& Slice<T>::operator[](size_t index) {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

template<typename T> constexpr inline
Slice<T>::operator const T *() const {
    return this->ptr;
}

template<typename T> constexpr inline
Slice<T>::operator T *() {
    return this->ptr;
}

template<typename T> constexpr inline
const T& Slice<T>::operator*() const {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

template<typename T> constexpr inline
T& Slice<T>::operator*() {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

template<typename T> constexpr inline
Slice<T> Slice<T>::operator+(size_t adv) const {
    if(adv > this->len) {
        adv = this->len;
    }

    union {
        const T *cptr;
        T       *ptr;
    } remove_const = {.cptr=this->ptr};

    Slice<T> result;
    result.len = this->len - adv;
    result.ptr = remove_const.ptr + adv;
    return result;
}

template<typename T> constexpr inline
Slice<T>& Slice<T>::operator+=(size_t adv) {
    return *this = this->operator+(adv);
}

template<typename T> constexpr inline
Slice<T>& Slice<T>::operator++() {
    return *this = this->operator+(1);
}

template<typename T> constexpr inline
Slice<T>& Slice<T>::operator++(int) {
    return *this = this->operator+(1);
}

template<typename T> constexpr inline
const T *Slice<T>::begin() const {
    return this->ptr;
}
template<typename T> constexpr inline
const T *Slice<T>::end() const {
    return this->ptr + this->len;
}
template<typename T> constexpr inline
T *Slice<T>::begin() {
    return this->ptr;
}
template<typename T> constexpr inline
T *Slice<T>::end() {
    return this->ptr + this->len;
}

constexpr inline
Slice<char>::Slice() : len(0), ptr(nullptr) {}

template<size_t N> constexpr inline
Slice<char>::Slice(const char (&cstring)[N]) : len(N-1), ptr((char *)cstring) {}

constexpr inline
const char& Slice<char>::operator[](size_t index) const {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

constexpr inline
char& Slice<char>::operator[](size_t index) {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

constexpr inline
Slice<char>::operator const char *() const {
    return this->ptr;
}

constexpr inline
Slice<char>::operator char *() {
    return this->ptr;
}

constexpr inline
const char& Slice<char>::operator*() const {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

constexpr inline
char& Slice<char>::operator*() {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

constexpr inline
Slice<char> Slice<char>::operator+(size_t adv) const {
    if(adv > this->len) {
        adv = this->len;
    }

    union {
        const char *cptr;
        char       *ptr;
    } remove_const = {.cptr=this->ptr};

    Slice<char> result;
    result.len = this->len - adv;
    result.ptr = remove_const.ptr + adv;
    return result;
}

constexpr inline
Slice<char>& Slice<char>::operator+=(size_t adv) {
    return *this = this->operator+(adv);
}

constexpr inline
Slice<char>& Slice<char>::operator++() {
    return *this = this->operator+(1);
}

constexpr inline
Slice<char>& Slice<char>::operator++(int) {
    return *this = this->operator+(1);
}

constexpr inline
const char *Slice<char>::begin() const {
    return this->ptr;
}
constexpr inline
const char *Slice<char>::end() const {
    return this->ptr + this->len;
}
constexpr inline
char *Slice<char>::begin() {
    return this->ptr;
}
constexpr inline
char *Slice<char>::end() {
    return this->ptr + this->len;
}

constexpr inline
Slice<wchar_t>::Slice() : len(0), ptr(nullptr) {}

template<size_t N> constexpr inline
Slice<wchar_t>::Slice(const wchar_t (&cstring)[N]) : len(N-1), ptr((wchar_t *)cstring) {}

constexpr inline
const wchar_t& Slice<wchar_t>::operator[](size_t index) const {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

constexpr inline
wchar_t& Slice<wchar_t>::operator[](size_t index) {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

constexpr inline
Slice<wchar_t>::operator const wchar_t *() const {
    return this->ptr;
}

constexpr inline
Slice<wchar_t>::operator wchar_t *() {
    return this->ptr;
}

constexpr inline
const wchar_t& Slice<wchar_t>::operator*() const {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

constexpr inline
wchar_t& Slice<wchar_t>::operator*() {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

constexpr inline
Slice<wchar_t> Slice<wchar_t>::operator+(size_t adv) const {
    if(adv > this->len) {
        adv = this->len;
    }

    union {
        const wchar_t *cptr;
        wchar_t       *ptr;
    } remove_const = {.cptr=this->ptr};

    Slice<wchar_t> result;
    result.len = this->len - adv;
    result.ptr = remove_const.ptr + adv;
    return result;
}

constexpr inline
Slice<wchar_t>& Slice<wchar_t>::operator+=(size_t adv) {
    return *this = this->operator+(adv);
}

constexpr inline
Slice<wchar_t>& Slice<wchar_t>::operator++() {
    return *this = this->operator+(1);
}

constexpr inline
Slice<wchar_t>& Slice<wchar_t>::operator++(int) {
    return *this = this->operator+(1);
}

constexpr inline
const wchar_t *Slice<wchar_t>::begin() const {
    return this->ptr;
}
constexpr inline
const wchar_t *Slice<wchar_t>::end() const {
    return this->ptr + this->len;
}
constexpr inline
wchar_t *Slice<wchar_t>::begin() {
    return this->ptr;
}
constexpr inline
wchar_t *Slice<wchar_t>::end() {
    return this->ptr + this->len;
}

constexpr inline
Slice<char32_t>::Slice() : len(0), ptr(nullptr) {}

template<size_t N> constexpr inline
Slice<char32_t>::Slice(const char32_t (&cstring)[N]) : len(N-1), ptr((char32_t *)cstring) {}

constexpr inline
const char32_t& Slice<char32_t>::operator[](size_t index) const {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

constexpr inline
char32_t& Slice<char32_t>::operator[](size_t index) {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

constexpr inline
Slice<char32_t>::operator const char32_t *() const {
    return this->ptr;
}

constexpr inline
Slice<char32_t>::operator char32_t *() {
    return this->ptr;
}

constexpr inline
const char32_t& Slice<char32_t>::operator*() const {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

constexpr inline
char32_t& Slice<char32_t>::operator*() {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

constexpr inline
Slice<char32_t> Slice<char32_t>::operator+(size_t adv) const {
    if(adv > this->len) {
        adv = this->len;
    }

    union {
        const char32_t *cptr;
        char32_t       *ptr;
    } remove_const = {.cptr=this->ptr};

    Slice<char32_t> result;
    result.len = this->len - adv;
    result.ptr = remove_const.ptr + adv;
    return result;
}

constexpr inline
Slice<char32_t>& Slice<char32_t>::operator+=(size_t adv) {
    return *this = this->operator+(adv);
}

constexpr inline
Slice<char32_t>& Slice<char32_t>::operator++() {
    return *this = this->operator+(1);
}

constexpr inline
Slice<char32_t>& Slice<char32_t>::operator++(int) {
    return *this = this->operator+(1);
}

constexpr inline
const char32_t *Slice<char32_t>::begin() const {
    return this->ptr;
}
constexpr inline
const char32_t *Slice<char32_t>::end() const {
    return this->ptr + this->len;
}
constexpr inline
char32_t *Slice<char32_t>::begin() {
    return this->ptr;
}
constexpr inline
char32_t *Slice<char32_t>::end() {
    return this->ptr + this->len;
}

template<typename T> inline
void set(Slice<T>& s, const T& value) {
    for(auto& v : s) {
        v = value;
    }
}

template<typename T> inline
void quicksort(Slice<T> s, CmpFn *cmpfn, void *params, bool is_reverse) {
    quicksort(s.len, s.ptr, cmpfn, params, is_reverse);
}

// NOTE(alicia): impl:Buffer

template<typename T> inline
Buffer<T> buffer_alloc(size_t amount) {
    void *ptr = calloc(amount, sizeof(T));
    return buffer((T *)ptr, amount);
}

template<typename T> constexpr inline
Buffer<T> buffer(const T *ptr, size_t cap, size_t len) {
    MINI_ASSERT(len <= cap);

    union {
        const T *cptr;
        T       *ptr;
    } remove_const = {.cptr=ptr};

    Buffer<T> result;
    result.cap = cap;
    result.len = len;
    result.ptr = remove_const.ptr;
    return result;
}

template<typename T> constexpr inline
Buffer<T> buffer(Slice<T> s, size_t len) {
    return buffer(s->ptr, s->len, len);
}

template<typename T> constexpr inline
const T& Buffer<T>::operator[](size_t index) const {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

template<typename T> constexpr inline
T& Buffer<T>::operator[](size_t index) {
    MINI_ASSERT(this->len ? index < this->len : true);
    return this->ptr[index];
}

template<typename T> constexpr inline
Buffer<T>::operator const T *() const {
    return this->ptr;
}

template<typename T> constexpr inline
Buffer<T>::operator T *() {
    return this->ptr;
}

template<typename T> constexpr inline
const T& Buffer<T>::operator*() const {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

template<typename T> constexpr inline
T& Buffer<T>::operator*() {
    MINI_ASSERT(this->len);
    return *this->ptr;
}

template<typename T> constexpr inline
const T *Buffer<T>::begin() const {
    return this->ptr;
}
template<typename T> constexpr inline
const T *Buffer<T>::end() const {
    return this->ptr + this->len;
}
template<typename T> constexpr inline
T *Buffer<T>::begin() {
    return this->ptr;
}
template<typename T> constexpr inline
T *Buffer<T>::end() {
    return this->ptr + this->len;
}

template<typename T> constexpr inline
size_t remaining(const Buffer<T>& b) {
    return b.cap - b.len;
}

template<typename T> inline
void clear(Buffer<T>& b) {
    b.len = 0;
}

template<typename T> inline
void buffer_free(Buffer<T>& b) {
    if(b.ptr) {
        free(b.ptr);
    }
    b.cap = b.len = 0;
    b.ptr = nullptr;
}

template<typename T> inline
void shrink(Buffer<T>& b) {
    if(!b.ptr || !b.len || (b.len == b.cap)) {
        return;
    }

    Buffer<T> new_buf = buffer_alloc(b.len);
    memcpy(new_buf.ptr, b.ptr, sizeof(T) * b.len);
    new_buf.len = b.len;

    free(b.ptr);

    b = new_buf;
}

template<typename T> inline
void grow(Buffer<T>& b, size_t amount) {
    if(b.ptr) {
        void *newptr = realloc(b.ptr, sizeof(T) * amount);
        memset((T *)newptr + b.cap, 0, sizeof(T) * amount);
        b.ptr  = (T *)newptr;
        b.cap += amount;
    } else {
        void *ptr = calloc(amount, sizeof(T));
        b.ptr = (T *)ptr;
        b.cap = amount;
        b.len = 0;
    }
}

template<typename T> inline
void reserve(Buffer<T>& b, size_t minimum) {
    if((b.cap - b.len) >= minimum) {
        return;
    }

    size_t delta = (b.cap - b.len) + minimum;
    delta = (delta % 16) ? (delta + (16 - (delta % 16))) : delta;

    grow(b, delta);
}

template<typename T> inline
bool try_push(Buffer<T>& b, const T& item) {
    if(b.cap - b.len) {
        b.ptr[b.len++] = item;
        return true;
    } else {
        return false;
    }
}

template<typename T> inline
bool try_insert(Buffer<T>& b, size_t index, const T& item) {
    MINI_ASSERT(index <= b.len);
    if(b.cap - b.len) {
        memmove(b.ptr + index + 1, b.ptr + index, sizeof(T) * (b.len - index));
        b.ptr[index] = item;
        b.len++;

        return true;
    } else {
        return false;
    }
}

template<typename T> inline
bool try_prepend(Buffer<T>& b, const T& item) {
    if(b.cap - b.len) {
        memmove(b.ptr + 1, b.ptr, sizeof(T) * b.len);
        b.ptr[0] = item;
        b.len++;

        return true;
    } else {
        return false;
    }
}

template<typename T> inline
bool try_append(Buffer<T>& b, const T& item) {
    return try_push(b, item);
}

template<typename T> inline
bool try_insert(Buffer<T>& b, size_t index, size_t count, const T *items) {
    MINI_ASSERT(index <= b.len);

    if(remaining(b) >= count) {
        memmove(b.ptr + index + count, b.ptr + index, sizeof(T) * (b.len - index));
        memmove(b.ptr + index, items, sizeof(T) * count);
        b.len += count;

        return true;
    } else {
        return false;
    }
}

template<typename T> inline
bool try_prepend(Buffer<T>& b, size_t count, const T *items) {
    if(remaining(b) >= count) {
        memmove(b.ptr + count, b.ptr, sizeof(T) * b.len);
        memmove(b.ptr, items, sizeof(T) * count);
        b.len += count;

        return true;
    } else {
        return false;
    }
}

template<typename T> inline
bool try_append(Buffer<T>& b, size_t count, const T *items) {
    if(remaining(b) >= count) {
        memmove(b.ptr + b.len, items, sizeof(T) * count);
        b.len += count;

        return true;
    } else {
        return false;
    }
}

template<typename T> inline
bool try_insert(Buffer<T>& b, size_t index, Slice<T> items) {
    return try_insert(b, index, items.len, items.ptr);
}

template<typename T> inline
bool try_prepend(Buffer<T>& b, Slice<T> items) {
    return try_prepend(b, items.len, items.ptr);
}

template<typename T> inline
bool try_append(Buffer<T>& b, Slice<T> items) {
    return try_append(b, items.len, items.ptr);
}

template<typename T> inline
void push(Buffer<T>& b, const T& item) {
    reserve(b, 1);
    try_push(b, item);
}

template<typename T> inline
void insert(Buffer<T>& b, size_t index, const T& item) {
    reserve(b, 1);
    try_insert(b, index, item);
}

template<typename T> inline
void prepend(Buffer<T>& b, const T& item) {
    reserve(b, 1);
    try_prepend(b, item);
}

template<typename T> inline
void append(Buffer<T>& b, const T& item) {
    push(b, item);
}

template<typename T> inline
void insert(Buffer<T>& b, size_t index, size_t count, const T *items) {
    reserve(b, count);
    try_insert(b, index, count, items);
}

template<typename T> inline
void prepend(Buffer<T>& b, size_t count, const T *items) {
    reserve(b, count);
    try_prepend(b, count, items);
}

template<typename T> inline
void append(Buffer<T>& b, size_t count, const T *items) {
    reserve(b, count);
    try_append(b, count, items);
}

template<typename T> inline
void insert(Buffer<T>& b, size_t index, Slice<T> items) {
    insert(b, index, items.len, items.ptr);
}

template<typename T> inline
void prepend(Buffer<T>& b, Slice<T> items) {
    prepend(b, items.len, items.ptr);
}

template<typename T> inline
void append(Buffer<T>& b, Slice<T> items) {
    append(b, items.len, items.ptr);
}

template<typename T> inline
Option<T> pop(Buffer<T>& b) {
    if(b.len) {
        return some(b.ptr[b.len--]);
    } else {
        return none<T>();
    }
}

template<typename T> inline
void remove(Buffer<T>& b, size_t index) {
    MINI_ASSERT(index < b.len);
    memmove(b.ptr + index, b.ptr + index + 1, sizeof(T) * (b.len - (index + 1)));
    b.len--;
}

template<typename T> inline
void remove_swap(Buffer<T>& b, size_t index) {
    MINI_ASSERT(index < b.len);
    b.ptr[index] = b.ptr[--b.len];
}

template<typename T> inline
void remove_range(Buffer<T>& b, size_t from, size_t to) {
    MINI_ASSERT(to >= from);
    MINI_ASSERT((from + to) <= b.len);

    if(to - from) {
        memmove(b.ptr + from + to, b.ptr + from, sizeof(T) * (b.len - from));
        b.len -= to - from;
    }
}

// NOTE(alicia): impl:Option

template<typename T> constexpr inline
Option<T> some(const T& value) {
    Option<T> result = {.is_valid=true, .value=value};
    return result;
}

template<typename T> constexpr inline
Option<T> none() {
    union {
        char      bytes[sizeof(Option<T>)] = {0};
        Option<T> opt;
    } result;

    return result.opt;
}

template<typename T> constexpr inline
Option<T>::operator bool() const {
    return this->is_valid;
}

template<typename T> inline
T unwrap(Option<T>& opt) {
    MINI_ASSERT(opt);
    return opt.value;
}

// NOTE(alicia): impl:Array

template<typename T, size_t N> constexpr inline
Array<T,N> array() {
    union {
        char bytes[sizeof(T) * N] = {0};
        Array<T,N> array;
    } result;
    return result.array;
}

template<typename First, typename... Rest> constexpr inline
Array<First,(1 + sizeof...(Rest))> array(First first, Rest... rest) {
    auto result = array<First, (1 + sizeof...(Rest))>();
    result[0] = first;
    if constexpr(sizeof...(Rest)) {
        First arr[] = {rest...};
        for(size_t i = 1; i < result.len; ++i) {
            result[i] = arr[i - 1];
        }
    }
    return result;
}

template<typename T, size_t N> constexpr inline
const T& Array<T,N>::operator[](size_t index) const {
    MINI_ASSERT(index < this->len);
    return this->ptr[index];
}

template<typename T, size_t N> constexpr inline
T& Array<T,N>::operator[](size_t index) {
    MINI_ASSERT(index < this->len);
    return this->ptr[index];
}

template<typename T, size_t N> constexpr inline
Array<T,N>::operator const T *() const {
    return this->ptr;
}

template<typename T, size_t N> constexpr inline
Array<T,N>::operator T *() {
    return this->ptr;
}

template<typename T, size_t N> constexpr inline
Array<T,N>::operator Slice<T>() const {
    return slice(this->len, this->ptr);
}

template<typename T, size_t N> constexpr inline
Array<T,N>::operator Slice<T>() {
    return slice(this->len, this->ptr);
}

template<typename T, size_t N> constexpr inline
const T& Array<T,N>::operator*() const {
    return *this->ptr;
}

template<typename T, size_t N> constexpr inline
T& Array<T,N>::operator*() {
    return *this->ptr;
}

template<typename T, size_t N> constexpr inline
Slice<T> Array<T,N>::operator+(size_t adv) const {
    if(adv > this->len) {
        adv = this->len;
    }

    union {
        const T *cptr;
        T       *ptr;
    } remove_const = {.cptr=this->ptr};

    Slice<T> result;
    result.len = this->len - adv;
    result.ptr = remove_const.ptr + adv;
    return result;
}

template<typename T, size_t N> constexpr inline
const T *Array<T,N>::begin() const {
    return this->ptr;
}
template<typename T, size_t N> constexpr inline
const T *Array<T,N>::end() const {
    return this->ptr + this->len;
}
template<typename T, size_t N> constexpr inline
T *Array<T,N>::begin() {
    return this->ptr;
}
template<typename T, size_t N> constexpr inline
T *Array<T,N>::end() {
    return this->ptr + this->len;
}

// NOTE(alicia): impl:Tuple

template<typename First, typename... Rest> constexpr inline
Tuple<First, Rest...> tuple() {
    union {
        char bytes[sizeof(Tuple<First, Rest...>)] = {0};
        Tuple<First, Rest...> t;
    } result = {};
    return result.t;
}

template<typename First, typename... Rest> constexpr inline
Tuple<First, Rest...> tuple(First first, Rest... rest) {
    Tuple<First, Rest...> result = tuple<First, Rest...>();
    result.value = first;
    if constexpr (sizeof...(rest)) {
        result.rest  = tuple(rest...);
    }
    return result;
}

template<size_t Which, typename First, typename... Rest> constexpr inline
const auto& get(const Tuple<First, Rest...>& t) {
    if constexpr (Which) {
        return get<Which-1, Rest...>(t.rest);
    } else {
        return t.value;
    }
}

template<size_t Which, typename First, typename... Rest> constexpr inline
auto& get(Tuple<First, Rest...>& t) {
    if constexpr (Which) {
        return get<Which-1, Rest...>(t.rest);
    } else {
        return t.value;
    }
}

#undef MINI_ASSERT
#endif /* header guard */
