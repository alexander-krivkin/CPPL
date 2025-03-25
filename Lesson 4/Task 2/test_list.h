#pragma once


#include "List.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>


TEST_CASE("test PushBack PushFront PopBack PopFront", "[PushBack PushFront PopBack PopFront]")
{
	List testObj{};

	SECTION("Without exceptions")
	{
		testObj.PushBack(11);
		testObj.PushBack(22);
		testObj.PushFront(1);
		CHECK(testObj.Size() == 3);
		testObj.PopBack();
		CHECK(testObj.PopBack() == 11);
		CHECK(testObj.PopFront() == 1);
		CHECK(testObj.Size() == 0);
	}

	SECTION("Exceptions")
	{
		REQUIRE_THROWS(testObj.PopFront());
	}
}