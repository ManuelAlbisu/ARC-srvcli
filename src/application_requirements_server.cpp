#include "application_requirements/srv/requirements.hpp"
#include "rclcpp/rclcpp.hpp"

#include <memory>

using Requirements = application_requirements::srv::Requirements;

void applicability(const std::shared_ptr<Requirements::Request> request, std::shared_ptr<Requirements::Response> response) {
    response->is_applicable = false; 

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Applicant information received.\nage: %d \nname: %s \ncitizen: %s \nstudent: %s",
                request->age, request->name.c_str(), request->is_citizen ? "yes" : "no", request->is_student ? "yes" : "no");
    
    if (request->age >= 18 && request->is_citizen && request->is_student)
        response->is_applicable = true;

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Applicant elegibility: %s", 
                response->is_applicable ? "elegible" : "not elegible");
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("application_requirements_server");

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Retrieving applicant information...");

    rclcpp::Service<Requirements>::SharedPtr service = node->create_service<Requirements>("Requirements", &applicability);

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
