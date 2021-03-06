#pragma once

#include "vec.hpp"

#pragma warning(push)
#pragma warning(disable : 4201)
namespace engine::core::math
{

    template <Primitive T>
    struct vec<3, T>
    {
        static_assert(!std::is_const_v<T>);
        using type = T;
        static constexpr size_t size = 3;
        constexpr vec() = default;
        template <Primitive U>
        explicit constexpr vec(U value);
        template <Primitive A, Primitive B, Primitive C>
        explicit constexpr vec(A a, B b, C c);
        template <typename... U>
        explicit constexpr vec(U... data);
        explicit constexpr vec(std::array<T, size> const &arr) : data{arr} {}
        explicit constexpr vec(std::array<T, size> &&arr) : data{std::move(arr)} {}

        constexpr void reset() noexcept;
        template <typename U>
        constexpr vec<size, T> &operator=(rvec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }
        template <typename U>
        constexpr vec<size, T> &operator=(vec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }

        [[nodiscard]] constexpr vec<3, T> const &operator+() const noexcept;
        [[nodiscard]] constexpr vec<3, T> operator-() const noexcept;

        template <Primitive U>
        constexpr vec<3, T> &operator+=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<3, T> &operator-=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<3, T> &operator*=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<3, T> &operator/=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<3, T> &operator%=(U const value) noexcept;
        template <AnyVec U>
        constexpr vec<3, T> &operator+=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<3, T> &operator-=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<3, T> &operator*=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<3, T> &operator/=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<3, T> &operator%=(U const &other) noexcept requires(size == U::size);

        [[nodiscard]] constexpr T &operator[](size_t i);
        [[nodiscard]] constexpr T const &operator[](size_t i) const;

        constexpr explicit operator rvec<3, T>() noexcept { return rvec<3, T>{x, y, z}; }
        constexpr explicit operator rvec<3, const T>() const noexcept { return rvec<3, const T>{x, y, z}; }

        template <size_t n = size>
        [[nodiscard]] constexpr rvec<n, T> as_rvec() noexcept requires(n >= 2 && n <= size);

        template <size_t n = size, Primitive U = T>
        [[nodiscard]] constexpr vec<n, U> as_vec() const noexcept requires(n >= 2 && n <= size);
        template <size_t n = size>
        [[nodiscard]] constexpr rvec<n, const T> as_crvec() const noexcept requires(n >= 2 && n <= size);
        union
        {
            struct
            {
                union
                {
                    T x, r, s;
                };
                union
                {
                    T y, g, t;
                };
                union
                {
                    T z, b, p;
                };
            };
            std::array<T, 3> data;
        };
        static_assert(sizeof(data) == 3 * sizeof(T));

    private:
        template <Primitive _>
        static constexpr size_t get_parameter_pack_size();
        template <class V>
        static constexpr size_t get_parameter_pack_size();
        template <typename A, typename B, typename... C>
        static constexpr size_t get_parameter_pack_size();

        template <Primitive U>
        constexpr void unpack_data(size_t offset, U u);
        template <class V>
        constexpr void unpack_data(size_t offset, V vec);
        template <typename A, typename B, typename... C>
        constexpr void unpack_data(size_t offset, A a, B b, C... c);
    };

    template <Primitive T, Primitive U>
    constexpr vec<3, T> cross(vec<3, T> const &left, vec<3, U> const &right);

}; // namespace engine::core::math

#pragma warning(pop)
#include "vec3.inl"