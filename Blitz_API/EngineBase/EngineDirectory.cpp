#include "PreCompiledFile.h"
#include "EngineDirectory.h"

UEngineDirectory::UEngineDirectory()
{
	FilePath = std::filesystem::current_path();

}

UEngineDirectory::~UEngineDirectory()
{
}
