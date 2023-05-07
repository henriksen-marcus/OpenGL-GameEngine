#pragma once

/**
 * \brief Zigzag interpolates between two values.
 * \tparam T Datatype, e.g. float, int
 */
template<class T>
class ZigZag
{
public:
	ZigZag(const T& min, const T& max, const T& increment);
	virtual ~ZigZag();

	/**
	 * \return The current t value.
	 * \remarks The t value is incremented when calling this function.
	 */
	T operator()();

	/**
	 * \return The current t value.
	 * \remarks Does not increment the t value.
	 */
	T Get() const { return t; }

	T mMin, mMax, mIncrement;

protected:
	bool mDirection = true;
	T t;
};


template <class T>
ZigZag<T>::ZigZag(const T& min, const T& max, const T& increment)
	: mMin(min), mMax(max), mIncrement(increment), t(min)
{
}

template <class T>
ZigZag<T>::~ZigZag()
{
}

template <class T>
T ZigZag<T>::operator()()
{
	T value = std::clamp(t, mMin, mMax);
	t = mDirection ? t + mIncrement : t - mIncrement;
	if (t >= mMax || t <= mMin) mDirection = !mDirection;
	return value;
}
