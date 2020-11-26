template <class T>
Vector2Temple<T>::Vector2Temple()
{
	x = 0;
	y = 0;
}

template <class T>
Vector2Temple<T>::Vector2Temple(T x, T y)
{
	Vector2Temple::x = x;
	Vector2Temple::y = y;
}

template <class T>
Vector2Temple<T>::~Vector2Temple()
{
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator=(const Vector2Temple<T>& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template <class T>
T& Vector2Temple<T>::operator[](int no)
{
	if (no == 0)
	{
		return x;
	}
	else if (no == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(const Vector2Temple<T>& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(const Vector2Temple<T>& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(T k)
{
	this->x += k;
	this->y += k;

	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(T k)
{
	this->x -= k;
	this->y -= k;

	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(T k)
{
	this->x *= k;
	this->y *= k;

	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator/=(T k)
{
	this->x /= k;
	this->y /= k;

	return *this;
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator+() const
{
	return *this;
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator-() const
{
	return Vector2Temple<T>(-this->x,-this->y);
}

template <class T>
bool Vector2Temple<T>::operator==(const Vector2Temple<T>& vec) const
{
	return ((x == vec.x) && (y == vec.y));
}

template <class T>
bool Vector2Temple<T>::operator!=(const Vector2Temple<T>& vec) const
{
	return !((x == vec.x) && (y == vec.y));
}

template <class T>
bool Vector2Temple<T>::operator>(const Vector2Temple<T>& vec) const
{
	return  ((x > vec.x) && (y > vec.y));
}

template <class T>
bool Vector2Temple<T>::operator>=(const Vector2Temple<T>& vec) const
{
	return ((x >= vec.x) && (y >= vec.y));
}

template <class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& v, T k)
{
	Vector2Temple<T> vec;
	vec.x = v.x + k;
	vec.y = v.y + k;

	return vec;
}

template <class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& v, T k)
{
	Vector2Temple<T> vec;
	vec.x = v.x - k;
	vec.y = v.y - k;

	return vec;
}

template <class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& v, T k)
{
	Vector2Temple<T> vec;
	vec.x = v.x * k;
	vec.y = v.y * k;

	return vec;
}

template <class T>
Vector2Temple<T> operator*(T k, const Vector2Temple<T>& v)
{
	Vector2Temple<T> vec;
	vec.x = k * v.x;
	vec.y = k * v.y;

	return vec;
}

template <class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& v, T k)
{
	Vector2Temple<T> vec;
	vec.x = v.x / k;
	vec.y = v.y / k;

	return vec;
}

template <class T>
Vector2Temple<T> operator%(const Vector2Temple<T>& v, T k)
{
	Vector2Temple<T> vec;
	vec.x = v.x % k;
	vec.y = v.y % k;

	return vec;
}

template <class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, const Vector2Temple<T>& v)
{
	Vector2Temple<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}

template <class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& u, const Vector2Temple<T>& v)
{
	Vector2Temple<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}