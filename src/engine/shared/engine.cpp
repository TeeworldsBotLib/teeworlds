/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <stdlib.h> // srand

#include <base/system.h>

#include <engine/console.h>
#include <engine/engine.h>


static int HostLookupThread(void *pUser)
{
	CHostLookup *pLookup = (CHostLookup *)pUser;
	return net_host_lookup(pLookup->m_aHostname, &pLookup->m_Addr, pLookup->m_Nettype);
}

class CEngine : public IEngine
{
public:
	IConsole *m_pConsole;
	bool m_Logging;
	IOHANDLE m_DataLogSent;
	IOHANDLE m_DataLogRecv;
	const char *m_pAppname;

	static void Con_DbgLognetwork(IConsole::IResult *pResult, void *pUserData)
	{
	}

	CEngine(const char *pAppname)
	{
	}

	~CEngine()
	{
		StopLogging();
	}

	void Init()
	{
	}

	void ShutdownJobs()
	{
	}

	void InitLogfile()
	{
	}

	void QueryNetLogHandles(IOHANDLE *pHDLSend, IOHANDLE *pHDLRecv)
	{
	}

	void StartLogging(IOHANDLE DataLogSent, IOHANDLE DataLogRecv)
	{
	}

	void StopLogging()
	{
	}

	void HostLookup(CHostLookup *pLookup, const char *pHostname, int Nettype)
	{
	}

	void AddJob(CJob *pJob, JOBFUNC pfnFunc, void *pData)
	{
	}
};

IEngine *CreateEngine(const char *pAppname) { return new CEngine(pAppname); }
