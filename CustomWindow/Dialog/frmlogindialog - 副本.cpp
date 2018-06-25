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
//Ϊ���ܹ�ʹ����ʽ������ҪΪ�Զ���Widget�ṩpaintEvent�¼�
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
	//startTimer(1000);       // ����ֵΪ1, ��timerId 
	
	//std::thread t1(&frmLoginDialog::timerUpdate(), this);//����һ����֧�̣߳��ص���myThread������
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
	//			             ui->lbl1->setText(tr("ÿ�����һ�������: %1").arg(qrand() % 10));
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

	//���ô������������
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
	ui->label_login_png->setPixmap(QPixmap::fromImage(QImage(":/res/login")));
	ui->label_login_png->setFixedWidth(389);
	ui->label_login_png->setFixedHeight(598);
	QStringList list;
	list << tr("���ױ���") << tr("�����ʺ�");//<< tr("����֤") << tr("�۰�ͨ��֤");
	ui->comboBox_login_type->addItems(list);

	ui->textEdit_user_pswd->setEchoMode(QLineEdit::Password);
	ui->textEdit_userId->setText(App::user);
	//ui->textEdit_user_pswd->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	//���ñ���
	//QString strDialogStyle = "QDialog{background:rgba(255,255,255,255)}";
	//setStyleSheet(strDialogStyle);

	//���ð�ť��ʽ
	//QString strButtonStyle = "QPushButton{background:#2a3a57;color:#ffffff;font-size:18px;height:35px;margin:15px}\
	//	QPushButton:hover{ background:#227dc3}";
	//ui->pushButton_login->setStyleSheet(strButtonStyle);
	//ui->pushButton_exit->setStyleSheet(strButtonStyle);

	//�����²���
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
	//����ͼ������
	//IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015));
	//IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d));
	//�����رհ�ť
	//connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
	//connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}


void frmLoginDialog::checkInfo()
{
	//��ʼУ���û���,���룬������
	
	//doUpdateUiTask([=]()
	//{
	//	ui->label_note->setText("У���˻���...");
	//	ui->label_note->show();
	//});
	mNote = "У���˻���...";
	ShowNote("У���˻���...");
	Sleep(100);
	if (CheckInput())
	{
		//doUpdateUiTask([=]()
		//{
		//	ui->label_note->setText("��¼��...");
		//});
		//mNote = "��¼��...";
		ShowNote("��¼��...");
		//�ɹ�
		success = true;

		// ��ʼ��
		g_TraderCpMgr.Init();

		QString userType;
		if (ui->comboBox_login_type->currentText() == "�ͻ���" || ui->comboBox_login_type->currentText() == "���ױ���")
		{
			userType = "1";
		}
		else
		{
			userType = "2";
		}

		bool bSigned = ui->checkBox->isChecked();
		//��֤
		int ret = g_TraderCpMgr.Authenticate(ui->textEdit_userId->text().toLatin1(),
											ui->textEdit_user_pswd->text().toLatin1(),
											App::ip.toLatin1(),
											App::port.toInt(),
											userType,
											bSigned);

		// �������֤�ɹ����߷���������Ӧ��������ѭ��
		//if (0 == ret || -2 == ret)
		//{
		//	accept();
		//	return;
		//}

		if (YLINK_ERROR_NETWORK == ret)
		{
			/*LOG("�û���¼��֤ʧ��");

			//AfxMessageBox("�������ݴ���ʧ�ܣ�������");*/
			//ui->label_note->setText("�û���¼��֤ʧ��");
			mNote = "�û���¼��֤ʧ��";
		}
		else if (-1 == ret || -2 == ret)
		{
			/*	LOG("�û���¼��֤ʧ��");
				AfxMessageBox("��֤ʧ��");*/
			ui->label_note->setText("�û���¼��֤ʧ��");
			mNote = "�û���¼��֤ʧ��";
		}
		else
		{
			int iLoginResult = g_TraderCpMgr.UserLogin(userType, bSigned);
			if (iLoginResult == -1)
			{
				/*LOG("�û���¼ʧ��");
				AfxMessageBox("��½ʧ��");*/
				ui->label_note->setText("�û���¼ʧ��");
			}
			else if (iLoginResult == -2)
			{
				/*LOG("�û�����Ŀ¼ʧ�ܣ��޷���½");*/
				ui->label_note->setText("�û�����Ŀ¼ʧ�ܣ��޷���½");
			}
			// ��Ҫ�޸�����
			else if (iLoginResult == 1)
			{
				//Ӧ�ø�Ϊ��������ʾ���ã�������Ķ���
				ui->label_note->setText("��Ҫ�޸�������ܵ�½���Ƿ��޸ģ�");
				//wc.Restore();

				//if (MessageBox("����Ҫ�޸�������ܵ�½��ȷ���޸ģ�", "��ʾ", MB_YESNO | MB_ICONINFORMATION) == IDYES) //����ȷ�ϴ��� 
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
				//	ui->label_note->setText("�û���¼�ɹ�");
				//});
				timer->stop();

				mNote = "�û���¼�ɹ�";
				//LOG("�û���¼�ɹ�");
				// �����¼�ɹ�
				/*EndDialog(IDOK);*/
				ShowNote("�û���¼�ɹ�...");

				accept();
			}


			////��¼ʧ�ܣ�ˢ����֤��
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
		ui->label_note->setText("�û������ܺ��пո�");
		ui->textEdit_userId->setFocus();
		return false;
	}

	
	if (ui->textEdit_user_pswd->text().isEmpty())
	{
		ui->label_note->setText("�û����벻�ܺ��пո�");
		ui->textEdit_user_pswd->setFocus();
		return false;
	}


	if (ui->textEdit_ensure_code->text().isEmpty())
	{
		ui->label_note->setText("��֤�벻��Ϊ�գ�");
		ui->textEdit_ensure_code->setFocus();
		return false;
	}

	int len = ui->textEdit_user_pswd->text().length();

	// ����ͨ�汾���루��¼���ʽ����룩ֻ��Ϊ6λ����
	if (len != 6)
	{
		ui->label_note->setText("��¼����ֻ��Ϊ6λ������");
		return false;
	}


	// �ж���֤�������Ƿ���ȷ
	QString strTmp = ui->textEdit_ensure_code->text().toLower();
	QString strTmp2 = ui->label_ensure_png->m_strCode.toLower();
	
	if (strTmp != strTmp2)
	{
		ui->label_note->setText("��֤��������������룡");
		ui->label_ensure_png->ShowCode();
		ui->textEdit_ensure_code->setText("");
		ui->textEdit_ensure_code->setFocus();
		return false;
	}

	return true;
}



//������Ϣ
bool frmLoginDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{

	MSG* msg = reinterpret_cast<MSG*>(message);

	if (msg->message == WM_MYTASK)//�����Զ�����Ϣ
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