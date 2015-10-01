#ifndef COMMANDDISPATCHER_H
#define COMMANDDISPATCHER_H

class CommandDispatcher
{
public:
    CommandDispatcher(int port = 5555);
    ~CommandDispatcher();

    /** Advertises a fake user */
    void advertise();

private:
    class Private;
    Private * const d;
};

#endif  // COMMANDDISPATCHER_H
