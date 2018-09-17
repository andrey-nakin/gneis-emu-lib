#ifndef isnp_util_NonCopyable_hh
#define isnp_util_NonCopyable_hh

namespace isnp {

namespace util {

class NonCopyable {

protected:

	NonCopyable() = default;

	NonCopyable(NonCopyable&) = delete;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable(volatile NonCopyable&) = delete;
	NonCopyable(const volatile NonCopyable&) = delete;

	NonCopyable(NonCopyable&&) = delete;

	NonCopyable& operator=(NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
	NonCopyable& operator=(volatile NonCopyable&) = delete;
	NonCopyable& operator=(const volatile NonCopyable&) = delete;

	NonCopyable& operator=(NonCopyable&&) = delete;

public:

	virtual ~NonCopyable() = default;

};

}

}

#endif	//	isnp_util_NonCopyable_hh
