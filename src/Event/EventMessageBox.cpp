#include <Tsuki/Event/EventMessageBox.h>

namespace Tsuki
{
    
Event::MessageBox::MessageBox(const Event& event) :  
    m_Event(event.m_Event.user)
{
    auto data = Event::unhold(event.m_Event.user.data1);
    m_Data = std::static_pointer_cast<MessageBoxEventData>(data);
}

Event::MessageBox::~MessageBox()
{

}

const std::string Event::MessageBox::name() const
{
    if(m_Data == nullptr)
    {
        return "";
    }
    return m_Data->name;
}

Event::MessageBox::Button Event::MessageBox::button() const
{
    if(m_Data == nullptr)
    {
        return MessageBoxButton::None;
    }
    return m_Data->button;
}

}; // namespace Tsuki