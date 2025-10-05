#pragma once
#include <floattetwild/Parameters.h>
#include <ftetwild/dll_export.h>
#include <Eigen/Core>

namespace ftetwild {
enum class BooleanOp
{
    None         = -1,
    Union        = 0,
    Intersection = 1,
    Difference   = 2
};

class FLOAT_TETWILD_API Parameters
{
  public:
    BooleanOp boolean_op    = BooleanOp::None;
    bool      skip_simplify = false;
};

class FLOAT_TETWILD_API FtetWild
{
  public:
    FtetWild();
    ~FtetWild();
    int tetrahedralization(const Eigen::MatrixXd& InputV,
                           const Eigen::MatrixXd& InputF,
                           Eigen::MatrixXd&       OutV,
                           Eigen::MatrixXi&       OutT,
                           const Parameters&      params);

  private:
    class Impl;
    Impl* impl;
};
}  // namespace ftetwild
