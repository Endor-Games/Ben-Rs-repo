#include "pch.h"
#include "Log.h"

namespace Engine {
	std::shared_ptr<spdlog::logger> Log::s_pLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_pLogger = spdlog::stdout_color_mt("ENGINE");
		s_pLogger->set_level(spdlog::level::trace);
	}
}
