#ifdef _WIN32
#include "WinWindow.hxx"
#include "utils.hxx"

WinWindow::WinWindow(HWND window, std::string name)
  : m_window(window)
  , m_name(name)
{
}

std::string WinWindow::getName() 
{
  return m_name;
}

void WinWindow::moveAndResize(int x, int y, unsigned int width, unsigned int height) 
{
  MoveWindow(m_window, x, y, width, height, true);
}

void WinWindow::raise()
{
  RECT rect;
  if (GetWindowRect(m_window, &rect))
  {
    LOG_INFO("Raise to top: " << m_name);
    SetWindowPos(m_window, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_ASYNCWINDOWPOS);
  }
}
#endif
