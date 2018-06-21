#include "isnp/util/DataFrame.hh"

namespace isnp {

namespace util {

static G4String const NO_NAME = "";

DataFrame::DataFrame(DataFrame&& aDataFrame) :
		data(std::move(aDataFrame.data)) {
}

DataFrame::DataFrame(std::unique_ptr<DataPack> aData) :
		data(std::move(aData)) {

}

DataFrame::size_type DataFrame::size() const {

	return data->floatColumns.empty() ?
			0 : data->floatColumns.cbegin()->second.size();

}

G4String const& DataFrame::categoryName(const G4String& columnName,
		CategoryId const id) const {

	auto const it = data->categoryNames.find(columnName);
	if (it == data->categoryNames.cend()) {
		throw NoSuchColumnException();
	}

	auto const nameMap = it->second;
	auto const nameit = nameMap.find(id);
	if (nameit == nameMap.cend()) {
		return NO_NAME;
	} else {
		return nameit->second;
	}

}

const DataFrame::CategoryVector& DataFrame::categoryColumn(
		const G4String& columnName) const {

	auto const it = data->categoryColumns.find(columnName);
	if (it == data->categoryColumns.cend()) {
		throw NoSuchColumnException();
	}

	return it->second;

}

const DataFrame::FloatVector& DataFrame::floatColumn(
		const G4String& columnName) const {

	auto const it = data->floatColumns.find(columnName);
	if (it == data->floatColumns.cend()) {
		throw NoSuchColumnException();
	}

	return it->second;

}

unsigned DataFrame::Precision(const G4String& columnName) const {

	auto const it = data->precisions.find(columnName);
	if (it == data->precisions.cend()) {
		throw NoSuchColumnException();
	}

	return it->second;

}

}

}
