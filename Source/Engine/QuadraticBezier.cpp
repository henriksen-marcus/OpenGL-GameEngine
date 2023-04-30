#include "QuadraticBezier.h"
#include "Math.h"

QuadraticBezier::QuadraticBezier(const QVector3D& start) :
	Bezier(start)
{
}

QuadraticBezier::~QuadraticBezier()
{
}

void QuadraticBezier::Init()
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
			QVector3D point = Math::QuadraticBezier(c, (float)k/((float)mResolution - 1));
			mVertices.emplace_back(point, mColor);
			mIndices.push_back(index - 1);
			mIndices.push_back(index);
			index++;
		}

		// Manual last point push, don't need to waste calculation on this.
		mVertices.emplace_back(c.c, mColor);
		// Add the last line segment.
		mIndices.push_back(index - 1);
		mIndices.push_back(index);
		index++;
	}

	MeshComponent::Init();
}

void QuadraticBezier::InitPoints()
{
	mVertices_points.clear();

	for (const auto& [a, b, c] : mCurves)
	{
		mVertices_points.emplace_back(a, QVector3D(1.f, 1.f, 1.f));
		mVertices_points.emplace_back(b, QVector3D(1.f, 0.f, 0.f));
		mVertices_points.emplace_back(c, QVector3D(1.f, 1.f, 1.f));
	}

	Bezier::InitPoints();
}

void QuadraticBezier::AddSegment(const QCurveSegment& segment)
{
	if (mCurves.empty())
		mCurves.push_back(QuadraticCurve{mStart, segment.control, segment.point});
	else
		mCurves.push_back(QuadraticCurve{mCurves.back().c, segment.control, segment.point});
}

QVector3D QuadraticBezier::operator()(float t) const
{
	if (mCurves.empty())
        return mStart;

    float segmentLength = 1.f / mCurves.size();
    int segmentIndex = static_cast<int>(t * mCurves.size());
    if (segmentIndex == mCurves.size()) segmentIndex--;
    float segmentTime = (t - segmentIndex * segmentLength) / segmentLength;
    return mWorldLocation + Math::QuadraticBezier(mCurves[segmentIndex], segmentTime);
}

const QuadraticCurve& QuadraticBezier::operator[](int index) const
{
	return mCurves[index];
}
