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

class FtetWild;

class FLOAT_TETWILD_API Parameters
{
  public:
    Parameters();
    ~Parameters();

    // ideal_edge_length = diag_of_bbox * L. (double, optional, default: 0.05)
    void   ideal_edge_length_rel(double val);
    double ideal_edge_length_rel() const;

    // epsilon = diag_of_bbox * EPS. (double, optional, default: 1e-3)
    void   eps_rel(double val);
    double eps_rel() const;

    // log info to given file
    void        log_path(const char* val);
    const char* log_path() const;

    void      boolean_op(BooleanOp val);
    BooleanOp boolean_op() const;

    // skip preprocessing
    void skip_simplify(bool val);
    bool skip_simplify() const;

    // suppress log output on console
    void is_quiet(bool val);
    bool is_quiet() const;

    void log_level(int val);
    int  log_level() const;

    // force the output to be manifold
    void manifold_surface(bool val);
    bool manifold_surface() const;

    void     max_threads(uint32_t val);
    uint32_t max_threads() const;

  private:
    friend class FtetWild;
    class Impl;
    Impl* impl;
};

class FLOAT_TETWILD_API FtetWild
{
  public:
    FtetWild();
    ~FtetWild();
    int tetrahedralization(const Eigen::MatrixXd& InputV,
                           const Eigen::MatrixXi& InputF,
                           Eigen::MatrixXd&       OutV,
                           Eigen::MatrixXi&       OutT,
                           const Parameters&      params = Parameters {});

  private:
    class Impl;
    Impl* impl;
};
}  // namespace ftetwild
