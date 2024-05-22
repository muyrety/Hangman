#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string_view>

namespace error_code
{
	inline constexpr int score_success{ 0 };
	inline constexpr int negative_score{ 1 };
	inline constexpr int score_fail{ 2 };
	inline constexpr auto topic_fail{ "1" };
	inline constexpr auto word_fail{ "1" };
	inline constexpr auto word_topic_not_found{ "2" };
}

#endif