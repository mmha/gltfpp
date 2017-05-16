#pragma once

extern "C" inline int backtrace(void **, int) {
	return 0;
}

extern "C" inline char **backtrace_symbols(void *const *, int) {
	return nullptr;
}

extern "C" inline void backtrace_symbols_fd(void *const *, int, int) {
}
