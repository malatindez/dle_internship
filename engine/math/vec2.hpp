#pragma once

#include "vec.hpp"

namespace math {

template <Primitive T>
class type_vec2 final {
 public:
  type_vec2(T value = 0) { data_[0] = data_[1] = value; }
  type_vec2(T x, T y) {
    data_[0] = x;
    data_[1] = y;
  }

  [[nodiscard]] inline T x() const noexcept { return data_[0]; }
  [[nodiscard]] inline T y() const noexcept { return data_[1]; }
  [[nodiscard]] inline T operator[](int i) const { return data_[i]; }
  [[nodiscard]] inline T& operator[](int i) { return data_[i]; }

  [[nodiscard]] inline float length() const noexcept {
    return std::sqrt(squared_length());
  }
  [[nodiscard]] inline float squared_length() const noexcept {
    float sum = 0;
    for (int i = 0; i < 2; i++) {
      sum += data_[i] * data_[i];
    }
    return sum;
  }

  [[nodiscard]] inline type_vec2<T> unit_vector() const noexcept {
    return *this / length();
  }
  inline void make_unit_vector() { operator/=(length()); }

  [[nodiscard]] inline type_vec2<T> const& operator+() const noexcept {
    return *this;
  }
  [[nodiscard]] inline type_vec2<T> operator-() const noexcept {
    type_vec2<T> return_value{};
    for (int i = 0; i < 2; i++) {
      return_value[i] = -return_value[i];
    }
    return return_value;
  }

  template <Primitive U>
  inline type_vec2<T>& operator+=(U const value) noexcept {
    for (int i = 0; i < 2; i++) {
      data_[i] += value;
    }
    return *this;
  }
  template <Primitive U>
  inline type_vec2<T>& operator-=(U const value) noexcept {
    for (int i = 0; i < 2; i++) {
      data_[i] -= value;
    }
    return *this;
  }
  template <Primitive U>
  inline type_vec2<T>& operator*=(U const value) noexcept {
    for (int i = 0; i < 2; i++) {
      data_[i] *= value;
    }
    return *this;
  }
  template <Primitive U>
  inline type_vec2<T>& operator/=(U const value) noexcept {
    for (int i = 0; i < 2; i++) {
      data_[i] /= value;
    }
    return *this;
  }

  template <Primitive U>
  [[nodiscard]] inline type_vec2<T>& operator+(U const value) const noexcept {
    type_vec2<T> return_value{*this};
    return_value += value;
    return return_value;
  }
  template <Primitive U>
  [[nodiscard]] inline type_vec2<T>& operator-(U const value) const noexcept {
    type_vec2<T> return_value{*this};
    return_value -= value;
    return return_value;
  }
  template <Primitive U>
  [[nodiscard]] inline type_vec2<T>& operator*(U const value) const noexcept {
    type_vec2<T> return_value{*this};
    return_value *= value;
    return return_value;
  }
  template <Primitive U>
  [[nodiscard]] inline type_vec2<T>& operator/(U const value) const noexcept {
    type_vec2<T> return_value{*this};
    return_value /= value;
    return return_value;
  }
  template <typename U>
  inline type_vec2<T> operator+=(type_vec2<U> const& other) noexcept {
    for (int i = 0; i < 2; i++) {
      data_[i] += other[i];
    }
    return *this;
  }
  template <typename U>
  inline type_vec2<T> operator-=(type_vec2<U> const& other) noexcept {
    for (int i = 0; i < 2; i++) {
      data_[i] -= other[i];
    }
    return *this;
  }
  template <typename U>
  inline type_vec2<T> operator*=(type_vec2<U> const& other) noexcept {
    for (int i = 0; i < 2; i++) {
      data_[i] *= other[i];
    }
    return *this;
  }
  template <typename U>
  inline type_vec2<T> operator/=(type_vec2<U> const& other) noexcept {
    for (int i = 0; i < 2; i++) {
      data_[i] /= other[i];
    }
    return *this;
  }

  template <typename U>
  [[nodiscard]] inline type_vec2<T> operator+(
      type_vec2<U> const& other) const noexcept {
    type_vec2<T> return_value{*this};
    return_value += other;
    return return_value;
  }
  template <typename U>
  [[nodiscard]] inline type_vec2<T> operator-(
      type_vec2<U> const& other) const noexcept {
    type_vec2<T> return_value{*this};
    return_value -= other;
    return return_value;
  }
  template <typename U>
  [[nodiscard]] inline type_vec2<T> operator*(
      type_vec2<U> const& other) const noexcept {
    type_vec2<T> return_value{*this};
    return_value *= other;
    return return_value;
  }
  template <typename U>
  [[nodiscard]] inline type_vec2<T> operator/(
      type_vec2<U> const& other) const noexcept {
    type_vec2<T> return_value{*this};
    return_value /= other;
    return return_value;
  }

 protected:
  T data_[2];
};
template <Primitive T>
inline std::istream& operator>>(std::istream& is, type_vec2<T>& vec) {
  is >> vec.data_[0] >> vec.data_[1];
  return is;
}
template <Primitive T>
inline std::ostream& operator>>(std::ostream& os, type_vec2<T>& vec) {
  os << vec.data_[0] << " " << vec.data_[1];
  return os;
}

template <Primitive T, Primitive U>
inline T dot(const type_vec2<T>& left, const type_vec2<U>& right) {
  return left.x() * left.x() + left.y() * left.y();
}
using vec2 = type_vec2<float>;
using dvec2 = type_vec2<double>;
using ivec2 = type_vec2<int>;
using bvec2 = type_vec2<bool>;
};  // namespace math