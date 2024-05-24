/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <base/math.h>
#include <base/system.h>

#include <engine/config.h>
#include <engine/console.h>
#include <engine/engine.h>
#include <engine/map.h>
#include <engine/server.h>
#include <engine/storage.h>

#include <engine/shared/compression.h>
#include <engine/shared/config.h>
#include <engine/shared/datafile.h>
#include <engine/shared/demo.h>
#include <engine/shared/econ.h>
#include <engine/shared/filecollection.h>
#include <engine/shared/mapchecker.h>
#include <engine/shared/netban.h>
#include <engine/shared/network.h>
#include <engine/shared/packer.h>
#include <engine/shared/protocol.h>
#include <engine/shared/snapshot.h>

#include "server.h"

#include <signal.h>

volatile sig_atomic_t InterruptSignaled = 0;

CSnapIDPool::CSnapIDPool()
{
	Reset();
}

void CSnapIDPool::Reset()
{
	for(int i = 0; i < MAX_IDS; i++)
	{
		m_aIDs[i].m_Next = i+1;
		m_aIDs[i].m_State = 0;
	}

	m_aIDs[MAX_IDS-1].m_Next = -1;
	m_FirstFree = 0;
	m_FirstTimed = -1;
	m_LastTimed = -1;
	m_Usage = 0;
	m_InUsage = 0;
}


void CSnapIDPool::RemoveFirstTimeout()
{
	int NextTimed = m_aIDs[m_FirstTimed].m_Next;

	// add it to the free list
	m_aIDs[m_FirstTimed].m_Next = m_FirstFree;
	m_aIDs[m_FirstTimed].m_State = 0;
	m_FirstFree = m_FirstTimed;

	// remove it from the timed list
	m_FirstTimed = NextTimed;
	if(m_FirstTimed == -1)
		m_LastTimed = -1;

	m_Usage--;
}

int CSnapIDPool::NewID()
{
	int64 Now = time_get();

	// process timed ids
	while(m_FirstTimed != -1 && m_aIDs[m_FirstTimed].m_Timeout < Now)
		RemoveFirstTimeout();

	int ID = m_FirstFree;
	dbg_assert(ID != -1, "id error");
	if(ID == -1)
		return ID;
	m_FirstFree = m_aIDs[m_FirstFree].m_Next;
	m_aIDs[ID].m_State = 1;
	m_Usage++;
	m_InUsage++;
	return ID;
}

void CSnapIDPool::TimeoutIDs()
{
	// process timed ids
	while(m_FirstTimed != -1)
		RemoveFirstTimeout();
}

void CSnapIDPool::FreeID(int ID)
{
	if(ID < 0)
		return;
	dbg_assert(m_aIDs[ID].m_State == 1, "id is not allocated");

	m_InUsage--;
	m_aIDs[ID].m_State = 2;
	m_aIDs[ID].m_Timeout = time_get()+time_freq()*5;
	m_aIDs[ID].m_Next = -1;

	if(m_LastTimed != -1)
	{
		m_aIDs[m_LastTimed].m_Next = ID;
		m_LastTimed = ID;
	}
	else
	{
		m_FirstTimed = ID;
		m_LastTimed = ID;
	}
}



void CServer::SetClientName(int ClientID, const char *pName)
{
}

void CServer::SetClientClan(int ClientID, const char *pClan)
{
}

void CServer::SetClientCountry(int ClientID, int Country)
{
}

void CServer::SetClientScore(int ClientID, int Score)
{
}

void CServer::Kick(int ClientID, const char *pReason)
{
}

int64 CServer::TickStartTime(int Tick)
{
	return 0;
}

int CServer::Init()
{
	return 0;
}

void CServer::SetRconCID(int ClientID)
{
}

bool CServer::IsAuthed(int ClientID) const
{
	return false;
}

bool CServer::IsBanned(int ClientID)
{
	return false;
}

int CServer::GetClientInfo(int ClientID, CClientInfo *pInfo) const
{
	return 0;
}

void CServer::GetClientAddr(int ClientID, char *pAddrStr, int Size) const
{
}

int CServer::GetClientVersion(int ClientID) const
{
	return 0;
}

const char *CServer::ClientName(int ClientID) const
{
return "";
}

const char *CServer::ClientClan(int ClientID) const
{
		return "";
}

int CServer::ClientCountry(int ClientID) const
{
		return -1;
}

bool CServer::ClientIngame(int ClientID) const
{
	return false;
}

void CServer::InitRconPasswordIfUnset()
{
}

int CServer::SendMsg(CMsgPacker *pMsg, int Flags, int ClientID)
{
	return 0;
}

void CServer::DoSnapshot()
{
}


int CServer::NewClientCallback(int ClientID, void *pUser)
{

	return 0;
}

int CServer::DelClientCallback(int ClientID, const char *pReason, void *pUser)
{
	return 0;
}

void CServer::SendMap(int ClientID)
{
}

void CServer::SendConnectionReady(int ClientID)
{
}

void CServer::SendRconLine(int ClientID, const char *pLine)
{
}

void CServer::SendRconLineAuthed(const char *pLine, void *pUser, bool Highlighted)
{
}


void CServer::PumpNetwork()
{
}

const char *CServer::GetMapName()
{
	return "";
}

void CServer::ChangeMap(const char *pMap)
{
}

int CServer::LoadMap(const char *pMapName)
{
	return 1;
}


void CServer::InitInterfaces(IKernel *pKernel)
{
}

#include <chrono>
#include <thread>
#include <dlfcn.h>

#include <bots/sample.h>
#include <shared/hotreload.h>
#include <shared/types.h>
#include <cstdio>

void *LoadTick(FTwbl_BotTick *pfnBotTick)
{
	*pfnBotTick = nullptr;

	dlerror(); // clear old error
	void *pHandle = dlopen("./libtwbl_bottick.so", RTLD_NOW | RTLD_GLOBAL);
	const char *pError = dlerror();
	if(!pHandle || pError)
	{
		fprintf(stderr, "dlopen failed: %s\n", pError);
		if(pHandle)
			dlclose(pHandle);
		return nullptr;
	}

	*pfnBotTick = (FTwbl_BotTick)dlsym(pHandle, "Twbl_SampleTick");
	pError = dlerror();
	if(!*pfnBotTick || pError)
	{
		fprintf(stderr, "dlsym failed: %s\n", pError);
		if(pHandle)
			dlclose(pHandle);
		return nullptr;
	}
	return pHandle;
}

void Sleep(int Miliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(Miliseconds));
}

int CServer::Run()
{
	puts("starting server ...");

	while(true)
	{
		FTwbl_BotTick pfnBotTick;
		void *pHandle = LoadTick(&pfnBotTick);
		CServerBotStateIn State;
		State.m_pCollision = nullptr;
		CServerBotStateOut Bot;

		if(pHandle)
		{
			pfnBotTick(&State, &Bot);
			dlclose(pHandle);
		}
		else
		{
			Twbl_SampleTick(&State, &Bot);
		}

		Sleep(20);
	}

	return 0;
}

void CServer::Free()
{
}

struct CSubdirCallbackUserdata
{
	CServer *m_pServer;
	char m_aName[IConsole::TEMPMAP_NAME_LENGTH];
	bool m_StandardOnly;
};


void CServer::DemoRecorder_HandleAutoStart()
{
}

bool CServer::DemoRecorder_IsRecording()
{
	return false;
}


void CServer::RegisterCommands()
{
}


int CServer::SnapNewID()
{
}

void CServer::SnapFreeID(int ID)
{
}


void *CServer::SnapNewItem(int Type, int ID, int Size)
{
	return nullptr;
}

void CServer::SnapSetStaticsize(int ItemType, int Size)
{
}

static CServer *CreateServer() { return new CServer(); }


void HandleSigIntTerm(int Param)
{
	InterruptSignaled = 1;

	// Exit the next time a signal is received
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

int main(int argc, const char **argv)
{
	cmdline_fix(&argc, &argv);
#if defined(CONF_FAMILY_WINDOWS)
	for(int i = 1; i < argc; i++)
	{
		if(str_comp("-s", argv[i]) == 0 || str_comp("--silent", argv[i]) == 0)
		{
			dbg_console_hide();
			break;
		}
	}
#endif

	bool UseDefaultConfig = false;
	for(int i = 1; i < argc; i++)
	{
		if(str_comp("-d", argv[i]) == 0 || str_comp("--default", argv[i]) == 0)
		{
			UseDefaultConfig = true;
			break;
		}
	}

	if(secure_random_init() != 0)
	{
		dbg_msg("secure", "could not initialize secure RNG");
		return -1;
	}

	signal(SIGINT, HandleSigIntTerm);
	signal(SIGTERM, HandleSigIntTerm);

	CServer *pServer = CreateServer();

	// run the server
	dbg_msg("server", "starting...");
	int Ret = pServer->Run();


	secure_random_uninit();
	cmdline_free(argc, argv);
	return Ret;
}
