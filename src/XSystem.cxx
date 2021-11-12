#include "XSystem.hxx"
#include "XWindow.hxx"
#include <string>
#include "utils.hxx"

XSystem::XSystem() 
  : m_display(XOpenDisplay(nullptr))
  , m_screen(XDefaultScreen(m_display))
  , m_root(XDefaultRootWindow(m_display))
{
}

Display* XSystem::getDisplay()
{ 
  return m_display;
}

int XSystem::getScreen()
{
  return m_screen;
}

Window XSystem::getRoot()
{
  return m_root;
}

std::vector<XWindow> XSystem::getWindowStack()
{  
  std::vector<XWindow> stack;
  traverseWindowStack(stack, m_root);
  return stack;
}

void XSystem::traverseWindowStack(std::vector<XWindow>& outStack, Window entry)
{ 
  Window root, parent;
  Window* children;
  unsigned int numChildren;

  if (0 != XQueryTree(m_display, entry, &root, &parent, &children, &numChildren))
  {
    for (unsigned int idx = 0U; idx < numChildren; ++idx)
    {
      XWindowAttributes attr;
      XTextProperty prop;
      if ((0 != XGetWindowAttributes(m_display, children[idx], &attr))
        && (0 != XGetWMName(m_display, children[idx], &prop))
        && (8 == prop.format)
        && (attr.width > 1) && (attr.height > 1) && (attr.c_class))
      {
        auto name = std::string(reinterpret_cast<const char*>(prop.value), prop.nitems);
        if (!name.empty())
        {
          outStack.emplace_back(XWindow(*this, root, children[idx], name));
        }
      }
      traverseWindowStack(outStack, children[idx]);
    }
  }
}

