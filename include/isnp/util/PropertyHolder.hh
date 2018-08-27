#ifndef isnp_util_PropertyHolder_hh
#define isnp_util_PropertyHolder_hh

namespace isnp {

namespace util {

template<typename Properties>
class PropertyHolder {

	Properties props;

public:

	typedef Properties prop_type;

	PropertyHolder(const Properties& aProps) :
			props(aProps) {
	}

	PropertyHolder(Properties&& aProps) :
			props(aProps) {
	}

	Properties const& GetProps() const {

		return props;

	}

	Properties& GetProps() {

		return props;

	}

};

}

}

#endif	//	isnp_util_PropertyHolder_hh
