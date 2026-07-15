#pragma once

template<typename T>
void SafeRelease(T*& _obj)
{
	if (_obj)
	{
		_obj->Release();
		_obj = nullptr;
	}
}