
#include <cassert>
//#include <windowsx.h>
//#include <windows.h>

#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QSplitter>
#include "StandardItemModel.h"
#include <QStatusbar>
#include "mainWindow.h"
#include "myHelper.h"
#include "macrodefs.h"
#include "HJConstant.h"
#include "HJGlobalFun.h"
#include "Mgr/CodeTableMgr.h"
#include "Global.h"

//kenny  20171128  订阅,管理
#include "TraderCpMgr.h"

#pragma execution_character_set("utf-8")

void mainWindow::InitAccountUI()
{
	
	QHBoxLayout* accountlayout = new QHBoxLayout(this);
	accountlayout->addSpacing(60);

	ui.label_accountname_png->setPixmap(QPixmap::fromImage(QImage(":/res/accountname")));

	accountlayout->addWidget(ui.label_accountname_png);
	accountlayout->addWidget(ui.label_account_name);
	accountlayout->addWidget(ui.label_accountname_val);
	accountlayout->addSpacing(10);

	ui.label_capital_png->setPixmap(QPixmap::fromImage(QImage(":/res/accountcapital")));

	accountlayout->addWidget(ui.label_capital_png);
	accountlayout->addWidget(ui.label_capital);
	accountlayout->addWidget(ui.label_capital_val);
	accountlayout->addSpacing(10);

	ui.label_gain_png->setPixmap(QPixmap::fromImage(QImage(":/res/accountgain")));
	accountlayout->addWidget(ui.label_gain_png);
	accountlayout->addWidget(ui.label_gain);
	accountlayout->addWidget(ui.label_gain_val);
	accountlayout->addSpacing(10);

	ui.label_right_png->setPixmap(QPixmap::fromImage(QImage(":/res/accountright")));
	accountlayout->addWidget(ui.label_right_png);
	accountlayout->addWidget(ui.label_right);
	accountlayout->addWidget(ui.label_right_val);
	accountlayout->addSpacing(10);

	ui.label_static_right_png->setPixmap(QPixmap::fromImage(QImage(":/res/accountStaticRight")));
	accountlayout->addWidget(ui.label_static_right_png);
	accountlayout->addWidget(ui.label_static_right);
	accountlayout->addWidget(ui.label_static_right_val);
	accountlayout->addStretch();

	//添加上下带渐变的间隙  
	//auto * labelSpace = new QLabel(this);
	//QString str = "background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #030303,stop:1 #2a3a57);";
	//labelSpace->setStyleSheet(str);
	//auto *gridlayout = new QGridLayout(this);

	//auto * labelSpace2 = new QLabel(this);
	//labelSpace2->setStyleSheet(str);
	//
	//gridlayout->addWidget(labelSpace,0,0);
	//gridlayout->addLayout(accountlayout, 1, 0);
	//gridlayout->addWidget(labelSpace2, 2, 0);
	//m_layout->addLayout(gridlayout);

	//一条黑色直线，作为分割
	QFrame * line = new QFrame(this);
	line->setStyleSheet("QFrame{border: none; background-color: #030303; }");//height:6px;
	line->setFixedHeight(6);

	QFrame * line2 = new QFrame(this);
	line2->setStyleSheet("QFrame{border: none; background-color: #030303; }");//height:6px;
	line2->setFixedHeight(6);

	m_layout->addWidget(line);
    m_layout->addLayout(accountlayout);
	m_layout->addWidget(line2);
	

}


void mainWindow::InitTabViewUI()
{
	//一条黑色直线，作为分割
	//QFrame * line = new QFrame(this);
	//line->setStyleSheet("QFrame{border: none; background-color: #030303;height:6px; }");
	//line->setFixedHeight(6);
	

	//加入报价列表单
	ui.splitter->addWidget(ui.tableViewMarketPrice);

}

void mainWindow::InitOrderUI()
{
	auto *TabLeft = new QTabWidget;

	//第一个页面的内容
	auto *leftMainWin = new QWidget;
	auto * leftMainLayout = new QHBoxLayout;
	auto * hLayout_left = new QVBoxLayout;
	auto * left_line1 = new QHBoxLayout;
	auto * left_line2 = new QHBoxLayout;
	auto * left_line3 = new QHBoxLayout;
	auto * left_line4 = new QHBoxLayout;
	auto * left_line5 = new QHBoxLayout;
	auto * left_line6 = new QHBoxLayout;

	//一面一行
	QStringList  strList;
	strList.append("Ag(T+D)");strList.append("Au(T+D)");strList.append("Au9999");
	ui.securityComboBox->addItems(strList);
	ui.securityComboBox->setView(new QListView());//加此句，CSS样式下拉高度，背景等样式才生效

	left_line1->addWidget(ui.label);
	left_line1->addWidget(ui.securityComboBox);
	left_line1->addWidget(ui.label_security_tip);
	//left_line1->addStretch(1);
	//一面二行
	left_line2->addWidget(ui.label_2);
	left_line2->addWidget(ui.pushButton_yanqi);/*ui.pushButton_yanqi->setFixedSize(50, 23);*/
	left_line2->addWidget(ui.pushButton_jiaoshou);/*ui.pushButton_jiaoshou->setFixedSize(50, 23);*/
	left_line2->addWidget(ui.pushButton_zhonglicang);/*ui.pushButton_zhonglicang->setFixedSize(50, 23);*/
	//left_line2->addStretch();
	//一面三行
	left_line3->addWidget(ui.label_3);
	left_line3->addWidget(ui.pushButton_kaicang);
	left_line3->addWidget(ui.pushButton_pingcang);
	//left_line3->addStretch();
	//一面四行
	left_line4->addWidget(ui.label_4);
	left_line4->addWidget(ui.spinBox_order_num);
	left_line4->addWidget(ui.label_7);
	//left_line4->addStretch(1);
	//一面五行
	left_line5->addWidget(ui.label_5);
	left_line5->addWidget(ui.spinBox_order_price);
	left_line5->addWidget(ui.label_8);
	//left_line5->addStretch();
	//一面六行
	left_line6->addWidget(ui.pushButton_order);/*ui.pushButton_order->setFixedSize(75, 23);*/
	left_line6->addWidget(ui.pushButton_preOrder);/*ui.pushButton_preOrder->setFixedSize(75, 23);*/
	left_line6->addWidget(ui.pushButton_risk);/*ui.pushButton_risk->setFixedSize(75, 23);*/
	//left_line6->addStretch();
	
	//装配布局
	hLayout_left->addSpacing(5);
	hLayout_left->addLayout(left_line1);
	hLayout_left->addLayout(left_line2);
	hLayout_left->addLayout(left_line3);
	hLayout_left->addLayout(left_line4);
	hLayout_left->addLayout(left_line5);
	hLayout_left->addLayout(left_line6);
	hLayout_left->addStretch();//让上部的区域固定
	//报价部分
	auto * hLayout_right = new QVBoxLayout;
	auto * right_line1 = new QHBoxLayout;
	auto * right_line2 = new QHBoxLayout;
	auto * right_line3 = new QHBoxLayout;
	auto * right_line4 = new QHBoxLayout;
	auto * right_line5 = new QHBoxLayout;

	auto * right_lineSpace = new QHBoxLayout;

	auto * right_line6 = new QHBoxLayout;
	auto * right_line7 = new QHBoxLayout;
	auto * right_line8 = new QHBoxLayout;
	auto * right_line9 = new QHBoxLayout;
	auto * right_line10 = new QHBoxLayout;

	//设置line值
	right_line1->addWidget(ui.label_sell5);right_line1->addWidget(ui.label_sell_price5);right_line1->addSpacing(10); ;right_line1->addWidget(ui.label_sell_vol5);right_line1->addStretch();
	right_line2->addWidget(ui.label_sell4);right_line2->addWidget(ui.label_sell_price4);right_line2->addSpacing(10); right_line2->addWidget(ui.label_sell_vol4);right_line2->addStretch();
	right_line3->addWidget(ui.label_sell3);right_line3->addWidget(ui.label_sell_price3);right_line3->addSpacing(10); right_line3->addWidget(ui.label_sell_vol3);right_line3->addStretch();
	right_line4->addWidget(ui.label_sell2);right_line4->addWidget(ui.label_sell_price2);right_line4->addSpacing(10); ;right_line4->addWidget(ui.label_sell_vol2);right_line4->addStretch();
	right_line5->addWidget(ui.label_sell1);right_line5->addWidget(ui.label_sell_price1);right_line5->addSpacing(10); ;right_line5->addWidget(ui.label_sell_vol1);right_line5->addStretch();

	right_lineSpace->addWidget(ui.label_quote_space, 2,Qt::AlignLeft);right_lineSpace->addWidget(ui.label_quote_space_2, 4, Qt::AlignLeft);right_line5->addStretch();

	right_line6->addWidget(ui.label_buy1);right_line6->addWidget(ui.label_buy_price1);right_line6->addSpacing(10); ;right_line6->addWidget(ui.label_buy_vol1);right_line6->addStretch();
	right_line7->addWidget(ui.label_buy2);right_line7->addWidget(ui.label_buy_price2);right_line7->addSpacing(10); ;right_line7->addWidget(ui.label_buy_vol2);right_line7->addStretch();
	right_line8->addWidget(ui.label_buy3);right_line8->addWidget(ui.label_buy_price3);right_line8->addSpacing(10); ;right_line8->addWidget(ui.label_buy_vol3);right_line8->addStretch();
	right_line9->addWidget(ui.label_buy4);right_line9->addWidget(ui.label_buy_price4);right_line9->addSpacing(10); ;right_line9->addWidget(ui.label_buy_vol4);right_line9->addStretch();
	right_line10->addWidget(ui.label_buy5);right_line10->addWidget(ui.label_buy_price5);right_line10->addSpacing(10); ;right_line10->addWidget(ui.label_buy_vol5);right_line10->addStretch();


	hLayout_right->addLayout(right_line1);
	hLayout_right->addLayout(right_line2);
	hLayout_right->addLayout(right_line3);
	hLayout_right->addLayout(right_line4);
	hLayout_right->addLayout(right_line5);

	
	hLayout_right->addLayout(right_lineSpace);

/////////////////////////////买卖力度///////////////////////////////////////////	
	right_lineSpace->setMargin(0);
	right_lineSpace->setSpacing(0);//买卖无间隙
	//增加间隔样式
	ui.label_quote_space->setText("");
	ui.label_quote_space->setStyleSheet("QLabel{border: none; background-color: rgb(255,43,26); margin:0px;Spacing:0px;}");//height:6px;
	ui.label_quote_space->setFixedHeight(4);
	ui.label_quote_space->setFixedWidth(65);

	//增加间隔样式2
	ui.label_quote_space_2->setText("");
	ui.label_quote_space_2->setStyleSheet("QLabel{border: none; background-color: #6cad3c; margin:0px;Spacing:0px;}");//height:6px;
	ui.label_quote_space_2->setFixedHeight(4);
	ui.label_quote_space_2->setFixedWidth(85);
//////////////////////////////////////////////////////////////////////////////

	hLayout_right->addLayout(right_line6);
	hLayout_right->addLayout(right_line7);
	hLayout_right->addLayout(right_line8);
	hLayout_right->addLayout(right_line9);
	hLayout_right->addLayout(right_line10);
	hLayout_right->addStretch();//让上面的报价区域固定


	leftMainLayout->addSpacing(20);
	leftMainLayout->addLayout(hLayout_left);
	leftMainLayout->addSpacing(40);
	leftMainLayout->addLayout(hLayout_right);
	leftMainLayout->addStretch();

	leftMainWin->setFixedWidth(450);
	leftMainWin->setMinimumHeight(200);
	leftMainWin->setLayout(leftMainLayout);

	//改变TAB的按钮样式，TAB的背景颜色
	//QString tabBarStyle = "QTabBar::tab {min-width:80px;min-height:25px;border:none;padding:5px;font:14px;spacing:10;font-weight:bold;margin= 5px}"
	//	"QTabBar::tab:!selected {margin-top: 1px;color: #e8e8e8 ;background:: #2a3a57;}"//color:red
	//	"QTabBar::tab:selected {color: white;background: #227dc3}"
	//	"QWidget {background-color: #17202f;}";


	TabLeft->addTab(leftMainWin, "下单板");
	TabLeft->setBaseSize(400, 200);

	m_pSplitterOrderAndOrderReturn->addWidget(TabLeft);

	//添加本控件的消息
	//connect(ui.securityComboBox, SIGNAL(clicked()), this, SLOT(changeQuote()));
}

void mainWindow::InitOrderReturnUI()
{
	auto *TabRight   = new QTabWidget;
	auto *RightTab_1 = new QTableView(this);
	auto *RightTab_2 = new QWidget;

	RightTab_1->setMinimumWidth(300);

	TabRight->addTab(RightTab_1, "报单流水");
	TabRight->addTab(RightTab_2, "预埋单");

	m_pSplitterOrderAndOrderReturn->addWidget(TabRight);

	//调整初始化高度
	m_pSplitterOrderAndOrderReturn->setStretchFactor(0, 1);
	m_pSplitterOrderAndOrderReturn->setStretchFactor(1, 7);

	//Demo
	auto *tableModel = new GcnStandardItemModel();

	////设置行
	tableModel->setColumnCount(10);
	int columnIndex = 0;
	tableModel->setHeaderData(columnIndex, Qt::Horizontal, tr("合约代码"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("交易类型"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("委托价格"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("委托数量"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("未成交数量"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("报单类型"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("委托时间"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("操作信息"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("本地报单号"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("报单号"));

	//tableModel->sort(0,Qt::DescendingOrder);
	tableModel->setSortRole(1);
	RightTab_1->setModel(tableModel);
	//RightTab_1->setStyleSheet("QWidget {"	"background-color: #17202f;" "}");
	//setWidgetStyleFromQssFile(TabRight, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\mianwindow.css"));
	setWidgetStyleFromQssFile(TabRight, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\table.css"));

	RightTab_1->setBaseSize(width()+50, 350);
	RightTab_1->horizontalHeader()->setFixedHeight(32);
	RightTab_1->verticalHeader()->hide();
	RightTab_1->verticalHeader()->setDefaultSectionSize(30);
	RightTab_1->setShowGrid(false);
	//RightTab_1->setSelectionBehavior(SelectRows);
	RightTab_1->setSortingEnabled(false);
	RightTab_1->setAlternatingRowColors(true);//隔行换色
	RightTab_1->setSelectionMode(QAbstractItemView::SingleSelection);
	RightTab_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

//持仓/库存/资金
void mainWindow::InitLocalDBUI()
{
	


	//Demo
	auto *tabWidget_pos = new QTabWidget;
	auto *Tabview_1 = new QTableView(this);
	auto *Tabview_2 = new QTableView(this);
	auto *Tabview_3 = new QTableView(this);

	

	tabWidget_pos->addTab(Tabview_1, "持仓");
	tabWidget_pos->addTab(Tabview_2, "库存");
	tabWidget_pos->addTab(Tabview_3, "资金");

	auto *tableModel = new GcnStandardItemModel();

	////设置行
	tableModel->setColumnCount(9);
	int columnIndex = 0;
	tableModel->setHeaderData(columnIndex, Qt::Horizontal, tr("合约代码"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("持仓方向"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("总持仓"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("昨仓"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("今仓"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("可用仓"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("持仓均价"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("持仓盈亏"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("占用保证金"));


	tableModel->setSortRole(1);
	Tabview_1->setModel(tableModel);
	Tabview_1->setMinimumWidth(200);
	setWidgetStyleFromQssFile(tabWidget_pos, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\table.css"));

	Tabview_1->setBaseSize(tabWidget_pos->width(), 350);
	Tabview_1->horizontalHeader()->setFixedHeight(32);
	Tabview_1->verticalHeader()->hide();
	Tabview_1->verticalHeader()->setDefaultSectionSize(30);
	Tabview_1->setShowGrid(false);
	Tabview_1->setSortingEnabled(false);
	Tabview_1->setAlternatingRowColors(true);//隔行换色
	Tabview_1->setSelectionMode(QAbstractItemView::SingleSelection);
	Tabview_1->setEditTriggers(QAbstractItemView::NoEditTriggers);





	m_pSplitterLocalDBAndTransReturn->addWidget(tabWidget_pos);
}


void mainWindow::InitTransReturnUI()
{
	

	//demo
	auto *TabTrans      = new QTabWidget;
	auto *TabView_trans = new QTableView();
	auto *tableModel    = new GcnStandardItemModel();

	////设置行
	tableModel->setColumnCount(7);
	int columnIndex = 0;
	tableModel->setHeaderData(columnIndex, Qt::Horizontal, tr("成交流水号"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("保单号"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("合约代码"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("交易类型"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("成交价格"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("成交数量"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("成交时间"));


	tableModel->setSortRole(1);
	TabView_trans->setModel(tableModel);
	TabTrans->setMinimumWidth(200);
	setWidgetStyleFromQssFile(TabTrans, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\table.css"));

	TabView_trans->setBaseSize(TabTrans->width(), TabTrans->height());
	TabView_trans->horizontalHeader()->setFixedHeight(32);
	TabView_trans->verticalHeader()->hide();
	TabView_trans->verticalHeader()->setDefaultSectionSize(30);
	TabView_trans->setShowGrid(false);
	TabView_trans->setSortingEnabled(false);
	TabView_trans->setAlternatingRowColors(true);//隔行换色
	TabView_trans->setSelectionMode(QAbstractItemView::SingleSelection);
	TabView_trans->setEditTriggers(QAbstractItemView::NoEditTriggers);

	TabTrans->addTab(TabView_trans, "报单流水");




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
	//QString strStyle = "QStatusBar{font:bold;font-size:14px;}";//height:30px
	QStatusBar *statusbar = new QStatusBar(this);
	//statusbar->setStyleSheet(strStyle);
	statusbar->setFixedHeight(50);

	QHBoxLayout* statuslayout = new QHBoxLayout(this);
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
	setWidgetStyleFromQssFile(win, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\mainwindow.css"));
	statusbar->addWidget(win);

	//一条黑色直线，作为分割
	ui.line_status->setFixedHeight(5);
	ui.line_status->setStyleSheet("QFrame{border: none; background-color: #030303;}");
	
	m_layout->addWidget(ui.line_status);
	m_layout->addWidget(statusbar);
	
}

//整个区域由 title  + center 构成
mainWindow::mainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);

	//HWND hwnd = (HWND)this->winId();
	//DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
	//::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

	this->setProperty("CanMove", true);

	setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\mainwindow.css"));

	
	StyleSheetWidget* center = new StyleSheetWidget(this);
	this->setCentralWidget(center);
	//center->setStyleSheet("QWidget {"	"background-color: red;" "}");


	m_layout = new QVBoxLayout(center);
	m_layout->setMargin(0);
	m_layout->setSpacing(0);
	center->setLayout(m_layout);
	


	//分割器
	m_pSplitterOrderAndOrderReturn = new QSplitter(Qt::Orientation::Horizontal);//水平  
	m_pSplitterLocalDBAndTransReturn = new QSplitter(Qt::Orientation::Horizontal);//水平  
	m_pSplitterAllTithoutLabel = new QSplitter(Qt::Orientation::Vertical);//垂直  

	//1.添加标头
	m_title = new WindowTitle(this);
	connect(m_title, SIGNAL(buttonClick(WindowTitle::ButtonStatus)), this, SLOT(titleButtonClick(WindowTitle::ButtonStatus)));
	m_layout->addWidget(m_title);


	//2.添加资金区域
	InitAccountUI();
	//3.添加报价表
	InitTabViewUI();
	//4.添加下单板
	InitOrderUI();
	//添加报单回报
	InitOrderReturnUI();
	//添加磁场/资金/库存
	InitLocalDBUI();
	//添加成交流水
	InitTransReturnUI();

	InitSplitterUI();

	InitStatusLabelUI();



	//订阅广播消息
	g_TraderCpMgr.Reigister((HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONNEWBOURSEBULLETIN, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONNEWMEMBERBULLETIN, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRISKNOTIFY, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONSYSINIT, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_UPDATE_LIST, (HWND)winId());


	g_TraderCpMgr.SubscribeAll((HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONSYSINIT, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_REFRESHFUND, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERQUOTATION, (HWND)winId());//订阅行情

	//客户账号信息
	g_TraderCpMgr.Subscribe(E_CUSTOM_INFO_CHANGE, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_SURPLUS_CHANGE, (HWND)winId());//持仓盈亏


	//状态条信息
	g_TraderCpMgr.Subscribe(E_ONSYSSTATCHANGE, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_HQ_STATE, (HWND)winId());


	// 订阅广播消息
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERDELIVERYQUOTATION, (HWND)winId());

	//订阅行情
	g_TraderCpMgr.Subscribe(E_ONRECVSPOTQUOTATION, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVFORWARDQUOTATION, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERQUOTATION, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERDELIVERYQUOTATION, (HWND)winId());

	g_TraderCpMgr.Subscribe(E_ONRECVRTNSPOTINSTSTATEUPDATE, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVRTNFORWARDINSTSTATEUPDATE, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVRTNDEFERINSTSTATEUPDATE, (HWND)winId());


	//交易区
	// 订阅广播消息
	g_TraderCpMgr.Subscribe(E_ONRECVSPOTQUOTATION, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVFORWARDQUOTATION, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERQUOTATION, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONRECVDEFERDELIVERYQUOTATION, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONLOGINSUCC, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_ONCUSTRISKDEGREECHANGE, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_CUSTOM_INFO_CHANGE, (HWND)winId());

	g_TraderCpMgr.Subscribe(E_COMMIT_POSI, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_COMMIT_STORE, (HWND)winId());
	g_TraderCpMgr.Subscribe(E_UPDATE_LIST, (HWND)winId());

}

mainWindow::~mainWindow()
{
	// 取消订阅广播消息
	g_TraderCpMgr.Unsubscribe(E_ONRECVRTNSPOTORDER, (HWND)winId());

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



void mainWindow::changeQuote(QString string)
{
	
	auto it = g_TraderCpMgr.m_QMapQuotation.find(sInstID);
	if (it != g_TraderCpMgr.m_QMapQuotation.end())
	{
		QUOTATION& stQuotation = it->second;
		qt = &stQuotation;
	}
	//更换行情
	/*if (string == "Ag(T+D)")
	{
		ui.label_sell_price5->setText("3851.00");
		ui.label_sell_vol5->setText("723");
		ui.label_sell_price4->setText("3850.00");
		ui.label_sell_vol4->setText("12612");
		ui.label_sell_price3->setText("3849.00");
		ui.label_sell_vol3->setText("7095");
		ui.label_sell_price2->setText("3848.00");
		ui.label_sell_vol2->setText("4698");
		ui.label_sell_price1->setText("3847.00");
		ui.label_sell_vol1->setText("1651");

		ui.label_buy_price5->setText("3846.00");
		ui.label_buy_vol5->setText("4377");
		ui.label_buy_price4->setText("3845.00");
		ui.label_buy_vol4->setText("4491");
		ui.label_buy_price3->setText("3844.00");
		ui.label_buy_vol3->setText("4105");
		ui.label_buy_price2->setText("3843.00");
		ui.label_buy_vol2->setText("5527");
		ui.label_buy_price1->setText("3842.00");
		ui.label_buy_vol1->setText("8675");
	}
	else if (string == "Au(T+D)")
	{
		ui.label_sell_price5->setText("274.83");
		ui.label_sell_vol5->setText("1");
		ui.label_sell_price4->setText("274.80");
		ui.label_sell_vol4->setText("10");
		ui.label_sell_price3->setText("274.77");
		ui.label_sell_vol3->setText("25");
		ui.label_sell_price2->setText("274.76");
		ui.label_sell_vol2->setText("11");
		ui.label_sell_price1->setText("274.75");
		ui.label_sell_vol1->setText("7");

		ui.label_buy_price5->setText("274.73");
		ui.label_buy_vol5->setText("4");
		ui.label_buy_price4->setText("274.72");
		ui.label_buy_vol4->setText("6");
		ui.label_buy_price3->setText("274.71");
		ui.label_buy_vol3->setText("32");
		ui.label_buy_price2->setText("274.70");
		ui.label_buy_vol2->setText("116");
		ui.label_buy_price1->setText("274.69");
		ui.label_buy_vol1->setText("8");

	}*/

}




//接收消息
bool mainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	   //if (eventType == "windows_generic_MSG")
	   MSG* msg = reinterpret_cast<MSG*>(message);
/*		if (msg->message != WM_NCHITTEST)
		{
#if QT_VERSION < 0x050000  
			return QWidget::winEvent(message, result);
#else  
			return QWidget::nativeEvent("", message, result);
#endif  
		}
		else */
	   if (msg->message == MSG_RECV_QUOTATION)
		{

			return  true;
		}
		else if (msg->message == WM_FORCE_LOGOUT)
		{
			TForceLogout *stLogout = (TForceLogout *)msg->wParam;
			QMessageBox::information(nullptr,"系统提示",CHJGlobalFun::str2qstr( stLogout->hint_msg));

			//退出系统
			this->close();
			return  true;
		}
		else if (msg->message == WM_SYS_STAT_CHANGE)
		{
			SysStat *sys = (SysStat *)msg->wParam;
			QMessageBox::information(nullptr,"系统提示",CHJGlobalFun::str2qstr(sys->m_sys_stat));
			return  true;
		}


		return  false;
}