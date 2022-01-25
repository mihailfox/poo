#include <iostream>
#include "menuItem.h"

menuItem::menuItem() = default;

menuItem::menuItem(string itemId, string label, void *function) {
    this->itemId = itemId;
    this->label = label;
    this->function = function;
}

void menuItem::setItemId(string itemId) {
    this->itemId = itemId;
}

string menuItem::getItemId() {
    return this->itemId;
}

void menuItem::setAction(void *function) {
    this->function = function;
}

void *menuItem::getAction() {
    return function;
}


string menuItem::toString() {
    return this->itemId + ". " + this->label;
}

menuItem::~menuItem() {
    this->itemId.clear();
    this->label.clear();
}

bool menuItem::operator==(const menuItem &rhs) const {
    return itemId == rhs.itemId &&
           label == rhs.label &&
           function == rhs.function;
}

bool menuItem::operator!=(const menuItem &rhs) const {
    return !(rhs == *this);
}

