#pragma once

#include "vec.hpp"

namespace engine::math
{

  template <Primitive T>
  struct vec<2, T>
  {
    using type = T;
    static constexpr size_t size = 2;
    constexpr vec() = default;
    template <Primitive U>
    explicit constexpr vec(U value);
    template <Primitive A, Primitive B>
    explicit constexpr vec(A a, B b);
    template <typename... U>
    explicit constexpr vec(U... data);
    constexpr void reset() noexcept;

    [[nodiscard]] constexpr vec<2, T> const &operator+() const noexcept;

    [[nodiscard]] constexpr vec<2, T> operator-() const noexcept;

    template <Primitive U>
    constexpr vec<2, T> &operator+=(U const value) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator-=(U const value) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator*=(U const value) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator/=(U const value) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator%=(U const value) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator+=(vec<2, U> const &other) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator-=(vec<2, U> const &other) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator*=(vec<2, U> const &other) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator/=(vec<2, U> const &other) noexcept;
    template <Primitive U>
    constexpr vec<2, T> &operator%=(vec<2, U> const &other) noexcept;
    [[nodiscard]] constexpr T &operator[](size_t i);
    [[nodiscard]] constexpr T const &operator[](size_t i) const;
    union
    {
      struct
      {
        union { T x, r, s, u; };
        union { T y, g, t, v; };
      };
      std::array<T, 2> data;
    };
    static_assert(sizeof(data) == 2 * sizeof(T));

  private:
    template <Primitive _>
    static constexpr size_t get_parameter_pack_size();
    template <class V>
    static constexpr size_t get_parameter_pack_size();
    template <typename A, typename B, typename... C>
    static constexpr size_t get_parameter_pack_size();

    template <Primitive U>
    constexpr void unpack_data(int offset, U u);
    template <class V>
    constexpr void unpack_data(int offset, V vec);
    template <typename A, typename B, typename... C>
    constexpr void unpack_data(int offset, A a, B b, C... c);
  };

}; // namespace engine::math

#include "vec2.inl"