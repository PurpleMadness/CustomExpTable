#pragma once
#include "pch.h"

namespace ExpTableHook
{
	// Search for any known level up experience values
	// and you should be able to find the address.
	// This is the address for version 83.
	const unsigned long nextLevelAddress = 0x0078C8A6;
	
	typedef void*(__cdecl* lpfnNextLevel)(int[]);
	auto originalNextLevel = reinterpret_cast<lpfnNextLevel>(nextLevelAddress);

	BOOL setHook(__in BOOL bInstall, __inout PVOID* ppvTarget, __in PVOID pvDetour)
	{
		if (DetourTransactionBegin() != NO_ERROR)
			return FALSE;

		if (DetourUpdateThread(GetCurrentThread()) == NO_ERROR)
			if ((bInstall ? DetourAttach : DetourDetach)(ppvTarget, pvDetour) == NO_ERROR)
				if (DetourTransactionCommit() == NO_ERROR)
					return TRUE;

		DetourTransactionAbort();
		return FALSE;
	}

	void* __fastcall customNextLevel(int expTable[])
	{
		int level = 1;
		
		while(level <= 5)
		{
			expTable[level] = level * (level * level / 2 + 15);
			level++;
		}

		while(level <= 50)
		{
			expTable[level] = level * level / 3 * (level * level / 3 + 19);
			level++;
		}

		while(level < 200)
		{
			expTable[level] = long(double(expTable[level - 1]) * 1.0548);
			level++;
		}

		expTable[200] = 0;

		return expTable;
	}

	void doHook()
	{
		setHook(true, reinterpret_cast<PVOID*>(&originalNextLevel), &customNextLevel);
	}
}