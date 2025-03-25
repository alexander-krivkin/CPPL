#pragma once


#include "List.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>


TEST_CASE("test Empty Size Clear", "[Empty]")
{
	List testObj{};

	SECTION("Empty")
	{
		CHECK(testObj.Empty() == true);
	}

	SECTION("Size")
	{
		CHECK(testObj.Size() == 0);
		testObj.PushBack(22);
		testObj.PushBack(11);
		CHECK(testObj.Size() == 2);
	}

	SECTION("Clear")
	{
		testObj.PushBack(22);
		testObj.PushBack(11);
		testObj.Clear();
		CHECK(testObj.Size() == 0);
	}
}