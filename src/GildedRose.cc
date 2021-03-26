#include "GildedRose.h"

GildedRose::GildedRose(vector<Item> &items) : items(items) {}

void GildedRose::updateQuality() {
    for (int i = 0; i < items.size(); i++) {
        updateItem(items[i]);
    }
}

void GildedRose::updateItem(Item &item) {
    updateIfAgedBrie(item);
    updateIfBackstagePasses(item);
    updateIfSulfuras(item);
    updateIfNormalItem(item);
    updateIfConjured(item);
}

void GildedRose::updateIfNormalItem(Item &item) {
    if (isNormalItem(item)) {
        item.sellIn--;
        if (item.sellIn < 0) {
                item.quality -= 2;
        } else {
            item.quality--;
        }

        ensureMinimumQuality(item);
    }
}

void GildedRose::ensureMinimumQuality(Item &item) {
    if (item.quality < 0) {
        item.quality = 0;
    }
}

bool GildedRose::isNormalItem(const Item &item) { return item.name != backstagePasses && item.name != agedBrie && item.name != sulfuras && item.name != conjured; }

void GildedRose::updateIfSulfuras(const Item &item) { if (item.name == sulfuras) {}}

void GildedRose::updateIfBackstagePasses(Item &item) {
    if (item.name == backstagePasses) {
        if (item.sellIn < reallyCloseToConcertDate) {
            item.quality += 3;
        } else if (item.sellIn < closeToConcertDate) {
            item.quality += 2;
        } else {
            item.quality++;
        }
        ensureMaximumQuality(item);

        item.sellIn--;

        if (item.sellIn < 0) {
            item.quality = 0;
        }
    }
}

void GildedRose::updateIfAgedBrie(Item &item) {
    if (item.name == agedBrie) {
        item.sellIn--;
        if (item.sellIn < 0) {
            item.quality += 2;
        } else {
            item.quality ++;
        }
        ensureMaximumQuality(item);
    }
}

void GildedRose::updateIfConjured(Item &item) {
    if (item.name == conjured) {
        item.sellIn--;
        item.quality -= 2;
    }
    ensureMinimumQuality(item);
}

void GildedRose::ensureMaximumQuality(Item &item) {
    if (item.quality > maximumQuality) {
        item.quality = maximumQuality;
    }
}
