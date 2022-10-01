#include <matdash.hpp>

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

// matdash::create_console
#include <matdash/console.hpp>

// gd.h includes cocos2d.h
#include <gd.h>

void MenuLayer_onNewgrounds(gd::MenuLayer* self, cocos2d::CCObject* sender) {
    std::cout << "cool!" << std::endl;
    matdash::orig<&MenuLayer_onNewgrounds>(self, sender);
}

bool GJDropDownLayer_init(gd::GJDropDownLayer* self, const char* title, float height) {
    return matdash::orig<&GJDropDownLayer_init>(self, "my own title", height * 0.5f);
}

matdash::cc::thiscall<void> PlayLayer_update(gd::PlayLayer* self, float dt) {
    matdash::orig<&PlayLayer_update>(self, dt * 0.5f);
    // this is due to the calling convention wrapper
    // because matdash::cc::thiscall<void> is not actually void
    // see https://github.com/matcool/mat-dash#usage for more info
    return {};
}

bool MenuLayer_init(gd::MenuLayer* self) {
    if (!matdash::orig<&MenuLayer_init>(self)) return false;

    auto* sprite = cocos2d::CCSprite::create("dialogIcon_017.png");
    sprite->setPosition(ccp(100, 100));
    sprite->setScale(0.5f);
    self->addChild(sprite);

    auto* label = cocos2d::CCLabelBMFont::create("Hello world!", "bigFont.fnt");
    label->setPosition(ccp(100, 150));
    label->setAnchorPoint(ccp(0, 0.5));
    self->addChild(label);

    return true;
}

void mod_main(HMODULE) {
    // this creates a console window whenever the mod is injected
    // which is very useful for debugging, but make sure to remove
    // on release builds! :D
    matdash::create_console();

    matdash::add_hook<&MenuLayer_onNewgrounds>(gd::base + 0x191e90);
    matdash::add_hook<&GJDropDownLayer_init>(gd::base + 0x113530);
    matdash::add_hook<&PlayLayer_update>(gd::base + 0x2029c0);
    matdash::add_hook<&MenuLayer_init>(gd::base + 0x1907B0);
}