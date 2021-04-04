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

TEST_CASE("\"Aged Brie\" actually increases in Quality the older it gets")
{
    vector<Item> items;
    items.emplace_back("Aged Brie", 15, 42);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(43 == item.quality);

    app.updateQuality();
    REQUIRE(44 == item.quality);

    // Branch coverage
    vector<Item> items2;
    items2.emplace_back("Aged Brie", -1, 50);
    GildedRose app2(items2);

    Item &item2 = app2.items[0];
    app2.updateQuality();
    REQUIRE(-2 == item2.sellIn);
    REQUIRE(50 == item2.quality);
}

TEST_CASE("The Quality of an item is never more than 50")
{
    vector<Item> items;
    items.emplace_back("Aged Brie", 15, 50);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(50 == item.quality);

    app.updateQuality();
    REQUIRE(50 == item.quality);
}

TEST_CASE("\"Sulfuras\", being a legendary item, never has to be sold or decreases in Quality")
{
    vector<Item> items;
    items.emplace_back("Sulfuras, Hand of Ragnaros", 15, 42);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(15 == item.sellIn);
    REQUIRE(42 == item.quality);

    app.updateQuality();
    REQUIRE(15 == item.sellIn);
    REQUIRE(42 == item.quality);

    // Branch coverage
    vector<Item> items2;
    items2.emplace_back("Sulfuras, Hand of Ragnaros", -1, 42);
    GildedRose app2(items2);

    Item &item2 = app2.items[0];
    app2.updateQuality();
    REQUIRE(-1 == item2.sellIn);
    REQUIRE(42 == item2.quality);
}

TEST_CASE("\"Backstage passes\", like aged brie, increases in Quality as its SellIn value approaches")
{
    vector<Item> items;
    items.emplace_back("Backstage passes to a TAFKAL80ETC concert", 15, 42);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(14 == item.sellIn);
    REQUIRE(43 == item.quality);

    app.updateQuality();
    REQUIRE(13 == item.sellIn);
    REQUIRE(44 == item.quality);
}

TEST_CASE("Backstage passes: Quality increases by 2 when there are 10 days or less and by 3 when there are 5 days or less")
{
    vector<Item> items;
    items.emplace_back("Backstage passes to a TAFKAL80ETC concert", 10, 21);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(9 == item.sellIn);
    REQUIRE(23 == item.quality);

    app.updateQuality();
    app.updateQuality();
    app.updateQuality();
    app.updateQuality();
    REQUIRE(5 == item.sellIn);
    REQUIRE(31 == item.quality);
    app.updateQuality();
    REQUIRE(4 == item.sellIn);
    REQUIRE(34 == item.quality);

    // Branch coverage
    vector<Item> items2;
    items2.emplace_back("Backstage passes to a TAFKAL80ETC concert", 10, 49);
    GildedRose app2(items2);
    Item &item2 = app2.items[0];
    app2.updateQuality();
    REQUIRE(9 == item2.sellIn);
    REQUIRE(50 == item2.quality);

    // Branch coverage
    vector<Item> items3;
    items3.emplace_back("Backstage passes to a TAFKAL80ETC concert", 5, 48);
    GildedRose app3(items3);
    Item &item3 = app3.items[0];
    app3.updateQuality();
    REQUIRE(4 == item3.sellIn);
    REQUIRE(50 == item3.quality);
}

TEST_CASE("Backstage passes: Quality drops to 0 after the concert")
{
    vector<Item> items;
    items.emplace_back("Backstage passes to a TAFKAL80ETC concert", 0, 42);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(-1 == item.sellIn);
    REQUIRE(0 == item.quality);
}

TEST_CASE("Aged Brie, sellin < 0, quality < 50")
{
    vector<Item> items;
    items.emplace_back("Aged Brie", -1, 42);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(-2 == item.sellIn);
    REQUIRE(44 == item.quality);
}

TEST_CASE("\"Conjured\" items degrade in Quality twice as fast as normal items")
{
    vector<Item> items;
    items.emplace_back("Conjured", 1, 4);
    GildedRose app(items);

    Item &item = app.items[0];
    app.updateQuality();
    REQUIRE(0 == item.sellIn);
    REQUIRE(2 == item.quality);

    app.updateQuality();
    REQUIRE(-1 == item.sellIn);
    REQUIRE(0 == item.quality);

    app.updateQuality();
    REQUIRE(-2 == item.sellIn);
    REQUIRE(0 == item.quality);
}