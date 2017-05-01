#pragma once

extern "C" inline int backtrace (void **buffer, int size) {
	return 0;
}

extern "C" inline char ** backtrace_symbols (void *const *buffer, int size) {
	return nullptr;
}

extern "C" inline void backtrace_symbols_fd (void *const *buffer, int size, int fd) {

}
