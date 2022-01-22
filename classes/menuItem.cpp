#include <iostream>
#include "menuItem.h"

menuItem::menuItem() { }

menuItem::menuItem(string itemId, string label, void *function, char consoleKey) {
    this->itemId = itemId;
    this->label = label;
    this->function = function;
    this->consoleKey = consoleKey;
}

void menuItem::setItemId(string itemId) {
    this->itemId = itemId;
}

string menuItem::getItemId() {
    return this->itemId;
}

void menuItem::setConsoleKey(char consoleKey) {
    this->consoleKey = consoleKey;
}

char menuItem::getConsoleKey() {
    return this->consoleKey;
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

