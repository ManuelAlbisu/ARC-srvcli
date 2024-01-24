#include "application_requirements/srv/requirements.hpp"
#include "rclcpp/rclcpp.hpp"

#include <memory>

using Requirements = application_requirements::srv::Requirements;

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("application_requirements_client");
    rclcpp::Client<Requirements>::SharedPtr client = node->create_client<Requirements>("Requirements");

    auto request = std::make_shared<Requirements::Request>();
    request->age = atol(argv[1]);
    request->name = std::string(argv[2]);
    request->is_citizen = bool(argv[3]);
    request->is_student = bool(argv[4]);

    rclcpp::shutdown();

    return 0;
}