#pragma once

#include <Eigen/Eigen>
#include <fuse_core/graph.h>
#include <fuse_variables/orientation_3d_stamped.h>
#include <fuse_variables/position_3d_stamped.h>
#include <fuse_variables/velocity_linear_3d_stamped.h>

#include <beam_variables/imu_bias_gyro_3d_stamped.h>
#include <beam_variables/imu_bias_accel_3d_stamped.h>

namespace beam_models { namespace frame_to_frame {

class ImuState {
public:
  /**
   * @brief default constructor
   */
  ImuState() = default;

  /**
   * @brief constructor when inputting time. Orientation is set to identity,
   * while all other variables are set to zero.
   * @param time timestamp for this imu state
   */
  ImuState(const ros::Time& time);

  /**
   * @brief constructor when inputting orientation, position, and velocity. Bias
   * variables are set to zero.
   * @param time timestamp for this imu state
   * @param orientation orientation for this imu state
   * @param position position for this imu state
   * @param velocity velocity for this imu state
   */
  ImuState(const ros::Time& time, const Eigen::Quaterniond& orientation,
           const Eigen::Vector3d& position, const Eigen::Vector3d& velocity);

  /**
   * @brief constructor when inputting orientation, position, and velocity,
   * gyroscope bias, and acceleration bias
   * @param time timestamp for this imu state
   * @param orientation orientation for this imu state
   * @param position position for this imu state
   * @param velocity velocity for this imu state
   * @param gyrobias gyroscope bias for this imu state
   * @param accelbias acceleration bias for this imu state
   */
  ImuState(const ros::Time& time, const Eigen::Quaterniond& orientation,
           const Eigen::Vector3d& position, const Eigen::Vector3d& velocity,
           const Eigen::Vector3d& gyrobias, const Eigen::Vector3d& accelbias);

  /**
   * @brief update the variables of this ImuState given some graph message
   * @param graph_msg results from some optimizer which should contain the same
   * variable uuids that are stored herein
   * @return true update was successful (i.e., uuids were in the graph message)
   */
  bool Update(const fuse_core::Graph::ConstSharedPtr& graph_msg);

  /**
   * @brief get the number of times this ImuState has its variables updated by
   * some graph optimizer
   * @return number of variable updates
   */

  int Updates() const;

  /**
   * @brief return timestamp associated with this ImuState
   * @return stamp
   */
  ros::Time Stamp() const;

  /**
   * @brief return the current estimate of the orientation
   * @return orientation fuse variable
   */
  fuse_variables::Orientation3DStamped Orientation() const;

  /**
   * @brief return the current estimate of the orientation
   * @return orientation quaternion
   */
  Eigen::Quaterniond OrientationQuat() const;

  /**
   * @brief return the current estimate of the position
   * @return position fuse variable
   */
  fuse_variables::Position3DStamped Position() const;

  /**
   * @brief return the current estimate of the position
   * @return position vector
   */
  Eigen::Vector3d PositionVec() const;

  /**
   * @brief return the current estimate of the velocity
   * @return velocity fuse variable
   */
  fuse_variables::VelocityLinear3DStamped Velocity() const;

  /**
   * @brief return the current estimate of the velocity
   * @return velocity vector
   */
  Eigen::Vector3d VelocityVec() const;

  /**
   * @brief return the current estimate of the gyroscope bias
   * @return gyroscope bias beam variable
   */
  beam_variables::ImuBiasGyro3DStamped GyroBias() const;

  /**
   * @brief return the current estimate of the gyroscope bias
   * @return gyroscope bias vector
   */
  Eigen::Vector3d GyroBiasVec() const;

  /**
   * @brief return the current estimate of the acceleration bias
   * @return acceleration bias beam variable
   */
  beam_variables::ImuBiasAccel3DStamped AccelBias() const;

  /**
   * @brief return the current estimate of the acceleration bias
   * @return acceleration bias vector
   */
  Eigen::Vector3d AccelBiasVec() const;

  /**
   * @brief set orientation using double data type
   */
  void SetOrientation(const double& w, const double& x, const double& y,
                      const double& z);

  /**
   * @brief set orientation using Eigen::Quaterniond data type
   */
  void SetOrientation(const Eigen::Quaterniond& orientation);

  /**
   * @brief set orientation using c-style array
   */
  void SetOrientation(const double* orientation);

  /**
   * @brief set position using double data type
   */
  void SetPosition(const double& x, const double& y, const double& z);

  /**
   * @brief set position using Eigen::Vector3d data type
   */
  void SetPosition(const Eigen::Vector3d& position);

  /**
   * @brief set position using c-style array
   */
  void SetPosition(const double* position);

  /**
   * @brief set velocity using double data type
   */
  void SetVelocity(const double& x, const double& y, const double& z);

  /**
   * @brief set velocity using Eigen::Vector3d data type
   */
  void SetVelocity(const Eigen::Vector3d& velocity);

  /**
   * @brief set velocity using c-style array
   */
  void SetVelocity(const double* velocity);

  /**
   * @brief set gyroscope bias using double data type
   */
  void SetGyroBias(const double& x, const double& y, const double& z);

  /**
   * @brief set gyroscope bias using Eigen::Vector3d data type
   */
  void SetGyroBias(const Eigen::Vector3d& gyrobias);

  /**
   * @brief set gyroscope bias using c-style array
   */
  void SetGyroBias(const double* gyrobias);

  /**
   * @brief set acceleration bias using double data type
   */
  void SetAccelBias(const double& x, const double& y, const double& z);

  /**
   * @brief set acceleration bias using Eigen::Vector3d data type
   */
  void SetAccelBias(const Eigen::Vector3d& accelbias);

  /**
   * @brief set acceleration bias using c-style array
   */
  void SetAccelBias(const double* accelbias);

  /**
   * @brief print relevant information about what is currently contained in this
   * ImuState.
   * @param stream input stream
   */
  void Print(std::ostream& stream = std::cout) const;

private:
  /**
   * @brief instantiates fuse/beam variables contained in this ImuState
   */
  void InstantiateVariables();

  int updates_{0};
  ros::Time stamp_;
  fuse_variables::Orientation3DStamped orientation_;
  fuse_variables::Position3DStamped position_;
  fuse_variables::VelocityLinear3DStamped velocity_;
  beam_variables::ImuBiasGyro3DStamped gyrobias_;
  beam_variables::ImuBiasAccel3DStamped accelbias_;
};

}}  // namespace beam_models::frame_to_frame
