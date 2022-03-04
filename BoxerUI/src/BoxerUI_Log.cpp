#include "BoxerUI_Log.h"
//In Canada: Toronto. Using Payscale
//DevOps Engineer: Min(63k), Med(88k), Max(125k)
//QA Engineer: Min(47k), Med(65k), Max(92k)
//Backend Engineer: Min(46k), Med(78k), Max(98k)
//Frontend Engineer: Min(47k), Med(65k), Max(92k)

//Indeed: Toronto
//DevOps Engineer: Avg(105k)
//QA Engineer: Avg(69k)
//Backend Engineer: Avg(92k)
//Frontend Engineer: Avg(87k)

//Intern: Canada(glassdoor)
//C++ Intern Developer: Avg(80k)

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