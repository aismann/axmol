/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmol.dev/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

//
// Bug-350
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=350
//

#include "Bug-350.h"

using namespace ax;

bool Bug350Layer::init()
{
    if (BugsTestBase::init())
    {
        auto size       = Director::getInstance()->getWinSize();
        auto background = Sprite::create("Hello.png");
        background->setPosition(size.width / 2, size.height / 2);
        addChild(background);

        auto drawNode = DrawNode::create();
        addChild(drawNode);
        drawNode->setAnchorPoint(Vec2(0.5f, 0.5f));
        // drawNode->drawRect(Vec2(123, 123), Vec2(227, 227), Color(1, 1, 0, 1), 2);
        // drawNode->drawRect(Vec2(115, 130), Vec2(130, 115), Vec2(115, 100), Vec2(100, 115), Color::MAGENTA, 2);
        for (int i = 0; i < 10; i++)
        {
            drawNode->drawRoundedRect(Vec2(115, 130), Vec2(130, 115), 40, Color4F::GREEN, Color4F::GREEN, 2);
            drawNode->drawRoundedRect(Vec2(10, 50), Vec2(227, 70), 20, Color4F::YELLOW, Color4F::GREEN, 2);
            drawNode->drawRoundedRect(Vec2(300, 50), Vec2(100, 60), 5, Color4F::GRAY, Color4F::GREEN, 2);
        }



        return true;
    }

    return false;
}
