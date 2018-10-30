#include "frmlogindialog.h"
#include "ui_frmlogindialog.h"
#include "myHelper.h"
#include <QPainter>
#include "macrodefs.h"
#include  <QStyleOption>
#include <QTextCodec>

#include "TraderCpMgr.h"
#include "app.h"
#include "Global.h"
#include "HJConstant.h"

#include <functional>
#include <QGraphicsDropShadowEffect>



#pragma execution_character_set("utf-8")



frmLoginDialog::frmLoginDialog(QWidget *parent) :
	StyleSheetDialog(parent),
    ui(new Ui::frmLoginDialog)
{
    ui->setupUi(this);
	initStyle();

	setLayout(ui->horizontalLayout_main);

	connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(checkInfo()));
	connect(ui->pushButton_exit, SIGNAL(clicked()), this, SLOT(exitSys()));
	

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	timer->start(400);

	//初始化提示
	ui->label_note->setText("");
	QFont font("Microsoft YaHei UI", 10, QFont::Bold);
	ui->label_note->setFont(font);
	//pool = new ThreadPool();

	m_bLoginState = false;

	//增加模糊效果
	//QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
	//windowShadow->setBlurRadius(9.0);
	//windowShadow->setColor(QColor("#20293a"));//palette().color(QPalette::Highlight));
	//windowShadow->setOffset(0.0);
	//this->setGraphicsEffect(windowShadow);

	connect(this, SIGNAL(notify(QString)), this, SLOT(OnNotify(QStirng)));
}


frmLoginDialog::~frmLoginDialog()
{
	//pool->Stop();

	timer->stop();

    delete ui;
}


void frmLoginDialog::initStyle()
{


#ifdef  _WIN32
        setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\logindialog.css"));
#else
        //kenny  20180305  ?????????
        QString strPath = QCoreApplication::applicationDirPath();
        QDir  dir;
        dir.setCurrent(strPath);

        setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack/logindialog.css"));
#endif

        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
        this->setProperty("Form", true);
        this->setProperty("CanMove", true);

        ui->horizontalLayout_main->setGeometry(QRect(0,0,width(),height()));


        ui->label_login_png->setPixmap(QPixmap::fromImage(QImage(":/res/login")));
        ui->label_login_png->setFixedWidth(389);
        ui->label_login_png->setFixedHeight(598);
        QStringList list;

	list << tr("交易编码") << tr("银行帐号");//<< tr("回乡证") << tr("港澳通行证");
	ui->comboBox_login_type->addItems(list);

	ui->textEdit_user_pswd->setEchoMode(QLineEdit::Password);
	ui->textEdit_userId->setText(App::user);
	
}

void frmLoginDialog::OnNotify(QString  str)
{
	ui->label_note->setText(str);
};

void frmLoginDialog::checkLogic()
{
	QString strPath = g_Global.GetSystemIniPath();
	QString strVal;
	App::GetPriProfileString(strPath, "info", "demo", strVal);
	if (strVal.contains("1"))
	{
		m_bLoginState = true;
		accept();
		return;
	}


	mNote = "服务器认证中...";
	emit notify(mNote);

	QString userType;
	if (ui->comboBox_login_type->currentText() == "客户号" || ui->comboBox_login_type->currentText() == "交易编码")
	{
		userType = "1";
	}
	else
	{
		userType = "2";
	}



	bool bSigned = ui->checkBox->isChecked();

	mNote = "开始验证...";
	emit notify(mNote);
	//验证
	int ret = g_TraderCpMgr.Authenticate(ui->textEdit_userId->text().toLatin1(),
								ui->textEdit_user_pswd->text().toLatin1(),
								App::ip.toLatin1(),
								App::port.toInt(),
								userType,
								bSigned);

	////登录厦门，不认证
	//ret = 0;
	if (YLINK_ERROR_NETWORK == ret)
	{
		mNote = "用户登录认证失败";
	}
	else if (-1 == ret || -2 == ret)
	{
		mNote = "用户登录认证失败";
	}
	else
	{
		//若是新账户，需要更新到多账户的配置
		bool bFind=false;
		for (size_t i = 0; i < App::accMgr.size(); i++)
		{
			if (ui->textEdit_userId->text() == App::accMgr.value(i).user)
				bFind = true;
		}
		if (!bFind)
		{
			int size = App::accMgr.size();
			App::WriteServerProperty("account", "ACCOUNT.count", QString::number(size+1));
			AccountMgr acc;
			acc.alias = ui->textEdit_userId->text();
			acc.user  = ui->textEdit_userId->text();
			acc.psw   = ui->textEdit_user_pswd->text();

			App::WriteServerProperty("account", QString("ACCOUNT.account%1.alias").arg(QString::number(size)), acc.alias);
			App::WriteServerProperty("account", QString("ACCOUNT.account%1.user").arg(QString::number(size)), acc.user);
			App::WriteServerProperty("account", QString("ACCOUNT.account%1.pswd").arg(QString::number(size)), acc.psw);

			App::accMgr.push_back(acc);
		}

		mNote = "服务器登录...";
		emit notify(mNote);
		int iLoginResult = g_TraderCpMgr.UserLogin(userType, bSigned);
		if (iLoginResult == -1)
		{
			ui->label_note->setText("用户登录失败");
		}
		else if (iLoginResult == -2)
		{
			ui->label_note->setText("用户创建目录失败，无法登陆");
		}
		// 需要修改密码
		else if (iLoginResult == 1)
		{
			//应该改为弹出框提示更好，【后面改动】
			ui->label_note->setText("需要修改密码才能登陆，是否修改？");
			accept();
			m_bLoginState = true;
		}
		else
		{
			//timer->stop();

			//mNote = "用户登录成功";
			//emit notify(mNote);
			m_bLoginState = true;
			accept();
			return;
		}


		////登录失败，刷新验证码
		ui->label_ensure_png->ShowCode();
		ui->textEdit_ensure_code->setText("");
		ui->textEdit_ensure_code->setFocus();

		return;

	}



}

//在线程中执行逻辑，定时器刷新界面提示
void frmLoginDialog::checkInfo()
{	

	//开始校验用户名,密码，加密码
	//ui->label_note->clear();
	//ui->label_note->adjustSize();
	mNote = "";
	if (CheckInput())
	{
		//成功
		success = true;

		// 初始化
		g_TraderCpMgr.Init();

		//const std::function<void()> func1 = std::bind(&frmLoginDialog::checkLogic, this);
		doUpdateUiTask(std::bind(&frmLoginDialog::checkLogic, this));

		mNote = "登录中...";
	}
	else
	{
		success = false;
		//StyleSheetDialog::reject();
	}


}

void frmLoginDialog::exitSys()
{
	success = false;
	close();
}

void frmLoginDialog::refreshCode()
{
	int test = 0;
}



bool frmLoginDialog::CheckInput()
{
	
	if (ui->textEdit_userId->text().isEmpty())
	{
		ui->label_note->setText("用户名不能含有空格！");
		ui->label_note->adjustSize();
		this->repaint();
		ui->textEdit_userId->setFocus();
		return false;
	}

	
	if (ui->textEdit_user_pswd->text().isEmpty())
	{
		ui->label_note->setText("用户密码不能含有空格！");
		ui->label_note->adjustSize();
		this->repaint();
		ui->textEdit_user_pswd->setFocus();
		return false;
	}


	if (ui->textEdit_ensure_code->text().isEmpty())
	{
		ui->label_note->setText("验证码不能为空！");
		ui->label_note->adjustSize();
		this->repaint();
		ui->textEdit_ensure_code->setFocus();
		return false;
	}

	int len = ui->textEdit_user_pswd->text().length();

	// 金联通版本密码（登录和资金密码）只能为6位数字
	if (len != 6)
	{
		ui->label_note->setText("登录密码只能为6位的数字");
		ui->label_note->adjustSize();
		this->repaint();
		return false;
	}


	// 判断验证码输入是否正确
	QString strTmp = ui->textEdit_ensure_code->text().toLower();
	QString strTmp2 = ui->label_ensure_png->m_strCode.toLower();
	
	if (strTmp != strTmp2)
	{
		ui->label_note->setText("验证码错误，请重新输入！");
		ui->label_note->adjustSize();
		this->repaint();

		ui->label_ensure_png->ShowCode();
		ui->textEdit_ensure_code->setText("");
		ui->textEdit_ensure_code->setFocus();
		return false;
	}

	return true;
}




void  frmLoginDialog::customEvent(QEvent *e)
{
	if (e->type() == WM_MYTASK)   //捕获消息
	{
		OnUITask(0, 0);
	}
}

template<class F, class... Args>
auto frmLoginDialog::doUpdateUiTask(F&& f, Args&&... args)
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


	QApplication::postEvent(this,new QEvent(WM_MYTASK));

	return res;
}



int frmLoginDialog::OnUITask(void * wparam, void* lparam)
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



void frmLoginDialog::timerUpdate()
{
	ui->label_note->setText(mNote);
	//ui->label_note->update();
	update();
}



void frmLoginDialog::SetLoginMessage(const QString &Message)
{
	//
	mNote = Message;
}


TradeType  frmLoginDialog::GetType()
{
	return  TradeType::Real;
}


bool  frmLoginDialog::GetState()
{
	return  true;
}