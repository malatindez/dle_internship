#pragma once

#include "vec.hpp"
#include <cstddef>

namespace engine::math
{

    template <size_t L, Primitive T>
    struct vec
    {
        static constexpr size_t size = L;
        constexpr vec() = default;
        explicit constexpr vec(T value)
        {
            for (int i = 0; i < size; i++)
            {
                data[i] = value;
            }
        }

        void reset()
        {
            for (int i = 0; i < size; i++)
            {
                data[i] = 0;
            }
        }

        [[nodiscard]] constexpr float length() const noexcept
        {
            return std::sqrt(squared_length());
        }

        [[nodiscard]] constexpr float squared_length() const noexcept
        {
            float return_value;
            for (int i = 0; i < size; i++)
            {
                return_value += data[i] * data[i];
            }
            return return_value;
        }

        [[nodiscard]] constexpr vec<size, T> unit_vector() const noexcept
        {
            return *this / length();
        }
        constexpr void make_unit_vector() { operator/=(length()); }

        template <Primitive U>
        constexpr vec<size, T> &operator+=(U const value) noexcept
        {
            for (int i = 0; i < size; i++)
            {
                data[i] += value;
            }
            return *this;
        }
        template <Primitive U>
        constexpr vec<size, T> &operator-=(U const value) noexcept
        {
            for (int i = 0; i < size; i++)
            {
                data[i] -= value;
            }
            return *this;
        }
        template <Primitive U>
        constexpr vec<size, T> &operator*=(U const value) noexcept
        {
            for (int i = 0; i < size; i++)
            {
                data[i] *= value;
            }
            return *this;
        }
        template <Primitive U>
        constexpr vec<size, T> &operator/=(U const value) noexcept
        {
            for (int i = 0; i < size; i++)
            {
                data[i] /= value;
            }
            return *this;
        }
        template <Primitive U>
        constexpr vec<size, T> &operator+=(vec<size, U> const &other) noexcept
        {
            for (int i = 0; i < size; i++)
            {
                data[i] += other.data[i];
            }
            return *this;
        }
        template <Primitive U>
        constexpr vec<size, T> &operator-=(vec<size, U> const &other) noexcept
        {
            for (int i = 0; i < size; i++)
            {
                data[i] -= other.data[i];
            }
            return *this;
        }
        template <Primitive U>
        constexpr vec<size, T> &operator*=(vec<size, U> const &other) noexcept
        {
            for (int i = 0; i < size; i++)
            {
                data[i] *= other.data[i];
            }
            return *this;
        }
        template <Primitive U>
        constexpr vec<size, T> &operator/=(vec<size, U> const &other) noexcept
        {
            for (int i = 0; i < size; i++)
            {
                data[i] /= other.data[i];
            }
            return *this;
        }

        [[nodiscard]] constexpr T &operator[](size_t i)
        {
            assert(i < size);
            return data[i];
        }
        [[nodiscard]] constexpr T const &operator[](size_t i) const
        {
            assert(i < size);
            return data[i];
        }
        std::array<T, size> data;
    };

}; // namespace engine::math