#include <algorithm>
#include <cmath>

#include "gneis/testutil/Stat.hh"

gneis::testutil::Stat::Stat() :
		count(0), sum(0.0), sum2(0.0), maxValue(0.0) {

}

G4double gneis::testutil::Stat::GetMean() const {
	return count ? sum / count : 0.0;
}

G4double gneis::testutil::Stat::GetMeanStd() const {
	return count > 0 ? GetStd() / std::sqrt(count) : 0.0;
}

G4double gneis::testutil::Stat::GetStd() const {
	auto const var = GetVar();
	return var < 0.0 ? 0.0 : std::sqrt(var);
}

G4double gneis::testutil::Stat::GetVar() const {
	return count > 1 ? (sum2 - sum * sum / count) / (count - 1) : 0.0;
}

G4double gneis::testutil::Stat::GetMin() const {
	return minValue;
}

G4double gneis::testutil::Stat::GetMax() const {
	return maxValue;
}

gneis::testutil::Stat& gneis::testutil::Stat::operator+=(G4double const value) {
	sum += value;
	sum2 += value * value;

	if (count > 0) {
		minValue = std::min(minValue, value);
		maxValue = std::max(maxValue, value);
	} else {
		minValue = maxValue = value;
	}

	++count;

	return *this;
}

bool gneis::testutil::Stat::Is(G4double const value) const {
	auto const ConfLevel999Quantile = 3.29;

	auto const mean = GetMean();
	auto const sampleStd = GetMeanStd();

	return value > mean - sampleStd * ConfLevel999Quantile
			&& value < mean + sampleStd * ConfLevel999Quantile;
}
