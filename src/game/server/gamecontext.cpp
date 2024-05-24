/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <base/math.h>

#include <engine/shared/config.h>
#include <engine/shared/memheap.h>
#include <engine/storage.h>
#include <engine/map.h>

#include <generated/server_data.h>
#include <game/collision.h>
#include <game/gamecore.h>
#include <game/version.h>

#include "entities/character.h"
#include "gamecontext.h"
#include "player.h"

enum
{
	RESET,
	NO_RESET
};

void CGameContext::Construct(int Resetting)
{
}

CGameContext::CGameContext(int Resetting)
{
}

CGameContext::CGameContext()
{
}

CGameContext::~CGameContext()
{
}

void CGameContext::Clear()
{
}


class CCharacter *CGameContext::GetPlayerChar(int ClientID)
{
	return m_apPlayers[ClientID]->GetCharacter();
}

void CGameContext::CreateDamage(vec2 Pos, int Id, vec2 Source, int HealthAmount, int ArmorAmount, bool Self)
{
}

void CGameContext::CreateHammerHit(vec2 Pos)
{
}


void CGameContext::CreateExplosion(vec2 Pos, int Owner, int Weapon, int MaxDamage)
{
}

void CGameContext::CreatePlayerSpawn(vec2 Pos)
{
}

void CGameContext::CreateDeath(vec2 Pos, int ClientID)
{
}

void CGameContext::CreateSound(vec2 Pos, int Sound, int64 Mask)
{
}

void CGameContext::SendChat(int ChatterClientID, int Mode, int To, const char *pText)
{
}

void CGameContext::SendBroadcast(const char* pText, int ClientID)
{
}

void CGameContext::SendEmoticon(int ClientID, int Emoticon)
{
}

void CGameContext::SendWeaponPickup(int ClientID, int Weapon)
{
}

void CGameContext::SendMotd(int ClientID)
{
}

void CGameContext::SendSettings(int ClientID)
{
}

void CGameContext::SendSkinChange(int ClientID, int TargetID)
{
}

void CGameContext::SendGameMsg(int GameMsgID, int ClientID)
{
}

void CGameContext::SendGameMsg(int GameMsgID, int ParaI1, int ClientID)
{
}

void CGameContext::SendGameMsg(int GameMsgID, int ParaI1, int ParaI2, int ParaI3, int ClientID)
{
}

void CGameContext::SendChatCommand(const CCommandManager::CCommand *pCommand, int ClientID)
{
}

void CGameContext::SendChatCommands(int ClientID)
{
}

void CGameContext::SendRemoveChatCommand(const CCommandManager::CCommand *pCommand, int ClientID)
{
}

//
void CGameContext::StartVote(const char *pDesc, const char *pCommand, const char *pReason)
{
}


void CGameContext::EndVote(int Type, bool Force)
{
}

void CGameContext::ForceVote(int Type, const char *pDescription, const char *pReason)
{
}

void CGameContext::SendVoteSet(int Type, int ToClientID)
{
}

void CGameContext::SendVoteStatus(int ClientID, int Total, int Yes, int No)
{
}

void CGameContext::AbortVoteOnDisconnect(int ClientID)
{
}

void CGameContext::AbortVoteOnTeamChange(int ClientID)
{
}


void CGameContext::CheckPureTuning()
{
}

void CGameContext::SendTuningParams(int ClientID)
{
}

void CGameContext::SwapTeams()
{
}

void CGameContext::OnTick()
{
}

// Server hooks
void CGameContext::OnClientDirectInput(int ClientID, void *pInput)
{
}

void CGameContext::OnClientPredictedInput(int ClientID, void *pInput)
{
}

void CGameContext::OnClientEnter(int ClientID)
{
}

void CGameContext::OnClientConnected(int ClientID, bool Dummy, bool AsSpec)
{
}

void CGameContext::OnClientTeamChange(int ClientID)
{
}

void CGameContext::OnClientDrop(int ClientID, const char *pReason)
{
}

void CGameContext::OnMessage(int MsgID, CUnpacker *pUnpacker, int ClientID)
{
}

void CGameContext::ConTuneParam(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConTuneReset(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConTunes(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConPause(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConChangeMap(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConRestart(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConSay(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConBroadcast(IConsole::IResult* pResult, void* pUserData)
{
}

void CGameContext::ConSetTeam(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConSetTeamAll(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConSwapTeams(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConShuffleTeams(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConLockTeams(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConForceTeamBalance(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConAddVote(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConRemoveVote(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConClearVotes(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConVote(IConsole::IResult *pResult, void *pUserData)
{
}

void CGameContext::ConchainSpecialMotdupdate(IConsole::IResult *pResult, void *pUserData, IConsole::FCommandCallback pfnCallback, void *pCallbackUserData)
{
}

void CGameContext::ConchainSettingUpdate(IConsole::IResult *pResult, void *pUserData, IConsole::FCommandCallback pfnCallback, void *pCallbackUserData)
{
	pfnCallback(pResult, pCallbackUserData);
	if(pResult->NumArguments())
	{
		CGameContext *pSelf = (CGameContext *)pUserData;
		pSelf->SendSettings(-1);
	}
}

void CGameContext::ConchainGameinfoUpdate(IConsole::IResult *pResult, void *pUserData, IConsole::FCommandCallback pfnCallback, void *pCallbackUserData)
{
}

void CGameContext::OnConsoleInit()
{
	m_pServer = Kernel()->RequestInterface<IServer>();
	m_pConfig = Kernel()->RequestInterface<IConfigManager>()->Values();
	m_pConsole = Kernel()->RequestInterface<IConsole>();

	Console()->Register("tune", "s[tuning] ?i[value]", CFGFLAG_SERVER, ConTuneParam, this, "Tune variable to value or show current value");
	Console()->Register("tune_reset", "?s[tuning]", CFGFLAG_SERVER, ConTuneReset, this, "Reset all or one tuning variable to default");
	Console()->Register("tunes", "", CFGFLAG_SERVER, ConTunes, this, "List all tuning variables and their values");

	Console()->Register("pause", "?i[seconds]", CFGFLAG_SERVER|CFGFLAG_STORE, ConPause, this, "Pause/unpause game");
	Console()->Register("change_map", "?r[map]", CFGFLAG_SERVER|CFGFLAG_STORE, ConChangeMap, this, "Change map");
	Console()->Register("restart", "?i[seconds]", CFGFLAG_SERVER|CFGFLAG_STORE, ConRestart, this, "Restart in x seconds (-1 = abort)");
	Console()->Register("say", "r[text]", CFGFLAG_SERVER, ConSay, this, "Say in chat");
	Console()->Register("broadcast", "r[text]", CFGFLAG_SERVER, ConBroadcast, this, "Broadcast message");
	Console()->Register("set_team", "i[id] i[team] ?i[delay]", CFGFLAG_SERVER, ConSetTeam, this, "Set team of player to team");
	Console()->Register("set_team_all", "i[team]", CFGFLAG_SERVER, ConSetTeamAll, this, "Set team of all players to team");
	Console()->Register("swap_teams", "", CFGFLAG_SERVER, ConSwapTeams, this, "Swap the current teams");
	Console()->Register("shuffle_teams", "", CFGFLAG_SERVER, ConShuffleTeams, this, "Shuffle the current teams");
	Console()->Register("lock_teams", "", CFGFLAG_SERVER, ConLockTeams, this, "Lock/unlock teams");
	Console()->Register("force_teambalance", "", CFGFLAG_SERVER, ConForceTeamBalance, this, "Force team balance");

	Console()->Register("add_vote", "s[option] r[command]", CFGFLAG_SERVER, ConAddVote, this, "Add a voting option");
	Console()->Register("remove_vote", "s[option]", CFGFLAG_SERVER, ConRemoveVote, this, "remove a voting option");
	Console()->Register("clear_votes", "", CFGFLAG_SERVER, ConClearVotes, this, "Clears the voting options");
	Console()->Register("vote", "r['yes'|'no']", CFGFLAG_SERVER, ConVote, this, "Force a vote to yes/no");
}

void CGameContext::NewCommandHook(const CCommandManager::CCommand *pCommand, void *pContext)
{
	CGameContext *pSelf = (CGameContext *)pContext;
	pSelf->SendChatCommand(pCommand, -1);
}

void CGameContext::RemoveCommandHook(const CCommandManager::CCommand *pCommand, void *pContext)
{
	CGameContext *pSelf = (CGameContext *)pContext;
	pSelf->SendRemoveChatCommand(pCommand, -1);
}

void CGameContext::OnInit()
{
}

void CGameContext::OnShutdown()
{
}

void CGameContext::OnSnap(int ClientID)
{
}
void CGameContext::OnPreSnap() {}
void CGameContext::OnPostSnap()
{
	m_World.PostSnap();
	m_Events.Clear();
}

bool CGameContext::IsClientBot(int ClientID) const
{
	return m_apPlayers[ClientID] && m_apPlayers[ClientID]->IsDummy();
}

bool CGameContext::IsClientReady(int ClientID) const
{
	return m_apPlayers[ClientID] && m_apPlayers[ClientID]->m_IsReadyToEnter;
}

bool CGameContext::IsClientPlayer(int ClientID) const
{
	return m_apPlayers[ClientID] && m_apPlayers[ClientID]->GetTeam() != TEAM_SPECTATORS;
}

bool CGameContext::IsClientSpectator(int ClientID) const
{
	return m_apPlayers[ClientID] && m_apPlayers[ClientID]->GetTeam() == TEAM_SPECTATORS;
}

const char *CGameContext::Version() const { return GAME_VERSION; }
const char *CGameContext::NetVersion() const { return GAME_NETVERSION; }
const char *CGameContext::NetVersionHashUsed() const { return GAME_NETVERSION_HASH_FORCED; }
const char *CGameContext::NetVersionHashReal() const { return GAME_NETVERSION_HASH; }

IGameServer *CreateGameServer() { return new CGameContext; }
