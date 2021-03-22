#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.hpp"
#include "GildedRose.h"

TEST_CASE("At the end of each day our system lowers both values (sellin and quality) for every item")
{
    vector<Item> items;
    items.emplace_back("Foo", 0, 0);
    items.emplace_back("Bar", 6, 7);
    GildedRose app(items);
    app.updateQuality();

    Item &item0 = app.items[0];
    REQUIRE("Foo" == item0.name);
    REQUIRE(-1 == item0.sellIn);
    REQUIRE(0 == item0.quality);

    Item &item1 = app.items[1];
    REQUIRE("Bar" == item1.name);
    REQUIRE(5 == item1.sellIn);
    REQUIRE(6 == item1.quality);
}
