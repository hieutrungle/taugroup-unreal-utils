#include "utils.hpp"

// glm::vec3 is a vector of 3 floats, glm::vec3(1.0f, 2.0f, 3.0f) is a vector of (1.0f, 2.0f, 3.0f)
// glm is similar to struct { float x, y, z; } but with more features and added functionalities

float calc_reflection_coefficient(const glm::vec3& start_pos, const glm::vec3& end_pos, const glm::vec3& normal, const float& eta1, const float& eta2, const std::string& polar) {
    glm::vec3 incident_dir = glm::normalize(end_pos - start_pos);
    glm::vec3 reflected_dir{ glm::normalize(glm::reflect(incident_dir, normal)) };
    float cos_2theta1 = glm::dot(-incident_dir, reflected_dir);
    float incident_angle = std::acos(cos_2theta1) / 2;
    return calc_reflection_coefficient(incident_angle, eta1, eta2, polar);
}


float calc_reflection_coefficient(const float& incident_angle, const float& eta1, const float& eta2, const std::string& polar) {
    float coefficient{};
    if (std::sqrt(eta1 / eta2) * std::sin(incident_angle) >= 1.0f) {
        // std::cout << "Total internal reflection" << std::endl;
        coefficient = 1.0f;
    }
    else {
        float sqrt_eta1 = std::sqrt(eta1);
        float sqrt_eta2 = std::sqrt(eta2);
        float cos_theta1 = std::cos(incident_angle);
        float cos_theta2 = std::sqrt(1 - (eta1 / eta2) * std::pow(std::sin(incident_angle), 2));
        if (polar == "TM") {
            coefficient = (sqrt_eta2 * cos_theta1 - sqrt_eta1 * cos_theta2) / (sqrt_eta2 * cos_theta1 + sqrt_eta1 * cos_theta2);
        }
        else if (polar == "TE") {
            coefficient = (sqrt_eta1 * cos_theta1 - sqrt_eta2 * cos_theta2) / (sqrt_eta1 * cos_theta1 + sqrt_eta2 * cos_theta2);
        }
        else {
            std::cerr << "Invalid polarization" << std::endl;
            coefficient = 0.0f;
        }
    }
    return std::fabs(coefficient);
}


float calc_friss_strength(const glm::vec3& start_pos, const glm::vec3& end_pos, float frequency, float tx_power, float tx_gain, float rx_gain, float ref_coef, float scale) {
    float lambda = LIGHT_SPEED / frequency;
    float dist = glm::distance(start_pos, end_pos) * scale;
    float path_loss_inv{};
    if (dist <= 1.0f) { path_loss_inv = 1.0f; }
    else { path_loss_inv = std::pow(lambda / (4 * Constant::PI * dist), 2); }
    // float strength = tx_power * tx_gain * rx_gain * std::pow(lambda / (4 * Constant::PI * dist), 2) ;
    float strength = tx_power * tx_gain * rx_gain * path_loss_inv;
    return strength * std::pow(ref_coef, 2);
}