#include "stdafx.h"

#include "RessourcePackage\RessourcePackage.h"

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
	char* inputExtension;
	char* inputFilename;
	char inputFilenameWithoutExtensionBuffer[MAX_PATH];
	char outputPath[MAX_PATH];

	Print("IronsightUnpacker %s\n", GIT_VERSION);
	
	if (argc >= 2)
	{
		for (int i = 1; i < argc; i++)
		{
			char* fileToProcess = argv[i];
			FILE* fp_in;

			inputExtension = IronsightUnpacker::GetExtension(fileToProcess);

			strncpy_s(inputFilenameWithoutExtensionBuffer, fileToProcess, MAX_PATH);
			IronsightUnpacker::StripExtension(inputFilenameWithoutExtensionBuffer);
			inputFilename = IronsightUnpacker::GetFilename(inputFilenameWithoutExtensionBuffer);

			if (strcmp(inputExtension, ".wpg") != 0)
			{
				Print("Failed to unpack: Not a wpg file\n");
				return 1;
			}

			strncpy_s(outputPath, fileToProcess, MAX_PATH);
			IronsightUnpacker::StripFilename(outputPath);
			strcat_s(outputPath, inputFilename);

			if (fopen_s(&fp_in, fileToProcess, "rb") == 0)
			{
				IronsightUnpacker::RessourcePackage package;

				if (!package.Open(fp_in))
				{
					return 1;
				}

				Print("Unpacking RessourcePackage '%s'\n", inputFilename);
				package.DumpAll(outputPath);
			}
		}
	}
	else
	{
		Print("Drag and drop an Ironsight file on this exe to unpack\n");
		Print("Press enter to close...\n");
		getc(stdin);
	}

    return 0;
}

