#include "core/bitmap-window.hpp"
namespace engine
{
  BitmapWindow::BitmapWindow(WNDCLASSEXW const &window_class,
                             DWORD extended_style, std::wstring const &class_name,
                             std::wstring const &window_name, DWORD style,
                             math::ivec2 position, math::ivec2 size,
                             HWND parent_window, HMENU menu, HINSTANCE instance,
                             LPVOID lp_param)
      : Window(window_class, extended_style, class_name, window_name, style,
               position, size, parent_window, menu, instance, lp_param)
  {
    bitmap_.resize(size_t(size.x) * size.y);

    hdc_ = GetDC(handle());

    bitmap_info_.bmiHeader.biSize = sizeof(bitmap_info_.bmiHeader);
    bitmap_info_.bmiHeader.biPlanes = 1;
    bitmap_info_.bmiHeader.biBitCount = 32;
    bitmap_info_.bmiHeader.biCompression = BI_RGB;
    bitmap_info_.bmiHeader.biWidth = size.x;
    bitmap_info_.bmiHeader.biHeight = size.y;
  }
  void BitmapWindow::OnSizeChanged()
  {
    const math::ivec2 size = this->size();
    bitmap_info_.bmiHeader.biWidth = size.x;
    bitmap_info_.bmiHeader.biHeight = size.y;
    bitmap_.resize(size_t(size.x) * size.y);
  }

  bool BitmapWindow::PeekOSMessages()
  {
    bool rv = Window::PeekOSMessages();
    StretchDIBits(hdc_, 0, 0, size().x, size().y, 0, 0, size().x, size().y,
                  bitmap_.data(), &bitmap_info_, DIB_RGB_COLORS, SRCCOPY);
    return rv;
  }
} // namespace engine