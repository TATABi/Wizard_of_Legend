#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Bag.h"
#include "Counter.h"

namespace game_framework {

	Counter::Counter()
	{
		_time = 0;
		_counter = 0;
		_is_start = true;
	}

	void Counter::SetTime(int time)
	{
		_time = time;
	}

	void Counter::SetCount(int count)
	{
		_counter = count;
	}

	void Counter::Count()
	{
		if(_is_start)
			_counter > 0 ? _counter-- : NULL;
	}

	bool Counter::Result()
	{
		return _counter == 0;
	}

	void Counter::Reset()
	{
		_counter = _time;
	}

	void Counter::Stop()
	{
		_is_start = false;
	}
	
	void Counter::Start()
	{
		_is_start = true;
	}

	int Counter::Now()
	{
		return _counter;
	}
}