#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <deque>

#include "array.h"

class Particle {
public:
    /**
     * @brief      Initialize particle.
     *
     * @param[in]  position      The position (m)
     * @param[in]  velocity      The velocity (m/s)
     * @param[in]  acceleration  The acceleration (m/s²)
     * @param[in]  radius        The radius (m)
     * @param[in]  mass          The mass (kg)
     * @param[in]  color         The color
     * @param[in]  name          The name
     */
    Particle(
        const std::array<double, 3>& position,
        const std::array<double, 3>& velocity,
        const std::array<double, 3>& acceleration,
        const double radius, const double mass,
        const std::array<float, 3>& color,
        const std::string& name = ""
        );

    /**
     * @brief      Gets the position.
     *
     * @return     The position
     */
    std::array<double, 3> getPosition() const {return position_;}


    /**
     * @brief      Gets the x coordinate of the posision.
     *
     * @return     The x coordinate
     */
    double getX() const {return position_[0];}

    /**
     * @brief      Gets the y coordinate of the posision.
     *
     * @return     The y coordinate
     */
    double getY() const {return position_[1];}

    /**
     * @brief      Gets the y coordinate of the posision.
     *
     * @return     The z coordinate
     */
    double getZ() const {return position_[2];}

    /**
     * @brief      Sets the position.
     *
     * @param[in]  position  The position
     */
    void setPosition(const std::array<double, 3>& position) {position_ = position;}

    /**
     * @brief      Sets the x coordinate of the position.
     *
     * @param[in]  x     The new value
     */
    void setX(const double x) {position_[0] = x;}

    /**
     * @brief      Sets the y coordinate of the position.
     *
     * @param[in]  y     The new value
     */
    void setY(const double y) {position_[1] = y;}

    /**
     * @brief      Sets the z coordinate of the position.
     *
     * @param[in]  z     The new value
     */
    void setZ(const double z) {position_[2] = z;}

    /**
     * @brief      Gets the velocity.
     *
     * @return     The velocity
     */
    std::array<double, 3> getVelocity() const {return velocity_;}

    /**
     * @brief      Gets the x coordinate of the velocity.
     *
     * @return     The x coordinate
     */
    double getVX() const {return velocity_[0];}

    /**
     * @brief      Gets the y coordinate of the velocity.
     *
     * @return     The y coordinate
     */
    double getVY() const {return velocity_[1];}

    /**
     * @brief      Gets the z coordinate of the velocity.
     *
     * @return     The z coordinate
     */
    double getVZ() const {return velocity_[2];}

    /**
     * @brief      Sets the velocity.
     *
     * @param[in]  velocity  The velocity
     */
    void setVelocity(const std::array<double, 3>& velocity) {velocity_ = velocity;}

    /**
     * @brief      Sets the x coordinate of the velocity.
     *
     * @param[in]  vx    The new value
     */
    void setVX(const double vx) {velocity_[0] = vx;}

    /**
     * @brief      Sets the y coordinate of the velocity.
     *
     * @param[in]  vy    The new value
     */
    void setVY(const double vy) {velocity_[1] = vy;}

    /**
     * @brief      Sets the z coordinate of the velocity.
     *
     * @param[in]  vz    The new value
     */
    void setVZ(const double vz) {velocity_[2] = vz;}

    /**
     * @brief      Gets the acceleration.
     *
     * @return     The acceleration
     */
    std::array<double, 3> getAcceleration() const {return acceleration_;}

    /**
     * @brief      Sets the acceleration.
     *
     * @param[in]  acceleration  The acceleration
     */
    void setAcceleration(const std::array<double, 3>& acceleration) {acceleration_ = acceleration;}

    /**
     * @brief      Sets the x coordinate of the acceleration.
     *
     * @param[in]  ax    The new value
     */
    void setAX(const double ax) {acceleration_[0] = ax;}

    /**
     * @brief      Sets the y coordinate of the acceleration.
     *
     * @param[in]  ay    The new value
     */
    void setAY(const double ay) {acceleration_[1] = ay;}

    /**
     * @brief      Sets the z coordinate of the acceleration.
     *
     * @param[in]  az    The new value
     */
    void setAZ(const double az) {acceleration_[2] = az;}

    /**
     * @brief      Gets the radius.
     *
     * @return     The radius
     */
    double getRadius() const {return radius_;}

    /**
     * @brief      Sets the radius.
     *
     * @param[in]  radius  The radius
     */
    void setRadius(const double radius) {radius_ = radius;}

    /**
     * @brief      Gets the mass.
     *
     * @return     The mass
     */
    double getMass() const {return mass_;}

    /**
     * @brief      Sets the mass.
     *
     * @param[in]  mass  The mass
     */
    void setMass(const double mass) {mass_ = mass;}

    /**
     * @brief      Gets the color.
     *
     * @return     The color
     */
    std::array<float, 3>& getColor() {return color_;}

    /**
     * @brief      Gets the name.
     *
     * @return     The name
     */
    const std::string& getName() const {return name_;}

    /**
     * @brief      Sets the name.
     *
     * @param[in]  The name
     * @return
     */
    void setName(const std::string name) {name_ = name;}

    /**
     * @brief      Updates the particle.
     *
     * @param[in]  deltaTime  The delta time
     */
    void update(const double deltaTime);

    /**
     * @brief      Adds a trail point.
     *
     * @param[in]  point  The point
     */
    void addTrailPoint(const std::array<double, 3>& point);

    /**
     * @brief      Gets the trail.
     *
     * @return     The trail
     */
    const std::deque<std::array<double, 3>>& getTrail() const {return trail_;}

private:
    std::array<double, 3> position_;     ///< Particle position (in m).
    std::array<double, 3> velocity_;     ///< Particle velocity (in m/s).
    std::array<double, 3> acceleration_; ///< Particle acceleration (in m/s²).
    double radius_;                      ///< Particle radius (in m).
    double mass_;                        ///< Particle mass (in kg).
    std::array<float, 3> color_;         ///< Particle color.
    std::string name_;                   ///< particle name.

    std::deque<std::array<double, 3>> trail_;       ///< trail particle.
    static constexpr size_t maxTrailLength_ = 5000; ///< max trail particle length.
};

#endif
