#include "arc_cpp_srvcli/srv/WorkerApplicabilityMsg.hpp"
#include <rclcpp/rclcpp.hpp>
#include <iostream>
#include <memory>

using Applicability = arc_cpp_srvcli::srv::WorkerApplicabilityMsg.srv;

bool callback(const std::shared_ptr<Applicability::Request> request, std::shared_ptr<Applicability::Response> response) {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Applicant information received.\nage: %d" "\nname: %s" "\ncitizen: %s" "\nstudent: %s", 
                request->age, request->name, request->is_citizen ? "true" : "false", request->is_student ? "true" : "false");

    if(request->age >= 18 && request->is_citizen && request->is_student)
        response->is_applicable = true;

    return response->is_applicable;
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("worker_applicability_server");

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Retrieving applicant information...");

    rclcpp::Service<Applicability>::SharedPtr service = node->create_service<Applicability>("WorkerApplicabilityMsg.srv", &callback);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Applicate elegibility status: %s", callback() ? "true" : "false");
    
    rclcpp::spin(node);
    rclcpp::shutdown();
}