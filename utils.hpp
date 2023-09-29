#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <glm/glm.hpp>

inline const float LIGHT_SPEED = 299792458.0;


/// @brief Calculate the reflection coefficient of a ray hitting a surface
/// @param trace_start a point (x, y, z) where the ray starts
/// @param hit_location a point (x, y, z) where the ray hits the surface
/// @param normal a vector (x, y, z) that is normal to the surface
/// @param eta1 a float representing the permittivity of the medium the ray is coming from
/// @param eta2 a float representing the permittivity of the medium the ray is entering
/// @param polar a string representing the polarization of the ray, either "TM" or "TE"
/// @return 
float calc_reflection_coefficient(const glm::vec3& trace_start, const glm::vec3& hit_location, const glm::vec3& normal, const float& eta1, const float& eta2, const std::string& polar = "TM");


/// @brief Calculate the reflection coefficient of a ray hitting a surface
/// @param incident_angle a float representing the angle of incidence of the ray
/// @param eta1 a float representing the permittivity of the medium the ray is coming from
/// @param eta2 a float representing the permittivity of the medium the ray is entering
/// @param polar a string representing the polarization of the ray, either "TM" or "TE"
/// @return 
float calc_reflection_coefficient(const float& incident_angle, const float& eta1, const float& eta2, const std::string& polar = "TM");

/// @brief Calculate the signal strength of a ray based on the space space loss and reflection coefficient
/// @param start_pos a point (x, y, z) where the ray starts
/// @param end_pos a point (x, y, z) where the ray ends
/// @param freq frequency of signal
/// @param tx_power power of transmitter, in mW
/// @param tx_gain gain of transmitter, in ratio (not dB)
/// @param rx_gain gain of receiver, in ratio (not dB)
/// @param ref_coef reflection coefficient of the ray
/// @param scale scaling factor for the screen, this affect the distance calculation, distance = scale * distance
/// @return 
float calc_friss_strength(const glm::vec3& start_pos, const glm::vec3& end_pos, float freq, float tx_power, float tx_gain, float rx_gain, float ref_coef = 1.0f, float scale = 1.0);