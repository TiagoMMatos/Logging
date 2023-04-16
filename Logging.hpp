#include <source_location>


#include "fmt/format.h"
#include "fmt/color.h" 
#include "fmt/ranges.h" 


#define LINFO Utility::Log::Info
#define LDEBUG Utility::Log::Debug


namespace Utility
{
	class Log
	{

		enum LOGLEVEL
		{
			INFO,
			DEBUG,
			WARNING,
			CRITICAL
		};

		struct FormatString
		{
			fmt::string_view m_Comment;
			std::source_location m_Location;

			FormatString(const char* comment,
						 const std::source_location location = std::source_location::current())
				: m_Comment(comment), m_Location(location) {}
		};

	private:
		static void FormatLog(const LOGLEVEL level, const FormatString& data, fmt::format_args args);

	public:
		template <typename... Args>
		static void Info(const FormatString& data, Args&&... args)
		{
			FormatLog(LOGLEVEL::INFO, data, fmt::make_format_args(
				args...));
		}

		template <typename... Args>
		static void Debug(const FormatString& data, Args&&... args)
		{
			FormatLog(LOGLEVEL::DEBUG, data, fmt::make_format_args(
				args...));
		}


	};

	void Log::FormatLog(const LOGLEVEL level, const FormatString& data, fmt::format_args args)
	{
		const auto& fileLocation = data.m_Location;
		fmt::string_view setLevel;
		fmt::color fgColor;
		fmt::color bgColor;
		fmt::emphasis emphasis = fmt::emphasis::bold;;


		switch(level)
		{
			case LOGLEVEL::INFO:
				setLevel = "INFO";
				fgColor = fmt::color::blue;
				bgColor = fmt::color::white;
				break;
			case LOGLEVEL::DEBUG:
				setLevel = "DEBUG";
				fgColor = fmt::color::yellow;
				bgColor = fmt::color::white;
				break;
			default:
				fgColor = fmt::color::red;
				bgColor = fmt::color::white;
				emphasis = fmt::emphasis::bold;
				setLevel = "BLANK";
				break;
		};


		fmt::print(emphasis | fmt::fg(fgColor), "{}: ", setLevel);
		fmt::vprint(data.m_Comment, args);
		fmt::print("\n");
		if(setLevel == "DEBUG")
		{
			fmt::print("FILE:{}\n LINE:{}\n  FUNCTION:{}\n ",
					   fileLocation.file_name(),
					   fileLocation.line(),
					   fileLocation.function_name());
		}

	}


}