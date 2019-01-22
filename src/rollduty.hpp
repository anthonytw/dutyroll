#pragma once

#include <Eigen/Dense>

namespace dutyroll
{
	Eigen::MatrixXd rollduty_fixed(
		const Eigen::VectorXd data,
		const int window,
		const Eigen::VectorXd thresholds);

	Eigen::MatrixXd rollduty_variable(
		const Eigen::VectorXd time,
		const Eigen::VectorXd data,
		const double window,
		const Eigen::VectorXd thresholds);
}
