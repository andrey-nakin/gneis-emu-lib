#include <sstream>
#include <gtest/gtest.h>
#include "isnp/util/DataFrameLoader.hh"

namespace isnp {

namespace util {

TEST(DataFrameLoader, Generic) {
	std::stringstream ss;
	ss << " # a comment\n" << "A\tC\tB\tD\n" << "\t# another comment\n"
			<< "1.23456e20\t0\t1.2345e-20\t0\n"
			<< "\t \t# yet another comment\n"
			<< "2.34567e20\t0\t2.3456e-20\t0\n";

	std::set<G4String> floatColumns;
	floatColumns.insert("A");
	floatColumns.insert("B");

	std::set<G4String> categoryColumns;
	DataFrameLoader loader(floatColumns, categoryColumns);

	DataFrame const df = loader.load(ss);
	EXPECT_EQ(2, df.Size());
	EXPECT_EQ(2, df.FloatColumn("A").size());
	EXPECT_EQ(2, df.FloatColumn("B").size());
	EXPECT_EQ(6, df.Precision("A"));
	EXPECT_EQ(5, df.Precision("B"));
	EXPECT_EQ(1.23456e20f, df.FloatColumn("A")[0]);
	EXPECT_EQ(1.2345e-20f, df.FloatColumn("B")[0]);
	EXPECT_EQ(2.34567e20f, df.FloatColumn("A")[1]);
	EXPECT_EQ(2.3456e-20f, df.FloatColumn("B")[1]);
}

}

}
