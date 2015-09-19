#include <iostream>
#include <vector>

using namespace std;

struct mem_byte{
	char byte;
	int address;
};


class MemoryAllocator
{
public:
	MemoryAllocator(int bytes);
	~MemoryAllocator();

	void monitor_mem();
	void* allocate_mem(int bytes);
	void* reallocate_mem(int *addr, int new_size);
	void free_mem(int *addr);

private:
	vector<mem_byte> memory;
	vector<mem_byte> tmp;
	int length;
	int free_length;

	void copy_bytes(int *addr);
};