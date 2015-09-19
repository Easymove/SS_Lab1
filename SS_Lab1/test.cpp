#include "mem_allocator.h"

int main(){
	int bytes = 1024;
	MemoryAllocator test = MemoryAllocator(bytes);
	
	int* addr = (int*)test.allocate_mem(8);
	int* addr2 = (int*)test.allocate_mem(16);
	
	test.monitor_mem();
	test.free_mem(addr);
	test.monitor_mem();

	addr = (int*)test.allocate_mem(32);
	test.monitor_mem();
	test.reallocate_mem(addr2, 24);
	test.monitor_mem();
}