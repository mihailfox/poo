#include "menuItem.h"

menuItem::menuItem() = default;

menuItem::menuItem(string itemId, string label, void *action) {
    this->itemId = itemId;
    this->label = label;
    this->action = action;
}

void menuItem::setItemId(string itemId) {
    this->itemId = itemId;
}

string menuItem::getItemId() {
    return this->itemId;
}

void menuItem::setAction(void *action) {
    this->action = action;
}

void *menuItem::getAction() {
    return this->action;
}

void menuItem::setLabel(string label) {
    this->label = label;
}

string menuItem::getLabel() {
    return this->label;
}


string menuItem::toString() {
    return this->itemId + ". " + this->label;
}

bool menuItem::isInitialized() {
    if(this->itemId.empty() && this->label.empty())
    {
        return false;
    }

    return true;
}

menuItem::~menuItem() {
    this->itemId.clear();
    this->label.clear();
}

bool menuItem::operator==(const menuItem &rhs) const {
    return itemId == rhs.itemId &&
           label == rhs.label &&
           action == rhs.action;
}

bool menuItem::operator!=(const menuItem &rhs) const {
    return !(rhs == *this);
}

