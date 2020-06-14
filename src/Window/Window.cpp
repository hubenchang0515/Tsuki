#include <Tsuki/Window.h>
#include <Tsuki/Log.hpp>
#include <Tsuki/Exception.hpp>
#include <Tsuki/MessageBox.h>

namespace Tsuki 
{

Window::Window(const std::string& title, int width, int height, int x, int y)
{
    m_Window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(m_Window == nullptr)
    {
        throw ObjectCreateError("SDL_CreateWindow(%s, %d, %d, %d, %d, %d) : %s", 
                title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, SDL_GetError());
    }
}

Window::~Window()
{
    if(m_Window == nullptr)
	{
		return;
	}

    SDL_DestroyWindow(m_Window);
}

SDL_Window* Window::getRaw() const
{
    return m_Window;
}

GLContext Window::createOpenGLContext() const
{
	if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return nullptr;
	}
	GLContext ret = SDL_GL_CreateContext(m_Window);
	if(ret == nullptr)
	{
		throw ObjectCreateError("SDL_GL_CreateContext(%p) : %s", m_Window, SDL_GetError());
	}
	return ret;
}

void Window::openGLPresent() const
{
	if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}
	SDL_GL_SwapWindow(m_Window);
}

void Window::setTitle(const std::string& title)
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    SDL_SetWindowTitle(m_Window, title.c_str());
}

void Window::getTitle(std::string& title) const
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    title = SDL_GetWindowTitle(m_Window);
}

void Window::setSize(int width, int height)
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    SDL_SetWindowSize(m_Window, width, height);
}

void Window::getSize(int& width, int& height) const
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    SDL_GetWindowSize(m_Window, &width, &height);
}

void Window::setPos(int x, int y)
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    SDL_SetWindowPosition(m_Window, x, y);
}

void Window::getPos(int& x, int& y) const
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    SDL_GetWindowPosition(m_Window, &x, &y);
}

void Window::show()
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    SDL_ShowWindow(m_Window);
}

void Window::hide()
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    SDL_HideWindow(m_Window);
}

void Window::focus()
{
    if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return;
	}

    SDL_RaiseWindow(m_Window);
}

MessageBox::Button Window::messageBox(const std::string& title, const std::string& content, MessageBox::Type type)
{
	if(m_Window == nullptr)
	{
		throw NullError("SDL_Window is nullptr");
		return MessageBox::Button::None;
	}

	MessageBox mbox("Tsuki::Window");
	return mbox.show(*this, title, content, type);
}	

} // namespace Tsuki 