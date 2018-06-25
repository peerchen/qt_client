#ifndef LXNAMESPACE_H
#define LXNAMESPACE_H

#include <QString>
#include <QList>
#include <QTime>

namespace Lx {
    enum MsgType
    {
        MarketLink = 0,//行情连接
        SwitchChannel,//切换通道
        SyntaxError,//条件编辑框语法错误提示
        StrategyMgrRecord,//策略库管理记录
        RealAccountLink,//实盘账户连接
        ManualTrade,//手动交易
        StrategyTrade,//策略交易

        MsgTypeEnd,//枚举结束
    };

    enum MsgLevel
    {
        High,//高
        Mid,//中
        Low,//低
    };
    typedef struct LxMsg{
        Lx::MsgType type;//消息类型
        QString channel;//通道 该字段可以用下面两个宏 REAL_CHANNEL SIMULATE_CHANNEL
        Lx::MsgLevel     level;//级别
        QDateTime time;//时间
        QString src;//来源
        QString desc;//事件描述

    } LxMsg;


#define REAL_CHANNEL QString::fromLocal8Bit("真实交易")
#define SIMULATE_CHANNEL QString::fromLocal8Bit("模拟交易")
#define TIME_FORMAT "yyyy/M/d HH:m:s"


    struct LxStrPair//键值对
    {
        QString key;
        QString value;
        QString type;
    };

    const QString XML_Root("Theme");
    const QString XML_Surface("Surface");
    const QString XML_Voice("Voice");
    const QString XML_TradeSignal("TradeSignal");
    const QString XML_IconAndScreen("IconAndScreen");

    const QString XML_ColorSheme("ColorSheme");
    const QString XML_General("General");
    const QString XML_Market("Market");
    const QString XML_KLine("KLine");
    const QString XML_InfoBar("InfoBar");
    const QString XML_Report("Report");
    const QString XML_Curve("Curve");
    const QString XML_Indicator("Indicator");
    const QString XML_TableItem("TableItem");

    const QString XML_OpenTime("OpenTime");
    const QString XML_CloseTime("CloseTime");
    const QString XML_TradeBuyTime("TradeBuyTime");
    const QString XML_TradeSellTime("TradeSellTime");
    const QString XML_NetWorkTime("NetWorkTime");

    const QString XML_TriggerMark("TriggerMark");
    const QString XML_TriggerLine("TriggerLine");
    const QString XML_TradeMark("TradeMark");
    const QString XML_TradeLine("TradeLine");

    const QString Attr_KLineState("kLineState");
    const QString Attr_Name("name");
    const QString Attr_IsCurrentUse("isCurrentUse");
    const QString Attr_Key("key");
    const QString Attr_Value("value");
    const QString Attr_Type("type");
    const QString Attr_EnableVoice("enableVoice");
    const QString Attr_VoicPath("voicePath");
    const QString Attr_VoicTime("voiceTime");

    const QString Attr_EnableLockScreenHotKey("enableLockScreenHotKey");
    const QString Attr_HotKey("hotKey");
    const QString Attr_LockTime("lockTime");
    const QString Attr_EnableLockTime("enableLockTime");
    const QString Attr_IconMode("IconMode");
}


#endif // LXNAMESPACE_H
