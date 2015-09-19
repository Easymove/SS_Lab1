#include "mem_allocator.h"

MemoryAllocator::MemoryAllocator(int bytes)
{
	for (int i = 0; i < bytes; i++){
		mem_byte byte = { 0, -1 };
		memory.push_back(byte);
	}
	length = memory.size();
	free_length = length;
}

MemoryAllocator::~MemoryAllocator()
{
}

void MemoryAllocator::monitor_mem(){
	cout << "===========================================" << endl;

	int start = 0;
	
	while (start < length){
		if (memory[start].address >= 0){
			int i = start;
			while (i < length){
				if (memory[start].address != memory[i].address){
					cout << "RESERVED  =>  addres: " << start << "; length: " << i - start << ";" << endl;
					start = i;
				}
				i++;
			}
		}
		else{
			start++;
		}
	}

	cout << "SUMMURY ::>  USED: " << length - free_length << "; FREE: " << free_length << ";" << endl << endl;
}

void* MemoryAllocator::allocate_mem(int size){
	int canon_size;
	if (size % 4 == 0){
		canon_size = size;
	}
	else{
		canon_size = (size + (4 + (size % 4)));
	}
	int start = 0;
	while (start < length){
		int free_bytes = 0;
		for (int i = start; i < length - start; i++){
			if (free_bytes == canon_size){
				for (int j = start; j < i; j++){
					memory[j].address = start;
					memory[j].byte = 1 + rand() % 228;
				}
				free_length = free_length - canon_size;
				return &memory[start].address;
			}
			if (memory[i].address < 0){
				free_bytes++;
			}
			else
			{
				break;
			}
		}
		start++;
	}
	return NULL;
}

void MemoryAllocator::free_mem(int *addr){
	int start = *addr;
	int i = *addr;
	while (i < length){
		if (memory[i].address != start){
			break;
		}
		memory[i].address = -1;
		i++;
	}
	free_length += (i - start);
}

void MemoryAllocator::copy_bytes(int *addr){
	int start = *addr;
	int i = *addr;
	while (i < length){
		if (memory[i].address != start){
			break;
		}
		mem_byte tmp_byte = { memory[i].byte, memory[i].address };
		tmp.push_back(tmp_byte);
		i++;
	}
}

void* MemoryAllocator::reallocate_mem(int *addr, int new_size){
	copy_bytes(addr);
	free_mem(addr);
	int *new_addr = (int*)allocate_mem(new_size);
	if (new_addr != NULL){
		int i = *new_addr;
		while (((i - *new_addr) < tmp.size()) && (i < *new_addr + new_size)){
			memory[i].byte = tmp[i - *new_addr].byte;
			i++;
		}
	}
	return new_addr;
}