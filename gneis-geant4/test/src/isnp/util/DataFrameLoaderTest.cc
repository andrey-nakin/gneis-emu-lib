#include <sstream>
#include <gtest/gtest.h>
#include "isnp/util/DataFrameLoader.hh"

namespace isnp {

namespace util {

TEST(DataFrameLoader, Generic) {
	std::stringstream ss;
	ss << "\n\n" << " # a comment\n\n" << "A\tC\tB\tE\tD\n"
			<< "\t# another comment\n" << "1.23456e20\tabc\t1.2345e-20\ta\t0\n"
			<< "\t \t# yet another comment\n\n"
			<< "2.34567e20\tcba\t2.3456e-20\tb\t0\n"
			<< "2.34567e20\tabc\t2.3456e-20\ta\t0\n";

	std::set<G4String> floatColumns;
	floatColumns.insert("A");
	floatColumns.insert("B");

	std::set<G4String> categoryColumns;
	categoryColumns.insert("E");
	categoryColumns.insert("C");
	DataFrameLoader loader(floatColumns, categoryColumns);

	DataFrame const df = loader.load(ss);
	EXPECT_EQ(3, df.Size());

	EXPECT_EQ(3, df.CategoryColumn("E").size());
	EXPECT_EQ(3, df.CategoryColumn("C").size());

	EXPECT_EQ("a", df.CategoryName("E", 0));
	EXPECT_EQ("b", df.CategoryName("E", 1));
	EXPECT_EQ("abc", df.CategoryName("C", 0));
	EXPECT_EQ("cba", df.CategoryName("C", 1));

	EXPECT_EQ(0, df.CategoryColumn("E")[0]);
	EXPECT_EQ(0, df.CategoryColumn("C")[0]);
	EXPECT_EQ(1, df.CategoryColumn("E")[1]);
	EXPECT_EQ(1, df.CategoryColumn("C")[1]);
	EXPECT_EQ(0, df.CategoryColumn("E")[2]);
	EXPECT_EQ(0, df.CategoryColumn("C")[2]);

	EXPECT_EQ("a", df.CategoryValue("E", 0));
	EXPECT_EQ("abc", df.CategoryValue("C", 0));
	EXPECT_EQ("b", df.CategoryValue("E", 1));
	EXPECT_EQ("cba", df.CategoryValue("C", 1));
	EXPECT_EQ("a", df.CategoryValue("E", 2));
	EXPECT_EQ("abc", df.CategoryValue("C", 2));

	EXPECT_EQ(3, df.FloatColumn("A").size());
	EXPECT_EQ(3, df.FloatColumn("B").size());

	EXPECT_EQ(6, df.Precision("A"));
	EXPECT_EQ(5, df.Precision("B"));

	EXPECT_EQ(1.23456e20f, df.FloatColumn("A")[0]);
	EXPECT_EQ(1.2345e-20f, df.FloatColumn("B")[0]);
	EXPECT_EQ(2.34567e20f, df.FloatColumn("A")[1]);
	EXPECT_EQ(2.3456e-20f, df.FloatColumn("B")[1]);

	EXPECT_EQ(1.23456e20f, df.FloatValue("A", 0));
	EXPECT_EQ(1.2345e-20f, df.FloatValue("B", 0));
	EXPECT_EQ(2.34567e20f, df.FloatValue("A", 1));
	EXPECT_EQ(2.3456e-20f, df.FloatValue("B", 1));

}

}

}
