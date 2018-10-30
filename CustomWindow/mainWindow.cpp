#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QSplitter>
#include "QuoteStandardItemModel.h"
#include <QStatusbar>
#include "mainWindow.h"
#include "myHelper.h"
#include "macrodefs.h"
#include "HJConstant.h"
#include "HJGlobalFun.h"
#include "Mgr/CodeTableMgr.h"
#include "Mgr/PosiMgr.h"
#include "Mgr/QuotationMgr.h"
#include "frmConfirmDlg.h"
#include "Global.h"
#include "HJCommon.h"
#include "frmTipsDlg.h"
#include "IniFilesManager.h"
#include "CommonStandardItemModel.h"
#include "TraderCpMgr.h"
#include "ClientTips.h"
#include "HJConstant.h"
#include "QParamEvent.h"
#include "CustomInfoMgrEx.h"
#include "TableItemDelegate.h"

extern QUOTATION gpQuotation;

#pragma execution_character_set("utf-8")


//整个区域由 title  + center 构成
mainWindow::mainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	bLoadAllData = false;
	
	
}

void mainWindow::Init()
{
	//1.初始化相关参数
	initParam();

	//2.添加资金区域
	InitAccountUI();
	//3.添加报价表
	InitTabViewUI();
	//4.添加下单板
	InitOrderUI();
	//添加报单回报
	InitOrderReturnUI();
	//添加持仓/资金/库存
	InitLocalDBUI();
	//添加成交流水
	InitTransReturnUI();
	//添加splitter
	InitSplitterUI();
	//添加状态
	InitStatusLabelUI();
	//初始化深度行情界面
	InitDeepQuoteUI();
	//初始化订阅消息
	InitSubscribe();
	//初始化右键菜单
	InitTableContextMenu();
	//从内存加载数据
	InitAllData();

	bLoadAllData = true;

	//增加模糊效果  2018-1-2
	QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
	windowShadow->setBlurRadius(9.0);
	windowShadow->setColor(QColor("#227dc3"));//palette().color(QPalette::Highlight));
	windowShadow->setOffset(0.0);
	this->setGraphicsEffect(windowShadow);

	m_pConfig = new CConfigImpl();

	QString csPath;
	myHelper::GetSystemIniPath(csPath);

	m_pConfig->Load(csPath.toStdString());

	QObject::connect(ui.securityComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slotChangeQuote(const QString &)));

	QString strCode = "Au(T+D)";
	emit ui.securityComboBox->currentIndexChanged(strCode);

	m_nTimerID = this->startTimer(10000);//间隔5秒

	m_nTimerPosiID  = this->startTimer(5000);//间隔5秒
	//请求风险通知单
	std::thread t(std::bind(&mainWindow::getRiskNotify, this));
	t.detach();

	//响应事件-修改价格，动态计算最大手数目
	QObject::connect(ui.spinBox_order_price, static_cast<void(QDoubleSpinBox::*)(const QString &)>(&QDoubleSpinBox::valueChanged), [&](const QString & strText)
	{
		//ui.label_high_hand->setText(QString::number(hand));
		CalculateMax();
	});
}
mainWindow::~mainWindow()
{
	if (0 != m_pConfig)
	{
		delete m_pConfig;
		m_pConfig = 0;
	}
	// 取消订阅广播消息
	g_TraderCpMgr.Unsubscribe(E_ONNEWBOURSEBULLETIN, this);
	g_TraderCpMgr.Unsubscribe(E_ONNEWMEMBERBULLETIN, this);
	g_TraderCpMgr.Unsubscribe(E_ONRISKNOTIFY, this);
	g_TraderCpMgr.Unsubscribe(E_ONSYSINIT, this);
	g_TraderCpMgr.Unsubscribe(E_UPDATE_LIST, this);

	g_TraderCpMgr.Unsubscribe(E_REFRESHFUND, this);

	//客户账号信息
	g_TraderCpMgr.Unsubscribe(E_CUSTOM_INFO_CHANGE, this);
	g_TraderCpMgr.Unsubscribe(E_SURPLUS_CHANGE, this);//持仓盈亏
															   //状态条信息
	g_TraderCpMgr.Unsubscribe(E_ONSYSSTATCHANGE, this);
	g_TraderCpMgr.Unsubscribe(E_HQ_STATE, this);

	//订阅行情
	g_TraderCpMgr.Unsubscribe(E_ONRECVFORWARDQUOTATION, this);
	g_TraderCpMgr.Unsubscribe(E_ONRECVDEFERDELIVERYQUOTATION, this);

	g_TraderCpMgr.Unsubscribe(E_ONRECVRTNSPOTINSTSTATEUPDATE, this);
	g_TraderCpMgr.Unsubscribe(E_ONRECVRTNFORWARDINSTSTATEUPDATE, this);
	g_TraderCpMgr.Unsubscribe(E_ONRECVRTNDEFERINSTSTATEUPDATE, this);

	g_TraderCpMgr.Unsubscribe(E_ONRECVSPOTQUOTATION, this);
	g_TraderCpMgr.Unsubscribe(E_ONRECVDEFERQUOTATION, this);
	g_TraderCpMgr.Unsubscribe(E_ONLOGINSUCC, this);
	g_TraderCpMgr.Unsubscribe(E_ONCUSTRISKDEGREECHANGE, this);

	g_TraderCpMgr.Unsubscribe(E_COMMIT_POSI, this);
	g_TraderCpMgr.Unsubscribe(E_COMMIT_STORE, this);

	g_TraderCpMgr.SubscribeAll(this, false);


	g_TraderCpMgr.UserLogout();
}



void mainWindow::InitAccountUI()
{
	accountBarWidget = new QWidget(this);
	QVBoxLayout *accountvlayout = new QVBoxLayout();
	QHBoxLayout *accountlayout = new QHBoxLayout();
	accountlayout->addSpacing(20);

	accountlayout->addWidget(ui.label_account_change);
	accountlayout->addSpacing(10);
	ui.comboBox_account->setFixedWidth(110);

	QStringList list;
	int accIndex = 0;
	for (size_t i = 0; i < App::accMgr.size(); i++)
	{
		list << App::accMgr.value(i).alias;
		if (g_Global.m_strUserID == App::accMgr.value(i).user)
			accIndex = i;
	}
	ui.comboBox_account->addItems(list);
	ui.comboBox_account->setCurrentIndex(accIndex);

	accountlayout->addWidget(ui.comboBox_account);
	accountlayout->addSpacing(15);
	
	accountlayout->addWidget(ui.pushButton_add); ui.pushButton_add->setFixedWidth(60);
	accountlayout->addSpacing(10);

	accountlayout->addWidget(ui.label_account_name);
	accountlayout->addSpacing(10);
	accountlayout->addWidget(ui.label_accountname_val);
	accountlayout->addSpacing(20);

	accountlayout->addWidget(ui.label_capital);
	accountlayout->addSpacing(10);
	accountlayout->addWidget(ui.label_capital_val);
	accountlayout->addSpacing(20);

	accountlayout->addWidget(ui.label_gain);
	accountlayout->addSpacing(10);
	accountlayout->addWidget(ui.label_gain_val);
	accountlayout->addSpacing(20);

	accountlayout->addWidget(ui.label_right);
	accountlayout->addSpacing(10);
	accountlayout->addWidget(ui.label_right_val);
	accountlayout->addSpacing(20);

	accountlayout->addWidget(ui.label_static_right);
	accountlayout->addSpacing(10);
	accountlayout->addWidget(ui.label_static_right_val);
	accountlayout->addSpacing(20);

	accountlayout->addWidget(ui.label_account_risk);
	accountlayout->addSpacing(10);
	accountlayout->addWidget(ui.label_account_risk_val);

	accountlayout->addStretch();

	//一条黑色直线，作为分割
	QFrame * line = new QFrame(this);
	line->setStyleSheet("QFrame{border: none; background-color: #030303; width:3000px;}");//height:6px;
	line->setFixedHeight(6);

	QFrame * line2 = new QFrame(this);
	line2->setStyleSheet("QFrame{border: none; background-color: #030303; width:3000px;}");//height:6px;
	line2->setFixedHeight(6);

	accountvlayout->setSpacing(0);
	accountvlayout->setMargin(0);

	accountvlayout->addWidget(line);
	accountvlayout->addLayout(accountlayout);
	accountvlayout->addWidget(line2);
	
	//用widget封一层，便于重新布局
	accountBarWidget->setLayout(accountvlayout);

	m_layout->addWidget(accountBarWidget);
}


void mainWindow::InitTabViewUI()
{
	ui.tableViewMarketPrice->setMainWinId(this);
	
	//加入报价列表单
	ui.splitter->addWidget(ui.tableViewMarketPrice);
}

void mainWindow::createOrderUI()
{
	orderWidget           = new QWidget(this);
	hLayout_left          = new QVBoxLayout();	//报单局部模块的内容

	QHBoxLayout *highLine = new QHBoxLayout();//涨停布局
	QHBoxLayout *lowLine  = new QHBoxLayout();//跌停布局
	QVBoxLayout *com      = new QVBoxLayout();//组合布局

	auto * left_line1 = new QHBoxLayout;
	auto * left_line2 = new QHBoxLayout;
	auto * left_line3 = new QHBoxLayout;
	auto * left_line4 = new QHBoxLayout;
	auto * left_line5 = new QHBoxLayout;
	auto * left_line6 = new QHBoxLayout;
	auto * left_line7 = new QHBoxLayout;

	QIniFilesManager mag;
	vector<QString> vecUserNames;
	ui.securityComboBox->clear();
	mag.ReadUserChoose(g_Global.GetListIniPath("InsID"), "UserColumnIndexs", true, vecUserNames);
	for (size_t i = 0; i < vecUserNames.size(); i++)
	{
		ui.securityComboBox->insertItem(i, vecUserNames.at(i));;
	}
	ui.securityComboBox->setView(new QListView());//加此句，CSS样式下拉高度，背景等样式才生效

	//限价报单、限价FOK、限价FAK、市价FOK、市价FAK、市价转限价
	QStringList list;
	list<< "限价报单" << "限价FOK" << "限价FAK"<< "市价FOK"<<"市价FAK" <<"市价转限价";
	ui.indiComboBox->addItems(list);
	ui.indiComboBox->setCurrentIndex(0);

	left_line1->addWidget(ui.label);
	left_line1->addSpacing(40);
	left_line1->addWidget(ui.securityComboBox);
	left_line1->addWidget(ui.label_security_tip);
	left_line1->addStretch();
	//一面二行
	left_line2->addWidget(ui.label_2);
	left_line2->addSpacing(40);
	left_line2->addWidget(ui.pushButton_yanqi);/*ui.pushButton_yanqi->setFixedSize(50, 23);*/
	left_line2->addWidget(ui.pushButton_jiaoshou);/*ui.pushButton_jiaoshou->setFixedSize(50, 23);*/
	left_line2->addWidget(ui.pushButton_zhonglicang);/*ui.pushButton_zhonglicang->setFixedSize(50, 23);*/
	left_line2->addStretch();

	//一面三行
	left_line3->addWidget(ui.label_6);
	left_line3->addSpacing(40);
	left_line3->addWidget(ui.pushButton_buy);
	left_line3->addWidget(ui.pushButton_sell);
	left_line3->addStretch();
	//一面四行
	left_line4->addWidget(ui.label_3);
	left_line4->addSpacing(40);
	left_line4->addWidget(ui.pushButton_kaicang);
	left_line4->addWidget(ui.pushButton_pingcang);
	left_line4->addStretch();
	//一面五行
	left_line5->setMargin(0);
	left_line5->addWidget(ui.label_4);
	left_line5->addSpacing(40);
	left_line5->addWidget(ui.spinBox_order_num);
	left_line5->addWidget(ui.label_7);
	left_line5->addWidget(ui.label_high_hand);

	left_line5->addStretch();
	//一面六行
	ui.label_pricetype->setText("指定价");
	ui.label_pricetype->mLastPriceMode = false;//true为最新价，false为指定价
	left_line6->setMargin(0);
	left_line6->addWidget(ui.label_pricetype);
	left_line6->addSpacing(20);
	left_line6->addWidget(ui.spinBox_order_price);


	//涨跌停价
	highLine->addWidget(ui.label_8);highLine->addWidget(ui.label_high_price);
	lowLine->addWidget(ui.label_9);lowLine->addWidget(ui.label_low_price);
	com->addLayout(highLine);com->addLayout(lowLine);
	left_line6->addLayout(com);

	left_line6->addStretch();
	//一面7行
	left_line7->addWidget(ui.pushButton_order);/*ui.pushButton_order->setFixedSize(75, 23);*/
	left_line7->addWidget(ui.pushButton_preOrder);/*ui.pushButton_preOrder->setFixedSize(75, 23);*/
	left_line7->addWidget(ui.indiComboBox);/*ui.pushButton_risk->setFixedSize(75, 23);*/
	left_line7->addStretch();

	//	//装配布局
	//hLayout_left->addSpacing(5);
	hLayout_left->addLayout(left_line1);
	hLayout_left->addLayout(left_line2);
	hLayout_left->addLayout(left_line3);
	hLayout_left->addLayout(left_line4);
	hLayout_left->addLayout(left_line5);
	hLayout_left->addLayout(left_line6);
	hLayout_left->addLayout(left_line7);

	hLayout_left->addStretch();//让上部的区域固定
	orderWidget->setFixedWidth(300);
	orderWidget->setLayout(hLayout_left);
}
void mainWindow::InitOrderUI()
{
	TabOrderBoard        = new QTabWidget;//下单板的TAB控件
	OrderBoardMainLayout = new QHBoxLayout;//下单板快整体布局【报价加行情】
	
	createOrderUI();
//	//报价部分
	createQuoteUI();

    InitNormalQuoteUI();
	//初始化状态【可通过配置，记住上次的退出的选择】
	slotChangeOrderType();
	slotChangeOpenCloseType();
	slotChangeBuyType();

	//深度行情按钮位置
	quoteButton = new QPushButton(TabOrderBoard);
	quoteButton->setGeometry(400, 0, 75, 25);
	quoteButton->setBackgroundRole(QPalette::Base);
	quoteButton->setText("深度行情");

	connect(quoteButton, &QPushButton::clicked, [this]() {
		//show非模态展示，open是模态，exec是ApplicationModal
		deepQuoteDlg->show();
		showDeepQuote = true;
		ShowDeepQuoteUI();

		quoteButton->setGeometry(230, 0, 75, 25);
	});

	connect(ui.pushButton_add, &QPushButton::clicked, this, &mainWindow::slotChangeAccount);
	connect(ui.comboBox_account, &QComboBox::currentTextChanged, this, &mainWindow::slotLoginAccount);

	m_pSplitterOrderAndOrderReturn->addWidget(TabOrderBoard);

	//添加本控件的消息
	//connect(ui.securityComboBox, SIGNAL(clicked()), this, SLOT(changeQuote()));
}

void mainWindow::InitDeepQuoteUI()
{
	showDeepQuote = false;//默认五档行情
	deepQuoteDlg  = new frmDeepQuoteDlg(this);
	deepQuoteDlg->setWindowTitle("深度行情");
	deepQuoteDlg->setGeometry(300, 200, 200, 550);
	deepQuoteDlg->setFixedSize(200, 550);

	connect(deepQuoteDlg, &frmDeepQuoteDlg::setHide, [this]() {
		deepQuoteDlg->hide();
		showDeepQuote = false;
		ShowNormalQuoteUI();

		quoteButton->setGeometry(400, 0, 75, 25);
	});
}

void mainWindow::createQuoteUI()
{
	hLayout_right = new QVBoxLayout;
	quoteWidget   = new QWidget(this);

	auto * right_line1 = new QHBoxLayout;
	auto * right_line2 = new QHBoxLayout;
	auto * right_line3 = new QHBoxLayout;
	auto * right_line4 = new QHBoxLayout;
	auto * right_line5 = new QHBoxLayout;
	auto * right_line6 = new QHBoxLayout;
	auto * right_line7 = new QHBoxLayout;
	auto * right_line8 = new QHBoxLayout;
	auto * right_line9 = new QHBoxLayout;
	auto * right_line10 = new QHBoxLayout;

	auto * right_lineSpace = new QHBoxLayout;

	auto * right_line11 = new QHBoxLayout;
	auto * right_line12 = new QHBoxLayout;
	auto * right_line13 = new QHBoxLayout;
	auto * right_line14 = new QHBoxLayout;
	auto * right_line15 = new QHBoxLayout;
	auto * right_line16 = new QHBoxLayout;
	auto * right_line17 = new QHBoxLayout;
	auto * right_line18 = new QHBoxLayout;
	auto * right_line19 = new QHBoxLayout;
	auto * right_line20 = new QHBoxLayout;


	right_lineSpace->setMargin(0);
	right_lineSpace->setSpacing(0);//买卖无间隙
	//设置line值
	right_line1->addWidget(ui.label_sell10);right_line1->addWidget(ui.label_sell_price10);right_line1->addSpacing(10); right_line1->addWidget(ui.label_sell_vol10);	right_line1->addStretch();
	right_line2->addWidget(ui.label_sell9);right_line2->addWidget(ui.label_sell_price9);right_line2->addSpacing(10); right_line2->addWidget(ui.label_sell_vol9);right_line2->addStretch();
	right_line3->addWidget(ui.label_sell8);right_line3->addWidget(ui.label_sell_price8);right_line3->addSpacing(10); right_line3->addWidget(ui.label_sell_vol8);right_line3->addStretch();
	right_line4->addWidget(ui.label_sell7);right_line4->addWidget(ui.label_sell_price7);right_line4->addSpacing(10); ;right_line4->addWidget(ui.label_sell_vol7);right_line4->addStretch();
	right_line5->addWidget(ui.label_sell6);right_line5->addWidget(ui.label_sell_price6);right_line5->addSpacing(10); ;right_line5->addWidget(ui.label_sell_vol6);right_line5->addStretch();
	right_line6->addWidget(ui.label_sell5);right_line6->addWidget(ui.label_sell_price5);right_line6->addSpacing(10); ;right_line6->addWidget(ui.label_sell_vol5);right_line6->addStretch();
	right_line7->addWidget(ui.label_sell4);right_line7->addWidget(ui.label_sell_price4);right_line7->addSpacing(10); right_line7->addWidget(ui.label_sell_vol4);right_line7->addStretch();
	right_line8->addWidget(ui.label_sell3);right_line8->addWidget(ui.label_sell_price3);right_line8->addSpacing(10); right_line8->addWidget(ui.label_sell_vol3);right_line8->addStretch();
	right_line9->addWidget(ui.label_sell2);right_line9->addWidget(ui.label_sell_price2);right_line9->addSpacing(10); ;right_line9->addWidget(ui.label_sell_vol2);right_line9->addStretch();
	right_line10->addWidget(ui.label_sell1);right_line10->addWidget(ui.label_sell_price1);right_line10->addSpacing(10); ;right_line10->addWidget(ui.label_sell_vol1);right_line10->addStretch();

	right_lineSpace->addWidget(ui.label_quote_space, 1);right_lineSpace->addWidget(ui.label_quote_space_2, 1);right_lineSpace->addStretch(0);

	right_line11->addWidget(ui.label_buy1);right_line11->addWidget(ui.label_buy_price1);right_line11->addSpacing(10); ;right_line11->addWidget(ui.label_buy_vol1);right_line11->addStretch();
	right_line12->addWidget(ui.label_buy2);right_line12->addWidget(ui.label_buy_price2);right_line12->addSpacing(10); ;right_line12->addWidget(ui.label_buy_vol2);right_line12->addStretch();
	right_line13->addWidget(ui.label_buy3);right_line13->addWidget(ui.label_buy_price3);right_line13->addSpacing(10); ;right_line13->addWidget(ui.label_buy_vol3);right_line13->addStretch();
	right_line14->addWidget(ui.label_buy4);right_line14->addWidget(ui.label_buy_price4);right_line14->addSpacing(10); ;right_line14->addWidget(ui.label_buy_vol4);right_line14->addStretch();
	right_line15->addWidget(ui.label_buy5);right_line15->addWidget(ui.label_buy_price5);right_line15->addSpacing(10); ;right_line15->addWidget(ui.label_buy_vol5);right_line15->addStretch();
	right_line16->addWidget(ui.label_buy6);right_line16->addWidget(ui.label_buy_price6);right_line16->addSpacing(10); ;right_line16->addWidget(ui.label_buy_vol6);right_line16->addStretch();
	right_line17->addWidget(ui.label_buy7);right_line17->addWidget(ui.label_buy_price7);right_line17->addSpacing(10); ;right_line17->addWidget(ui.label_buy_vol7);right_line17->addStretch();
	right_line18->addWidget(ui.label_buy8);right_line18->addWidget(ui.label_buy_price8);right_line18->addSpacing(10); ;right_line18->addWidget(ui.label_buy_vol8);right_line18->addStretch();
	right_line19->addWidget(ui.label_buy9);right_line19->addWidget(ui.label_buy_price9);right_line19->addSpacing(10); ;right_line19->addWidget(ui.label_buy_vol9);right_line19->addStretch();
	right_line20->addWidget(ui.label_buy10);right_line20->addWidget(ui.label_buy_price10);right_line20->addSpacing(10); ;right_line20->addWidget(ui.label_buy_vol10);right_line20->addStretch();

	hLayout_right->addSpacing(10);

	//10档卖盘
	hLayout_right->addLayout(right_line1);
	hLayout_right->addLayout(right_line2);
	hLayout_right->addLayout(right_line3);
	hLayout_right->addLayout(right_line4);
	hLayout_right->addLayout(right_line5);

	hLayout_right->addLayout(right_line6);
	hLayout_right->addLayout(right_line7);
	hLayout_right->addLayout(right_line8);
	hLayout_right->addLayout(right_line9);
	hLayout_right->addLayout(right_line10);

	hLayout_right->addLayout(right_lineSpace);

	/////////////////////////////买卖力度///////////////////////////////////////////	
	right_lineSpace->setDirection(QBoxLayout::LeftToRight);
	//增加间隔样式
	ui.label_quote_space->setText("");
	ui.label_quote_space->setStyleSheet("QLabel{border: none; background-color: rgb(255,43,26); margin:0px;Spacing:0px;}");//height:6px;
	ui.label_quote_space->setFixedHeight(6);
	ui.label_quote_space->setBaseSize(80, 5);

	//增加间隔样式2
	ui.label_quote_space_2->setText("");
	ui.label_quote_space_2->setStyleSheet("QLabel{border: none; background-color: #6cad3c; margin:0px;Spacing:0px;}");//height:6px;
	ui.label_quote_space_2->setFixedHeight(6);
	ui.label_quote_space_2->setBaseSize(80,5);
	//////////////////////////////////////////////////////////////////////////////

	//10档买盘
	hLayout_right->addLayout(right_line11);
	hLayout_right->addLayout(right_line12);
	hLayout_right->addLayout(right_line13);
	hLayout_right->addLayout(right_line14);
	hLayout_right->addLayout(right_line15);

	//待屏蔽
	hLayout_right->addLayout(right_line16);
	hLayout_right->addLayout(right_line17);
	hLayout_right->addLayout(right_line18);
	hLayout_right->addLayout(right_line19);
	hLayout_right->addLayout(right_line20);

	hLayout_right->addStretch();//让上面的报价区域固定
}


void mainWindow::InitNormalQuoteUI()
{
	//创建一个动态组件，容纳下单模块
	auto * leftMainWin    = new QWidget;

	hLayout_right->removeWidget(ui.label_sell10);ui.label_sell10->hide();
	hLayout_right->removeWidget(ui.label_sell9);ui.label_sell9->hide();
	hLayout_right->removeWidget(ui.label_sell8);ui.label_sell8->hide();
	hLayout_right->removeWidget(ui.label_sell7);ui.label_sell7->hide();
	hLayout_right->removeWidget(ui.label_sell6);ui.label_sell6->hide();

	hLayout_right->removeWidget(ui.label_sell_price10);ui.label_sell_price10->hide();
	hLayout_right->removeWidget(ui.label_sell_price9);ui.label_sell_price9->hide();
	hLayout_right->removeWidget(ui.label_sell_price8);ui.label_sell_price8->hide();
	hLayout_right->removeWidget(ui.label_sell_price7);ui.label_sell_price7->hide();
	hLayout_right->removeWidget(ui.label_sell_price6);ui.label_sell_price6->hide();

	hLayout_right->removeWidget(ui.label_sell_vol10);ui.label_sell_vol10->hide();
	hLayout_right->removeWidget(ui.label_sell_vol9);ui.label_sell_vol9->hide();
	hLayout_right->removeWidget(ui.label_sell_vol8);ui.label_sell_vol8->hide();
	hLayout_right->removeWidget(ui.label_sell_vol7);ui.label_sell_vol7->hide();
	hLayout_right->removeWidget(ui.label_sell_vol6);ui.label_sell_vol6->hide();

	hLayout_right->removeWidget(ui.label_buy10);ui.label_buy10->hide();
	hLayout_right->removeWidget(ui.label_buy9);ui.label_buy9->hide();
	hLayout_right->removeWidget(ui.label_buy8);ui.label_buy8->hide();
	hLayout_right->removeWidget(ui.label_buy7);ui.label_buy7->hide();
	hLayout_right->removeWidget(ui.label_buy6);ui.label_buy6->hide();

	hLayout_right->removeWidget(ui.label_buy_price10);ui.label_buy_price10->hide();
	hLayout_right->removeWidget(ui.label_buy_price9);ui.label_buy_price9->hide();
	hLayout_right->removeWidget(ui.label_buy_price8);ui.label_buy_price8->hide();
	hLayout_right->removeWidget(ui.label_buy_price7);ui.label_buy_price7->hide();
	hLayout_right->removeWidget(ui.label_buy_price6);ui.label_buy_price6->hide();

	hLayout_right->removeWidget(ui.label_buy_vol10);ui.label_buy_vol10->hide();
	hLayout_right->removeWidget(ui.label_buy_vol9);ui.label_buy_vol9->hide();
	hLayout_right->removeWidget(ui.label_buy_vol8);ui.label_buy_vol8->hide();
	hLayout_right->removeWidget(ui.label_buy_vol7);ui.label_buy_vol7->hide();
	hLayout_right->removeWidget(ui.label_buy_vol6);ui.label_buy_vol6->hide();

	//为5档报价设置布局
	quoteWidget->setLayout(hLayout_right);

	OrderBoardMainLayout->addSpacing(20);
	OrderBoardMainLayout->addWidget(orderWidget);//加报盘区域
	OrderBoardMainLayout->addSpacing(20);
	OrderBoardMainLayout->addWidget(quoteWidget);//加报价区域
	OrderBoardMainLayout->addStretch();

	//再次用窗口封了一层
	leftMainWin->setBaseSize(600, 320);
	leftMainWin->setLayout(OrderBoardMainLayout);

	TabOrderBoard->addTab(leftMainWin, "下单板");
	TabOrderBoard->setBaseSize(560, 280);
}

//removeWidget，并没有真正删除，需要hide
void mainWindow::ShowNormalQuoteUI()
{
	hLayout_right->removeWidget(ui.label_sell10);ui.label_sell10->hide();
	hLayout_right->removeWidget(ui.label_sell9);ui.label_sell9->hide();
	hLayout_right->removeWidget(ui.label_sell8);ui.label_sell8->hide();
	hLayout_right->removeWidget(ui.label_sell7);ui.label_sell7->hide();
	hLayout_right->removeWidget(ui.label_sell6);ui.label_sell6->hide();

	hLayout_right->removeWidget(ui.label_sell_price10);ui.label_sell_price10->hide();
	hLayout_right->removeWidget(ui.label_sell_price9);ui.label_sell_price9->hide();
	hLayout_right->removeWidget(ui.label_sell_price8);ui.label_sell_price8->hide();
	hLayout_right->removeWidget(ui.label_sell_price7);ui.label_sell_price7->hide();
	hLayout_right->removeWidget(ui.label_sell_price6);ui.label_sell_price6->hide();

	hLayout_right->removeWidget(ui.label_sell_vol10);ui.label_sell_vol10->hide();
	hLayout_right->removeWidget(ui.label_sell_vol9);ui.label_sell_vol9->hide();
	hLayout_right->removeWidget(ui.label_sell_vol8);ui.label_sell_vol8->hide();
	hLayout_right->removeWidget(ui.label_sell_vol7);ui.label_sell_vol7->hide();
	hLayout_right->removeWidget(ui.label_sell_vol6);ui.label_sell_vol6->hide();

	hLayout_right->removeWidget(ui.label_buy10);ui.label_buy10->hide();
	hLayout_right->removeWidget(ui.label_buy9);ui.label_buy9->hide();
	hLayout_right->removeWidget(ui.label_buy8);ui.label_buy8->hide();
	hLayout_right->removeWidget(ui.label_buy7);ui.label_buy7->hide();
	hLayout_right->removeWidget(ui.label_buy6);ui.label_buy6->hide();

	hLayout_right->removeWidget(ui.label_buy_price10);ui.label_buy_price10->hide();
	hLayout_right->removeWidget(ui.label_buy_price9);ui.label_buy_price9->hide();
	hLayout_right->removeWidget(ui.label_buy_price8);ui.label_buy_price8->hide();
	hLayout_right->removeWidget(ui.label_buy_price7);ui.label_buy_price7->hide();
	hLayout_right->removeWidget(ui.label_buy_price6);ui.label_buy_price6->hide();

	hLayout_right->removeWidget(ui.label_buy_vol10);ui.label_buy_vol10->hide();
	hLayout_right->removeWidget(ui.label_buy_vol9);ui.label_buy_vol9->hide();
	hLayout_right->removeWidget(ui.label_buy_vol8);ui.label_buy_vol8->hide();
	hLayout_right->removeWidget(ui.label_buy_vol7);ui.label_buy_vol7->hide();
	hLayout_right->removeWidget(ui.label_buy_vol6);ui.label_buy_vol6->hide();

	OrderBoardMainLayout->addWidget(quoteWidget);
	quoteWidget->setLayout(hLayout_right);
	quoteWidget->show();
}

//removeWidget，并没有真正删除，需要hide
void mainWindow::ShowDeepQuoteUI()
{	
	//格式化界面
	OrderBoardMainLayout->removeWidget(quoteWidget);
	quoteWidget->hide();
	OrderBoardMainLayout->setSizeConstraint(QLayout::SetMinimumSize);

	deepQuoteDlg->setLayout(hLayout_right);
	quoteWidget->show();
	//报价部分
	ui.label_sell10->show();ui.label_sell_vol10->show();
	ui.label_sell9->show();ui.label_sell9->show();
	ui.label_sell8->show();ui.label_sell8->show();
	ui.label_sell7->show();ui.label_sell7->show();
	ui.label_sell6->show();ui.label_sell6->show();

	ui.label_sell_price10->show();ui.label_sell_price10->show();
	ui.label_sell_price9->show();ui.label_sell_price9->show();
	ui.label_sell_price8->show();ui.label_sell_price8->show();
	ui.label_sell_price7->show();ui.label_sell_price7->show();
	ui.label_sell_price6->show();ui.label_sell_price6->show();

	ui.label_sell_vol10->show();ui.label_sell_vol10->show();
	ui.label_sell_vol9->show();ui.label_sell_vol9->show();
	ui.label_sell_vol8->show();ui.label_sell_vol8->show();
	ui.label_sell_vol7->show();ui.label_sell_vol7->show();
	ui.label_sell_vol6->show();ui.label_sell_vol6->show();

	ui.label_buy10->show();ui.label_buy_vol10->show();
	ui.label_buy9->show();ui.label_buy9->show();
	ui.label_buy8->show();ui.label_buy8->show();
	ui.label_buy7->show();ui.label_buy7->show();
	ui.label_buy6->show();ui.label_buy6->show();

	ui.label_buy_price10->show();ui.label_buy_price10->show();
	ui.label_buy_price9->show();ui.label_buy_price9->show();
	ui.label_buy_price8->show();ui.label_buy_price8->show();
	ui.label_buy_price7->show();ui.label_buy_price7->show();
	ui.label_buy_price6->show();ui.label_buy_price6->show();

	ui.label_buy_vol10->show();ui.label_buy_vol10->show();
	ui.label_buy_vol9->show();ui.label_buy_vol9->show();
	ui.label_buy_vol8->show();ui.label_buy_vol8->show();
	ui.label_buy_vol7->show();ui.label_buy_vol7->show();
	ui.label_buy_vol6->show();ui.label_buy_vol6->show();
}

void mainWindow::InitOrderReturnUI()
{
	TabRight    = new QTabWidget(this);
	orderReturnTable = new QTableView(this);
	preorderReturnTable = new QTableView(this);
	preOrderReturnWidget = new QWidget(this);

	orderReturnTable->setItemDelegate(new TableItemDelegate(orderReturnTable));
    preorderReturnTable->setItemDelegate(new TableItemDelegate(orderReturnTable));

	orderReturnTable->setMinimumWidth(300);

	orderReturnWidget = new QWidget(this);

	//加入报单的按钮以及布局
	QHBoxLayout * layout = new QHBoxLayout();
	QVBoxLayout *vlayout = new QVBoxLayout();

	vlayout->addSpacing(25);
	vlayout->addWidget(ui.pushButton_cancelorder);
	vlayout->addWidget(ui.pushButton_cancelallorder);
	vlayout->addWidget(ui.pushButton_changeorder);
	vlayout->addStretch();

	layout->setMargin(0);
	layout->addWidget(orderReturnTable);
	layout->addSpacing(5);
	layout->addLayout(vlayout);
	layout->addSpacing(15);
	//持仓页面加上布局
	orderReturnWidget->setLayout(layout);

#ifdef  _WIN32

        setWidgetStyleFromQssFile(orderReturnWidget, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\ordertable.css"));
#else
        setWidgetStyleFromQssFile(orderReturnWidget, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/ordertable.css"));
#endif

	//加入预埋单的按钮以及布局
	QVBoxLayout * prelayout = new QVBoxLayout();
	QHBoxLayout *hlayout    = new QHBoxLayout();

	hlayout->addSpacing(20);
	hlayout->addWidget(ui.pushButton_pre_delete);
	hlayout->addWidget(ui.pushButton_pre_send);
	hlayout->addWidget(ui.pushButton_clear_send);
	hlayout->addStretch();

	prelayout->setMargin(0);
	prelayout->addWidget(preorderReturnTable);
	prelayout->addLayout(hlayout);
	//持仓页面加上布局
	preOrderReturnWidget->setLayout(prelayout);

#ifdef  _WIN32

        setWidgetStyleFromQssFile(preOrderReturnWidget, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\ordertable.css"));
#else
        setWidgetStyleFromQssFile(preOrderReturnWidget, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/ordertable.css"));
#endif

	TabRight->addTab(orderReturnWidget, "报单流水");
	TabRight->addTab(preOrderReturnWidget, "预埋单");

	m_pSplitterOrderAndOrderReturn->addWidget(TabRight);

	//调整初始化高度
	m_pSplitterOrderAndOrderReturn->setStretchFactor(0, 1);
	m_pSplitterOrderAndOrderReturn->setStretchFactor(1, 7);

	
	//设置报单表
	//tableModel_order = new QStandardItemModel();
	tableModel_order = new CommonStandardItemModel();
	((CommonStandardItemModel *)tableModel_order)->LoadList(g_Global.GetListIniPath("EntrFlow"));

	//tableModel_order->sort(0,Qt::DescendingOrder);
	tableModel_order->setSortRole(1);
	orderReturnTable->setModel(tableModel_order);

	orderReturnTable->setBaseSize(width()+50, 350);
	orderReturnTable->horizontalHeader()->setFixedHeight(32);
	orderReturnTable->verticalHeader()->hide();
	orderReturnTable->verticalHeader()->setDefaultSectionSize(30);
	orderReturnTable->setShowGrid(false);
	orderReturnTable->setSortingEnabled(false);
	orderReturnTable->setAlternatingRowColors(true);//隔行换色
	orderReturnTable->setSelectionMode(QAbstractItemView::SingleSelection);
	orderReturnTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	orderReturnTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	//设置预埋单表
	//设置报单表
	//tableModel_preorder = new QStandardItemModel();
	tableModel_preorder = new CommonStandardItemModel();
	((CommonStandardItemModel *)tableModel_preorder)->LoadList(g_Global.GetListIniPath("PreOrder"));

	tableModel_preorder->setSortRole(1);
	preorderReturnTable->setModel(tableModel_preorder);

	preorderReturnTable->setBaseSize(width() + 50, 350);
	preorderReturnTable->horizontalHeader()->setFixedHeight(32);
	preorderReturnTable->verticalHeader()->hide();
	preorderReturnTable->verticalHeader()->setDefaultSectionSize(30);
	preorderReturnTable->setShowGrid(false);
	preorderReturnTable->setSortingEnabled(false);
	preorderReturnTable->setAlternatingRowColors(true);//隔行换色
	preorderReturnTable->setSelectionMode(QAbstractItemView::SingleSelection);
	preorderReturnTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	preorderReturnTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	//撤单
	connect(ui.pushButton_cancelorder, &QPushButton::clicked, this, &mainWindow::OnBnClickedButtonCancel);
	//全撤
	connect(ui.pushButton_cancelallorder, &QPushButton::clicked, this, &mainWindow::OnBnClickedButtonCancelAll);
	//改单
	connect(ui.pushButton_changeorder, &QPushButton::clicked, this, &mainWindow::OnBnClickedButtonModify);
	//删除
	connect(ui.pushButton_pre_delete, &QPushButton::clicked, this, &mainWindow::OnBnClickedButtonPreDelete);
	//立即发送
	connect(ui.pushButton_pre_send, &QPushButton::clicked, this, &mainWindow::OnBnClickedButtonPreSend);
	//清空已发送
	connect(ui.pushButton_clear_send, &QPushButton::clicked, this, &mainWindow::OnBnClickedButtonPreClear);

}


void mainWindow::loadPosiUI()
{
	tableModel_posi = new CommonStandardItemModel();
	((CommonStandardItemModel *)tableModel_posi)->LoadList(g_Global.GetListIniPath("DeferPosi"));
	
	tableModel_posi->setSortRole(1);
	Tabview_1->setModel(tableModel_posi);
	Tabview_1->setMinimumWidth(200);

	Tabview_1->horizontalHeader()->setFixedHeight(32);
	Tabview_1->verticalHeader()->hide();
	Tabview_1->verticalHeader()->setDefaultSectionSize(30);
	Tabview_1->setShowGrid(false);
	Tabview_1->setSortingEnabled(false);
	Tabview_1->setAlternatingRowColors(true);//隔行换色
	Tabview_1->setSelectionMode(QAbstractItemView::SingleSelection);
	Tabview_1->setSelectionBehavior(QAbstractItemView::SelectRows);
	Tabview_1->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许编辑

	Tabview_1->setItemDelegate(new TableItemDelegate(Tabview_1));
	
	posiWidget = new QWidget(this);
	//加入平仓，反手按钮以及布局
	QHBoxLayout * layout = new QHBoxLayout();
	QVBoxLayout *vlayout = new QVBoxLayout();

	vlayout->addSpacing(25);
	vlayout->addWidget(ui.pushButton_closePosi);
	vlayout->addWidget(ui.pushButton_reverse_order);
	vlayout->addStretch();

	layout->setMargin(0);
	layout->addWidget(Tabview_1);
	layout->addLayout(vlayout);
	layout->addSpacing(10);
	//持仓页面加上布局
	posiWidget->setLayout(layout);

#ifdef  _WIN32

        setWidgetStyleFromQssFile(posiWidget, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\positable.css"));
#else
        setWidgetStyleFromQssFile(posiWidget, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/positable.css"));
#endif


	connect(Tabview_1->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
		this, SLOT(showPosiOperationDetails(const QModelIndex &, const QModelIndex &)));


	//平仓
	connect(ui.pushButton_closePosi, &QPushButton::clicked,	this, &mainWindow::OnBnClickedButtonCov);
	//反手
	connect(ui.pushButton_reverse_order, &QPushButton::clicked,	this, &mainWindow::OnBnClickedButtonOpp);
}


void mainWindow::loadStoreUI()
{
	tableModel_store = new CommonStandardItemModel();
	((CommonStandardItemModel *)tableModel_store)->LoadList(g_Global.GetListIniPath("Store"));

	tableModel_store->setSortRole(1);
	Tabview_2->setModel(tableModel_store);
	Tabview_2->setMinimumWidth(200);

	Tabview_2->horizontalHeader()->setFixedHeight(32);
	Tabview_2->verticalHeader()->hide();
	Tabview_2->verticalHeader()->setDefaultSectionSize(30);
	Tabview_2->setShowGrid(false);
	Tabview_2->setSortingEnabled(false);
	Tabview_2->setAlternatingRowColors(true);//隔行换色
	Tabview_2->setSelectionMode(QAbstractItemView::SingleSelection);
	Tabview_2->setSelectionBehavior(QAbstractItemView::SelectRows);
	Tabview_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许编辑
	Tabview_2->setItemDelegate(new TableItemDelegate(Tabview_2));

	storeWidget = new QWidget(this);
	//加入平仓，反手按钮以及布局
	QHBoxLayout * layout = new QHBoxLayout();
	QVBoxLayout *vlayout = new QVBoxLayout();

	layout->addSpacing(20);
	layout->addWidget(ui.pushButton_getgoods);
	layout->addStretch();
	
	vlayout->setMargin(0);
	vlayout->addWidget(Tabview_2);
	vlayout->addLayout(layout);
	//持仓页面加上布局
	storeWidget->setLayout(vlayout);

#ifdef  _WIN32
        setWidgetStyleFromQssFile(storeWidget, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\positable.css"));
#else
        setWidgetStyleFromQssFile(storeWidget, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/positable.css"));
#endif

	connect(ui.pushButton_getgoods, &QPushButton::clicked, this, &mainWindow::handle2FiveSlot);

}

void mainWindow::loadCapitalUI()
{
	//tableModel_capital = new QStandardItemModel();
	tableModel_capital = new CommonStandardItemModel();
	((CommonStandardItemModel *)tableModel_capital)->LoadList(g_Global.GetListIniPath("Fund"));

	tableModel_capital->setSortRole(1);
	Tabview_3->setModel(tableModel_capital);
	Tabview_3->setMinimumWidth(200);

	Tabview_3->horizontalHeader()->setFixedHeight(32);
	Tabview_3->verticalHeader()->hide();
	Tabview_3->verticalHeader()->setDefaultSectionSize(30);
	Tabview_3->setShowGrid(false);
	Tabview_3->setSortingEnabled(false);
	Tabview_3->setAlternatingRowColors(true);//隔行换色
	Tabview_3->setSelectionMode(QAbstractItemView::SingleSelection);
	Tabview_3->setSelectionBehavior(QAbstractItemView::SelectRows);
	Tabview_3->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许编辑
	Tabview_3->setItemDelegate(new TableItemDelegate(Tabview_3));

	capitalWidget = new QWidget(this);
	//加入平仓，反手按钮以及布局
	QHBoxLayout * layout = new QHBoxLayout();
	QVBoxLayout *vlayout = new QVBoxLayout();

	layout->addSpacing(20);
	layout->addWidget(ui.pushButton_FunfInOut);
	layout->addStretch();

	vlayout->setMargin(0);
	vlayout->addWidget(Tabview_3);
	vlayout->addLayout(layout);
	//持仓页面加上布局
	capitalWidget->setLayout(vlayout);

	//给出入金添加响应
	connect(ui.pushButton_FunfInOut, &QPushButton::clicked, this, &mainWindow::handle2FourSlot);

#ifdef  _WIN32
        setWidgetStyleFromQssFile(Tabview_3, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\positable.css"));
#else
        setWidgetStyleFromQssFile(Tabview_3, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/positable.css"));
#endif

	//自适应宽度  20180404
	Tabview_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	Tabview_3->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}
//持仓/库存/资金
void mainWindow::InitLocalDBUI()
{
	tabWidget_own = new QTabWidget(this);

#ifdef  _WIN32

        setWidgetStyleFromQssFile(tabWidget_own, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\positable.css"));
#else
        setWidgetStyleFromQssFile(tabWidget_own, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/positable.css"));
#endif

	Tabview_1 = new QTableView(this);
	Tabview_2 = new QTableView(this);
	Tabview_3 = new QTableView(this);

	loadPosiUI();
	loadStoreUI();
	loadCapitalUI();
	

	tabWidget_own->addTab(posiWidget, "持仓");
	tabWidget_own->addTab(storeWidget, "库存");
	tabWidget_own->addTab(capitalWidget, "资金");

	m_pSplitterLocalDBAndTransReturn->addWidget(tabWidget_own);
}


void mainWindow::InitTransReturnUI()
{
	TabTrans            = new QTabWidget;
	TabView_trans       = new QTableView(this);
		
	tableModel_match = new CommonStandardItemModel();
	((CommonStandardItemModel *)tableModel_match)->LoadList(g_Global.GetListIniPath("MatchFlow"));

	tableModel_match->setSortRole(1);
	TabView_trans->setModel(tableModel_match);
	TabTrans->setMinimumWidth(200);

#ifdef  _WIN32
        setWidgetStyleFromQssFile(TabView_trans, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\transtable.css"));
#else
        setWidgetStyleFromQssFile(TabView_trans, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/transtable.css"));
#endif


	TabView_trans->setBaseSize(TabTrans->width(), TabTrans->height());
	TabView_trans->horizontalHeader()->setFixedHeight(32);
	TabView_trans->verticalHeader()->hide();
	TabView_trans->verticalHeader()->setDefaultSectionSize(30);
	TabView_trans->setShowGrid(false);
	TabView_trans->setSortingEnabled(false);
	TabView_trans->setAlternatingRowColors(true);//隔行换色
	TabView_trans->setSelectionMode(QAbstractItemView::SingleSelection);
	TabView_trans->setEditTriggers(QAbstractItemView::NoEditTriggers);
	TabView_trans->setSelectionBehavior(QAbstractItemView::SelectRows);
	TabView_trans->setItemDelegate(new TableItemDelegate(TabView_trans));
	TabView_trans->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
	TabView_trans->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列


	TabTrans->addTab(TabView_trans, "成交流水");


	m_pSplitterLocalDBAndTransReturn->addWidget(TabTrans);
}

void mainWindow::InitSplitterUI()
{
	m_pSplitterAllTithoutLabel->addWidget(ui.splitter);
	m_pSplitterAllTithoutLabel->addWidget(m_pSplitterOrderAndOrderReturn);
	m_pSplitterAllTithoutLabel->addWidget(m_pSplitterLocalDBAndTransReturn);

	//调整初始化高度
	m_pSplitterAllTithoutLabel->setStretchFactor(0, 20);
	m_pSplitterAllTithoutLabel->setStretchFactor(1, 1);
	m_pSplitterAllTithoutLabel->setStretchFactor(2, 15);

	m_layout->addWidget(m_pSplitterAllTithoutLabel);
}

void mainWindow::InitStatusLabelUI()
{
	statusbar = new QStatusBar(this);
	statusbar->setFixedHeight(50);

	QHBoxLayout* statuslayout = new QHBoxLayout();
	statuslayout->addSpacing(120);

	ui.label_date_val->setText(CHJGlobalFun::FormatDate(g_Global.m_strExchDate));// 系统交易日
	statuslayout->addWidget(ui.label_date);
	statuslayout->addWidget(ui.label_date_val);
	statuslayout->addSpacing(100);
	
	ui.label_sysstatus_val->setText(g_CodeTableMgr.GetCodeNameFromID("m_sys_stat", g_Global.m_strSysState));// 系统状态
	statuslayout->addWidget(ui.label_sysstatus);
	statuslayout->addWidget(ui.label_sysstatus_val);
	statuslayout->addSpacing(100);


	ui.label_branch_val->setText(g_Global.m_strBranchName);
	statuslayout->addWidget(ui.label_branch);
	statuslayout->addWidget(ui.label_branch_val);
	statuslayout->addSpacing(100);

	//服务器状态
	CCommHandler* pHandler = CCommHandler::Instance();
	QString strStatusVal;
	if (pHandler->m_mapServerGroup.size() > 0) // 防止异常
	{
		const map<string, string>& pmServer = pHandler->m_mapServerGroup.GetMap(pHandler->m_nCurServerPos);
		strStatusVal = QString::fromLocal8Bit(pmServer.find("server_name")->second.data());
	}
	ui.label_server_val->setText(strStatusVal);

	statuslayout->addWidget(ui.label_server);
	statuslayout->addWidget(ui.label_server_val);
	statuslayout->addSpacing(100);

	ui.label_server_status_val->setText("连接");
	statuslayout->addWidget(ui.label_server_status);
	statuslayout->addWidget(ui.label_server_status_val);
	statuslayout->addSpacing(100);

    //建一个窗口装入布局
	QWidget * win = new QWidget();
	win->setLayout(statuslayout);

#ifdef  _WIN32
        setWidgetStyleFromQssFile(win, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\mainwindow.css"));
#else
        setWidgetStyleFromQssFile(win, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/mainwindow.css"));
#endif


	statusbar->addWidget(win);

	//一条黑色直线，作为分割
	ui.line_status->setFixedHeight(5);
	ui.line_status->setStyleSheet("QFrame{border: none; background-color: #030303;}");
	
	m_layout->addWidget(ui.line_status);
	m_layout->addWidget(statusbar);
	
}

void mainWindow::RefreshStatusLabelUI()
{
	ui.label_date_val->setText(CHJGlobalFun::FormatDate(g_Global.m_strExchDate));// 系统交易日
	ui.label_sysstatus_val->setText(g_CodeTableMgr.GetCodeNameFromID("m_sys_stat", g_Global.m_strSysState));// 系统状态

	//服务器状态
	CCommHandler* pHandler = CCommHandler::Instance();
	QString strStatusVal;
	if (pHandler->m_mapServerGroup.size() > 0) // 防止异常
	{
		const map<string, string>& pmServer = pHandler->m_mapServerGroup.GetMap(pHandler->m_nCurServerPos);
		strStatusVal = QString::fromLocal8Bit(pmServer.find("server_name")->second.data());
	}
	
	ui.label_server_val->setText(strStatusVal);

	if(strStatusVal != "")
		ui.label_server_status_val->setText("连接");
	else
		ui.label_server_status_val->setText("网络异常");


}

//暂时在这里设置初始化值，以后保存或者读取配置获得
void mainWindow::initParam()
{
	//报价区初始值
	type = 0;
	openclose = 0;
	bullsell = 0;

	showCapital   = true;
	classiclayout = 0;

	this->setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowMinimizeButtonHint*/);
	this->setAttribute(Qt::WA_TranslucentBackground, true);

	this->setProperty("CanMove", true);
	this->setProperty("CanResize", true);

#ifdef  _WIN32

	setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\mainwindow.css"));
#else
        setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/mainwindow.css"));
#endif

	StyleSheetWidget* center = new StyleSheetWidget(this);
	this->setCentralWidget(center);

	m_layout = new QVBoxLayout(center);
	m_layout->setMargin(0);
	m_layout->setSpacing(0);
	center->setLayout(m_layout);

	this->resize(1058, 900);

	//分割器
	m_pSplitterOrderAndOrderReturn   = new QSplitter(Qt::Orientation::Horizontal);//水平  
	m_pSplitterLocalDBAndTransReturn = new QSplitter(Qt::Orientation::Horizontal);//水平  


	m_pSplitterAllTithoutLabel = new QSplitter(Qt::Orientation::Vertical);//垂直  

	 //1.添加标头
	m_title = new WindowTitle(this);
	connect(m_title, SIGNAL(buttonClick(WindowTitle::ButtonStatus)), this, SLOT(titleButtonClick(WindowTitle::ButtonStatus)));
	m_layout->addWidget(m_title);
}


void 	mainWindow::InitSubscribe()
{

	g_TraderCpMgr.Reigister(this);

	g_TraderCpMgr.SubscribeAll(this, true);
	g_TraderCpMgr.Subscribe(E_REFRESHFUND, this);

	//客户账号信息
	g_TraderCpMgr.Subscribe(E_CUSTOM_INFO_CHANGE, this);
	g_TraderCpMgr.Subscribe(E_SURPLUS_CHANGE, this);//持仓盈亏
															 //订阅行情
	g_TraderCpMgr.Subscribe(E_ONRECVFORWARDQUOTATION, this);
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERDELIVERYQUOTATION, this);
	g_TraderCpMgr.Subscribe(E_ONRECVSPOTQUOTATION, this);
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERQUOTATION, this);

	g_TraderCpMgr.Subscribe(E_ONRECVRTNSPOTINSTSTATEUPDATE, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNFORWARDINSTSTATEUPDATE, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNDEFERINSTSTATEUPDATE, this);


	//交易广播
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERORDER, this);//延期报单
	g_TraderCpMgr.Subscribe(E_ONRECVSPOTORDER, this);//现货报单
	g_TraderCpMgr.Subscribe(E_ONRECVFORWARDORDER, this);//远期报单
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERDELIVERYAPPORDER, this);//报单
	g_TraderCpMgr.Subscribe(E_ONRECVMIDDLEAPPORDER, this);//报单

																   //交易回报
	g_TraderCpMgr.Subscribe(E_ONRECVRTNSPOTORDER, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRSPSPOTORDER, this);//
	g_TraderCpMgr.Subscribe(E_ONRECVRSPFORWARDORDER, this);//
	g_TraderCpMgr.Subscribe(E_ONRECVRTNFORWARDORDER, this);//
	g_TraderCpMgr.Subscribe(E_ONRECVRTNDEFERORDER, this);//
	g_TraderCpMgr.Subscribe(E_ONRECVRSPDEFERORDER, this);//
	g_TraderCpMgr.Subscribe(E_ONRECVRTNDEFERDELIVERYAPPORDER, this);//
	g_TraderCpMgr.Subscribe(E_ONRECVRSPDEFERDELIVERYAPPORDER, this);//
	g_TraderCpMgr.Subscribe(E_ONRECVRTNMIDDLEAPPORDER, this);//
	g_TraderCpMgr.Subscribe(E_ONRECVRSPMIDDLEAPPORDER, this);//

																	  //撤单
	g_TraderCpMgr.Subscribe(E_ONRECVRTNSPOTORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRSPSPOTORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNFORWARDORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRSPFORWARDORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNDEFERORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRSPDEFERORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNDEFERDELIVERYAPPORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRSPDEFERDELIVERYAPPORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNMIDDLEAPPORDERCANCEL, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRSPMIDDLEAPPORDERCANCEL, this);

	//成交流水
	g_TraderCpMgr.Subscribe(E_ONRECVRTNSPOTMATCH, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNFORWARDMATCH, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNDEFERMATCH, this);
	g_TraderCpMgr.Subscribe(E_ONRECVRTNDEFERDELIVERYAPPMATCH, this);


	g_TraderCpMgr.Subscribe(E_ONLOGINSUCC, this);
	g_TraderCpMgr.Subscribe(E_ONCUSTRISKDEGREECHANGE, this);

	g_TraderCpMgr.Subscribe(E_COMMIT_POSI, this);
	g_TraderCpMgr.Subscribe(E_COMMIT_STORE, this);

	g_TraderCpMgr.Subscribe(E_CUSTOM_INFO_CHANGE, this);

	//20180402 增加一条预埋单，界面更新消息
	g_TraderCpMgr.Subscribe(E_PREORDER_CHANGE, this);

	g_TraderCpMgr.Subscribe(E_ONNEWBOURSEBULLETIN, this);
	g_TraderCpMgr.Subscribe(E_ONNEWMEMBERBULLETIN, this);
	g_TraderCpMgr.Subscribe(E_ONRISKNOTIFY, this);
	g_TraderCpMgr.Subscribe(E_ONSYSINIT, this);
	g_TraderCpMgr.Subscribe(E_UPDATE_LIST, this);
	g_TraderCpMgr.Subscribe(E_ONSYSSTATCHANGE, this);
	g_TraderCpMgr.Subscribe(E_HQ_STATE, this);

}
//系统按钮响应
void mainWindow::titleButtonClick(WindowTitle::ButtonStatus status)
{
	switch (status) {
	case WindowTitle::ButtonMin:
		this->showMinimized();
		break;

	case WindowTitle::ButtonMax:
		this->showMaximized();
		break;

	case WindowTitle::ButtonRestore:
		this->showNormal();
		break;

	case WindowTitle::ButtonClose:
		this->close();
		break;

	default:
		assert(false);
		break;
	}
}



template<class F, class... Args>
auto mainWindow::doUpdateUiTask(F&& f, Args&&... args)
->std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared< std::packaged_task<return_type()> >(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);

	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(queue_mutex);

		tasks.emplace([task]() { (*task)(); });
	}


	QApplication::postEvent(this, new QEvent(WM_MY_UI_TASHK));

	return res;
}



int mainWindow::OnUITask(void * wparam, void * lparam)
{
	std::unique_lock<std::mutex> lock(queue_mutex);
	while (tasks.size() > 0)
	{
		std::function<void()> task = std::move(this->tasks.front());
		tasks.pop();
		task();
	}

	return 1;
}


//自定义消息
void  mainWindow::customEvent(QEvent *e)
{
	//qDebug("mainWindow::customEvent");
	try
	{
		//OnInstStateUpdate(nullptr);//test

		QParamEvent *msg = static_cast<QParamEvent *>(e);
		if (msg->type() == MSG_RECV_QUOTATION)//行情广播
		{
			SetQuotation((QUOTATION*)msg->wparam());
		}
		/*else if (msg->type() == WM_FORCE_LOGOUT)
		{
			TForceLogout *stLogout = (TForceLogout *)msg->wparam();
			//QMessageBox::information(nullptr, "系统提示", CHJGlobalFun::str2qstr(stLogout->hint_msg));
			QMessageBox::information(nullptr, "系统提示", "系统强制退出！");
			//kenny 20180320
			//退出底层网络端口
			//CCommHandler::Instance()->Finish();

			//退出系统，自动清理管理层
			this->close();
		}*/
		//界面表格展示更新
		else if (msg->type() == WM_UPDATE_ORDER)//下单，表头重建
		{
			//下单界面  重新加载
			QIniFilesManager mag;
			vector<QString> vecUserNames;
			ui.securityComboBox->clear();
			mag.ReadUserChoose(g_Global.GetListIniPath("InsID"), "UserColumnIndexs", true, vecUserNames);
			for (size_t i = 0; i < vecUserNames.size(); i++)
			{
				ui.securityComboBox->insertItem(i, vecUserNames.at(i));;
			}

			//ui.securityComboBox->setView(new QListView());
			//行情报价界面 重新加载
			ui.tableViewMarketPrice->InitColumn();
			ui.tableViewMarketPrice->InitRowData();
		}
		else if (msg->type() == WM_UPDATE_QUOTATION_LIST)//行情展示列表，重建
		{
			ui.tableViewMarketPrice->InitColumn();
			ui.tableViewMarketPrice->InitRowData();
		}
		else if (msg->type() == WM_UPDATE_ENTR_FLOW)//报单流水，表头重建
		{
			tableModel_order->clear();
			((CommonStandardItemModel *)tableModel_order)->LoadList(g_Global.GetListIniPath("EntrFlow"));
			RefreshOrder();
		}
		else if (msg->type() == WM_UPDATE_DEFER_POSI)//持仓，表头重建
		{
			tableModel_posi->clear();
			((CommonStandardItemModel *)tableModel_posi)->LoadList(g_Global.GetListIniPath("DeferPosi"));
			RefreshPosi();//加载持仓
		}
		else if (msg->type() == WM_UPDATE_STORE)//库存，表头重建
		{
			tableModel_store->clear();
			((CommonStandardItemModel *)tableModel_store)->LoadList(g_Global.GetListIniPath("Store"));
			RefreshStore();//加载库存
		}
		else if (msg->type() == WM_UPDATE_FUN)//资金，表头重建
		{
			tableModel_capital->clear();
			((CommonStandardItemModel *)tableModel_capital)->LoadList(g_Global.GetListIniPath("Fund"));
			RefreshCapital();
		}
		else if (msg->type() == WM_UPDATE_MATCH_FLOW)
		{
			tableModel_match->clear();
			((CommonStandardItemModel *)tableModel_match)->LoadList(g_Global.GetListIniPath("MatchFlow"));
			RefreshMatch();

		}
		else if (msg->type() == WM_SYS_STAT_CHANGE)
		{
			RefreshStatusLabelUI();
		}
		else if (msg->type() == WM_ON_SYS_INIT)//初始化，进行日切，清空报单成交流水
		{
			tableModel_match->removeRows(0, tableModel_match->rowCount());
			tableModel_preorder->removeRows(0, tableModel_preorder->rowCount());
			tableModel_order->removeRows(0, tableModel_order->rowCount());
		}
		else if (msg->type() == WM_ON_RISK_NOTIFY)//风险度
		{
			//已经通过定时器完成
			//有异常，先屏蔽
			//TRiskNotity *sys = (TRiskNotity *)msg->wparam();
			//string str = sys->risk_idx1;
			//string content = sys->notify_content;
			//QMessageBox::information(nullptr, "系统提示", CHJGlobalFun::str2qstr(sys->risk_idx1));
		}
		else if (msg->type() == WM_HQ_STATE_CHANGE)
		{
			int  param = (int)msg->OrderId();
			if (param == 2)
				ui.label_server_status_val->setText("网络异常");
			else
				ui.label_server_status_val->setText("连接");

		}
		else if (msg->type() == WM_SelectTableRow)//选中行情的行
		{
			DeferInstState *state = (DeferInstState *)msg->wparam();
			if (state->instID == "")
				return;
			//Set
			if (ui.securityComboBox->currentText().compare(CHJGlobalFun::str2qstr(state->instID)) != 0)
			{
				ui.securityComboBox->setCurrentText(CHJGlobalFun::str2qstr(state->instID));
				slotChangeQuote(CHJGlobalFun::str2qstr(state->instID));
			}

		}
		else if (msg->type() == WM_PREORDER_CHANGE)//预埋单  界面更新
		{

			OnRecvPreOrderChange(msg->OrderId(), msg->getInt());

		}
		//////////////报单流水相关//////////////////////////////////////////////////////////////////
		else if (msg->type() == MSG_RECV_DEFER_ORDER)//延期报单回报
		{
			// DeferOrder *pDeferOrder= (DeferOrder *)msg->wparam();
			HandleDeferOrder(msg->wparam());
		}
		else if (msg->type() == WM_SHOW_TD_TO_TRADE)//kenny  20180329  报单同时发送来的消息，更新持仓界面
		{
			//采用自刷新解决及时响应
			/*	QString &csProdCode  = *(QString*)msg->wparam();
				bool    &csLong  = *(bool *)msg->lparam();

				UpdatePosiInfo(csProdCode,csLong);*/

		}
		else if (msg->type() == MSG_RECV_MA_ORDER)//报单流水
		{
			HandleMAOrder(msg->wparam());
		}
		else if (msg->type() == MSG_RECV_FORWARD_ORDER)//
		{
			HandleForwardOrder(msg->wparam());
		}
		else if (msg->type() == MSG_RECV_DDA_ORDER)//报单流水
		{
			HandleDDAOrder(msg->wparam());

		}
		else if (msg->type() == MSG_RECV_SPOT_ORDER)//报单流水广播
		{
			HandleSpotOrder(msg->wparam());//只处理报单回报

		}
		else if (msg->type() == MSG_MA_ORDER_CANCEL)
		{
			// DeferOrder *pDeferOrder= (DeferOrder *)msg->wparam();
			//HandleMAOrderCancel(msg->wparam());
		}
		else if (msg->type() == MSG_RECV_ORDER_CANCEL)
		{
			// DeferOrder *pDeferOrder= (DeferOrder *)msg->wparam();
			//HandleSpotOrderCancel(msg->wparam());
			//HandleOrderCancel(msg->wparam());

			RefreshOrder();
		}
		else if (msg->type() == MSG_DEFER_ORDER_CANCEL)//延期撤单
		{
			// DeferOrder *pDeferOrder= (DeferOrder *)msg->wparam();
			//HandleOrderCancel(msg->wparam());
			RefreshOrder();
		}
		else if (msg->type() == MSG_DDA_ORDER_CANCEL)
		{
			// DeferOrder *pDeferOrder= (DeferOrder *)msg->wparam();
			//HandleSpotOrder(msg->wparam());
		}
		/////////////////////成交//////////////////////////////////////////////////////////////////////
		else if (msg->type() == MSG_RECV_RTN_DDA_MATCH)//成交流水
		{
			// DeferOrder *pDeferOrder= (DeferOrder *)msg->wparam();
			tableModel_order->removeRows(0, tableModel_order->rowCount());
			tableModel_match->removeRows(0, tableModel_match->rowCount());
			RefreshOrder();
			RefreshMatch();

		}
		else if (msg->type() == MSG_RECV_RTN_DEFER_MATCH)//成交流水
		{
			tableModel_order->removeRows(0, tableModel_order->rowCount());
			tableModel_match->removeRows(0, tableModel_match->rowCount());
			RefreshOrder();
			RefreshMatch();
		}
		else if (msg->type() == MSG_RECV_RTN_SPOT_MATCH)//成交流水
		{
			tableModel_order->removeRows(0, tableModel_order->rowCount());
			tableModel_match->removeRows(0, tableModel_match->rowCount());
			RefreshOrder();
			RefreshMatch();
		}
		/////////////////////远期相关//////////////////////////////////////////////////////////////////////
		else if (msg->type() == MSG_RECV_RTN_FORWARD_MATCH)//成交流水
		{
			// DeferOrder *pDeferOrder= (DeferOrder *)msg->wparam();
			tableModel_order->removeRows(0, tableModel_order->rowCount());
			tableModel_match->removeRows(0, tableModel_match->rowCount());
			RefreshOrder();
			RefreshMatch();
		}
		/////////////////////////////////持仓/库存/资金////////////////////////////////
		else if (msg->type() == WM_REFRESH_POSI)//持仓
		{
			//直接在内存去，不能再向服务器申请了
			RefreshPosi();
		}
		else if (msg->type() == WM_REFRESH_STORE)//库存
		{
			//直接在内存去，不能再向服务器申请了
			RefreshStore();
		}
		else if (msg->type() == WM_REFRESH_FUND)//资金变化
		{

			RefreshCapital();
			//直接在内存去，不能再向服务器申请了
		}
		else if (msg->type() == WM_CUS_BASE_INFO || msg->type() == WM_CUSTOM_INFO_CHANGE)//客户基本信息
		{
			// 更新当前品种的持仓或者库存信息
			RefreshAccount();
			ProdCodeInfo info;
			GetCurProdCodeInfo(info);
			ShowCurStore(info);

			RefreshPosi();
			//// 显示可委托手数
			CalculateMax();
		}
		else if (msg->type() == WM_MY_UI_TASHK)
		{
			OnUITask(0, 0);
		}
		else if (msg->type() == WM_TOTAL_SURPLUS_CHANGE)
		{
			RefreshAccount();
			RefreshCapital();
		}
		else if (msg->type() == WM_SURPLUS_CHANGE)//行情改变，浮动盈亏改变
		{
			DeferPosi* stDeferPosiPara = (DeferPosi *)msg->wparam();
			//int test = 0;
			RefreshPosi();
			RefreshCapital();
		}

		else if (msg->type() == WM_INST_STATE_UPDATE)//合约交易状态改变
		{
			OnInstStateUpdate(msg->wparam());

		}
		else if (msg->type() == WM_SHOW_ORDER_TIPS)//1.报单回报信息提示    2.预埋单回报显示信息
		{
			//int nAddPos = *((int *)(msg->wparam()));
			int nAddPos = (msg->getInt());
			//qDebug("mainWindow::customEvent:nAddPos");
			
			if (g_Global.m_bTipsAskFail || g_Global.m_bTipsAskSus)
			{
				frmTipsDlg dlg;
				dlg.Show(nAddPos);

				dlg.exec();

			}

			if (g_Global.m_bTipsOrderMatch)//回报
			{
				frmTipsDlg dlg;
				dlg.Show(nAddPos);

				dlg.exec();
			}

		}
		else if (msg->type() == WM_SHOW_ORDER_CANCEL_TIPS)//1.撤销报单回报信息提示
		{

			int nAddPos = (msg->getInt());

			frmTipsDlg dlg;
			dlg.Show(nAddPos);

			dlg.exec();

		}
		else if (msg->type() == WM_SHOW_ORDER_RESULT_TIPS)//1.报单回报信息提示    2.预埋单回报显示信息
		{
			int nAddPos = (msg->getInt());

			if (g_Global.m_bTipsOrderMatch)
			{
				frmTipsDlg dlg;
				dlg.Show(nAddPos);

				dlg.exec();
			}

		}
		//else if (msg->type() == WM_LOG_OUT)//签退广播
		//{
		//	PTForceLogout stLogout = (PTForceLogout)(msg->wparam());
		//	QMessageBox *box = new QMessageBox(QMessageBox::Information, "提示信息", QString::fromStdString(stLogout->hint_msg));
		//	box->setModal(false);
		//	box->setAttribute(Qt::WA_DeleteOnClose);
		//	QTimer::singleShot(5000, box, SLOT(accept()));
		//	box->show();

		//	this->close();
		//}



	}
	catch (...)
	{

	}

}

//响应菜单【设置】-【重新布局】
void mainWindow::ResetLayoutSlot()
{
	if (classiclayout == 0)
	{
		classiclayout = 1;
		changToClassicLayout();
	}
	else
	{
		classiclayout = 0;
		changToOldLayout();
	}

	//保存当前设置
	QString sfile = g_Global.GetUserIniPath();
	QString str   = QString::number(g_Global.m_iInterfaceStyle);
	g_Global.m_iInterfaceStyle = classiclayout;

	App::WritePriProfileString(sfile, ("Display"), ("UIStyle"), str);
}



//单类型
void mainWindow::slotChangeOrderType()
{
	type = 0;

	ui.pushButton_yanqi->setChecked(true);
	ui.pushButton_zhonglicang->setChecked(false);
	ui.pushButton_jiaoshou->setChecked(false);

	ui.pushButton_yanqi->setStyleSheet("background-color: #227dc3;");
	ui.pushButton_zhonglicang->setStyleSheet("background-color: #2a3a57;");
	ui.pushButton_jiaoshou->setStyleSheet("background-color: #2a3a57;");

	//打开开平仓和
	enableKaiPingOrderCtl();

	AskModeChange();
}

void mainWindow::slotChangeOrderType2()
{
	type = 1;
	ui.pushButton_yanqi->setChecked(false);
	ui.pushButton_zhonglicang->setChecked(true);
	ui.pushButton_jiaoshou->setChecked(false);

	ui.pushButton_jiaoshou->setStyleSheet("background-color: #227dc3;");
	ui.pushButton_yanqi->setStyleSheet("background-color: #2a3a57;");
	ui.pushButton_zhonglicang->setStyleSheet("background-color: #2a3a57;");

	//灰掉【开平/指定价】
	disableKaipingOrderCtl();

	AskModeChange();
}

void mainWindow::slotChangeOrderType3()
{
	type = 2;
	ui.pushButton_yanqi->setChecked(false);
	ui.pushButton_zhonglicang->setChecked(false);
	ui.pushButton_jiaoshou->setChecked(true);

	ui.pushButton_zhonglicang->setStyleSheet("background-color: #227dc3;");
	ui.pushButton_yanqi->setStyleSheet("background-color: #2a3a57;");
	ui.pushButton_jiaoshou->setStyleSheet("background-color: #2a3a57;");
	
	//灰掉【开平/指定价】
	disableKaipingOrderCtl();

	AskModeChange();
}

//开或平
void mainWindow::slotChangeOpenCloseType()
{
	openclose = 0;

	ui.pushButton_kaicang->setChecked(true);
	ui.pushButton_pingcang->setChecked(false);

	ui.pushButton_kaicang->setStyleSheet("background-color: #227dc3;");
	ui.pushButton_pingcang->setStyleSheet("background-color: #2a3a57;");

	AskModeChange();
}

void mainWindow::slotChangeOpenCloseType2()
{
	openclose = 1;

	ui.pushButton_kaicang->setChecked(false);
	ui.pushButton_pingcang->setChecked(true);

	ui.pushButton_kaicang->setStyleSheet("background-color:#2a3a57;");
	ui.pushButton_pingcang->setStyleSheet("background-color: #227dc3;");

	AskModeChange();
}


void mainWindow::slotChangeBuyType()
{
	bullsell = 0;

	ui.pushButton_buy->setChecked(true);
	ui.pushButton_sell->setChecked(false);

	ui.pushButton_buy->setStyleSheet("background-color: #227dc3;");
	ui.pushButton_sell->setStyleSheet("background-color: #2a3a57;");

	AskModeChange();
}

void mainWindow::slotChangeSellType()
{
	bullsell = 1;

	ui.pushButton_buy->setChecked(false);
	ui.pushButton_sell->setChecked(true);

	ui.pushButton_buy->setStyleSheet("background-color:#2a3a57;");
	ui.pushButton_sell->setStyleSheet("background-color: #227dc3;");

	AskModeChange();
}



void mainWindow::slotLabelClicked()
{


}

void mainWindow::slotPosiTableDoubleClick(const QModelIndex & QMindex)
{
	   //判断选择改变
	   //Tabview_1->changed
	   //根据当前合约名，切换报价区域
	  
}

//响应持仓表的选择改变
void mainWindow::showPosiOperationDetails(const QModelIndex &current, const QModelIndex &previous)
{
	QModelIndex codeIndex = tableModel_posi->index(current.row(), 0);//合约名称
	QModelIndex BSindex = tableModel_posi->index(current.row(), 1);//持仓方向
	QModelIndex handindex = tableModel_posi->index(current.row(), 2);//持仓手数

	QString code = codeIndex.data().toString();
	QString bs   = BSindex.data().toString();
	
	//改变合约选择和处理
	ui.securityComboBox->setCurrentText(code);
	slotChangeQuote(code);

	if (bs.contains(QString("多")))
		slotChangeSellType();
	else
		slotChangeBuyType();
	//设置为平仓
	slotChangeOpenCloseType2();

	// 设置手数为1
	ui.label_high_hand->setText(handindex.data().toString());
	ui.spinBox_order_num->setValue(handindex.data().toString().toInt());

	AskModeChange();
}

//响应持仓表的选择改变
void mainWindow::showStoreOperationDetails(const QModelIndex &current, const QModelIndex &previous)
{
	QModelIndex codeIndex = tableModel_store->index(current.row(), 0);//合约名称
	QModelIndex handindex = tableModel_store->index(current.row(), 2);//手数

	QString code = codeIndex.data().toString();

	//改变合约选择和处理
	ui.securityComboBox->setCurrentText(code);
	slotChangeQuote(std::move(code));
	//屏蔽方式
	disableYqZlJsOrderCtl();
	//设置为卖
	slotChangeSellType();

	//设置为平仓
	disableKaipingOrderCtl();

	// 设置手数为1
	ProdCodeInfo stProdinfo;
	if (g_TraderCpMgr.GetProdCodeInfo(code, stProdinfo))
	{
		int hand = handindex.data().toInt();
		hand = hand / stProdinfo.measure_unit+0.1;
		ui.label_high_hand->setText(QString::number(hand));
		ui.spinBox_order_num->setValue(hand);
	}

	AskModeChange();
}


void mainWindow::disableKaipingOrderCtl()
{
	ui.pushButton_kaicang->setEnabled(false);
	ui.pushButton_pingcang->setEnabled(false);
	ui.pushButton_kaicang->setStyleSheet("QPushButton{background-color:rgb(100, 100, 100);}");
	ui.pushButton_pingcang->setStyleSheet("QPushButton{background-color:rgb(100, 100, 100);}");


	ui.spinBox_order_price->setEnabled(false);
}

void mainWindow::enableKaiPingOrderCtl()
{
	ui.pushButton_kaicang->setEnabled(true);
	if(ui.securityComboBox->currentText() != "Ag99.9" && ui.securityComboBox->currentText() != "Ag99.99")
	ui.pushButton_pingcang->setEnabled(true);

	ui.pushButton_kaicang->setStyleSheet("background-color: #2a3a57;");
	ui.pushButton_pingcang->setStyleSheet("background-color: #2a3a57;");
	if (openclose == 0)
		ui.pushButton_kaicang->setStyleSheet("background-color: #227dc3;");
	else
		ui.pushButton_pingcang->setStyleSheet("background-color: #227dc3;");

	ui.spinBox_order_price->setEnabled(true);

}

//灰掉延期.交收，中立仓的样式
void mainWindow::disableYqZlJsOrderCtl()
{
	ui.pushButton_yanqi->setEnabled(false);
	ui.pushButton_zhonglicang->setEnabled(false);
	ui.pushButton_jiaoshou->setEnabled(false);

	ui.pushButton_yanqi->setStyleSheet("background-color: rgb(100, 100, 100);");
	ui.pushButton_zhonglicang->setStyleSheet("background-color: rgb(100, 100, 100);");
	ui.pushButton_jiaoshou->setStyleSheet("background-color: rgb(100, 100, 100);");

}

//初始化延期.交收，中立仓的样式
void mainWindow::enableYqZlJsOrderCtl()
{
	ui.pushButton_yanqi->setEnabled(true);
	ui.pushButton_zhonglicang->setEnabled(true);
	ui.pushButton_jiaoshou->setEnabled(true);

	ui.pushButton_yanqi->setStyleSheet("background-color: #2a3a57;");
	ui.pushButton_zhonglicang->setStyleSheet("background-color: #2a3a57;");
	ui.pushButton_jiaoshou->setStyleSheet("background-color: #2a3a57;");
	if (type == 0)
		ui.pushButton_yanqi->setStyleSheet("background-color: #227dc3;");
	else if (type == 1)
		ui.pushButton_jiaoshou->setStyleSheet("background-color: #227dc3;");
	else
		ui.pushButton_zhonglicang->setStyleSheet("background-color: #227dc3;");

}


//信号槽:响应combobox选择的改变
void mainWindow::slotChangeQuote(const QString & string)
{
	ProdCodeInfo info;
	GetCurProdCodeInfo(info);

	// 切换界面模式
	if (info.market_id == CONSTANT_B_MARKET_ID_SPOT) // 现货
	{
		SwitchMode(0);
	}
	else if (info.market_id == CONSTANT_B_MARKET_ID_FORWARD) // 远期
	{
		SwitchMode(2);
	}
	else if (info.market_id == CONSTANT_B_MARKET_ID_DEFER) // 延期
	{
		SwitchMode(1);
	}



	QUOTATION* qt = &(g_TraderCpMgr.m_QMapQuotation[CHJGlobalFun::qstr2str(info.prod_code)]);

	
	// 设置初始手数为1
	ui.label_high_hand->setText("1");
	
	// 显示价格信息
	ShowPriceInfo(CHJGlobalFun::qstr2str(info.prod_code), std::move(*qt));

	// 显示买卖1-5
	SetOrderQuotation(qt);

	// 显示当前品种的仓库信息
	ShowCurStore(info);



	// 是否切换tab界面
	if (g_Global.m_bInsTriggerInfo)
	{
		// 根据当前品种类型获取tab控件的标题
		QString csTitle = (info.market_id == CONSTANT_B_MARKET_ID_SPOT) ? "库存" : "持仓";
		// 根据界面风格获取所在的窗口
		//EDLGID eDlg = (g_Global.m_iInterfaceStyle == Interface_Style_Classic) ? E_DlgDownLeft : E_DlgUpRight;
		// 获取窗口句柄

		QParamEvent *msg = new QParamEvent(WM_CHANGE_TAB_SEL);
		msg->setWParam(&csTitle);
		QApplication::sendEvent(this, new QEvent(QEvent::Type(WM_CHANGE_TAB_SEL)));

	}

	//要切换
	if ( bLoadAllData)
	{
		//if(非经典布局)
		if (info.market_id == CONSTANT_B_MARKET_ID_SPOT)
			tabWidget_own->setCurrentIndex(1);
		else
			tabWidget_own->setCurrentIndex(0);
	}

	AskModeChange();

}


//边框阴影效果   2018-1-2
void mainWindow::paintEvent(QPaintEvent *event)
{

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(10, 10, this->width() - 20, this->height() - 20);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::green));

	QColor color(0, 0, 0, 50);
	for (int i = 0; i<10; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(10 - i, 10 - i, this->width() - (10 - i) * 2, this->height() - (10 - i) * 2);
		color.setAlpha(150 - qSqrt(i) * 50);
		painter.setPen(color);
		painter.drawPath(path);
	}
	
}

void mainWindow::cleanWidgetContent()
{
	//ui.label_accountname_val->setText("");
	ui.label_capital_val->setText("");
	ui.label_gain_val->setText("");
	ui.label_right_val->setText("");
	ui.label_static_right_val->setText("");
	ui.label_account_risk_val->setText("");

	tableModel_posi->removeRows(0,tableModel_posi->rowCount());
	tableModel_store->removeRows(0,tableModel_store->rowCount());
	tableModel_capital->removeRows(0, tableModel_capital->rowCount());
	tableModel_match->removeRows(0, tableModel_match->rowCount());
	tableModel_preorder->removeRows(0, tableModel_preorder->rowCount());
	tableModel_order->removeRows(0, tableModel_order->rowCount());

}
//切换账户
void mainWindow::slotLoginAccount(const QString & str)
{
	
	//doUpdateUiTask(std::bind(&mainWindow::cleanWidgetContent, this));
	cleanWidgetContent();
	//避免切换闪烁先填入账户别名
	ui.label_accountname_val->setText(str);
	killTimer(this->m_nTimerID);
	killTimer(this->m_nTimerPosiID);
	
	//保留此刻的行情
	auto map = g_TraderCpMgr.m_QMapQuotation;

	g_TraderCpMgr.resetAccount(str.toStdString().c_str());
		
	//slotChangeQuote(ui.securityComboBox->currentText());
	//恢复行情
	std::lock_guard <mutex>  lock(m_quote_mutex);
	g_TraderCpMgr.m_QMapQuotation = map;

	InitAllData();

	m_nTimerID = this->startTimer(10000);
	m_nTimerPosiID = this->startTimer(3000);
}

#include "TranMessage.h"
#include "Global.h"

void mainWindow::handleTimeout()
{
	// 获取风险度
	Rsp3099 rsp3099; //应答报文体
	int nRet = CTranMessage::Handle3099(rsp3099, false);
	
	if (nRet == 0)
		ui.label_account_risk_val->setText(CHJGlobalFun::str2qstr(/* g_Global.m_bRiskMode1 ? rsp3099.risk_degree1 :*/ rsp3099.risk_degree2));
	
}

void mainWindow::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_nTimerID) 
	{
		handleTimeout();
	
	}
	else if (event->timerId() == m_nTimerID)
	{
		RefreshPosi();//定时刷新
	}
}

#include "frmRiskNotifyDlg.h"


frmRiskNotifyDlg  *dialog;  //最好定义成全局变量



void mainWindow::getRiskNotify()
{
	//  暂时屏蔽
	// 获取风险通知单
	//Rsp3064 rsp3064; //应答报文体
	//if (CTranMessage::Handle3064(rsp3064, false) == 0)
	//{
	//	if (rsp3064.alm_result.size() == 1)
	//	{
	//		// 获取报文中得风险通知单信息到结构
	//		const ArrayListMsg &aMsg = rsp3064.alm_result.GetValue(0);

	//		// modify by xrs 20130130 解决可能存在的内存泄露
	//		TRiskNotity body;
	//		body.acct_no = aMsg.GetStringEx(3);
	//		body.exch_date = aMsg.GetStringEx(0);
	//		body.notify_content = aMsg.GetStringEx(11);

	//		body.notify_title = aMsg.GetStringEx(10);
	//		body.risk_idx1 = aMsg.GetStringEx(7);
	//		body.risk_idx2 = aMsg.GetStringEx(8);
	//		body.call_margin = aMsg.GetStringEx(9);

	//		//if (g_TraderCpMgr.m_hMainDlg != NULL)
	//		//{
	//		//	// 发送消息到主界面，由主界面处理
	//		//	::SendMessage(g_TraderCpMgr.m_hMainDlg, WM_ON_RISK_NOTIFY, (WPARAM)&body, 0);
	//		//}

	//		frmRiskNotifyDlg  dlg;
	//		dlg.setval(body.acct_no, body.risk_idx2, body.call_margin, body.exch_date, body.notify_content);
	//		dlg.setWindowTitle(CHJGlobalFun::str2qstr(body.notify_title));
	//		dlg.show();
	//	}
	//}
	//TRiskNotity body;
	//frmRiskNotifyDlg  dlg;
	////if(dialog == nullptr)
	////	dialog = new frmRiskNotifyDlg;

	//dlg.setval(body.acct_no, body.risk_idx2, body.call_margin, body.exch_date, body.notify_content);
	//dlg.setWindowTitle("风险变动通知");
	//dlg.exec();
	//return;

}