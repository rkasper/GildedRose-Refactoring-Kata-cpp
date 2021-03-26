#include <string>
#include <vector>

static const char *const agedBrie = "Aged Brie";
static const char *const backstagePasses = "Backstage passes to a TAFKAL80ETC concert";
static const char *const sulfuras = "Sulfuras, Hand of Ragnaros";
static const char *const conjured = "Conjured";

static const int reallyCloseToConcertDate = 6;
static const int closeToConcertDate = 11;
static const int maximumQuality = 50;

using namespace std;

class Item
{
public:
    string name;
    int sellIn;
    int quality;

    Item(string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) {}
};

class GildedRose
{
public:
    vector<Item> & items;
    explicit GildedRose(vector<Item> & items);
    void updateQuality();

private:
    static void updateItem(Item &item) ;
    static void updateIfAgedBrie(Item &item) ;
    static void updateIfBackstagePasses(Item &item) ;
    static void updateIfSulfuras(const Item &item) ;
    static void updateIfNormalItem(Item &item) ;
    static void updateIfConjured(Item &item);
    static void ensureMaximumQuality(Item &item) ;
    static bool isNormalItem(const Item &item);
    static void ensureMinimumQuality(Item &item);
};

