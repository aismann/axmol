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
//  Bug-12847.cpp
//  cocos2d_tests
//
//  Issue: https://github.com/cocos2d/cocos2d-x/issues/12847
//  Please test in iPhone5 +
//
//

#include "Bug-12847.h"

using namespace ax;

Bug12847Layer::Bug12847Layer()
{
    _projection = Director::getInstance()->getProjection();
}

Bug12847Layer::~Bug12847Layer()
{
    Director::getInstance()->setProjection(_projection);
}

bool Bug12847Layer::init()
{
    if (BugsTestBase::init())
    {

        Director::getInstance()->setProjection(Director::Projection::_2D);
        auto _visibleSize = Director::getInstance()->getVisibleSize();

        // Create with Sprite
        {
            sprite1 = Sprite::create("Images/bug12847_sprite.png");
            sprite1->getTexture()->setAliasTexParameters();
            sprite1->setPosition(Vec2(_visibleSize.width / 3, 50.0f));
            this->addChild(sprite1, 1);

            sprite2 = Sprite::create("Images/bug12847_sprite.png");
            sprite2->getTexture()->setAliasTexParameters();
            sprite2->setPosition(sprite1->getPosition() + Vec2(0.0f, sprite1->getContentSize().height));
            this->addChild(sprite2, 1);
        }
        // Create with SpriteFrame
        {
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/bug12847_spriteframe.plist");

            sprite3 = Sprite::createWithSpriteFrameName("bug12847_sprite2.png");
            sprite3->getTexture()->setAliasTexParameters();
            sprite3->setPosition(Vec2(_visibleSize.width * 2 / 3, 50.0f));
            this->addChild(sprite3, 1);

            sprite4 = Sprite::createWithSpriteFrameName("bug12847_sprite2.png");
            sprite4->getTexture()->setAliasTexParameters();
            sprite4->setPosition(sprite3->getPosition() + Vec2(0.0f, sprite3->getContentSize().height));
            this->addChild(sprite4, 1);
        }
        auto frameSize = Director::getInstance() -> getGLView()->getFrameSize();
        float fieldOfView = 1;
        float aspectRatio = frameSize.width / frameSize.height;

        //// https:  // werplay.medium.com/voronoi-split-screen-a-quick-cocos2d-x-tutorial-12be81fbc98d
        //auto camera1 = Camera::createPerspective(fieldOfView, aspectRatio, 1, 12000);
        //camera1->setCameraFlag(CameraFlag::USER5);
        //auto camera2 = Camera::createPerspective(fieldOfView, aspectRatio, 1, 12000);
        //camera2->setCameraFlag(CameraFlag::USER5);

        //auto fboSize = Director::getInstance()->getGLView()->getFrameSize();
        //auto fbo     = ax::SpriteFrame::create()
        //fbo->create(1, fboSize.width, fboSize.height);
        //fbo->setClearColor(Color4F(0, 0, 0, 0));
        //auto rt = new RenderView;
        //rt->init(fboSize.width, fboSize.height, Texture2D::PixelFormat::RGBA8888);
        //fbo->attachRenderTarget(rt);
        //fbo->getRenderTarget()->getTexture()->setAliasTexParameters();
        //rt->release();
        //auto rtDS = new DepthStencil;
        //rtDS->init(fboSize.width, fboSize.height);
        //fbo->attachDepthStencilTarget(rtDS);
        //rtDS->release();

        //camera1->setFrameBufferObject(fbo);

        //playerScreen1 = Sprite::create();
        //playerScreen1->initWithTexture(fbo->getRenderTarget()->getTexture());
        //this->addChild(playerScreen1);
        //playerScreen1->setScale(frameSize.width / playerScreen1->getContentSize().width,
        //                        frameSize.height / playerScreen1->getContentSize().height);
        //playerScreen1->setTextureRect(Rect(0, 0, fboSize.width / 2, fboSize.height));
        //playerScreen1->setFlippedY(true);
        //playerScreen1->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        //playerScreen1->setPosition(winSize.width / 2, winSize.height / 2);

        //playerScreen2->setTextureRect(Rect(fboSize.width / 2, 0, fboSize.width / 2, fboSize.height));
        //playerScreen2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

        //const float distanceToSplit = 900;
        //Point pointToLookAt         = Player2->getPosition().getMidpoint(Player1->getPosition());
        //float angle                 = Shared::calcAngle(Player::getInstance()->getPosition(), pointToLookAt);
        //camera1 > setPositionZ(3200);  // whatever Position z you want
        //camera2 > setPositionZ(3200);
        //camera->setRotation(angle);
        //playerScreen1->setRotation(angle);
        //playerScreen2->setRotation(angle);
        //if (Player1.distance(pointToLookAt) < distanceToSplit)
        //{
        //    // combine screens
        //    camera1 > setPosition(pointToLookAt);
        //    camera2 > setPosition(pointToLookAt);
        //}
        //else
        //{
        //    camera1 > setPosition(pointToLookAt.x + (Player1->getPosition().distance(pointToLookAt) - distanceToSplit) *
        //                                                cosf(CC_DEGREES_TO_RADIANS(camera1 > getRotation())),
        //                          pointToLookAt.y + (Player1->getPosition().distance(pointToLookAt) - distanceToSplit) *
        //                                                -sinf(CC_DEGREES_TO_RADIANS(camera1 > getRotation())));
        //    camera2->setPosition(pointToLookAt.x + (Player2->getPosition().distance(pointToLookAt) - distanceToSplit) *
        //                                               -cosf(CC_DEGREES_TO_RADIANS(camera2->getRotation())),
        //                         pointToLookAt.y + (Player2->getPosition().distance(pointToLookAt) - distanceToSplit) *
        //                                               sinf(CC_DEGREES_TO_RADIANS(camera2->getRotation())));
        //}

        this->scheduleUpdate();
        return true;
    }

    return false;
}

void Bug12847Layer::update(float dt)
{
    sprite1->setPositionY(sprite1->getPositionY() + 0.01f);
    sprite2->setPositionY(sprite2->getPositionY() + 0.01f);
    sprite3->setPositionY(sprite3->getPositionY() + 0.01f);
    sprite4->setPositionY(sprite4->getPositionY() + 0.01f);

    float distance = sprite1->getPosition().distance(sprite2->getPosition());
    Point midPoint = sprite1->getPosition().getMidpoint(sprite2->getPosition());
}

void Bug12847Layer::onEnter()
{
    BugsTestBase::onEnter();
    Director::getInstance()->setClearColor(Color4F::RED);
}

void Bug12847Layer::onExit()
{
    Director::getInstance()->setClearColor(Color4F::BLACK);
    BugsTestBase::onExit();
}
