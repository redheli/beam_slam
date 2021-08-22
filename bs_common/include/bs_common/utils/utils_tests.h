#pragma once

#include <gtest/gtest.h>
#include <Eigen/Geometry>

#include <beam_utils/math.h>

namespace bs_common {

void ExpectTransformsNear(const Eigen::Matrix4d& T1,
                          const Eigen::Matrix4d& T2) {
  Eigen::Quaterniond q1;
  Eigen::Vector3d p1;

  Eigen::Quaterniond q2;
  Eigen::Vector3d p2;

  beam::TransformMatrixToQuaternionAndTranslation(T1, q1, p1);
  beam::TransformMatrixToQuaternionAndTranslation(T2, q2, p2);

  EXPECT_NEAR(q1.w(), q2.w(), 1e-6);
  EXPECT_NEAR(q1.x(), q2.x(), 1e-6);
  EXPECT_NEAR(q1.y(), q2.y(), 1e-6);
  EXPECT_NEAR(q1.z(), q2.z(), 1e-6);
  EXPECT_NEAR(p1[0], p2[0], 1e-3);
  EXPECT_NEAR(p1[1], p2[1], 1e-3);
  EXPECT_NEAR(p1[2], p2[2], 1e-4);
}

void ExpectImuStateEq(const ImuState& IS1, const ImuState& IS2) {
  double tol = 1e-12;
  EXPECT_EQ(IS1.Stamp(), IS2.Stamp());
  EXPECT_NEAR(IS1.Orientation().w(), IS2.Orientation().w(), tol);
  EXPECT_NEAR(IS1.Orientation().x(), IS2.Orientation().x(), tol);
  EXPECT_NEAR(IS1.Orientation().y(), IS2.Orientation().y(), tol);
  EXPECT_NEAR(IS1.Orientation().z(), IS2.Orientation().z(), tol);
  EXPECT_NEAR(IS1.Position().x(), IS2.Position().x(), tol);
  EXPECT_NEAR(IS1.Position().y(), IS2.Position().y(), tol);
  EXPECT_NEAR(IS1.Position().z(), IS2.Position().z(), tol);
  EXPECT_NEAR(IS1.Velocity().x(), IS2.Velocity().x(), tol);
  EXPECT_NEAR(IS1.Velocity().y(), IS2.Velocity().y(), tol);
  EXPECT_NEAR(IS1.Velocity().z(), IS2.Velocity().z(), tol);
  EXPECT_NEAR(IS1.GyroBias().x(), IS2.GyroBias().x(), tol);
  EXPECT_NEAR(IS1.GyroBias().y(), IS2.GyroBias().y(), tol);
  EXPECT_NEAR(IS1.GyroBias().z(), IS2.GyroBias().z(), tol);
  EXPECT_NEAR(IS1.AccelBias().x(), IS2.AccelBias().x(), tol);
  EXPECT_NEAR(IS1.AccelBias().y(), IS2.AccelBias().y(), tol);
  EXPECT_NEAR(IS1.AccelBias().z(), IS2.AccelBias().z(), tol);
}

void ExpectImuStateNear(const ImuState& IS1, const ImuState& IS2) {
  EXPECT_EQ(IS1.Stamp(), IS2.Stamp());
  EXPECT_NEAR(IS1.Orientation().w(), IS2.Orientation().w(), 1e-6);
  EXPECT_NEAR(IS1.Orientation().x(), IS2.Orientation().x(), 1e-6);
  EXPECT_NEAR(IS1.Orientation().y(), IS2.Orientation().y(), 1e-6);
  EXPECT_NEAR(IS1.Orientation().z(), IS2.Orientation().z(), 1e-6);
  EXPECT_NEAR(IS1.Position().x(), IS2.Position().x(), 1e-3);
  EXPECT_NEAR(IS1.Position().y(), IS2.Position().y(), 1e-3);
  EXPECT_NEAR(IS1.Position().z(), IS2.Position().z(), 1e-4);
  EXPECT_NEAR(IS1.Velocity().x(), IS2.Velocity().x(), 1e-3);
  EXPECT_NEAR(IS1.Velocity().y(), IS2.Velocity().y(), 1e-3);
  EXPECT_NEAR(IS1.Velocity().z(), IS2.Velocity().z(), 1e-4);
  EXPECT_NEAR(IS1.GyroBias().x(), IS2.GyroBias().x(), 1e-9);
  EXPECT_NEAR(IS1.GyroBias().y(), IS2.GyroBias().y(), 1e-9);
  EXPECT_NEAR(IS1.GyroBias().z(), IS2.GyroBias().z(), 1e-9);
  EXPECT_NEAR(IS1.AccelBias().x(), IS2.AccelBias().x(), 1e-9);
  EXPECT_NEAR(IS1.AccelBias().y(), IS2.AccelBias().y(), 1e-9);
  EXPECT_NEAR(IS1.AccelBias().z(), IS2.AccelBias().z(), 1e-9);
}

}  // namespace bs_common