#pragma once

#include "Macros.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& Get() { return s_pLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_pLogger;
	};
}
