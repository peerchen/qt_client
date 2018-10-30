#include "Startup.h"

#include "frmlogindialog.h"

#include <qmessagebox.h>
#include <qapplication.h>

#include "Macrodefs.h"

QStartup::QStartup()
    :   m_pDlg(0)
    ,   m_pApp(0)
{

}

QStartup::~QStartup()
{

}

QStartup *QStartup::GetInstance()
{
    static QStartup _inst;
    return &_inst;
}

bool QStartup::Initialize()
{
    if (!m_pDlg || !m_pApp)
        return false;	

	frmLoginDialog *pDlgLogin = (frmLoginDialog*)m_pDlg;

    // 装载View
    //pDlgLogin->SetLoginMessage("正在初始化...");

    //pDlgLogin->SetLoginMessage("用户账号初始化完成。");

    //pDlgLogin->SetLoginMessage("用户登录...");
   // m_pApp->exec();

    //if (!pDlgLogin->GetState())
        //return false;

    return true;
}

void QStartup::Release()
{
 //   QAccountManager::GetInstance()->Release();
	//CFirstSession::GetInstance()->Release();
 //   CStrategySystem::GetInstance()->Release();
	//CComponentPlugins::GetInstance()->Release();
 //   QWorkspaceTemplateManager::GetInstance()->Release();
 //   QViewTemplateManager::GetInstance()->Release();
	//CRunningLog::GetInstance()->Release();
}

void QStartup::SetApplication(QApplication *pApp)
{
    m_pApp = pApp;
}

void QStartup::SetLoginDlg(QDialog *pDlg)
{
    m_pDlg = pDlg;
}

TradeType QStartup::GetLoginType()
{
	frmLoginDialog *pDlgLogin = (frmLoginDialog*)m_pDlg;
    return pDlgLogin->GetType();
}

