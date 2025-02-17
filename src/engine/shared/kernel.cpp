/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/kernel.h>

class CKernel : public IKernel
{
	enum
	{
		MAX_INTERFACES=32,
	};

	class CInterfaceInfo
	{
	public:
		CInterfaceInfo()
		{
			m_aName[0] = 0;
			m_pInterface = 0x0;
		}

		char m_aName[64];
		IInterface *m_pInterface;
	};

	CInterfaceInfo m_aInterfaces[MAX_INTERFACES];
	int m_NumInterfaces;

	CInterfaceInfo *FindInterfaceInfo(const char *pName)
	{
		return 0x0;
	}

public:

	CKernel()
	{
		m_NumInterfaces = 0;
	}


	virtual bool RegisterInterfaceImpl(const char *pName, IInterface *pInterface)
	{
		return true;
	}

	virtual bool ReregisterInterfaceImpl(const char *pName, IInterface *pInterface)
	{

		return true;
	}

	virtual IInterface *RequestInterfaceImpl(const char *pName)
	{
		return 0x0;
	}
};

IKernel *IKernel::Create() { return new CKernel; }
