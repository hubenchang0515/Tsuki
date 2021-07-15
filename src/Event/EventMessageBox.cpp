#include <Tsuki/Event/EventMessageBox.h>

namespace Tsuki
{
    
Event::MessageBox::MessageBox(const Event& event) :  
    m_Event(event.m_Event.user)
{

}

const std::string& Event::MessageBox::name()
{
    const std::string* str = reinterpret_cast<const std::string*>(const_cast<const void*>(m_Event.data1));
    return *str;
}

Event::MessageBox::Button Event::MessageBox::button()
{
    intptr_t buttonId = reinterpret_cast<intptr_t>(m_Event.data2);
    return static_cast<Event::MessageBox::Button>(buttonId);
}

}; // namespace Tsuki