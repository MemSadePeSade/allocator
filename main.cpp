#include <map> 
#include <scoped_allocator> 
#include <utility> 

#include"allocator.h"
#include"container.h"

MemoryBuffer buffer1(1024);  
MemoryBuffer buffer2(1024);
MyAllocator<std::pair<const unsigned int, unsigned int>> alloc1(&buffer1);
MyAllocator<int> alloc2(&buffer2);

using mymap = std::map<unsigned int, unsigned int, std::less<unsigned int>, MyAllocator<std::pair<const unsigned int, unsigned int>>>;

unsigned int fact(unsigned int n) 
{
	if (n != 0)
		return n*fact(n - 1);
	else
		return 1;
}

int main()
{
	std::map<unsigned int, unsigned int> number_fact;
	for (unsigned int i = 0; i < 10; i++)
	{
		number_fact[i] = fact(i);
	}
	
	mymap my_number_fact(alloc1);
	for (unsigned int i = 0; i < 10; i++)
	{
		my_number_fact[i] = fact(i);
	}
	
	for (const auto& var: my_number_fact)
	{
		std::cout << var.first << " " << var.second << std::endl;
	}
	
	MyContainer<int> container(10);
	for (unsigned int i = 0; i < 10; i++)
	{
		container.push_back(i);
	}
	
	MyContainer<int, MyAllocator<int>> my_container(alloc2, 10);
	for (unsigned int i = 0; i < 10; i++)
	{
		my_container.push_back(i);
	}
	
	for (const auto& var : my_container)
	{
		std::cout << var << std::endl;
	}
	
	system("pause");
}








