#include "CubicBezier.h"
#include "Math.h"
#include "Source/Utility/Color.h"


CubicBezier::CubicBezier(const QVector3D& start) :
	Bezier(start)
{
}

CubicBezier::~CubicBezier()
{
}

void CubicBezier::Init()
{
	mVertices.clear();
	mIndices.clear();

	// Start at index 1 because we are manually pushing the first point.
	unsigned index = 1;
	bool first = true;

	for (const auto& c : mCurves)
	{
		// Manual first point push, don't need to waste calculation on this.
		mVertices.emplace_back(c.a, mColor);

		if (!first)
		{
			mIndices.push_back(index - 1);
			mIndices.push_back(index);
			index++;
		} else first = false;

		for (unsigned k = 1; k < mResolution - 1; k++)
		{
			QVector3D point = Math::CubicBezier(c, (float)k/((float)mResolution - 1));
			mVertices.emplace_back(point, mColor);
			mIndices.push_back(index - 1);
			mIndices.push_back(index);
			index++;
		}

		// Manual last point push, don't need to waste calculation on this.
		mVertices.emplace_back(c.d, mColor);
		// Add the last line segment.
		mIndices.push_back(index - 1);
		mIndices.push_back(index);
		index++;
	}

	MeshComponent::Init();
}

void CubicBezier::InitPoints()
{
	mVertices_points.clear();

	for (const auto& [a, b, c, d] : mCurves)
	{
		mVertices_points.emplace_back(a, Color::White);
		mVertices_points.emplace_back(b, Color::Red);
		mVertices_points.emplace_back(c, Color::Red);
		mVertices_points.emplace_back(d, Color::White);
	}

	Bezier::InitPoints();
}

void CubicBezier::AddSegment(const CCurveSegment& segment)
{
	if (mCurves.empty())
		mCurves.push_back(CubicCurve{mStart, segment.control1, segment.control2, segment.point});
	else
		mCurves.push_back(CubicCurve{mCurves.back().d, segment.control1, segment.control2, segment.point});
}

QVector3D CubicBezier::operator()(float t) const
{
	if (mCurves.empty())
        return mStart;

    float segmentLength = 1.f / mCurves.size();
    int segmentIndex = static_cast<int>(t * mCurves.size());
    if (segmentIndex == mCurves.size()) segmentIndex--;
    float segmentTime = (t - segmentIndex * segmentLength) / segmentLength;
    return mWorldLocation + Math::CubicBezier(mCurves[segmentIndex], segmentTime);
}



const CubicCurve& CubicBezier::operator[](int index) const
{
	return mCurves[index];
}
