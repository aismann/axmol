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



   //             auto size = Director::getInstance()->getVisibleSize();
        // auto background = Sprite::create("Hello.png");
        // background->setPosition(size.width / 2, size.height / 2);
        //    addChild(background);

        auto drawNode = DrawNode::create();
        addChild(drawNode);
        drawNode->setAnchorPoint(Vec2(0.5f, 0.5f));
        // drawNode->drawRect(Vec2(123, 123), Vec2(227, 227), Color(1, 1, 0, 1), 2);
        // drawNode->drawRect(Vec2(115, 130), Vec2(130, 115), Vec2(115, 100), Vec2(100, 115), Color::MAGENTA, 2);
        //  for (int i = 0; i < 10; i++)
        {
            drawNode->drawRoundedRect(Vec2(215,180), Vec2(130, 115), 40, Color4F::GREEN, Color4F::GREEN, 2);
            drawNode->drawRoundedRect(Vec2(10, 150), Vec2(227, 70), 20, Color4F::YELLOW, Color4F::GREEN, 2);
            drawNode->drawRoundedRect(Vec2(300, 150), Vec2(100, 60), 5, Color4F::GRAY, Color4F::GREEN, 2);
        }

        // label = Label::createWithTTF("callback 1 called", "fonts/Marker Felt.ttf", 16.0f);
        // addChild(label);
        // label->setPosition(size.width / 2, size.height / 2);

        //    for (int i = 0; i < 500; i++)
        //{
        //    float x = 50 + AXRANDOM_0_1() * 400;
        //    float y = 50 + AXRANDOM_0_1() * 200;
        //    float r = 55;// + AXRANDOM_0_1() * 40;
        //  //  drawNode->drawSolidCircle(Vec2(x, y), r, 0, 36, Color::random().premultiplyAlpha());
        //    drawNode->drawSegment(Vec2(x, y), Vec2(x + 0.01, y), r * 4, Color::random().premultiplyAlpha());
        //}

        // drawNode->drawSegment(Vec2(195, 130), Vec2(195+0.01, 130), 160, Color::MAGENTA);
        //    drawNode->drawSegment(Vec2(195, 130), Vec2(160, 130), 150, Color::BLUE);
        // drawNode->drawSolidRect(Vec2(54, 250), Vec2(206, 113), Color::GREEN);
        // drawNode->setSkewX(100.0f);  // degrees
        // drawNode->setSkewY(0.0f);   // degrees
        //        background->setPosition(size / 2);
        // addChild(background);

        // Make a reference grid so distortion is visible
        // auto draw = DrawNode::create();
        // for (int x = -300; x <= 300; x += 30)
        //     draw->drawLine(Vec2(x, -300), Vec2(x, 300), Color(0.2f, 0.2f, 0.2f, 1));
        // for (int y = -300; y <= 300; y += 30)
        //     draw->drawLine(Vec2(-300, y), Vec2(300, y), Color(0.2f, 0.2f, 0.2f, 1));
        // addChild(draw);

        // // A test sprite
        // auto sp = Sprite::create("Hello.png");  // 200x200 recommended for visual clarity
        // sp->setPosition(size / 2);
        // sp->setAnchorPoint(Vec2(0.5f, 0.5f));
        // addChild(sp);

        // // Apply transforms via Node API
        // sp->setRotation(0.0f);  // degrees  -30
        // sp->setSkewX(30.0f);     // degrees
        // sp->setSkewY(0.0f);    // degrees

        // auto drawFairy = DrawNode::create();
        // addChild(drawFairy);
        // drawFairy->setPosition(size / 2);
        // drawFairy->drawSolidRect(Vec2(57, 255), Vec2(257, 455), Color::GREEN);
        // scheduleUpdate();

        auto layer = Layer::create();
        addChild(layer);

        // Create the stencil shape (e.g., a circle),
        auto stencil = DrawNode::create();
        stencil->drawRoundedRect(Vec2(115, 130), Vec2(100, 40), 10, Color4F(1, 1, 1, 1), Color4F(1, 1, 1, 0));
        //    stencil->setPosition(Vec2(240, 160));  // Center of screen

        //// Create the content to be clipped "D:\_git\axmol3org\tests\cpp-tests\Content\Images\pattern1.png"
        // "D:\_git\axmol3org\tests\cpp-tests\Content\hd\Images\MagentaSquare.png"
        auto sprite = Sprite::create("hd/Images/MagentaSquare.png");
        sprite->setPosition(Vec2(115, 130));
        sprite->setScaleX(2.5);
        // Create the clipping node
        auto clipper = ClippingNode::create();
        clipper->setStencil(stencil);
        clipper->setInverted(false);        // Set to true to invert the mask
        clipper->setAlphaThreshold(0.05f);  // Pixels with alpha < threshold are discarded
        clipper->addChild(sprite);
        layer->addChild(clipper);

        auto stencil1 = DrawNode::create();
        stencil1->drawRoundedRect(Vec2(215, 60), Vec2(200, 60), 30, Color4F(1, 1, 1, 1), Color4F(1, 1, 1, 0));
        sprite = Sprite::create("hd/Images/CyanSquare.png");
        sprite->setPosition(Vec2(215, 60));
        sprite->setScaleX(4.5);
        sprite->setScaleY(1.5);
        // Create the clipping node
        auto clipper1 = ClippingNode::create();
        clipper1->setStencil(stencil1);
        clipper1->setInverted(false);        // Set to true to invert the mask
        clipper1->setAlphaThreshold(0.05f);  // Pixels with alpha < threshold are discarded
        clipper1->addChild(sprite);

        layer->addChild(clipper1);

        //

        // auto stencil1 = DrawNode::create();
        // stencil1->drawSolidCircle(Vec2(0, 0), 10, 0, 36, Color(1, 1, 1, 1));
        // stencil->setPosition(Vec2(240, 160));  // Center of screen
        // auto clipper1 = ClippingNode::create();
        // clipper1->setStencil(stencil1);
        // clipper1->setInverted(true);        // Set to true to invert the mask
        // clipper1->setAlphaThreshold(0.05f);  // Pixels with alpha < threshold are discarded
        // clipper1->addChild(clipper);

        auto renderTex = RenderTexture::create(256, 256);

        const auto& proj = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

        renderTex->beginWithClear(0, 0, 0, 0);

        Vec2 verts[] = {Vec2(0, 0), Vec2(256, 0), Vec2(256, 256), Vec2(0, 256)};

        Color4F bottomColor(1, 0, 0, 1);  // Red
        Color4F topColor(0, 0, 1, 1);     // Blue

        Color4F colors[] = {bottomColor, bottomColor, topColor, topColor};

        drawNode = DrawNode::create();
        drawNode->drawPolygon(verts, 4, Color4F::WHITE, 0, Color4F::BLACK, colors);

        drawNode->visit(Director::getInstance()->getRenderer(), proj.getInversed(), 0);  // Draw into the render texture
        renderTex->end();

        // Create a sprite from the texture
        auto gradientSprite = Sprite::createWithTexture(renderTex->getSprite()->getTexture());
        gradientSprite->setFlippedY(true);  // Important: RenderTexture is upside-down
        gradientSprite->setPosition(Vec2(240, 160));
        addChild(gradientSprite);



        return true;
    }

    return false;
}
