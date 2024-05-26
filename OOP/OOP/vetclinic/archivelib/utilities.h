#pragma once
#include <iostream>
#include <Windows.h>
#include "archive.h"

namespace InputSystem {
	enum InsertMode { Back, Front, OneValue, SeveralValues };

	template <typename T>
	T* insert(size_t& n, size_t& pos, InputSystem::InsertMode& mode) noexcept;
}

namespace OutputSystem {
	void setCursor(int column, int line);
	void getCursor(int& column, int& line) noexcept;
	void insert() noexcept;

	template <typename T>
	void show(const TArchive<T>& archive) noexcept;
}