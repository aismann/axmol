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

#ifndef _TEXTURECACHE_TEST_H_
#define _TEXTURECACHE_TEST_H_

#include "axmol.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(TextureCacheTests);

class TextureCacheTest : public TestCase
{
public:
    CREATE_FUNC(TextureCacheTest);

    TextureCacheTest();
    ~TextureCacheTest() override;

    void addSprite();
    void loadingCallBack(ax::Texture2D* texture);

    float getDuration() const override { return 3.5f; }
    void onEnter() override;

private:
    ax::Label* _labelLoading;
    ax::Label* _labelPercent;
    int _numberOfSprites;
    int _numberOfLoadedSprites;
};

class TextureCacheUnbindTest : public TestCase
{
public:
    CREATE_FUNC(TextureCacheUnbindTest);

    TextureCacheUnbindTest();
    ~TextureCacheUnbindTest() override;

    void onEnter() override;

private:
    void textureLoadedA(ax::Texture2D* texture);
    void textureLoadedB(ax::Texture2D* texture);
};

#endif  // _TEXTURECACHE_TEST_H_
