
#ifndef BOS_RUNNABLE_H_
#define BOS_RUNNABLE_H_

namespace basilisk {

class Runnable {
public:
	virtual ~Runnable() {}
	virtual void Run() = 0;
};

} // namespace basilisk

#endif // BOS_RUNNABLE_H_
