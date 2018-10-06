#include <algorithm>
#include <cctype>
#include <string>
#include "isnp/util/DataFrameLoader.hh"

namespace isnp {

namespace util {

static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

static std::vector<std::string> tokenize(const std::string& s, char const c) {

	auto end = s.cend();
	auto start = end;

	std::vector<std::string> v;
	for (auto it = s.cbegin(); it != end; ++it) {
		if (*it != c) {
			if (start == end) {
				start = it;
			}
			continue;
		}
		if (start != end) {
			v.emplace_back(start, it);
			start = end;
		}
	}

	if (start != end) {
		v.emplace_back(start, end);
	}

	return v;

}

static unsigned detectPrecision(std::string const& s) {
	auto const p = std::find_if(std::begin(s), std::end(s), [](auto ch) {
		return ch == 'e' || ch == 'E';
	});
	auto const result = std::distance(std::begin(s), p);
	auto const dp = std::find(std::begin(s), p, '.');
	return dp == std::end(s) ? result : result - 1;
}

DataFrameLoader::NoColumnException::NoColumnException(G4String const& aColName) :
		colName(aColName) {
}

DataFrameLoader::NoValueException::NoValueException(G4String const& aColName,
		unsigned const aLineNo) :
		colName(aColName), lineNo(aLineNo) {
}

DataFrameLoader::DataFrameLoader(std::set<G4String> const& aFloatColumns,
		std::set<G4String> const& aCategoryColumns) :
		floatColumns(aFloatColumns), categoryColumns(aCategoryColumns), commentChar(
				'#'), separatorChar('\t') {

}

DataFrame DataFrameLoader::load(std::istream& is) {

	unsigned lineNo = 0;
	std::string line;
	bool isfirst = true, precisionDetected = false;
	std::vector<std::string> columnNames;
	std::vector<std::size_t> categoryIndices, floatIndices;
	std::map<G4String, std::map<G4String, DataFrame::CategoryId>> idMap;
	std::vector<DataFrame::CategoryVectorMap::iterator> categoryVectors;
	std::vector<DataFrame::FloatVectorMap::iterator> floatVectors;
	auto data = std::make_unique<DataFrame::DataPack>();
	DataFrame::CategoryVector const emptyCategoryVector;
	DataFrame::FloatVector const emptyFloatVector;
	std::size_t lastCategoryIndex = 0, lastFloatIndex = 0;

	while (is.good()) {
		std::getline(is, line);
		lineNo++;
		ltrim(line);
		if (line.empty()) {
			continue;
		}
		if (line[0] == commentChar) {
			continue;
		}

		if (isfirst) {
			// read column names
			columnNames = tokenize(line, separatorChar);

			std::for_each(std::begin(categoryColumns),
					std::end(categoryColumns),
					[&](auto cn) {
						std::string const sn = cn;
						auto const pos = std::find(std::begin(columnNames), std::end(columnNames), sn);
						if (pos == std::end(columnNames)) {
							throw NoColumnException(cn);
						}
						categoryIndices.push_back(std::distance(std::begin(columnNames), pos));
						categoryVectors.push_back(data->categoryColumns.insert(data->categoryColumns.end(), std::pair<G4String, DataFrame::CategoryVector>(cn, emptyCategoryVector)));
					});
			lastCategoryIndex = categoryIndices.size();

			std::for_each(std::begin(floatColumns), std::end(floatColumns),
					[&](auto cn) {
						std::string const sn = cn;
						auto const pos = std::find(std::begin(columnNames), std::end(columnNames), sn);
						if (pos == std::end(columnNames)) {
							throw NoColumnException(cn);
						}
						floatIndices.push_back(std::distance(std::begin(columnNames), pos));
						floatVectors.push_back(data->floatColumns.insert(data->floatColumns.end(), std::pair<G4String, DataFrame::FloatVector>(cn, emptyFloatVector)));
					});
			lastFloatIndex = floatIndices.size();

			isfirst = false;
			continue;
		}

		std::vector<std::string> const v = tokenize(line, separatorChar);
		if (!precisionDetected) {

			for (std::size_t i = 0; i < lastFloatIndex; i++) {
				auto const idx = floatIndices[i];
				if (idx >= v.size()) {
					throw NoValueException(columnNames[idx], lineNo);
				}
				data->precisions[columnNames[idx]] = detectPrecision(v[idx]);
			};

			precisionDetected = true;
		}

		for (std::size_t i = 0; i < lastCategoryIndex; i++) {
			auto const idx = categoryIndices[i];
			auto const colName = columnNames[idx];
			if (idx >= v.size()) {
				throw NoValueException(colName, lineNo);
			}

			auto im = idMap.find(colName);
			if (idMap.end() == im) {
				idMap[colName] = std::map<G4String, DataFrame::CategoryId>();
				im = idMap.find(colName);
				data->categoryNames[colName] = DataFrame::CategoryMap();
			}

			auto const value = v[idx];
			auto id = im->second.find(value);
			if (im->second.end() == id) {
				auto const newId =
						static_cast<DataFrame::CategoryId>(im->second.size());
				im->second[value] = newId;
				id = im->second.find(value);
				data->categoryNames[colName][newId] = value;
			}

			categoryVectors[i]->second.push_back(id->second);
		};

		for (std::size_t i = 0; i < lastFloatIndex; i++) {
			auto const idx = floatIndices[i];
			if (idx >= v.size()) {
				throw NoValueException(columnNames[idx], lineNo);
			}

			floatVectors[i]->second.push_back(std::stof(v[idx]));
		};
	}

	return DataFrame(std::move(data));

}

}

}
