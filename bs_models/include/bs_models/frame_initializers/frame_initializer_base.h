#pragma once

#include <Eigen/Dense>
#include <ros/ros.h>
#include <tf2/buffer_core.h>

#include <bs_common/pose_lookup.h>

namespace bs_models { namespace frame_initializers {

static std::string frame_initializer_error_msg = "";

/**
 * @brief This base class shows the contract between a FrameInitializer class.
 * The goal of this class is to initialize the pose of a frame given some
 * timestamp. This can simply be from a published topic, or can use an odometry
 * methodology with input sensor data. For more information on frames, see the
 * PoseLookup and ExtrinsicsLookupOnline classes.
 *
 * All input data to the derived classes should be added in a custom
 * constructor. The constructor also needs to initialize pose_lookup_ and poses_
 *
 */
class FrameInitializerBase {
public:
  /**
   * @brief Gets estimated pose of sensor frame wrt world frame using
   * Poselookup.
   * @param T_WORLD_SENSOR reference to result
   * @param time stamp of the frame being initialized
   * @param sensor_frame sensor frame id.
   * @return true if pose lookup was successful
   */
  bool GetEstimatedPose(Eigen::Matrix4d& T_WORLD_SENSOR, const ros::Time& time,
                        const std::string& sensor_frame_id,
                        std::string& error_msg = frame_initializer_error_msg) {
    return pose_lookup_->GetT_WORLD_SENSOR(T_WORLD_SENSOR, sensor_frame_id,
                                           time, error_msg);
  };

protected:
  std::string authority_;
  std::shared_ptr<bs_common::PoseLookup> pose_lookup_;
};

}} // namespace bs_models::frame_initializers