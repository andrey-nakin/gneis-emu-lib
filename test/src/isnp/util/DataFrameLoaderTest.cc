#include <sstream>
#include <gtest/gtest.h>
#include "isnp/util/DataFrameLoader.hh"

namespace isnp {

namespace util {

TEST(DataFrameLoader, Generic)
{
	std::stringstream ss;
	ss << " # a comment\n" << "A\tC\tB\tD\n" << "1.23456e20\t0\t1.23456e-20\t0\n" << "2.34567e20\t0\t2.34567e-20\t0\n";

	std::set<G4String> floatColumns;
	floatColumns.insert("A");
	floatColumns.insert("B");

	std::set<G4String> categoryColumns;
	DataFrameLoader loader(floatColumns, categoryColumns);

	DataFrame const df = loader.load(ss);
	EXPECT_EQ(2, df.size());
	EXPECT_EQ(2, df.floatColumn("A").size());
	EXPECT_EQ(2, df.floatColumn("B").size());
	EXPECT_EQ(1.23456e20f, df.floatColumn("A")[0]);
	EXPECT_EQ(1.23456e-20f, df.floatColumn("B")[0]);
	EXPECT_EQ(2.34567e20f, df.floatColumn("A")[1]);
	EXPECT_EQ(2.34567e-20f, df.floatColumn("B")[1]);
}

}

}
