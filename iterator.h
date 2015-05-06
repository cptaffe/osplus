
#ifndef BOS_ITERATOR_H_
#define BOS_ITERATOR_H_

namespace basilisk {

template <typename Type>
class Iterator {
public:
	virtual ~Iterator() {}
	// increment to next item
	virtual void Next() = 0;
	// check if done condition is met
	virtual bool Done() = 0;
	// get payload
	virtual Type &Get() = 0;
};

template <typename Type>
class Iterable {
public:
	virtual ~Iterable() {}
	virtual Iterator<Type> &Iter() const = 0;
};

} // namespace basilisk

#endif // BOS_ITERATOR_H_
