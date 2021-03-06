#include "stdafx.h"

#include "Packing\Packing.h"
#include "Packing\Unpacking.h"

void Print(char* fmt, ...)
{
	char buffer[2048];

	va_list args;
	va_start(args, fmt);

	_vsnprintf_s(buffer,
		sizeof(buffer),
		fmt,
		args);

	va_end(args);

	printf(buffer);

#ifdef _DEBUG
	OutputDebugStringA(buffer);
#endif
}

int main(int argc, char** argv)
{
	bool result;

	Print("IronsightRessourcePacker %s\n", GIT_VERSION);
	
	if (argc >= 2)
	{
		for (int i = 1; i < argc; i++)
		{
			char* target = argv[i];

			if (IronsightRessourcePacker::Utils::DirectoryExists(target))
			{
				if (!IronsightRessourcePacker::PackRessourcePackage(target))
					Print("Packing failed\n");
			}
			else
			{
				if(!IronsightRessourcePacker::UnpackRessourcePackage(target))
					Print("Unpacking failed\n");
			}
		}
	}
	else
	{
		Print("Drag and drop an Ironsight wpg file on this exe to unpack\n");
		Print("Drag and drop a directory on this exe to pack a new wpg\n");
		Print("Press enter to close...\n");
		getc(stdin);
	}

    return 0;
}

