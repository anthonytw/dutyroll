#include "rollduty.hpp"

#include <algorithm>
#include <numeric>
#include <limits>

namespace dutyroll
{
	using namespace std;
	using namespace Eigen;

	VectorXi get_sorted_indices(
		const VectorXd data)
	{
		VectorXi idx(data.size());

		// Generate index range.
		size_t n = 0;
		generate(idx.data(), idx.data() + idx.size(), [&n]{ return n++; });

		// Sort.
		sort(
			idx.data(),
			idx.data() + idx.size(),
			[&data](const int idx1, const int idx2) { return data[idx1] < data[idx2]; });

		return idx;
	}

	size_t find_split(
		const VectorXd data,
		const VectorXi sorted_idx,
		const double threshold,
		const size_t lidx,
		const size_t uidx)
	{
		if (lidx == uidx) return lidx;

		size_t cidx = ((uidx - lidx) / 2) + lidx;

		if (data[sorted_idx[cidx]] < threshold)
			return find_split(data, sorted_idx, threshold, cidx + 1, uidx);
		else
		{
			if (lidx == cidx) return lidx;
			else return find_split(data, sorted_idx, threshold, lidx, cidx);
		}
	}

	VectorXi get_flags(
		const VectorXd data,
		const VectorXi sorted_idx,
		const double threshold)
	{
		VectorXi flags(data.size());
		auto split_idx = find_split(data, sorted_idx, threshold, 0, data.size());
		for (auto i = 0; i < split_idx; ++i)
			flags[sorted_idx[i]] = 0;
		for (auto i = split_idx; i < flags.size(); ++i)
			flags[sorted_idx[i]] = 1;
		return flags;
	}

	VectorXi cumsum(const VectorXi counts)
	{
		VectorXi result(counts.size());
		partial_sum(counts.data(), counts.data() + counts.size(), result.data());
		return result;
	}

	void get_window_params(
		const VectorXd time,
		const double window,
		VectorXi & lidx,
		VectorXi & nobs)
	{
		auto N = time.size();
		lidx.resize(N);
		nobs.resize(N);

		if (N > 0)
		{
			size_t lidx_i = 0;
			size_t uidx_i = 0;

			for (auto i = 0; i < N; ++i, ++uidx_i)
			{
				// Fast-forward lidx to be within the window.
				while ((lidx_i <= uidx_i) && (time[uidx_i] - time[lidx_i]) > window)
					++lidx_i;

				lidx[i] = lidx_i - 1;
				nobs[i] = i - lidx_i + 1;
			}
		}
	}

	Eigen::MatrixXd rollduty_fixed(
		const Eigen::VectorXd data,
		const int window,
		const Eigen::VectorXd thresholds)
	{
		MatrixXd result(thresholds.size(), data.size());
		if ((window < 1) || (data.size() < window))
			return result.setConstant(numeric_limits<double>::quiet_NaN());

		auto sorted_idx = get_sorted_indices(data);

		#pragma omp parallel for
		for (auto ti = 0; ti < thresholds.size(); ++ti)
		{
			auto flags = get_flags(data, sorted_idx, thresholds[ti]);
			auto flags_cumsum = cumsum(flags);
			auto row = result.row(ti);

			size_t lidx = 0;
			size_t uidx = window;
			row.leftCols(window - 1).setConstant(numeric_limits<double>::quiet_NaN());
			row[window - 1] = flags_cumsum[window - 1];
			for (; uidx < data.size(); ++uidx, ++lidx)
				row[uidx] = flags_cumsum[uidx] - flags_cumsum[lidx];
		}
		result /= window;
		return result;
	}

	Eigen::MatrixXd rollduty_variable(
		const Eigen::VectorXd time,
		const Eigen::VectorXd data,
		const double window,
		const Eigen::VectorXd thresholds)
	{
		if (time.size() != data.size())
			throw runtime_error("time and data must contain the same number of elements.");
		MatrixXd result(thresholds.size(), data.size());
		auto sorted_idx = get_sorted_indices(data);

		VectorXi lidx, nobs;
		get_window_params(time, window, lidx, nobs);
		VectorXd nobsf = nobs.cast<double>().array().inverse();

		#pragma omp parallel for
		for (auto ti = 0; ti < thresholds.size(); ++ti)
		{
			auto flags = get_flags(data, sorted_idx, thresholds[ti]);
			auto flags_cumsum = cumsum(flags);
			auto row = result.row(ti);

			for (auto i = 0; i < data.size(); ++i)
			{
				auto lidx_i = lidx[i];
				auto sub = lidx_i < 0 ? 0 : flags_cumsum[lidx_i];
				row[i] = (flags_cumsum[i] - sub) * nobsf[i];
			}
		}
		return result;
	}
}
