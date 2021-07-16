#ifndef TSUKI_EVENT_MESSAGEBOX_H
#define TSUKI_EVENT_MESSAGEBOX_H

#include <Tsuki/Event/EventBase.h>
#include <Tsuki/Window/MessageBox.h>

namespace Tsuki
{

class Event::MessageBox
{
public:
    using Button = Tsuki::MessageBox::Button;

    MessageBox() = delete;
    MessageBox(const Event& event);
    ~MessageBox();

    const std::string name() const;
    Button button() const;

private:
    const SDL_UserEvent& m_Event;
    std::shared_ptr<MessageBoxEventData> m_Data;
};

}; // namespace Tsuki

#endif 