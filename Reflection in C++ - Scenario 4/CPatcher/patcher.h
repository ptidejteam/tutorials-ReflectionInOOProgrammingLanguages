///patcher.h

#ifndef ___C_CPP_PATCHER_H___
#define ___C_CPP_PATCHER_H___


#include<windows.h>
#include <iostream>

class CPatch
{
private:
	//don't care about leaks, it is allocated only once
	static HANDLE s_hHeap;
private:
	bool m_valid;
	bool m_patched;
	bool m_set_forever;
	long m_old_jmp;
	char* m_PatchInstructionSet;
	char* m_RestorePatchSet;
	int m_size;
	int m_restore_size;
	DWORD m_protect;
	long m_FuncToHook;
	CPatch(){}
	CPatch(CPatch&){}

	template<class T1, class T2> inline void HookClassFunctions(T1& fn_funcToHook, T2 fn_Hook, bool patch_now, bool set_forever)
	{
		// CANNOT COMPILE
		// http://stackoverflow.com/questions/1307278/casting-between-void-and-a-pointer-to-member-function
		// long& NewCallAddress( *reinterpret_cast<long*>(&fn_funcToHook)  );
		// long  MyHook        ( *reinterpret_cast<long*>(&fn_Hook)        );
		// HookFunction(NewCallAddress, MyHook, &NewCallAddress, patch_now);
	}
protected:
	bool okToRewriteTragetInstructionSet(long addr, int& rw_len);
	BOOL HookFunction(long FuncToHook, long  MyHook, long* NewCallAddress, bool patch_now = true);
public:
	template<class TFunction>explicit CPatch(TFunction FuncToHook, TFunction MyHook, TFunction& NewCallAddress, bool patch_now = true, bool set_forever = false)
								: m_valid(false)
								, m_patched(false)
								, m_set_forever(set_forever)
								, m_PatchInstructionSet(0)
								, m_RestorePatchSet(0)
	{
		HookFunction(reinterpret_cast<long>(FuncToHook), reinterpret_cast<long>(MyHook), reinterpret_cast<long*>(&NewCallAddress), patch_now);
	}
	template<class TFunction>explicit CPatch(TFunction FuncToHook, TFunction MyHook, TFunction* NewCallAddress, bool patch_now = true, bool set_forever = false)
								: m_valid(false)
								, m_patched(false)
								, m_set_forever(set_forever)
								, m_PatchInstructionSet(0)
								, m_RestorePatchSet(0)
	{
		HookFunction(reinterpret_cast<long>(FuncToHook), reinterpret_cast<long>(MyHook), reinterpret_cast<long*>(NewCallAddress), patch_now);
	}
	template<class TFunction>explicit CPatch(TFunction& NewCallAddress, TFunction MyHook, bool patch_now = true, bool set_forever = false)
								: m_valid(false)
								, m_patched(false)
								, m_set_forever(set_forever)
								, m_PatchInstructionSet(0)
								, m_RestorePatchSet(0)
	{
		HookFunction(reinterpret_cast<long>(NewCallAddress), reinterpret_cast<long>(MyHook), reinterpret_cast<long*>(&NewCallAddress), patch_now);
	}
	template<class TFunction>explicit CPatch(TFunction* NewCallAddress, TFunction MyHook, bool patch_now = true, bool set_forever = false)
								: m_valid(false)
								, m_patched(false)
								, m_set_forever(set_forever)
								, m_PatchInstructionSet(0)
								, m_RestorePatchSet(0)
	{
		HookFunction(reinterpret_cast<long>(*NewCallAddress), reinterpret_cast<long>(MyHook), reinterpret_cast<long*>(*NewCallAddress), patch_now);
	}


#define ____C_CPP_PATCHER_DEFINISIONS_INCL____
#include "patcher_defines.h"

	~CPatch();

	bool patched();
	bool ok();
	bool ok(bool _valid);
	void remove_patch(bool forever = false);
	void set_patch();



};

#endif
