#include "../Parser.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Parser_Tests, AbsorbBOMAbsorbsBOM)
{
	std::stringstream input{"\xEF\xBB\xBFMore text"};
	commonItems::absorbBOM(input);

	char buffer[256];
	input.getline(buffer, sizeof buffer);
	ASSERT_EQ("More text", std::string{buffer});
}


TEST(Parser_Tests, AbsorbBOMDoesNotAbsorbNonBOM)
{
	std::stringstream input{"More text"};
	commonItems::absorbBOM(input);

	char buffer[256];
	input.getline(buffer, sizeof buffer);
	ASSERT_EQ("More text", std::string{buffer});
}