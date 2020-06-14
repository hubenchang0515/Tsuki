#include <Tsuki/Event/EventMessageBox.h>

namespace Tsuki
{
    
Event::MessageBox::MessageBox(const Event& event) :  
    m_Event(event.m_Event.user)
{

}

const std::string Event::MessageBox::name()
{
    char* str = static_cast<char*>(m_Event.data1);
    return str;
}

Event::MessageBox::Button Event::MessageBox::button()
{
    uint64_t buttonId = reinterpret_cast<uint64_t>(m_Event.data2);
    return static_cast<Event::MessageBox::Button>(buttonId);
}

}; // namespace Tsuki