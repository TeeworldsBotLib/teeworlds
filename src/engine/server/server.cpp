/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <engine/console.h>
#include <engine/server.h>

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
}

int CSnapIDPool::NewID()
{
	return 0;
}

void CSnapIDPool::TimeoutIDs()
{
}

void CSnapIDPool::FreeID(int ID)
{
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
	signal(SIGINT, HandleSigIntTerm);
	signal(SIGTERM, HandleSigIntTerm);

	CServer *pServer = CreateServer();

	// run the server
	int Ret = pServer->Run();


	return Ret;
}
