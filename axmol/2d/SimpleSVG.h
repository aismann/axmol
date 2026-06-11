/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

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

#pragma once

 /// @cond DO_NOT_SHOW

#include <cmath>
#include <vector>

namespace ax
{
    class AX_DLL SimpleSVG : public Object
    {
    public:
        struct CubicBezier
        {
            Vec2 p0, p1, p2, p3;
        };

        struct SvgSubpath
        {
            std::vector<ax::Vec2> points;
            ax::Color color;
            bool closed = false;
        };

        static std::vector<CubicBezier> svgArcToBezier(Vec2 p0, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, Vec2 p1);
        static std::vector<ax::Vec2> svgArcToPoints(ax::Vec2 p0, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, ax::Vec2 p1, int segments = 32);  // number of output points
        static void flattenCubic(const ax::Vec2& p0, const ax::Vec2& p1, const ax::Vec2& p2, const ax::Vec2& p3, std::vector<ax::Vec2>& out, int segments);
        static void flattenQuad(const ax::Vec2& p0, const ax::Vec2& p1, const ax::Vec2& p2, std::vector<ax::Vec2>& out, int segments);
        static std::vector<SimpleSVG::SvgSubpath> parseSvgPathToAxmolPolygons(const std::string& d, int curveSegments = 16, int arcSegments = 32);


        static void SvgPathStream(const std::string& str);

        static void skipWs();
        static bool readCommand(char& c);
        static bool readFloat(float& v);
        static bool readString(std::string& v);

        // Delete constructor to prevent instantiation
        SimpleSVG() = delete;
        SimpleSVG(const SimpleSVG&) = delete;
        SimpleSVG& operator=(const SimpleSVG&) = delete;

    private:
        static inline char* s;// = "Some string value";
    };

}  // namespace ax

/// @endcond
