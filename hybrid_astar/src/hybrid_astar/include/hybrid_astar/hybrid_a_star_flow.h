#ifndef HYBRID_A_STAR_HYBRID_A_STAR_FLOW_H
#define HYBRID_A_STAR_HYBRID_A_STAR_FLOW_H

#include "hybrid_a_star.h"
#include "costmap_subscriber.h"
#include "init_pose_subscriber.h"
#include "goal_pose_subscriber.h"

#include <ros/ros.h>
#include <vector>

class HybridAStarFlow {
public:
    HybridAStarFlow() = default;

    explicit HybridAStarFlow(ros::NodeHandle &nh);

    void Run();

private:
    void InitPoseData();

    void ReadData();

    bool HasStartPose();

    bool HasGoalPose();

    void PublishPath(const VectorVec3d &path);

    void PublishSearchedTree(const VectorVec4d &searched_tree);

    void PublishVehiclePath(const VectorVec3d &path, double width,
                            double length, unsigned int vehicle_interval);

private:
    std::shared_ptr<HybridAStar> kinodynamic_astar_searcher_ptr_;
    std::shared_ptr<CostMapSubscriber> costmap_sub_ptr_;
    std::shared_ptr<InitPoseSubscriber2D> init_pose_sub_ptr_;
    std::shared_ptr<GoalPoseSubscriber2D> goal_pose_sub_ptr_;

    ros::Publisher path_pub_;
    ros::Publisher ori;
    ros::Publisher searched_tree_pub_;
    ros::Publisher vehicle_path_pub_;

    std::deque<geometry_msgs::PoseWithCovarianceStampedPtr> init_pose_deque_;
    std::deque<geometry_msgs::PoseStampedPtr> goal_pose_deque_;
    std::deque<nav_msgs::OccupancyGridPtr> costmap_deque_;

    geometry_msgs::PoseWithCovarianceStampedPtr current_init_pose_ptr_;
    geometry_msgs::PoseStampedPtr current_goal_pose_ptr_;
    nav_msgs::OccupancyGridPtr current_costmap_ptr_;

    ros::Time timestamp_;

    bool has_map_{};
};

#endif //HYBRID_A_STAR_HYBRID_A_STAR_FLOW_H
