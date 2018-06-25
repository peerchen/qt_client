#include "frmlogindialog.h"
#include "ui_frmlogindialog.h"
#include "myHelper.h"
#include <QPainter>
#include "macrodefs.h"
#include  <QStyleOption>
#include <QTextCodec>

#include "TraderCpMgr.h"
#include "app.h"
#pragma execution_character_set("utf-8")

const int  WM_MYTASK = WM_APP + 100;
//为了能够使用样式表则需要为自定义Widget提供paintEvent事件
void StyleSheetDialog::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QStyleOption opt;
	opt.init(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}


void SetTask(frmLoginDialog *wd,QString strtext)
{
	wd->MyTask(strtext);
}

void frmLoginDialog::MyTask(const QString &strText)
{
	ui->label_note->setText(mNote);
}


void frmLoginDialog::ShowNote(const QString &strText)
{
	std::thread td(SetTask, this, std::ref(strText));
	td.detach();
}

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
	timer->start(100);
	//startTimer(1000);       // 返回值为1, 即timerId 
	
	//std::thread t1(&frmLoginDialog::timerUpdate(), this);//创建一个分支线程，回调到myThread函数里
	//t1.join();
}

 //void MainWindow::timerEvent(QTimerEvent *t)
 //{
	//     switch (t->timerId())
	//	     {
	//	     case 1:
	//		         {
	//			            QDateTime time = QDateTime::currentDateTime();
	//			             QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
	//			             ui->label_note->setText(str);
	//			             ui->lbl1->setText(tr("每秒产生一个随机数: %1").arg(qrand() % 10));
	//			             ui->lbl1->adjustSize();
	//			         }
	//		         break;
	//		
	// }

frmLoginDialog::~frmLoginDialog()
{
    delete ui;
}


void frmLoginDialog::initStyle()
{
	setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\dialog.css"));
	this->setProperty("Form", true);
	this->setProperty("CanMove", true);
	ui->horizontalLayout_main->setGeometry(QRect(0,0,width(),height()));

	//设置窗体标题栏隐藏
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
	ui->label_login_png->setPixmap(QPixmap::fromImage(QImage(":/res/login")));
	ui->label_login_png->setFixedWidth(389);
	ui->label_login_png->setFixedHeight(598);
	QStringList list;
	list << tr("交易编码") << tr("银行帐号");//<< tr("回乡证") << tr("港澳通行证");
	ui->comboBox_login_type->addItems(list);

	ui->textEdit_user_pswd->setEchoMode(QLineEdit::Password);
	ui->textEdit_userId->setText(App::user);
	//ui->textEdit_user_pswd->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	//设置背景
	//QString strDialogStyle = "QDialog{background:rgba(255,255,255,255)}";
	//setStyleSheet(strDialogStyle);

	//设置按钮样式
	//QString strButtonStyle = "QPushButton{background:#2a3a57;color:#ffffff;font-size:18px;height:35px;margin:15px}\
	//	QPushButton:hover{ background:#227dc3}";
	//ui->pushButton_login->setStyleSheet(strButtonStyle);
	//ui->pushButton_exit->setStyleSheet(strButtonStyle);

	//调整下布局
	//QString strTitleStyle = "QLabel{font-size:30px;margin:0px;margin-top:40px;padding:0px}";
	//ui->label_login_title->setStyleSheet(strTitleStyle);
	
	//ui->verticalLayout_login_info

	//ui->label_login_title->setFixedHeight(70);

	//QHBoxLayout *pUser = new QHBoxLayout(this);
	//pUser->addWidget(ui->textEdit_userId);

	//QVBoxLayout *Psw = new QVBoxLayout(this);
	//Psw->addWidget(ui->textEdit_user_pswd);
	//Psw->addWidget(ui->label_key_png);

	//QVBoxLayout *Ensure = new QVBoxLayout(this);
	//Ensure->addWidget(ui->textEdit_ensure_code);
	//Ensure->addWidget(ui->label_ensure_png);
	//Ensure->addWidget(ui->label_refresh_code);

	//QVBoxLayout *book = new QVBoxLayout(this);
	//book->addWidget(ui->checkBox);
	//book->addWidget(ui->label_com_set);
	


	//QString strComboStyle = "QComboBox{font-size:30px;margin:0px;margin-top:20px;padding:0px}";
	//ui->comboBox_login_type->setStyleSheet(strComboStyle);
	//ui->comboBox_login_type->setFixedWidth(width()-200);
	//设置图形字体
	//IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015));
	//IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d));
	//关联关闭按钮
	//connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
	//connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}


void frmLoginDialog::checkInfo()
{
	//开始校验用户名,密码，加密码
	
	//doUpdateUiTask([=]()
	//{
	//	ui->label_note->setText("校验账户中...");
	//	ui->label_note->show();
	//});
	mNote = "校验账户中...";
	ShowNote("校验账户中...");
	Sleep(100);
	if (CheckInput())
	{
		//doUpdateUiTask([=]()
		//{
		//	ui->label_note->setText("登录中...");
		//});
		//mNote = "登录中...";
		ShowNote("登录中...");
		//成功
		success = true;

		// 初始化
		g_TraderCpMgr.Init();

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
		//验证
		int ret = g_TraderCpMgr.Authenticate(ui->textEdit_userId->text().toLatin1(),
											ui->textEdit_user_pswd->text().toLatin1(),
											App::ip.toLatin1(),
											App::port.toInt(),
											userType,
											bSigned);

		// 如果是认证成功或者服务器有响应，则跳出循环
		//if (0 == ret || -2 == ret)
		//{
		//	accept();
		//	return;
		//}

		if (YLINK_ERROR_NETWORK == ret)
		{
			/*LOG("用户登录认证失败");

			//AfxMessageBox("网络数据传输失败，请重试");*/
			//ui->label_note->setText("用户登录认证失败");
			mNote = "用户登录认证失败";
		}
		else if (-1 == ret || -2 == ret)
		{
			/*	LOG("用户登录认证失败");
				AfxMessageBox("认证失败");*/
			ui->label_note->setText("用户登录认证失败");
			mNote = "用户登录认证失败";
		}
		else
		{
			int iLoginResult = g_TraderCpMgr.UserLogin(userType, bSigned);
			if (iLoginResult == -1)
			{
				/*LOG("用户登录失败");
				AfxMessageBox("登陆失败");*/
				ui->label_note->setText("用户登录失败");
			}
			else if (iLoginResult == -2)
			{
				/*LOG("用户创建目录失败，无法登陆");*/
				ui->label_note->setText("用户创建目录失败，无法登陆");
			}
			// 需要修改密码
			else if (iLoginResult == 1)
			{
				//应该改为弹出框提示更好，【后面改动】
				ui->label_note->setText("需要修改密码才能登陆，是否修改？");
				//wc.Restore();

				//if (MessageBox("你需要修改密码才能登陆，确定修改？", "提示", MB_YESNO | MB_ICONINFORMATION) == IDYES) //弹出确认窗口 
				//{
				//	CHJMMXGDlg dlg;
				//	INT_PTR nResponse = dlg.DoModal();
				//	if (nResponse == IDOK)
				//	{
				//		EndDialog(IDOK);
				//	}
				//}

				accept();
			}
			else
			{
				//doUpdateUiTask([=]()
				//{
				//	ui->label_note->setText("用户登录成功");
				//});
				timer->stop();

				mNote = "用户登录成功";
				//LOG("用户登录成功");
				// 如果登录成功
				/*EndDialog(IDOK);*/
				ShowNote("用户登录成功...");

				accept();
			}


			////登录失败，刷新验证码
			ui->label_ensure_png->ShowCode();
			ui->textEdit_ensure_code->setText("");
			ui->textEdit_ensure_code->setFocus();

			return;


		}
	}
	else
	{
		success = false;
		//QDialog::reject();
	}



}
void frmLoginDialog::exitSys()
{
	//
	success = false;
	close();
}

void frmLoginDialog::refreshCode()
{
	//
	int test = 0;
}



bool frmLoginDialog::CheckInput()
{
	
	if (ui->textEdit_userId->text().isEmpty())
	{
		ui->label_note->setText("用户名不能含有空格！");
		ui->textEdit_userId->setFocus();
		return false;
	}

	
	if (ui->textEdit_user_pswd->text().isEmpty())
	{
		ui->label_note->setText("用户密码不能含有空格！");
		ui->textEdit_user_pswd->setFocus();
		return false;
	}


	if (ui->textEdit_ensure_code->text().isEmpty())
	{
		ui->label_note->setText("验证码不能为空！");
		ui->textEdit_ensure_code->setFocus();
		return false;
	}

	int len = ui->textEdit_user_pswd->text().length();

	// 金联通版本密码（登录和资金密码）只能为6位数字
	if (len != 6)
	{
		ui->label_note->setText("登录密码只能为6位的数字");
		return false;
	}


	// 判断验证码输入是否正确
	QString strTmp = ui->textEdit_ensure_code->text().toLower();
	QString strTmp2 = ui->label_ensure_png->m_strCode.toLower();
	
	if (strTmp != strTmp2)
	{
		ui->label_note->setText("验证码错误，请重新输入！");
		ui->label_ensure_png->ShowCode();
		ui->textEdit_ensure_code->setText("");
		ui->textEdit_ensure_code->setFocus();
		return false;
	}

	return true;
}



//接收消息
bool frmLoginDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{

	MSG* msg = reinterpret_cast<MSG*>(message);

	if (msg->message == WM_MYTASK)//接收自定义消息
	{
		OnUITask(0,0);
		return  true;
	}



	return  false;
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
	SendMessage((HWND)winId(),WM_MYTASK, 0,0);

	return res;
}



int frmLoginDialog::OnUITask(WPARAM wparam, LPARAM lparam)
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
	ui->label_note->adjustSize();
	this->show();
	//OnUITask(0, 0);
}