#ifndef NON_STOP_PICKING_H
#define NON_STOP_PICKING_H

#include <exotica/Exotica.h>
#include <ik_solver/IKSolver.h>
#include <time_indexed_rrt_connect/TimeIndexedRRTConnect.h>

using namespace exotica;
struct CTState
{
    Eigen::VectorXd q;
    double t;
};
class NonStopPicking
{
public:
    NonStopPicking();
    ~NonStopPicking();

    bool initialise(const std::string &rrtconnect_filepath, const std::string &optimization_filepath);
    bool setConstraint(Trajectory &cons, double start, double end);
    bool solve(const CTState &start, const CTState &goal, Eigen::MatrixXd &solution);
    void solveConstraint(Eigen::VectorXd &q, double t);
    void solveConstraintTrajectory(const Eigen::VectorXd &qs, double ta, double tb, Eigen::MatrixXd &solution);
    void publishTrajectory(const Eigen::MatrixXd &solution);
    unsigned int max_trial_;

    bool has_constraint_;
    Trajectory constraint_;
    double tc_start_;
    double tc_end_;

    TimeIndexedSamplingProblem_ptr rrtconnect_problem_;
    TimeIndexedRRTConnect_ptr rrtconnect_solver_;
    PlanningProblem_ptr optimization_problem_;
    MotionSolver_ptr optimization_solver_;
};

typedef std::shared_ptr<NonStopPicking> NonStopPicking_ptr;

class NonStopPickingThreaded
{
public:
    NonStopPickingThreaded();
    ~NonStopPickingThreaded();
    bool initialise(const std::string &rrtconnect_filepath, const std::string &optimization_filepath, unsigned int num_threads = 1);
    bool solve(const CTState &start, const CTState &goal, Eigen::MatrixXd &solution);
    void publishTrajectory(const Eigen::MatrixXd &solution);

private:
    std::vector<NonStopPicking_ptr> NSPs_;
};
#endif