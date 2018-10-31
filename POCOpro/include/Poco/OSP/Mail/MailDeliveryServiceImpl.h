//
// MailDeliveryServiceImpl.h
//
// $Id: //poco/1.7/OSP/Mail/include/Poco/OSP/Mail/MailDeliveryServiceImpl.h#1 $
//
// Library: OSP/Mail
// Package: Mail
// Module:  MailDeliveryServiceImpl
//
// Definition of the MailDeliveryServiceImpl class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Mail_MailDeliveryServiceImpl_INCLUDED
#define OSP_Mail_MailDeliveryServiceImpl_INCLUDED


#include "Poco/OSP/Mail/MailDeliveryService.h"
#include "Poco/Net/SMTPClientSession.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace OSP {
namespace Mail {


class OSPMail_API MailDeliveryServiceImpl: public MailDeliveryService, public Poco::Runnable
	/// The default implementation of the MailDeliveryService.
	///
	/// This implementation uses a Poco::Net::SMTPClientSession to
	/// deliver the emails. Emails are managed through a queue and
	/// sending is done in batches.
{
public:
	typedef Poco::AutoPtr<MailDeliveryServiceImpl> Ptr;
	typedef Poco::SharedPtr<Poco::Net::SMTPClientSession> SMTPClientSessionPtr;

	struct Configuration
	{
		std::string host;
		Poco::UInt16 port;
		std::string sender;
		Poco::Timespan socketTimeout;
		Poco::Timespan sessionTimeout;
		Poco::Net::SMTPClientSession::LoginMethod loginMethod;
		std::string username;
		std::string password;
		int maxQueued;
		int maxFailedLogins;
	};

	MailDeliveryServiceImpl(const Configuration& config, Poco::Logger& logger);
		/// Creates the MailDeliveryServiceImpl using the given configuration and logger.
		
	~MailDeliveryServiceImpl();
		/// Destroys the MailDeliveryServiceImpl.

	// MailDeliveryService
	MailDeliveryHandle::Ptr sendMessage(MailMessagePtr pMessage);

	// Service
	const std::type_info& type() const;	
	bool isA(const std::type_info& otherType) const;

protected:
	virtual SMTPClientSessionPtr createSMTPClientSession(const Configuration& config);
	void closeSMTPClientSession();
	void run();

private:
	Configuration _config;
	Poco::NotificationQueue _queue;
	Poco::Thread _thread;
	SMTPClientSessionPtr _pSMTPClientSession;
	Poco::FastMutex _mutex;
	Poco::Event _shutdown;
	Poco::Logger& _logger;
};


} } } // namespace Poco::OSP::Mail


#endif // OSP_Mail_MailDeliveryServiceImpl_INCLUDED
