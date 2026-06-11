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

#include "SimpleSVG.h"

using namespace ax;

//
//struct CubicBezier
//{
//    Vec2 p0, p1, p2, p3;
//};
//
//
//struct SvgSubpath
//{
//    std::vector<ax::Vec2> points;
//    ax::Color color;
//    bool closed = false;
//};


std::vector<SimpleSVG::CubicBezier> SimpleSVG::svgArcToBezier(Vec2 p0, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, Vec2 p1)
{
    std::vector<CubicBezier> curves;

    // Step 1: Handle degenerate cases
    if (rx == 0 || ry == 0)
    {
        curves.push_back({ p0, p0, p1, p1 });
        return curves;
    }

    float phi = AX_DEGREES_TO_RADIANS(xAxisRotation);
    float cosphi = std::cos(phi);
    float sinphi = std::sin(phi);

    // Step 2: Transform into arc coordinate space
    float dx = (p0.x - p1.x) * 0.5f;
    float dy = (p0.y - p1.y) * 0.5f;

    float x1 = cosphi * dx + sinphi * dy;
    float y1 = -sinphi * dx + cosphi * dy;

    float rx2 = rx * rx;
    float ry2 = ry * ry;
    float x12 = x1 * x1;
    float y12 = y1 * y1;

    // Step 3: Correct radii if too small
    float lambda = x12 / rx2 + y12 / ry2;
    if (lambda > 1.0f)
    {
        float s = std::sqrt(lambda);
        rx *= s;
        ry *= s;
        rx2 = rx * rx;
        ry2 = ry * ry;
    }

    // Step 4: Compute center
    float sign = (largeArcFlag == sweepFlag) ? -1.0f : 1.0f;
    float num = rx2 * ry2 - rx2 * y12 - ry2 * x12;
    float den = rx2 * y12 + ry2 * x12;
    float c = std::sqrt(std::max(0.0f, num / den)) * sign;

    float cx1 = c * (rx * y1 / ry);
    float cy1 = c * (-ry * x1 / rx);

    float cx = cosphi * cx1 - sinphi * cy1 + (p0.x + p1.x) * 0.5f;
    float cy = sinphi * cx1 + cosphi * cy1 + (p0.y + p1.y) * 0.5f;

    // Step 5: Compute angles
    auto angle = [](float ux, float uy, float vx, float vy) {
        float dot = ux * vx + uy * vy;
        float len = std::sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy));
        float r = std::max(-1.0f, std::min(1.0f, dot / len));
        float a = std::acos(r);
        if (ux * vy - uy * vx < 0)
            a = -a;
        return a;
        };

    float theta1 = angle(1, 0, (x1 - cx1) / rx, (y1 - cy1) / ry);
    float dtheta = angle((x1 - cx1) / rx, (y1 - cy1) / ry, (-x1 - cx1) / rx, (-y1 - cy1) / ry);

    if (!sweepFlag && dtheta > 0)
        dtheta -= 2 * 3.14159265358979323846f;
    if (sweepFlag && dtheta < 0)
        dtheta += 2 * 3.14159265358979323846f;

    // Step 6: Split arc into segments of max 90°
    int segments = std::ceil(std::fabs(dtheta) / (3.14159265358979323846f / 2));
    float dt = dtheta / segments;

    for (int i = 0; i < segments; i++)
    {
        float t1 = theta1 + dt * i;
        float t2 = t1 + dt;

        float cos1 = std::cos(t1), sin1 = std::sin(t1);
        float cos2 = std::cos(t2), sin2 = std::sin(t2);

        // Endpoints
        Vec2 pA = { cx + rx * (cosphi * cos1 - sinphi * sin1), cy + ry * (sinphi * cos1 + cosphi * sin1) };
        Vec2 pB = { cx + rx * (cosphi * cos2 - sinphi * sin2), cy + ry * (sinphi * cos2 + cosphi * sin2) };

        // Derivatives
        float alpha = std::tan(dt / 4) * 4 / 3;

        Vec2 pA1 = { pA.x - alpha * (rx * (cosphi * sin1 + sinphi * cos1)),
            pA.y - alpha * (ry * (sinphi * sin1 - cosphi * cos1)) };
        Vec2 pB1 = { pB.x + alpha * (rx * (cosphi * sin2 + sinphi * cos2)),
            pB.y + alpha * (ry * (sinphi * sin2 - cosphi * cos2)) };

        curves.push_back({ pA, pA1, pB1, pB });
    }

    return curves;
}

std::vector<ax::Vec2> SimpleSVG::svgArcToPoints(ax::Vec2 p0,
    float rx,
    float ry,
    float xAxisRotation,
    bool largeArcFlag,
    bool sweepFlag,
    ax::Vec2 p1,
    int segments)  // number of output points
{
    std::vector<ax::Vec2> out;
    out.reserve(segments + 1);

    if (rx == 0 || ry == 0)
    {
        out.push_back(p0);
        out.push_back(p1);
        return out;
    }

    float phi = AX_DEGREES_TO_RADIANS(xAxisRotation);
    float cosphi = std::cos(phi);
    float sinphi = std::sin(phi);

    float dx = (p0.x - p1.x) * 0.5f;
    float dy = (p0.y - p1.y) * 0.5f;

    float x1 = cosphi * dx + sinphi * dy;
    float y1 = -sinphi * dx + cosphi * dy;

    float rx2 = rx * rx;
    float ry2 = ry * ry;
    float x12 = x1 * x1;
    float y12 = y1 * y1;

    float lambda = x12 / rx2 + y12 / ry2;
    if (lambda > 1.0f)
    {
        float s = std::sqrt(lambda);
        rx *= s;
        ry *= s;
        rx2 = rx * rx;
        ry2 = ry * ry;
    }

    float sign = (largeArcFlag == sweepFlag) ? -1.0f : 1.0f;
    float num = rx2 * ry2 - rx2 * y12 - ry2 * x12;
    float den = rx2 * y12 + ry2 * x12;
    float c = std::sqrt(std::max(0.0f, num / den)) * sign;

    float cx1 = c * (rx * y1 / ry);
    float cy1 = c * (-ry * x1 / rx);

    float cx = cosphi * cx1 - sinphi * cy1 + (p0.x + p1.x) * 0.5f;
    float cy = sinphi * cx1 + cosphi * cy1 + (p0.y + p1.y) * 0.5f;

    auto angle = [](float ux, float uy, float vx, float vy) {
        float dot = ux * vx + uy * vy;
        float len = std::sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy));
        float r = std::max(-1.0f, std::min(1.0f, dot / len));
        float a = std::acos(r);
        if (ux * vy - uy * vx < 0)
            a = -a;
        return a;
        };

    float theta1 = angle(1, 0, (x1 - cx1) / rx, (y1 - cy1) / ry);
    float dtheta = angle((x1 - cx1) / rx, (y1 - cy1) / ry, (-x1 - cx1) / rx, (-y1 - cy1) / ry);

    if (!sweepFlag && dtheta > 0)
        dtheta -= 2 * M_PI;
    if (sweepFlag && dtheta < 0)
        dtheta += 2 * M_PI;

    // Generate points
    for (int i = 0; i <= segments; i++)
    {
        float t = theta1 + dtheta * (float(i) / segments);
        float cosT = std::cos(t);
        float sinT = std::sin(t);

        float x = cx + rx * (cosphi * cosT - sinphi * sinT);
        float y = cy + -ry * (sinphi * cosT + cosphi * sinT);

        out.emplace_back(x, y);
    }

    return out;
}

//=============================================================




// === 3. Cubic & quadratic flattening

void SimpleSVG::flattenCubic(const ax::Vec2& p0,
    const ax::Vec2& p1,
    const ax::Vec2& p2,
    const ax::Vec2& p3,
    std::vector<ax::Vec2>& out,
    int segments)
{
    Vec2 pm1 = { 1, 1 };
    for (int i = 1; i <= segments; ++i)
    {
        float t = float(i) / segments;
        float u = 1.0f - t;
        float b0 = u * u * u;
        float b1 = 3 * u * u * t;
        float b2 = 3 * u * t * t;
        float b3 = t * t * t;
        ax::Vec2 p = pm1 * p0 * b0 + p1 * b1 + p2 * b2 + p3 * b3;
        out.push_back(p);
    }
}

void SimpleSVG::flattenQuad(const ax::Vec2& p0, const ax::Vec2& p1, const ax::Vec2& p2, std::vector<ax::Vec2>& out, int segments)
{
    for (int i = 1; i <= segments; ++i)
    {
        float t = float(i) / segments;
        float u = 1.0f - t;
        float b0 = u * u;
        float b1 = 2 * u * t;
        float b2 = t * t;
        ax::Vec2 p = p0 * b0 + p1 * b1 + p2 * b2;
        out.push_back(p);
    }
}


//==== 4. Tiny tokenizer for numbers/commands

void SimpleSVG::SvgPathStream(const std::string& str)
{
    s = new char[str.size()];; // Ensure enough space for string + null terminator
    size_t len = str.copy(s, str.size());
    s[len] = '\0'; // Null-terminate
}


void SimpleSVG::skipWs()
{
    while (*s && (std::isspace((unsigned char)*s) || *s == ','))
        ++s;
}

//bool SimpleSVG::eof() { return *s == '\0'; }

bool SimpleSVG::readCommand(char& c)
{
    skipWs();
    if (!*s)
        return false;
    if (std::isalpha((unsigned char)*s) || (*s == '#'))
    {
        c = *s++;
        return true;
    }
    return false;
}

bool SimpleSVG::readFloat(float& v)
{
    skipWs();
    if (!*s)
        return false;
    char* end = nullptr;
    v = std::strtof(s, &end);
    if (end == s)
        return false;
    s = end;
    return true;
}
bool SimpleSVG::readString(std::string& v)
{
    skipWs();
    if (!*s)
        return false;
    v = s;
    v = v.substr(0, v.find_first_of(", \t\n\r", 1));
    AXLOGD("v: '{}'", v);
    char* end = s + v.length() + 1;
    if (end == s)
        return false;
    s = end;
    AXLOGD("ss: '{}'", s);
    return true;
}




// Full SVG path → Axmol polygons Supports    : M m L l H h V v C c Q q A a Z z #HEXCOLOR.
std::vector<SimpleSVG::SvgSubpath> SimpleSVG::parseSvgPathToAxmolPolygons(const std::string& str, int curveSegments, int arcSegments)
{
    s = new char[str.size()];; // Ensure enough space for string + null terminator
    size_t len = str.copy(s, str.size());
    s[len] = '\0'; // Null-terminate

    std::vector<SvgSubpath> subpaths;
    std::string st = s;

    ax::Vec2 curr(0, 0), start(0, 0);
    ax::Vec2 lastCtrl(0, 0);
    char cmd = 0;

    auto newSubpath = [&]() {
        subpaths.emplace_back();
        };

    while (*s != '\0')
    {
        AXLOGD("s:   {}", s);
        char c;
        if (!readCommand(c))
        {
            if (!cmd)
                break;
            c = cmd;  // implicit command repetition
        }
        else
        {
            cmd = c;
        }
        AXLOGD("st.c: '{}'", s);
        bool rel = (c >= 'a' && c <= 'z');
        char C = std::toupper(c);

        if (C == 'M')
        {
            float x, y;
            if (!readFloat(x) || !readFloat(y))
                break;
            if (rel)
            {
                x += curr.x;
                y += curr.y;
            }

            newSubpath();
            subpaths.back().points.clear();
            curr = { x, y };
            start = curr;
            subpaths.back().points.push_back(curr);

            // subsequent pairs are implicit L
            while (true)
            {
                float x2, y2;
                if (!readFloat(x2) || !readFloat(y2))
                    break;
                if (rel)
                {
                    x2 += curr.x;
                    y2 += curr.y;
                }
                curr = { x2, y2 };
                subpaths.back().points.push_back(curr);
                cmd = rel ? 'l' : 'L';
            }
        }
        else if (C == 'L' || C == 'H' || C == 'V')
        {
            while (true)
            {
                float x = curr.x, y = curr.y;
                if (C == 'L')
                {
                    if (!readFloat(x) || !readFloat(y))
                        break;
                    if (rel)
                    {
                        x += curr.x;
                        y += curr.y;
                    }
                }
                else if (C == 'H')
                {
                    if (!readFloat(x))
                        break;
                    if (rel)
                        x += curr.x;
                    y = curr.y;
                }
                else
                {  // V
                    if (!readFloat(y))
                        break;
                    if (rel)
                        y += curr.y;
                    x = curr.x;
                }
                curr = { x, y };
                subpaths.back().points.push_back(curr);
            }
        }
        else if (C == 'C')
        {
            while (true)
            {
                float x1, y1, x2, y2, x, y;
                if (!readFloat(x1) || !readFloat(y1) || !readFloat(x2) || !readFloat(y2) ||
                    !readFloat(x) || !readFloat(y))
                    break;

                if (rel)
                {
                    x1 += curr.x;
                    y1 += curr.y;
                    x2 += curr.x;
                    y2 += curr.y;
                    x += curr.x;
                    y += curr.y;
                }

                std::vector<ax::Vec2> tmp;
                tmp.reserve(curveSegments);
                flattenCubic(curr, { x1, y1 }, { x2, y2 }, { x, y }, tmp, curveSegments);
                subpaths.back().points.insert(subpaths.back().points.end(), tmp.begin(), tmp.end());

                curr = { x, y };
                lastCtrl = { x2, y2 };
            }
        }
        else if (C == 'Q')
        {
            while (true)
            {
                float x1, y1, x, y;
                if (!readFloat(x1) || !readFloat(y1) || !readFloat(x) || !readFloat(y))
                    break;

                if (rel)
                {
                    x1 += curr.x;
                    y1 += curr.y;
                    x += curr.x;
                    y += curr.y;
                }

                std::vector<ax::Vec2> tmp;
                tmp.reserve(curveSegments);
                flattenQuad(curr, { x1, y1 }, { x, y }, tmp, curveSegments);
                subpaths.back().points.insert(subpaths.back().points.end(), tmp.begin(), tmp.end());

                curr = { x, y };
                lastCtrl = { x1, y1 };
            }
        }
        else if (C == 'A')
        {
            while (true)
            {
                float rx, ry, xRot, laf, sf, x, y;
                if (!readFloat(rx) || !readFloat(ry) || !readFloat(xRot) || !readFloat(laf) ||
                    !readFloat(sf) || !readFloat(x) || !readFloat(y))
                    break;

                if (rel)
                {
                    x += curr.x;
                    y += curr.y;
                }

                auto pts = svgArcToPoints(curr, rx, ry, xRot, laf != 0.0f, sf != 0.0f, { x, y }, arcSegments);

                // skip first (curr) to avoid duplicate
                subpaths.back().points.insert(subpaths.back().points.end(), pts.begin() + 1, pts.end());

                curr = { x, y };
            }
        }
        else if (C == 'Z')
        {
            subpaths.back().closed = true;
            subpaths.back().points.push_back(start);
            curr = start;

        }
        else if (C == '#')  // color stuff
        {

            std::string sc;
            subpaths.back().closed = true;

            unsigned int red = 255;
            unsigned int green = 255;
            unsigned int blue = 255;
            unsigned int alpha = 255;

            if (sc.length() > 5)
            {

                red = std::stoul(sc.substr(2, 2), nullptr, 16);
                green = std::stoul(sc.substr(2, 2), nullptr, 16);
                blue = std::stoul(sc.substr(4, 2), nullptr, 16);
                if (sc.length() > 6)
                {
                    alpha = std::stoul(sc.substr(6, 2), nullptr, 16);
                }
            }

            ax::Color color = ax::Color(red, green, blue, alpha);

            subpaths.back().color = color;
            curr = start;
            AXLOGD("Color: {}", sc);
        }
        else
        {
            // unsupported command – you can extend here
            break;
        }
    }
    //  delete [] s;
    return subpaths;
}
