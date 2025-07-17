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
        const std::array<int, 3>& color,
        const std::string& name = ""
        );
    
    /**
     * @brief      Gets the position.
     *
     * @return     The position.
     */
    std::array<double, 3> getPosition() const;


    /**
     * @brief      Gets the x coordinate of the posision.
     *
     * @return     The x.
     */
    double getX() const;

    /**
     * @brief      Gets the y coordinate of the posision.
     *
     * @return     The y.
     */
    double getY() const;

    /**
     * @brief      Gets the y coordinate of the posision.
     *
     * @return     The y.
     */
    double getZ() const;

    /**
     * @brief      Sets the position.
     *
     * @param[in]  position  The position
     */
    void setPosition(const std::array<double, 3>& position);

    /**
     * @brief      Sets the x coordinate of the position.
     *
     * @param[in]  x     The new value
     */
    void setX(double x);
    
    /**
     * @brief      Sets the y coordinate of the position.
     *
     * @param[in]  y     The new value
     */
    void setY(double y);

    /**
     * @brief      Sets the z coordinate of the position.
     *
     * @param[in]  z     The new value
     */
    void setZ(double z);

    /**
     * @brief      Gets the velocity.
     *
     * @return     The velocity.
     */
    std::array<double, 3> getVelocity() const ;

    /**
     * @brief      Gets the x coordinate of the velocity.
     *
     * @return     The x.
     */
    double getVX() const;

    /**
     * @brief      Gets the y coordinate of the velocity.
     *
     * @return     The y.
     */
    double getVY() const;

    /**
     * @brief      Gets the z coordinate of the velocity.
     *
     * @return     The z.
     */
    double getVZ() const;

    /**
     * @brief      Sets the velocity.
     *
     * @param[in]  velocity  The velocity
     */
    void setVelocity(const std::array<double, 3>& velocity);

    /**
     * @brief      Sets the x coordinate of the velocity.
     *
     * @param[in]  vx    The new value
     */
    void setVX(double vx);

    /**
     * @brief      Sets the y coordinate of the velocity.
     *
     * @param[in]  vy    The new value
     */
    void setVY(double vy);

    /**
     * @brief      Sets the z coordinate of the velocity.
     *
     * @param[in]  vz    The new value
     */
    void setVZ(double vz);

    /**
     * @brief      Gets the acceleration.
     *
     * @return     The acceleration.
     */
    std::array<double, 3> getAcceleration() const;

    /**
     * @brief      Sets the acceleration.
     *
     * @param[in]  acceleration  The acceleration
     */
    void setAcceleration(const std::array<double, 3>& acceleration);

    /**
     * @brief      Sets the x coordinate of the acceleration.
     *
     * @param[in]  ax    The new value
     */
    void setAX(double ax);

    /**
     * @brief      Sets the y coordinate of the acceleration.
     *
     * @param[in]  ay    The new value
     */
    void setAY(double ay);

    /**
     * @brief      Sets the z coordinate of the acceleration.
     *
     * @param[in]  az    The new value
     */
    void setAZ(double az);

    /**
     * @brief      Gets the radius.
     *
     * @return     The radius.
     */
    double getRadius() const;

    /**
     * @brief      Sets the radius.
     *
     * @param[in]  radius  The radius
     */
    void setRadius(double radius);

    /**
     * @brief      Gets the mass.
     *
     * @return     The mass.
     */
    double getMass() const;

    /**
     * @brief      Sets the mass.
     *
     * @param[in]  mass  The mass
     */
    void setMass(double mass);

    /**
     * @brief      Gets the color.
     *
     * @return     The color.
     */
    std::array<int, 3> getColor() const;

    /**
     * @brief      Updates the particle.
     *
     * @param[in]  deltaTime  The delta time
     */
    void update(double deltaTime);

    /**
     * @brief      Adds a trail point.
     *
     * @param[in]  point  The point
     */
    void addTrailPoint(const std::array<double, 3>& point);

    /**
     * @brief      Gets the trail.
     *
     * @return     The trail.
     */
    const std::deque<std::array<double, 3>>& getTrail() const;

private:
    std::array<double, 3> m_position;     ///< Particle position (in m).
    std::array<double, 3> m_velocity;     ///< Particle velocity (in m/s).
    std::array<double, 3> m_acceleration; ///< Particle acceleration (in m/s²).
    double m_radius;                      ///< Particle radius (in m).
    double m_mass;                        ///< Particle mass (in kg).
    std::array<int, 3> m_color;           ///< Particle colors.

    std::deque<std::array<double, 3>> m_trail;       ///< trail particle.
    static constexpr size_t m_maxTrailLength = 5000; ///< max trail particle length.

public:
    const std::string m_name; ///< particle name.
};

#endif
