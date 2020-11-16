#ifndef PARSER_H
#define PARSER_H



#include <functional>
#include <map>
#include <optional>
#include <regex>

#include "Log.h"


namespace commonItems
{

typedef std::function<void(const std::string&, std::istream&)> parsingFunction;


void absorbBOM(std::istream& theStream);


class parser
{
  public:
	parser() = default;
	~parser() = default;
	parser(const parser&) = default;
	parser(parser&&) noexcept = default;
	parser& operator=(const parser&) = default;
	parser& operator=(parser&&) = default;

	void registerKeyword(const std::string& keyword, const parsingFunction& function);
	void registerRegex(const std::string& keyword, const parsingFunction& function);
	void clearRegisteredKeywords() noexcept;

	void parseStream(std::istream& theStream);
	void parseFile(const std::string& filename);

	std::optional<std::string> getNextToken(std::istream& theStream);
	static std::optional<std::string> getNextTokenWithoutMatching(std::istream& theStream);


  private:
	void levelUp()
	{
		++level;
		registeredKeywordStrings.emplace_back();
		generatedRegexes.emplace_back();

		Log(LogLevel::Debug) << "vector size is " << registeredKeywordStrings.size();
		Log(LogLevel::Debug) << "up to " << level;
	}
	void levelDown()
	{
		registeredKeywordStrings.pop_back();
		generatedRegexes.pop_back();
		--level;
		Log(LogLevel::Debug) << "vector size is " << registeredKeywordStrings.size();
		Log(LogLevel::Debug) << "down to " << level;
	}
	
	// initialize the vectors with size of 1
	std::vector<std::map<std::string, parsingFunction>> registeredKeywordStrings = {
		 std::map<std::string, parsingFunction>()};
	std::vector<std::vector<std::pair<std::regex, parsingFunction>>> generatedRegexes = {
		 std::vector<std::pair<std::regex, parsingFunction>>()};
	
	unsigned int level = 0;
};

} // namespace commonItems



#endif // PARSER_H