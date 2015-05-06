
#include "standard.h"
#include "io.h"

extern "C" void *memcpy(void *dest, const void *src, basilisk::size n) {
	using namespace basilisk;

	// copy using size type copying
	size n_size = n % sizeof(size);
	if (n_size > 0) {
		for (size i = 0; i < n_size; i++) {
			((size *) dest)[i] = ((const size *) src)[i];
		}
	}

	// copy the rest by byte
	size n_remaining = n - (n_size * sizeof(size));
	for (size i = (n - n_remaining); i < n_remaining; i++) {
		((u8 *) dest)[i] = ((const u8 *) src)[i];
	}

	return dest;
}

extern "C" void *memmove(void *dest, const void *src, basilisk::size n) {
	basilisk::u8 buffer[n];
	memcpy(buffer, src, n);
	return memcpy(dest, buffer, n);
}

void operator delete(void *ptr) {
	// TODO: implement memory management.
}

namespace __cxxabiv1 {

extern "C" void __cxa_pure_virtual() {

	// TODO: This function should ideally make a lot of noise and fail,
	// this implementation does not.
}

extern "C" void __cxa_atexit(void (*func) (void *), void * arg, void * dso_handle) {
	// TODO: this function should be called on exit.
}

} // namespace __cxxabiv1
