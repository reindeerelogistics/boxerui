
#pragma once
#include "Boxerpch.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace BoxerUI {
	class Boxer_Log {
	public:

		inline static std::shared_ptr<spdlog::logger>& boxerUILogger() { return s_boxerUILogger; }
		static void initLogger();
		static void logFile();
	private:
		static std::shared_ptr<spdlog::logger> s_boxerLogger;// = std::make_shared<spdlog::logger>();
		static std::shared_ptr<spdlog::logger> s_boxerUILogger;// = std::make_shared<spdlog::logger>();
		static std::shared_ptr<spdlog::logger> s_boxerNetLogger;// = std::make_shared<spdlog::logger>();
	};
}

#define BOXER_FATAL_LOGGER(...)		::BoxerUI::Boxer_Log::boxerUILogger()->fatal(__VA_ARGS__)
#define BOXER_CRITICAL_LOGGER(...)	::BoxerUI::Boxer_Log::boxerUILogger()->critical(__VA_ARGS__)
#define BOXER_ERROR_LOGGER(...)		::BoxerUI::Boxer_Log::boxerUILogger()->error(__VA_ARGS__)
#define BOXER_WARN_LOGGER(...)		::BoxerUI::Boxer_Log::boxerUILogger()->warn(__VA_ARGS__)
#define BOXER_INFO_LOGGER(...)		::BoxerUI::Boxer_Log::boxerUILogger()->info(__VA_ARGS__)
#define BOXER_TRACE_LOGGER(...)		::BoxerUI::Boxer_Log::boxerUILogger()->trace(__VA_ARGS__)