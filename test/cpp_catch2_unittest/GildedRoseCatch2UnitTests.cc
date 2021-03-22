#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.hpp"
#include "GildedRose.h"

TEST_CASE("At the end of each day our system lowers both values (sellin and quality) for every item")
{
    vector<Item> items;
    items.emplace_back("Foo", 1, 15);
    items.emplace_back("Bar", 6, 7);
    GildedRose app(items);
    app.updateQuality();

    Item &item0 = app.items[0];
    REQUIRE("Foo" == item0.name);
    REQUIRE(0 == item0.sellIn);
    REQUIRE(14 == item0.quality);

    Item &item1 = app.items[1];
    REQUIRE("Bar" == item1.name);
    REQUIRE(5 == item1.sellIn);
    REQUIRE(6 == item1.quality);
}

TEST_CASE("Once the sell by date has passed, Quality degrades twice as fast")
{
    vector<Item> items;
    items.emplace_back("Foo", -1, 42);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(40 == item.quality);

    app.updateQuality();
    REQUIRE(38 == item.quality);
}

TEST_CASE("The Quality of an item is never negative")
{
    vector<Item> items;
    items.emplace_back("Foo", 0, 0);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(0 == item.quality);

    app.updateQuality();
    REQUIRE(0 == item.quality);
}