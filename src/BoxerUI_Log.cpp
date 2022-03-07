#include "BoxerUI_Log.h"
//DOCS: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
namespace BoxerUI {
	std::shared_ptr<spdlog::logger> Boxer_Log::s_boxerLogger;
	std::shared_ptr<spdlog::logger> Boxer_Log::s_boxerUILogger;
	std::shared_ptr<spdlog::logger> Boxer_Log::s_boxerNetLogger;
	//s_boxerUILogger = std::make_shared<spdlog::logger>();
	void	Boxer_Log::initLogger() {

		// change log pattern
		spdlog::set_pattern(" [thread %t] [%r] [%l] [%^%n: %v%$]  ");

		// create color multi threaded logger
		s_boxerLogger = spdlog::stdout_color_mt("BoxerAV");
		s_boxerUILogger = spdlog::stderr_color_mt("BoxerUI");
		s_boxerNetLogger = spdlog::stdout_color_mt("BoxerNet");
		//spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");

		s_boxerLogger->set_level(spdlog::level::critical);
		s_boxerUILogger->set_level(spdlog::level::trace);
		s_boxerNetLogger->set_level(spdlog::level::trace);
	}

	void Boxer_Log::logFile()
	{
		try
		{
			auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log init failed: " << ex.what() << std::endl;
		}
	}
}