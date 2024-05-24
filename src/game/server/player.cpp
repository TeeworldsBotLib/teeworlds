/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include "entities/character.h"
#include "gamecontext.h"
#include "player.h"


MACRO_ALLOC_POOL_ID_IMPL(CPlayer, MAX_CLIENTS)

IServer *CPlayer::Server() const { return m_pGameServer->Server(); }

CPlayer::CPlayer(CGameContext *pGameServer, int ClientID, bool Dummy, bool AsSpec)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
}

void CPlayer::PostTick()
{
}

void CPlayer::Snap(int SnappingClient)
{
}

void CPlayer::OnDisconnect()
{
}

void CPlayer::OnPredictedInput(CNetObj_PlayerInput *NewInput)
{
}

void CPlayer::OnDirectInput(CNetObj_PlayerInput *NewInput)
{
}

CCharacter *CPlayer::GetCharacter()
{
	return 0;
}

void CPlayer::KillCharacter(int Weapon)
{
}

void CPlayer::Respawn()
{
}

bool CPlayer::SetSpectatorID(int SpecMode, int SpectatorID)
{

	return false;
}

bool CPlayer::DeadCanFollow(CPlayer *pPlayer) const
{
	return (!pPlayer->m_RespawnDisabled || (pPlayer->GetCharacter() && pPlayer->GetCharacter()->IsAlive())) && pPlayer->GetTeam() == m_Team;
}

void CPlayer::UpdateDeadSpecMode()
{
}

void CPlayer::SetTeam(int Team, bool DoChatMsg)
{
}

void CPlayer::TryRespawn()
{
}
