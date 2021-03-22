#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.hpp"
#include "GildedRose.h"

TEST_CASE("At the end of each day our system lowers both values (sellin and quality) for every item")
{
    vector<Item> items;
    items.push_back(Item("Foo", 0, 0));
    items.push_back(Item("Bar", 6, 7));
    GildedRose app(items);
    app.updateQuality();

    REQUIRE("Foo" == app.items[0].name);
    REQUIRE(-1 == app.items[0].sellIn);
    REQUIRE(0 == app.items[0].quality);

    REQUIRE("Bar" == app.items[1].name);
    REQUIRE(5 == app.items[1].sellIn);
    REQUIRE(6 == app.items[1].quality);
}
