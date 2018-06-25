/*************************************************************************************
 * FILENAME : QMessageMap.h
 * FUNCTION : qt下的消息映射实现
 * VERSION  : CSMD3.0
 * NOTES    : 对照MFC消息映射的步骤来写即可
 ***************************************************************************************/

#pragma once

#include <QEvent>
#define q_msg
#define USER_MSG  QEvent::User
using sMSG = QEvent::Type;
using lparam = void*;
using wparam = void*;

using namespace std;

class  Message : public QEvent
{
public:
    explicit Message(sMSG type, const lparam p, const wparam w)
        :QEvent(type), m_lparam(p), m_wparam(w)
    {

    }

    ~Message(){}
    inline const lparam Lparam() const { return m_lparam; }
    inline const wparam Wparam() const { return m_wparam; }
protected:
    lparam m_lparam;
    wparam m_wparam;
};



#define REGISTER_MSG_MAP(msg) if (m_MapMsg.find(msg) == m_MapMsg.end())\
   m_MapMsg.insert(make_pair(msg, static_cast<sMSG>(QEvent::registerEventType(msg))))

#define DECLARE_MSG_MAP()  bool event(QEvent *e);\
    map<int, sMSG> m_MapMsg;

#define ON_MSG(sg,OnMsg)  case (sg) : \
    OnMsg##(msg->Lparam(), msg->Wparam());  \
    break;

#define BEGIN_MESSAGE_MAP(parent, child) bool child##::event(QEvent *e) \
{ \
    parent##::event(e); \
    Message* msg = (Message*)e;\
    switch(msg->type()) \
{

#define END_MESSAGE_MAP() default: \
      break;}\
    return true;}

#define PostMessage(msg, p, w)  REGISTER_MSG_MAP(msg);\
                 QCoreApplication::postEvent(this, new Message(m_MapMsg[msg], p, w))

#define gLPostMessage(receiver, msg, p, w) REGISTER_MSG_MAP(msg);\
QCoreApplication::postEvent(receiver, new Message(m_MapMsg[msg], p, w))
