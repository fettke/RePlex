#include <RePlex.h>
#include <iostream>

#ifdef DEBUG
const char* g_libPath = "RePlexTest.dll";
#else
const char* g_libPath = "RePlexTest.dll";
#endif

void (*foo)();

int main()
{
	HINSTANCE handle = reinterpret_cast<HINSTANCE>(Load(g_libPath));
	if (handle == NULL)
	{
		std::cout << "Could not load the dynamic library " << g_libPath << std::endl;
		return EXIT_FAILURE;
	}

	// Set the memory address of the function foo from the library to our foo
	foo = reinterpret_cast<void(*)()>(LoadSymbol(handle, "foo"));
	if (foo == NULL)
	{
		std::cout << "Could not locate the function" << std::endl;
		return EXIT_FAILURE;
	}

	foo();

	// Read the data from the global variable bar in the test library
	int bar = *reinterpret_cast<int*>(LoadSymbol(handle, "bar"));
	if (bar == NULL)
	{
		std::cout << "Could not locate the symbol" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "bar == " << bar << std::endl;

	FreeLibrary(handle);

	// Wait for input to give us a chance to recompile the library
	std::cout << "Make some changes, recompile, and press enter." << std::flush;
	while (std::cin.get() != '\n') {}

	// Reload the library
	handle = reinterpret_cast<HINSTANCE>(Load(g_libPath));
	if (handle == NULL)
	{
		std::cout << "Could not load the dynamic library " << g_libPath << std::endl;
		return EXIT_FAILURE;
	}

	// We need to refetch the symbol because it's location in memory may have changed
	foo = reinterpret_cast<void(*)()>(LoadSymbol(handle, "foo"));
	foo();

	// Do the same for bar
	bar = *reinterpret_cast<int*>(LoadSymbol(handle, "bar"));
	if (bar == NULL)
	{
		std::cout << "Could not locate the symbol" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "bar == " << bar << std::endl;

	FreeLibrary(handle);

	return 0;
}
