#include "application_requirements/srv/requirements.hpp"
#include "rclcpp/rclcpp.hpp"

#include <memory>

using Requirements = application_requirements::srv::Requirements;

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("application_requirements_client");
    rclcpp::Client<Requirements>::SharedPtr client = node->create_client<Requirements>("Requirements");

    auto request = std::make_shared<Requirements::Request>();
    request->age = atoi(argv[1]);
    request->name = std::string(argv[2]);
    request->is_citizen = std::string(argv[3]) == "true" || std::string(argv[3]) == "1" || std::string(argv[3]) == "yes";
    request->is_student = std::string(argv[4]) == "true" || std::string(argv[4]) == "1" || std::string(argv[4]) == "yes";

    auto result = client->async_send_request(request);
    if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS)
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), 
        "%s is %s for the position.\n", request->name.c_str(), result.get()->is_applicable ? "ELEGIBLE" : "NOT ELEGIBLE");
    else 
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service requirements\n");

    rclcpp::shutdown();

    return 0;
}