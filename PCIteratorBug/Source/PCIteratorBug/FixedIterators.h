#pragma once

#include "CoreMinimal.h"

// clang-format off

template< class T, bool LocalOnly > class TFixedBasePlayerControllerIterator
{
public:
	TFixedBasePlayerControllerIterator(class UWorld* InWorld)
		: Iter(InWorld->GetPlayerControllerIterator())
	{
		check(LocalOnly || InWorld->GetNetMode() != NM_Client);	// You should only iterate on non local player controllers if you are the server
		AdvanceCurrent();
	}

	void operator++()
	{
		Next();
	}
	T* operator*() const
	{
		return Current;
	}
	T* operator->() const
	{
		return Current;
	}
	explicit operator bool() const
	{
		return (Current!=NULL);
	}

protected:

	FConstPlayerControllerIterator Iter;
	T* Current;

	void AdvanceCurrent()
	{
		// Look at current Iter
		Current = Iter ? Cast<T>(*Iter) : nullptr;

		// Advance if we have to
		while(Iter && (!Current || (LocalOnly && !Current->IsLocalController())))
		{
			++Iter;
			Current = Iter ? Cast<T>(*Iter) : nullptr;
		}
	}

	void Next()
	{
		// Advance one
		++Iter;

		// Update Current
		AdvanceCurrent();
	}
};

template<class T>
struct TFixedPlayerControllerIterator
{
	typedef TFixedBasePlayerControllerIterator<T, true>	LocalOnly;	// Only iterates locally controlled player controllers - can be used on client or server
	typedef TFixedBasePlayerControllerIterator<T, false> ServerAll;	// Iterates all player controllers - local or remote - only can be used on server
};

// clang-format on
