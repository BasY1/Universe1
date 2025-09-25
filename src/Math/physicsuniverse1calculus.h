/*!
 * \file src/Math/physicsuniverse1calculus.h
 * \brief The Universe1 physics calculus tools
 */

#ifndef MATH_PHYSICSUNIVERSE1CALCULUS_H
#define MATH_PHYSICSUNIVERSE1CALCULUS_H

#include "orientation.h"
#include "spherecrosssection.h"

// xxxclang-format off

/*!
 * \page PageUniverse1 The Universe 1
 * \tableofcontents
 * The <b>Universe 1</b> is an "advanced" dynamic system, a mathematical model for describing the properties,
 * the mutual interactions and the motion dynamics of two kinds of objects: \b particles and \b waves.
 *
 * \section SecParticlesAndWaves1 Introduction - particles and waves
 *
 * In this system all \b particles are conceptualized as entities with an identical physical form, characterized
 * by a perfect spherical shape and constant size. The shape is always the same perfect sphere with a constant
 * radius \f$\mathbb{R}_1 [\mbox{m}]\f$ (Major system constant <b>particle radius</b>).
 * The entirety of particle's volume is comprised of a mass-less and charge-less material that is identical
 * for all particles and exhibits varying inner "oriented" states. All the singular points that form the body
 * of a particle are oriented, they are all pointing in exactly the same directions.
 *
 * The second category of objects are the \b waves, which are spherical objects that do not have volume,
 * they are planar only, in the sense that they are perfect spherical surfaces. The dynamics of \b waves is simple,
 * they act as an inflating spherical surfaces. In every singular moment, in every instant in this system a
 * one wave is created as a singular point in the central points of each particle body. It then "explodes", spreads
 * into the abs. spacetime in all directions at a constant growing rate equal to
 * \f$\mathbb{C}_1 [\frac{\mbox{m}}{\mbox{s}}]\f$ (Major system constant <b>universal speed</b>),
 * whereby the wave's radius raises with the rate of \f$\mathbb{C}_1\f$.
 * \b Waves are comprised of an "elastic", mass-less and charge-less material that is identical for all waves
 * and contains the information about "the particle body's inner state" at the moment of creation. This information
 * is always evenly distributed over the inflating spherical surface. All the singular points that form the surface
 * of inflated wave are also oriented, the direction can only be towards the point of wave's creation or in exactly
 * the opposite direction. The magnitude of the oriented vector is relative to current area of wave's surface
 * and to the magnitude of initial information given at the time of creation.
 *
 * \section SecAbsSpacetime Absolute spacetime
 *
 * This system uses the concept of <b>absolute spacetime</b>, but the <b>Euclidean space</b> and the <b>flow of time</b>
 * are strictly scaled by two major system constants:
 * | Name                   | Shortcut, value and unit                         |
 * | :--------------------- | :----------------------------------------------- |
 * | <b>Particle radius</b> | \f$\mathbb{R}_1 = 1 [\mbox{m}]\f$                |
 * | <b>Universal speed</b> | \f$\mathbb{C}_1 = 1 [\mbox{m}\,\mbox{s}^{-1}]\f$ |
 *
 * In this system, the <b>particle radius</b> is the quantity for measuring distances, so <b>one meter</b>
 * \f$1 \mbox{m}\f$ equals to the length of every <b>particle radius</b> \f$\mathbb{R}_1\f$
 *
 * In this system the flow of time is ruled by a system constant <b>universal speed</b>
 * \f$\mathbb{C}_1 = 1 \frac{\mbox{m}}{\mbox{s}}\f$, and the quantity for measuring time duration <b>one second</b>
 * \f$1 \mbox{s}\f$ is:
 * - the time duration, during which every particles (its central points) travels the distance of one
 *   <b>particle radius</b> \f$\mathbb{R}_1\f$ along its own trajectory.
 * - the time duration, during which every wave grows its radius by a length equal to one
 *   <b>particle radius</b> \f$\mathbb{R}_1\f$.
 *
 * \subsection SubSecPhysMathUnits Standard physical and mathematical units
 * Standard physical and mathematical units used in this system:
 * | Shortcut           | Name      | Purpose                               |
 * | -----------------: | :-------- | :------------------------------------ |
 * | \f$[\mbox{m}]\f$   | \b meter  | Quantity for measuring distances      |
 * | \f$[\mbox{s}]\f$   | \b second | Quantity for measuring time durations |
 * | \f$[\mbox{rad}]\f$ | \b radian | Quantity for measuring angles         |
 * In this system we still keep tracking the unit radian, this is mainly because we can observe this way
 * that some angular velocity is active in the system.
 *
 * \subsection SubSecVirtualUnits "Virtual" complex mathematical vector units
 * Complex mathematical units are always bound to 3D vectors:
 * | Shortcut               | Spectrum | Nature          |
 * | ---------------------: | :------- | :-------------- |
 * | \f$[\hat{\mbox{i}}]\f$ | \b red   | <i>scissors</i> |
 * | \f$[\hat{\mbox{j}}]\f$ | \b green | <i>paper</i>    |
 * | \f$[\hat{\mbox{k}}]\f$ | \b blue  | <i>rock</i>     |
 *
 * \subsection SubSecSystemConstants System constants
 * Major physical constants used in this system:
 * | Name                            | Shortcut, value and unit                                                   |
 * | :------------------------------ | :------------------------------------------------------------------------- |
 * | <b>Particle radius</b>          | \f$\mathbb{R}_1 = 1 [\mbox{m}]\f$                                          |
 * | <b>Universal speed</b>          | \f$\mathbb{C}_1 = 1 [\mbox{m}\,\mbox{s}^{-1}]\f$                           |
 * | <b>Major reaction constant</b>  | \f$\mathbb{G}_1 = (user\,value) [\mbox{1}]\f$                              |
 * | <b>Color reaction constant</b>  | \f$\mathbb{G}_c = (user\,value) [\mbox{m}^2\,\mbox{rad}\,\mbox{s}^{-1}]\f$ |
 * | <b>Major collision constant</b> | \f$\mathbb{X}_1 = (user\,value) [\mbox{rad}\,\mbox{s}^{-1}]\f$             |
 * | <b>Color collision constant</b> | \f$\mathbb{X}_c = (user\,value) [\mbox{rad}\,\mbox{s}^{-1}]\f$             |
 *
 * Derived system constants:
 * | Name                     | Shortcut, value and unit                                                          |
 * | :----------------------- | :-------------------------------------------------------------------------------- |
 * | Particle circumference   | \f$\mathbb{L}_1 = 2 \pi \mathbb{R}_1 = 2 \pi [\mbox{m}]\f$                        |
 * | Particle null plane area | \f$\mathbb{S}_1 = \pi \mathbb{R}_1^2 = \pi [\mbox{m}^2]\f$                        |
 * | Universal spin           | \f$\mathbb{W}_1=\frac{\mathbb{C}_1}{\mathbb{R}_1}=1[\mbox{rad}\,\mbox{s}^{-1}]\f$ |
 * | Period duration          | \f$\mathbb{T}_1 = \frac{2 \pi}{\mathbb{W}_1} = 2 \pi [\mbox{s}]\f$                |
 *
 * \subsection SubSec3DVecTypes 3D vector properties
 * 3D vector types and their meanings:
 * | Shortcut                | Unit                                  | 3D vector type                         |
 * | ----------------------: | :------------------------------------ | :------------------------------------- |
 * | \f$\vec{p}\f$           | \f$[\mbox{m}]\f$                      | Positional vector                      |
 * | \f$\vec{\mathcal{N}}\f$ | \f$[\mbox{1}]\f$                      | Unit vector - particle normal (axis)   |
 * | \f$\vec{\mathcal{I}}\f$ | \f$[\hat{\mbox{i}}]\f$                | Unit vector - particle red pointer     |
 * | \f$\vec{\mathcal{J}}\f$ | \f$[\hat{\mbox{j}}]\f$                | Unit vector - particle green pointer   |
 * | \f$\vec{\mathcal{K}}\f$ | \f$[\hat{\mbox{k}}]\f$                | Unit vector - particle blue pointer    |
 * | \f$\vec{v}\f$           | \f$[\mbox{m}\,\mbox{s}^{-1}]\f$       | Translational velocity vector          |
 * | \f$\vec{\omega}\f$      | \f$[\mbox{rad}\,\mbox{s}^{-1}]\f$     | Angular velocity vector (right-handed) |
 * | \f$\vec{\zeta}\f$       | \f$[\mbox{rad}^2\,\mbox{s}^{-2}]\f$   | Wave surface pointer                   |
 * | \f$\vec{\zeta}_{i}\f$   | \f$[\hat{\mbox{i}}\,\mbox{m}^{-2}]\f$ | Wave surface red spectrum pointer      |
 * | \f$\vec{\zeta}_{j}\f$   | \f$[\hat{\mbox{j}}\,\mbox{m}^{-2}]\f$ | Wave surface green spectrum pointer    |
 * | \f$\vec{\zeta}_{k}\f$   | \f$[\hat{\mbox{k}}\,\mbox{m}^{-2}]\f$ | Wave surface blue spectrum pointer     |
 *
 * 3D vector indexes and their meanings:
 * | Shortcut index                           | Detail                                                |
 * | :--------------------------------------- | :---------------------------------------------------- |
 * | \f$\vec{p}_{n:t}\f$                      | Positional vector for particle \b N at time-step \b t |
 * | \f$\vec{p}_{n:now}\f$ or \f$\vec{p}_n\f$ | Particle \b N at current time-step in the simulation  |
 *
 * 3D vectors for II. and III. generation of fermion particles:
 * | Dots on shortcut     | Detail                            |
 * | :------------------- | :-------------------------------- |
 * | \f$\vec{p}\f$        | I. generation positional vector   |
 * | \f$\vec{\dot{p}}\f$  | II. generation positional vector  |
 * | \f$\vec{\ddot{p}}\f$ | III. generation positional vector |
 *
 *
 * \section SecParticleBlock The particle block - a basic building block of particles
 *
 * The very most basic unit, the most basic building block, of which all particles are composed,
 * can be imagined as a perfect sphere with radius \f$\mathbb{R}_1\f$ filled with three different substances,
 * each substance oriented in its own unique direction in space.
 * It is as if our perfect sphere were filled with red substance, with each red singular point in the particle body
 * oriented in the same direction as the other red points and with the same constant unit magnitude
 * (\f$\vec{\mathcal{I}}\,[\hat{\mbox{i}}]\f$).
 * At the same time, however, this sphere is also filled with green and blue substances,
 * and each color has its own unique directions.
 * In other words, each green singular point in the particle body is oriented in the same direction
 * as the other green points(\f$\vec{\mathcal{J}}\,[\hat{\mbox{j}}]\f$),
 * and each blue singular point in the particle body is oriented in the same direction as the other blue points
 * (\f$\vec{\mathcal{K}}\,[\hat{\mbox{k}}]\f$).
 *
 * Particles always consist of at least 2 building blocks (photons and different colored gluons),
 * but we will also work with particles that consist of 3 blocks (fermions) and 4 blocks (Z and W+/- bosons)
 *
 * Here we call such color directions with unit color magnitudes the <b>color pointers</b>
 * (Red color pointer \f$\vec{\mathcal{I}}\,[\hat{\mbox{i}}]\f$,
 * green color pointer \f$\vec{\mathcal{J}}\,[\hat{\mbox{j}}]\f$
 * and blue color pointer \f$\vec{\mathcal{K}}\,[\hat{\mbox{k}}]\f$).
 *
 * \subsection SecParticleBlock1 Rules for color pointer directions within the particle block
 *
 * \section SecEnergyConservLaw Analogy for the energy conservation law
 * Although this system uses the concept of absolute space-time, it does not have a defined weight.
 * The \f$[\mbox{kg}]\f$ a physical quantity for measuring weights does not exist here.
 * This property emerges from how this system behaves.
 *
 * Thus we cannot express energy in standard Joules \b J \f$[\mbox{kg}\,\mbox{m}^2\,\mbox{s}^{-2}]\f$,
 * but we use an analogy that is named <b>the magnitude of information</b> \f$\mathbb{E}\f$ and it is described using:
 * \b meters, \b radians and \b seconds \f$[\mbox{rad}^2\,\mbox{m}^2\,\mbox{s}^{-2}]\f$.
 *
 * At each singular time instant in the system, each particle creates a wave
 * (fermions of II. generation create 2 waves and fermions of the III. generation create 3 waves).
 *
 * Each wave originates at a singular point and receives information about the internal "rotational" state
 * in the particle's body. This information depends on the square of the magnitude of the angular velocity
 * of the internal rotation and the size of the area of ​​the neutral plane.
 *
 * \subsection SecEnergyConservLaw1 I. generation fermions and bosons
 * \f$\mathbb{E}_{n:t} = \pi R_{n:t}^2\,|\vec{\omega}_{n:t}|^2 = \mathbb{S}_1\,|\vec{\omega}_{n:t}|^2\f$
 * - The total magnitude of information for particle \b n at time \b t is concentrated within a single wave
 * - \f$\vec{\omega}_{n:t}\f$ is an angular velocity vector describing a I. generation inner body rotation
 * - \f$R_{n:t} = \mathbb{R}_1\f$ is a radius of a I. generation null plane area (always constant)
 * - \f$\pi R_{n:t}^2 = \pi \mathbb{R}_1^2 = \mathbb{S}_1\f$ always constant area of a null plane
 *
 * \subsection SecEnergyConservLaw2 II. generation fermions
 * \f$\mathbb{E}_{n:t} = \mathbb{E}_{1:n:t} + \dot{\mathbb{E}}_{2:n:t} =
 * \mathbb{S}_1\,|\vec{\omega}_{n:t}|^2 + \pi \dot{R}_{n:t}^2\,|\vec{\dot{\omega}}_{n:t}|^2\f$
 * - The total magnitude of information for particle \b n at time \b t is concentrated in two waves
 *   \f$\mathbb{E}_{n:t} = \mathbb{E}_{1:n:t} + \dot{\mathbb{E}}_{2:n:t}\f$
 * - \f$\vec{\omega}_{n:t}\f$ is an angular velocity vector describing a I. generation inner body rotation
 * - \f$\vec{\dot{\omega}}_{n:t}\f$ is an angular velocity vector describing a II. generation inner body rotation
 *   + \f$|\vec{\dot{\omega}}_{n:t}| = \mathbb{W}_1\f$ Always constant magnitude equal to the <b>Universal spin</b>
 *   + \f$\vec{\dot{\omega}}_{n:t} \perp \vec{\omega}_{n:t}\f$ Always perpendicular to \f$\vec{\omega}_{n:t}\f$
 * - \f$\dot{R}_{n:t}\f$ is a radius of a II. generation null plane area (\f$\dot{R}_{n:t} < \mathbb{R}_1\f$)
 *
 * \subsection SecEnergyConservLaw3 III. generation fermions
 * \f$\mathbb{E}_{n:t} = \mathbb{E}_{1:n:t} + \dot{\mathbb{E}}_{2:n:t} + \ddot{\mathbb{E}}_{3:n:t} =
 *                       \mathbb{S}_1\,|\vec{\omega}_{n:t}|^2
 *                     + \pi \dot{R}_{n:t}^2\,|\vec{\dot{\omega}}_{n:t}|^2
 *                     + \pi \ddot{R}_{n:t}^2\,|\vec{\ddot{\omega}}_{n:t}|^2\f$
 * - The total magnitude of information for particle \b n at time \b t is concentrated in three waves
 *   \f$\mathbb{E}_{n:t} = \mathbb{E}_{1:n:t} + \dot{\mathbb{E}}_{2:n:t} + \ddot{\mathbb{E}}_{3:n:t}\f$
 * - \f$\vec{\omega}_{n:t}\f$ is an angular velocity vector describing a I. generation inner body rotation
 * - \f$\vec{\dot{\omega}}_{n:t}\f$ is an angular velocity vector describing a II. generation inner body rotation
 * - \f$\vec{\ddot{\omega}}_{n:t}\f$ is an angular velocity vector describing a III. generation inner body rotation
 *   + \f$\sqrt{|\vec{\dot{\omega}}_{n:t}|^2 + |\vec{\ddot{\omega}}_{n:t}|^2 } = \mathbb{W}_1\f$
 *   + \f$\vec{\dot{\omega}}_{n:t} \perp \vec{\omega}_{n:t}\f$ ;
 *     \f$\vec{\ddot{\omega}}_{n:t} \perp \vec{\omega}_{n:t}\f$ ;
 *     \f$\vec{\ddot{\omega}}_{n:t} \perp \vec{\dot{\omega}}_{n:t}\f$
 * - \f$\dot{R}_{n:t}\f$ is a radius of a II. generation null plane area (\f$\dot{R}_{n:t} < \mathbb{R}_1\f$)
 * - \f$\ddot{R}_{n:t}\f$ is a radius of a III. generation null plane area (\f$\ddot{R}_{n:t} < \dot{R}_{n:t}\f$)
 *
 * \subsection SecEnergyConservLaw4 Total magnitude of information in the system
 * The law of conservation of energy of the system is understood here in such a way that when we go through
 * all the places where the waves originated and count all the magnitudes of the waves, we always get the same value
 * of the total <b>the magnitude of information</b> of the system. The total number of places where waves originate
 * may change over time (\f$N \Rightarrow M\f$), but the total amount of accumulated <b>magnitude of information</b>
 * in the system is always the same value at any given time instant:
 * \f[ ‎‎\sum_{n=1}^{N}\mathbb{E}_{n:t} = ‎‎\sum_{n=1}^{M}\mathbb{E}_{n:(t+\Delta t)} = constant\,
 * [\mbox{rad}^2\,\mbox{m}^2\,\mbox{s}^{-2}]\f]
 *
 * \subsection SecEnergyConservLaw5 Particle's magnitude of information and waves.
 * At the moment when a wave is created as a singular point, it also receives information with some magnitude
 * (always a positive number expressed in units \f$[\mbox{rad}^2\,\mbox{m}^2\,\mbox{s}^{-2}]\f$).
 * This singular point from the moment of creation begins to expand in all directions like an inflating balloon
 * with a speed \f$\mathbb{C}_1\f$.
 * In other words, the wave exists as a singular point only at one singular moment in our absolute space-time.
 * From this moment of birth, it always has the body of a perfect surface of an inflating sphere.
 * The information that the wave received at birth is always evenly distributed on the surface of the inflating sphere.
 * It is as if every singular point on the surface of the inflating sphere
 * had the same portion of the original magnitude of information.
 * If we take any point on the surface of the inflating sphere, we will be able to determine the vector
 * \f$\vec{\zeta}\f$, which will always point towards the point of creation of the wave
 * and will have a magnitude inversely proportional to the actual area of ​​the wave's sphere.
 *
 * \subsection SecEnergyConservLaw6 The wave's surface point - wave surface pointer
 * - Let \b t be the time of waves creation and \b s to be the time when we want to observe the wave
 *   (the current time in the simulation), so the wave has its age: \f$\Delta t = s - t\,[\mbox{s}]\,;\,\Delta t > 0\f$
 * - Wave radius \f$r_{w:n:t \rightarrow s} = \Delta t\,\mathbb{C}_1\,[\mbox{m}]\f$
 * - Wave surface area \f$s_{w:n:t \rightarrow s} = 4 \pi r_{w:n:t \rightarrow s}^2\,[\mbox{m}^2]\f$
 * - Let \f$\vec{p}_{n:t}\f$ is the point where the wave was created, and
 *   \f$\vec{p}_{w:n:s}\f$ is randomly chosen point on the wave surface at the "current" time \b s
 *   (Wave radius \f$r_{w:n:t \rightarrow s} = |\vec{p}_{n:t} - \vec{p}_{w:n:s}|\f$).
 * - The direction normal of the wave surface point
 *
 *   \f$\vec{\mathcal{N}}_{w:n:t \rightarrow s} =
 *   \frac{\vec{p}_{n:t} - \vec{p}_{w:n:s}}{|\vec{p}_{n:t} - \vec{p}_{w:n:s}|} =
 *   \frac{\vec{p}_{n:t} - \vec{p}_{w:n:s}}{r_{w:n:t \rightarrow s}}\,[\mbox{1}]\f$
 * - Wave surface pointer (I. generation wave)
 *
 *   \f$\vec{\zeta}_{n:t \rightarrow s} =
 *   \vec{\mathcal{N}}_{w:n:t \rightarrow s} \frac{\mathbb{E}_{n:t}}{s_{w:n:t \rightarrow s}} =
 *   \frac{\vec{p}_{n:t} - \vec{p}_{w:n:s}}{r_{w:n:t \rightarrow s}}\,\frac{\mathbb{E}_{n:t}}
 *   {4 \pi r_{w:n:t \rightarrow s}^2} =
 *   (\vec{p}_{n:t} - \vec{p}_{w:n:s})\,\frac{\mathbb{E}_{n:t}}{4 \pi r_{w:n:t \rightarrow s}^3} =
 *   (\vec{p}_{n:t} - \vec{p}_{w:n:s})\,\frac{\pi R_{n:t}^2\,|\vec{\omega}_{n:t}|^2}{4 \pi r_{w:n:t \rightarrow s}^3} =
 *   (\vec{p}_{n:t} - \vec{p}_{w:n:s})\,\frac{\mathbb{R}_1^2\,|\vec{\omega}_{n:t}|^2}{4 r_{w:n:t \rightarrow s}^3}
 *   \,[\mbox{rad}^2\,\mbox{s}^{-2}]\f$
 *
 * \section SecChargeConservLaw Analogy for the charge conservation law
 * As with kilograms and energy, this system does not have a defined physical unit of electric current - the ampere.
 * Electromagnetism and electric charges are not directly described, but are secondary properties that emerge
 * from how the system behaves.
 *
 * However, there is an analogy here to color charges, which are used in quantum chronodynamics.
 * Each particle defined in this system has several color pointers
 * (unit vectors that have one of the colors red, green, or blue, resp. one of Hamiltonian indices
 * \f$\hat{\mbox{i}},\,\hat{\mbox{j}},\,\hat{\mbox{k}}\f$).
 *
 *
 *
 *
 * Such a color pointer also has one of these three attributes:
 * - An \b inactive pointer:
 *   + Lies in a neutral plane, i.e. perpendicular to the particle axis (and direction of motion)
 *   + Is neutralized by one opposite pointer of a different color, or by two pointers (all in different colors),
 *     which do not have to lie exactly in the axis of the inactive pointer,
 *     but their projection onto this axis creates a pointer in the opposite direction
 *   + Does not produce a color charged waves, resp. produces a color charged waves with the zero magnitude
 * - An \b active pointer:
 *   + It never lies in a neutral plane
 *   + The direction of this pointer can lie in:
 *     - front hemisphere according to translational motion and create positive color charged waves
 *     - back hemisphere according to translational motion and create negative color charged waves
 *   + All the active pointers in the single particle must form the same angle with particle axis
 * - A \b mixing pointer:
 *   + It is always neutralized by a same color pointer in exactly the opposite direction
 *   + It never lies in a neutral plane
 *   + All the mixing pointers in the single particle must form the same angle with particle axis
 *   + This angle directly affects the magnitude of the internal rotation \f$\vec{\omega}_{n:t}\f$
 *     (which is determining the energy of the particle and major magnitude of informations given to the waves
 *     \f$\mathbb{E}_{n:t}\f$).
 *   + Does not produce a color charged waves, resp. produces a color charged waves with the zero magnitude
 *
 * \f$\alpha_{n}\f$ is angle between all active pointers and particle axis

 *
 * \section SecTranslationalMotion Translational motion - "Exploding waves"
 *
 * Every particle's central point in the body, at any given instant of its existence produces a wave,
 * a singular point object that immediately "explodes at speed" \f$\mathbb{C}_1\f$. This also exerts a kick, a "force"
 * on the central point of the particle, causing it to move away from its current position at speed \f$\mathbb{C}_1\f$
 * "in the direction of its preferential choice".
 *
 * \subsection SecTranslationalMotion1 I. generation fermions and bosons
 * All <b>I. generation fermions</b> and <b>boson</b> particles produces <b>one</b> wave at any given instant
 * of its existence at <b>the central point</b> and that point is forced to move in the direction
 * of its preferential choice at velocity \f$\vec{v_1}, |\vec{v_1}| = \mathbb{C}_1\f$
 *
 * \subsection SecTranslationalMotion2 II. generation fermions particles
 * All <b>II. generation fermions</b> produces <b>two</b> waves at any given instant of its existence:
 * - <i>I. generation wave</i> is produced at <b>the central point</b> of the particle and it is kicking away this
 *   point in the direction of its preferential choice at velocity \f$\vec{v_1}, |\vec{v_1}| < \mathbb{C}_1\f$
 * - <i>II. generation wave</i> is produced at different point in the body of the particle then the central point
 *   (at <b>II. generation central point</b>) and is kicking away that point at velocity
 *   \f$\vec{v_2}, |\vec{v_2}| < \mathbb{C}_1, \sqrt{|\vec{v_1}|^2 + |\vec{v_2}|^2} = \mathbb{C}_1\f$ in the direction
 *   that is perpendicular to \f$\vec{v_1}\f$
 * - <b>II. generation central point</b> is moving through absolute spacetime at velocity \f$\vec{v_2}\f$
 *   and it is dragging the major I. generation <b>central point</b> of the particle
 *   and force it to move with this velocity too.
 * - <b>The central point</b> of the particle is performing 2 translational motions that are perpendicular each other:
 *   + kicked away by just created wave at velocity \f$\vec{v_1}\f$
 *   + dragged with the II. generation central point and its wave at velocity \f$\vec{v_2}\f$
 *   + <b>the central point</b> is keeping the total magnitude of the velocity constant at \f$\mathbb{C}_1\f$
 *     (\f$\sqrt{|\vec{v_1}|^2 + |\vec{v_2}|^2} = \mathbb{C}_1\f$).
 *
 * \subsection SecTranslationalMotion3 III. generation fermions particles
 * All <b>III. generation fermions</b> produces <b>three</b> waves at any given instant of its existence:
 * - <i>I. generation wave</i> is produced at <b>the central point</b> of the particle and it is kicking away this
 *   point in the direction of its preferential choice at velocity \f$\vec{v_1}, |\vec{v_1}| < \mathbb{C}_1\f$
 * - <i>II. generation wave</i> is produced at different point in the body of the particle then the central point
 *   (at <b>II. generation central point</b>) and is kicking away that point in the direction that is
 *   perpendicular to \f$\vec{v_1}\f$ at velocity \f$\vec{v_2}, |\vec{v_2}| < \mathbb{C}_1\f$
 * - <i>III. generation wave</i> is produced at different point in the II. generation body
 *   (at <b>III. generation central point</b>) and is kicking away that point in the direction that is
 *   perpendicular to both \f$\vec{v_1}\f$ and \f$\vec{v_2}\f$ at velocity
 *   \f$\vec{v_3}, |\vec{v_3}| < \mathbb{C}_1 , \sqrt{|\vec{v_1}|^2 + |\vec{v_2}|^2 + |\vec{v_3}|^2} = \mathbb{C}_1\f$
 * - <b>III. generation central point</b> is moving through absolute spacetime at velocity \f$\vec{v_3}\f$
 *   and it is dragging the II. generation <b>central point</b> and force it to move with this velocity too.
 * - <b>II. generation central point</b> is performing 2 translational motions that are perpendicular each other:
 *   + kicked away by just created wave at velocity \f$\vec{v_2}\f$
 *   + dragged with the II. generation central point and its wave at velocity \f$\vec{v_3}\f$
 * - <b>The central point</b> of the particle is performing 3 translational motions that are perpendicular each other:
 *   + kicked away by just created wave at velocity \f$\vec{v_1}\f$
 *   + dragged with the II. generation central point and its wave at velocity \f$\vec{v_2}\f$
 *   + dragged with the III. generation central point and its wave at velocity \f$\vec{v_3}\f$
 *   + <b>the central point</b> is keeping the total magnitude of the velocity constant at \f$\mathbb{C}_1\f$
 *     (\f$\sqrt{|\vec{v_1}|^2 + |\vec{v_2}|^2 + |\vec{v_3}|^2} = \mathbb{C}_1\f$).
 *
 * All particle central points are always at the same speed \f$\mathbb{C}_1\f$, they never accelerate or decelerate.
 * The "direction preferential choice" in which the central point is kicked away may change, but only the orientation,
 * never the magnitude. This represents the only known philosophy for translational motion of a particle body.
 *
 * \section SecRotationalMotion Rotational motion - Particle reaction to penetrating objects
 *
 * The second kind of motion that particle bodies are performing is the <b>rotation</b>
 *
 * \subsection SecRotationalMotion1 Particle reaction to penetrating waves
 * In every instant of particle's existence an infinity waves are penetrating the body of the particle.
 * The material from which all particles are composed can react to the material from which the waves are composed,
 * and this reaction is in the form of rotation. It is as if the whole body of the particle wanted to rotate
 * into more optimal orientation with respect to currently penetrating waves.
 *
 * \subsection SecRotationalMotion2 Particle collisions - Particle reaction to penetrating particles
 * Two or more particles can collide, their bodies can penetrate each other, or they can occur
 * at exactly the same positions. The material from witch the particles are created is the same,
 * but the orientation of their inner states can differ. Those inner state orientations
 * wants to align each other causing both particle bodies to rotate into more optimal orientations.
 *
 * \section SecAdvancedDynamicSystem "Advanced" dynamic system
 *
 * If a dynamical system uses absolute spacetime, then the "system state" is the synonymous for
 * "system at some global time-step".
 *
 * In general, a standard dynamical system is a system that can be described in various states and it provides
 * a way to calculate how to change the system from one state to another, always respecting
 * the law of conservation of energy.
 * The advantage of standard dynamic system is that once we calculate the new system state,
 * we can remove the data that covers the old "previous" state.
 * The memory requirements to run the simulation increase only if the number of objects in the simulation
 * increases and the simulation can theoretically run forever.
 *
 * "Advanced" dynamical system is understood here in the sense that we cannot delete previous system states,
 * because they still enter the calculation of all next states in the simulation.
 * Every position at which a particle once occurs is also the place where a wave was created and later,
 * at the currently calculated time-step in simulation this wave has its current size and can intersect particles.
 * The "advanced" dynamical system simulation <b>CAN NOT</b> run forever because it will run out of memory,
 * we always have to allocate new memory for every new system state.
 *
 *
 *
 * \subsection SubSecParticleDB Simulation memory management - Particle state database
 *
 */

// xxxclang-format on

namespace U1 {
namespace Math {

/*!
 * \namespace U1::Math::Universe1
 * \brief The Universe 1 physics tools
 * \details <b>Universe 1</b> is an advanced dynamic system, a set of definitions, descriptions, mathematical rules
 * and equations, a mathematical model for describing the properties and dynamics of two kinds of objects:
 * \b particles and \b waves.
 *
 * \b Particles are understood as objects, all in a perfect constant spherical shape, with the same radius
 * (universal system constant <b>particle radius</b> \f$\mathbb{R}_1\f$).
 *
 * \b Waves are understood as objects with dynamic (inflating) spherical shape. They are created as singular point
 * objects at central position in the body of every particle at every instant in the system and they carry
 * the information about "the particle body's inner state". At the moment of creation they also "explode"
 * and begin to act as inflating spherical surfaces, with the radius of the inflating sphere growing linearly
 * at <b>universal constant speed</b> \f$c_1\f$. II. and III. generation fermions produces two (or three) waves
 * at every instant in the system, I. generation wave is always created at central position in the body,
 * II. and III. generation fermion waves are always created at different position in the body (at the center of
 * translational-rotational motion of the particle's body)
 *
 * The waves that are generated as singular points at central position of particle instantaneously "explode"
 * at a velocity designated as \f$c_1\f$ and this "explosion" also propels that central point away at speed
 * with the magnitude equal to \f$c_1\f$. For the II. and III. generation fermion waves that are generated
 * as singular points at the center of translational-rotational motion inside the body, and not at central position
 * of particle, the "explosion" occurs in smaller inner part of a body and propels that specific point
 * in the body away at speed with the magnitude that is lower that \f$c_1\f$
 *
 *
 *
 */

namespace Universe1 {
Q_NAMESPACE

template <typename T>
struct Particle;

// clang-format off

/*! 
 * \brief The particle type names supported in this system
 * \details The value of every literal holds additional informations about the major normal helicity,
 * color normals helicity and generation (in the case of fermions)
 * | Bits                                | Additional property   | Additional property enumerations            |
 * | :---------------------------------- | :-------------------- | :------------------------------------------ |
 * | \c 000000000000000000000000000000XX | Major normal helicity | \sa U1::Math::Universe1::ParticleHelicity   |
 * | \c 0000000000000000000000000000XX00 | Red normal helicity   | \sa U1::Math::Universe1::ParticleChargeR    |
 * | \c 00000000000000000000000000XX0000 | Green normal helicity | \sa U1::Math::Universe1::ParticleChargeG    |
 * | \c 000000000000000000000000XX000000 | Blue normal helicity  | \sa U1::Math::Universe1::ParticleChargeB    |
 * | \c 0000000000000000000000XX00000000 | Generation            | \sa U1::Math::Universe1::ParticleGeneration |
 * | \c 00000000000000000XXXXX0000000000 | Particle class name   | \sa U1::Math::Universe1::ParticleClass      |
 */
enum ParticleType : int
{
    _ParticleInvalid   = 0,                                     //!< Invalid particle
    
    _NeutrinoG1Right   = (0b00000000000000000000010100000001),  //!<   I. generation <b>anti-neutrino</b> (spin +½)
    _NeutrinoG1Left    = (0b00000000000000000000010100000010),  //!<   I. generation <b>neutrino</b>      (spin -½)
    _NeutrinoG2Right   = (0b00000000000000000000011000000001),  //!<  II. generation <b>anti-neutrino</b> (spin +½)
    _NeutrinoG2Left    = (0b00000000000000000000011000000010),  //!<  II. generation <b>neutrino</b>      (spin -½)
    _NeutrinoG3Right   = (0b00000000000000000000011100000001),  //!< III. generation <b>anti-neutrino</b> (spin +½)
    _NeutrinoG3Left    = (0b00000000000000000000011100000010),  //!< III. generation <b>neutrino</b>      (spin -½)
    
    _PositronG1Right   = (0b00000000000000000000100101010101),  //!<   I. generation <b>positron</b> (spin +½, \f$[+\mbox{i}, +\mbox{j}, +\mbox{k}]\f$)
    _PositronG1Left    = (0b00000000000000000000100101010110),  //!<   I. generation <b>positron</b> (spin -½, \f$[+\mbox{i}, +\mbox{j}, +\mbox{k}]\f$)
    _ElectronG1Right   = (0b00000000000000000000100110101001),  //!<   I. generation <b>electron</b> (spin +½, \f$[-\mbox{i}, -\mbox{j}, -\mbox{k}]\f$)
    _ElectronG1Left    = (0b00000000000000000000100110101010),  //!<   I. generation <b>electron</b> (spin -½, \f$[-\mbox{i}, -\mbox{j}, -\mbox{k}]\f$)
    _PositronG2Right   = (0b00000000000000000000101001010101),  //!<  II. generation <b>positron</b> (spin +½, \f$[+\mbox{i}, +\mbox{j}, +\mbox{k}]\f$)
    _PositronG2Left    = (0b00000000000000000000101001010110),  //!<  II. generation <b>positron</b> (spin -½, \f$[+\mbox{i}, +\mbox{j}, +\mbox{k}]\f$)
    _ElectronG2Right   = (0b00000000000000000000101010101001),  //!<  II. generation <b>electron</b> (spin +½, \f$[-\mbox{i}, -\mbox{j}, -\mbox{k}]\f$)
    _ElectronG2Left    = (0b00000000000000000000101010101010),  //!<  II. generation <b>electron</b> (spin -½, \f$[-\mbox{i}, -\mbox{j}, -\mbox{k}]\f$)
    _PositronG3Right   = (0b00000000000000000000101101010101),  //!< III. generation <b>positron</b> (spin +½, \f$[+\mbox{i}, +\mbox{j}, +\mbox{k}]\f$)
    _PositronG3Left    = (0b00000000000000000000101101010110),  //!< III. generation <b>positron</b> (spin -½, \f$[+\mbox{i}, +\mbox{j}, +\mbox{k}]\f$)
    _ElectronG3Right   = (0b00000000000000000000101110101001),  //!< III. generation <b>electron</b> (spin +½, \f$[-\mbox{i}, -\mbox{j}, -\mbox{k}]\f$)
    _ElectronG3Left    = (0b00000000000000000000101110101010),  //!< III. generation <b>electron</b> (spin -½, \f$[-\mbox{i}, -\mbox{j}, -\mbox{k}]\f$)
    
    _QuarkUpG1RGRight  = (0b00000000000000000000110100010101),  //!<   I. generation <b>red-green up-quark</b>      (spin +½, \f$[+\mbox{i}, +\mbox{j}]\f$)
    _QuarkUpG1RGLeft   = (0b00000000000000000000110100010110),  //!<   I. generation <b>red-green up-quark</b>      (spin -½, \f$[+\mbox{i}, +\mbox{j}]\f$)
    _AntiQUpG1RGRight  = (0b00000000000000000000110100101001),  //!<   I. generation <b>red-green anti-up-quark</b> (spin +½, \f$[-\mbox{i}, -\mbox{j}]\f$)
    _AntiQUpG1RGLeft   = (0b00000000000000000000110100101010),  //!<   I. generation <b>red-green anti-up-quark</b> (spin -½, \f$[-\mbox{i}, -\mbox{j}]\f$)
    _QuarkUpG2RGRight  = (0b00000000000000000000111000010101),  //!<  II. generation <b>red-green up-quark</b>      (spin +½, \f$[+\mbox{i}, +\mbox{j}]\f$)
    _QuarkUpG2RGLeft   = (0b00000000000000000000111000010110),  //!<  II. generation <b>red-green up-quark</b>      (spin -½, \f$[+\mbox{i}, +\mbox{j}]\f$)
    _AntiQUpG2RGRight  = (0b00000000000000000000111000101001),  //!<  II. generation <b>red-green anti-up-quark</b> (spin +½, \f$[-\mbox{i}, -\mbox{j}]\f$)
    _AntiQUpG2RGLeft   = (0b00000000000000000000111000101010),  //!<  II. generation <b>red-green anti-up-quark</b> (spin -½, \f$[-\mbox{i}, -\mbox{j}]\f$)
    _QuarkUpG3RGRight  = (0b00000000000000000000111100010101),  //!< III. generation <b>red-green up-quark</b>      (spin +½, \f$[+\mbox{i}, +\mbox{j}]\f$)
    _QuarkUpG3RGLeft   = (0b00000000000000000000111100010110),  //!< III. generation <b>red-green up-quark</b>      (spin -½, \f$[+\mbox{i}, +\mbox{j}]\f$)
    _AntiQUpG3RGRight  = (0b00000000000000000000111100101001),  //!< III. generation <b>red-green anti-up-quark</b> (spin +½, \f$[-\mbox{i}, -\mbox{j}]\f$)
    _AntiQUpG3RGLeft   = (0b00000000000000000000111100101010),  //!< III. generation <b>red-green anti-up-quark</b> (spin -½, \f$[-\mbox{i}, -\mbox{j}]\f$)
    
    _QuarkUpG1GBRight  = (0b00000000000000000001000101010001),  //!<   I. generation <b>green-blue up-quark</b>      (spin +½, \f$[+\mbox{j}, +\mbox{k}]\f$)
    _QuarkUpG1GBLeft   = (0b00000000000000000001000101010010),  //!<   I. generation <b>green-blue up-quark</b>      (spin -½, \f$[+\mbox{j}, +\mbox{k}]\f$)
    _AntiQUpG1GBRight  = (0b00000000000000000001000110100001),  //!<   I. generation <b>green-blue anti-up-quark</b> (spin +½, \f$[-\mbox{j}, -\mbox{k}]\f$)
    _AntiQUpG1GBLeft   = (0b00000000000000000001000110100010),  //!<   I. generation <b>green-blue anti-up-quark</b> (spin -½, \f$[-\mbox{j}, -\mbox{k}]\f$)
    _QuarkUpG2GBRight  = (0b00000000000000000001001001010001),  //!<  II. generation <b>green-blue up-quark</b>      (spin +½, \f$[+\mbox{j}, +\mbox{k}]\f$)
    _QuarkUpG2GBLeft   = (0b00000000000000000001001001010010),  //!<  II. generation <b>green-blue up-quark</b>      (spin -½, \f$[+\mbox{j}, +\mbox{k}]\f$)
    _AntiQUpG2GBRight  = (0b00000000000000000001001010100001),  //!<  II. generation <b>green-blue anti-up-quark</b> (spin +½, \f$[-\mbox{j}, -\mbox{k}]\f$)
    _AntiQUpG2GBLeft   = (0b00000000000000000001001010100010),  //!<  II. generation <b>green-blue anti-up-quark</b> (spin -½, \f$[-\mbox{j}, -\mbox{k}]\f$)
    _QuarkUpG3GBRight  = (0b00000000000000000001001101010001),  //!< III. generation <b>green-blue up-quark</b>      (spin +½, \f$[+\mbox{j}, +\mbox{k}]\f$)
    _QuarkUpG3GBLeft   = (0b00000000000000000001001101010010),  //!< III. generation <b>green-blue up-quark</b>      (spin -½, \f$[+\mbox{j}, +\mbox{k}]\f$)
    _AntiQUpG3GBRight  = (0b00000000000000000001001110100001),  //!< III. generation <b>green-blue anti-up-quark</b> (spin +½, \f$[-\mbox{j}, -\mbox{k}]\f$)
    _AntiQUpG3GBLeft   = (0b00000000000000000001001110100010),  //!< III. generation <b>green-blue anti-up-quark</b> (spin -½, \f$[-\mbox{j}, -\mbox{k}]\f$)
    
    _QuarkUpG1BRRight  = (0b00000000000000000001010101000101),  //!<   I. generation <b>Blue-red up-quark</b>      (spin +½, \f$[+\mbox{k}, +\mbox{i}]\f$)
    _QuarkUpG1BRLeft   = (0b00000000000000000001010101000110),  //!<   I. generation <b>Blue-red up-quark</b>      (spin -½, \f$[+\mbox{k}, +\mbox{i}]\f$)
    _AntiQUpG1BRRight  = (0b00000000000000000001010110001001),  //!<   I. generation <b>Blue-red anti-up-quark</b> (spin +½, \f$[-\mbox{k}, -\mbox{i}]\f$)
    _AntiQUpG1BRLeft   = (0b00000000000000000001010110001010),  //!<   I. generation <b>Blue-red anti-up-quark</b> (spin -½, \f$[-\mbox{k}, -\mbox{i}]\f$)
    _QuarkUpG2BRRight  = (0b00000000000000000001011001000101),  //!<  II. generation <b>Blue-red up-quark</b>      (spin +½, \f$[+\mbox{k}, +\mbox{i}]\f$)
    _QuarkUpG2BRLeft   = (0b00000000000000000001011001000110),  //!<  II. generation <b>Blue-red up-quark</b>      (spin -½, \f$[+\mbox{k}, +\mbox{i}]\f$)
    _AntiQUpG2BRRight  = (0b00000000000000000001011010001001),  //!<  II. generation <b>Blue-red anti-up-quark</b> (spin +½, \f$[-\mbox{k}, -\mbox{i}]\f$)
    _AntiQUpG2BRLeft   = (0b00000000000000000001011010001010),  //!<  II. generation <b>Blue-red anti-up-quark</b> (spin -½, \f$[-\mbox{k}, -\mbox{i}]\f$)
    _QuarkUpG3BRRight  = (0b00000000000000000001011101000101),  //!< III. generation <b>Blue-red up-quark</b>      (spin +½, \f$[+\mbox{k}, +\mbox{i}]\f$)
    _QuarkUpG3BRLeft   = (0b00000000000000000001011101000110),  //!< III. generation <b>Blue-red up-quark</b>      (spin -½, \f$[+\mbox{k}, +\mbox{i}]\f$)
    _AntiQUpG3BRRight  = (0b00000000000000000001011110001001),  //!< III. generation <b>Blue-red anti-up-quark</b> (spin +½, \f$[-\mbox{k}, -\mbox{i}]\f$)
    _AntiQUpG3BRLeft   = (0b00000000000000000001011110001010),  //!< III. generation <b>Blue-red anti-up-quark</b> (spin -½, \f$[-\mbox{k}, -\mbox{i}]\f$)
    
    _AntiQDownG1RRight = (0b00000000000000000001100100000101),  //!<   I. generation <b>red anti-down-quark</b> (spin +½, \f$[+\mbox{i}]\f$)
    _AntiQDownG1RLeft  = (0b00000000000000000001100100000110),  //!<   I. generation <b>red anti-down-quark</b> (spin -½, \f$[+\mbox{i}]\f$)
    _QuarkDownG1RRight = (0b00000000000000000001100100001001),  //!<   I. generation <b>red down-quark</b>      (spin +½, \f$[-\mbox{i}]\f$)
    _QuarkDownG1RLeft  = (0b00000000000000000001100100001010),  //!<   I. generation <b>red down-quark</b>      (spin -½, \f$[-\mbox{i}]\f$)
    _AntiQDownG2RRight = (0b00000000000000000001101000000101),  //!<  II. generation <b>red anti-down-quark</b> (spin +½, \f$[+\mbox{i}]\f$)
    _AntiQDownG2RLeft  = (0b00000000000000000001101000000110),  //!<  II. generation <b>red anti-down-quark</b> (spin -½, \f$[+\mbox{i}]\f$)
    _QuarkDownG2RRight = (0b00000000000000000001101000001001),  //!<  II. generation <b>red down-quark</b>      (spin +½, \f$[-\mbox{i}]\f$)
    _QuarkDownG2RLeft  = (0b00000000000000000001101000001010),  //!<  II. generation <b>red down-quark</b>      (spin -½, \f$[-\mbox{i}]\f$)
    _AntiQDownG3RRight = (0b00000000000000000001101100000101),  //!< III. generation <b>red anti-down-quark</b> (spin +½, \f$[+\mbox{i}]\f$)
    _AntiQDownG3RLeft  = (0b00000000000000000001101100000110),  //!< III. generation <b>red anti-down-quark</b> (spin -½, \f$[+\mbox{i}]\f$)
    _QuarkDownG3RRight = (0b00000000000000000001101100001001),  //!< III. generation <b>red down-quark</b>      (spin +½, \f$[-\mbox{i}]\f$)
    _QuarkDownG3RLeft  = (0b00000000000000000001101100001010),  //!< III. generation <b>red down-quark</b>      (spin -½, \f$[-\mbox{i}]\f$)
    
    _AntiQDownG1GRight = (0b00000000000000000001110100010001),  //!<   I. generation <b>green anti-down-quark</b> (spin +½, \f$[+\mbox{j}]\f$)
    _AntiQDownG1GLeft  = (0b00000000000000000001110100010010),  //!<   I. generation <b>green anti-down-quark</b> (spin -½, \f$[+\mbox{j}]\f$)
    _QuarkDownG1GRight = (0b00000000000000000001110100100001),  //!<   I. generation <b>green down-quark</b>      (spin +½, \f$[-\mbox{j}]\f$)
    _QuarkDownG1GLeft  = (0b00000000000000000001110100100010),  //!<   I. generation <b>green down-quark</b>      (spin -½, \f$[-\mbox{j}]\f$)
    _AntiQDownG2GRight = (0b00000000000000000001111000010001),  //!<  II. generation <b>green anti-down-quark</b> (spin +½, \f$[+\mbox{j}]\f$)
    _AntiQDownG2GLeft  = (0b00000000000000000001111000010010),  //!<  II. generation <b>green anti-down-quark</b> (spin -½, \f$[+\mbox{j}]\f$)
    _QuarkDownG2GRight = (0b00000000000000000001111000100001),  //!<  II. generation <b>green down-quark</b>      (spin +½, \f$[-\mbox{j}]\f$)
    _QuarkDownG2GLeft  = (0b00000000000000000001111000100010),  //!<  II. generation <b>green down-quark</b>      (spin -½, \f$[-\mbox{j}]\f$)
    _AntiQDownG3GRight = (0b00000000000000000001111100010001),  //!< III. generation <b>green anti-down-quark</b> (spin +½, \f$[+\mbox{j}]\f$)
    _AntiQDownG3GLeft  = (0b00000000000000000001111100010010),  //!< III. generation <b>green anti-down-quark</b> (spin -½, \f$[+\mbox{j}]\f$)
    _QuarkDownG3GRight = (0b00000000000000000001111100100001),  //!< III. generation <b>green down-quark</b>      (spin +½, \f$[-\mbox{j}]\f$)
    _QuarkDownG3GLeft  = (0b00000000000000000001111100100010),  //!< III. generation <b>green down-quark</b>      (spin -½, \f$[-\mbox{j}]\f$)
    
    _AntiQDownG1BRight = (0b00000000000000000010000101000001),  //!<   I. generation <b>blue anti-down-quark</b> (spin +½, \f$[+\mbox{k}]\f$)
    _AntiQDownG1BLeft  = (0b00000000000000000010000101000010),  //!<   I. generation <b>blue anti-down-quark</b> (spin -½, \f$[+\mbox{k}]\f$)
    _QuarkDownG1BRight = (0b00000000000000000010000110000001),  //!<   I. generation <b>blue down-quark</b>      (spin +½, \f$[-\mbox{k}]\f$)
    _QuarkDownG1BLeft  = (0b00000000000000000010000110000010),  //!<   I. generation <b>blue down-quark</b>      (spin -½, \f$[-\mbox{k}]\f$)
    _AntiQDownG2BRight = (0b00000000000000000010001001000001),  //!<  II. generation <b>blue anti-down-quark</b> (spin +½, \f$[+\mbox{k}]\f$)
    _AntiQDownG2BLeft  = (0b00000000000000000010001001000010),  //!<  II. generation <b>blue anti-down-quark</b> (spin -½, \f$[+\mbox{k}]\f$)
    _QuarkDownG2BRight = (0b00000000000000000010001010000001),  //!<  II. generation <b>blue down-quark</b>      (spin +½, \f$[-\mbox{k}]\f$)
    _QuarkDownG2BLeft  = (0b00000000000000000010001010000010),  //!<  II. generation <b>blue down-quark</b>      (spin -½, \f$[-\mbox{k}]\f$)
    _AntiQDownG3BRight = (0b00000000000000000010001101000001),  //!< III. generation <b>blue anti-down-quark</b> (spin +½, \f$[+\mbox{k}]\f$)
    _AntiQDownG3BLeft  = (0b00000000000000000010001101000010),  //!< III. generation <b>blue anti-down-quark</b> (spin -½, \f$[+\mbox{k}]\f$)
    _QuarkDownG3BRight = (0b00000000000000000010001110000001),  //!< III. generation <b>blue down-quark</b>      (spin +½, \f$[-\mbox{k}]\f$)
    _QuarkDownG3BLeft  = (0b00000000000000000010001110000010),  //!< III. generation <b>blue down-quark</b>      (spin -½, \f$[-\mbox{k}]\f$)
    
    _PhotonRight       = (0b00000000000000000010010000000001),  //!< <b>Photon</b> (spin +1)
    _PhotonLeft        = (0b00000000000000000010010000000010),  //!< <b>Photon</b> (spin -1)
    
    _GluonRGRight      = (0b00000000000000000010110000100101),  //!< <b>Gluon - red anti-green</b> (spin +1)
    _GluonRGLeft       = (0b00000000000000000010110000100110),  //!< <b>Gluon - red anti-green</b> (spin -1)
    
    _GluonRBRight      = (0b00000000000000000011000010000101),  //!< <b>Gluon - red anti-blue</b> (spin +1)
    _GluonRBLeft       = (0b00000000000000000011000010000110),  //!< <b>Gluon - red anti-blue</b> (spin -1)
    
    _GluonGRRight      = (0b00000000000000000011100000011001),  //!< <b>Gluon - green anti-red</b> (spin +1)
    _GluonGRLeft       = (0b00000000000000000011100000011010),  //!< <b>Gluon - green anti-red</b> (spin -1)
    
    _GluonGBRight      = (0b00000000000000000011110010010001),  //!< <b>Gluon - green anti-blue</b> (spin +1)
    _GluonGBLeft       = (0b00000000000000000011110010010010),  //!< <b>Gluon - green anti-blue</b> (spin -1)
    
    _GluonBRRight      = (0b00000000000000000100000001001001),  //!< <b>Gluon - blue anti-red</b> (spin +1)
    _GluonBRLeft       = (0b00000000000000000100000001001010),  //!< <b>Gluon - blue anti-red</b> (spin -1)
    
    _GluonBGRight      = (0b00000000000000000100010001100001),  //!< <b>Gluon - blue anti-green</b> (spin +1)
    _GluonBGLeft       = (0b00000000000000000100010001100010),  //!< <b>Gluon - blue anti-green</b> (spin -1)
    
    _WbosonPositive    = (0b00000000000000000100100001010111),  //!< <b>W+ boson</b> - positive
    
    _WbosonNegative    = (0b00000000000000000100100010101011),  //!< <b>W- boson</b> - negative
    
    _Zboson            = (0b00000000000000000100110011111111),  //!< <b>Z boson</b>
};
Q_ENUM_NS(ParticleType)

/*! 
 * \brief Major normal helicity names
 * \details The helicity is established by an angle between major normal \f$\vec{N_1}\f$ and 
 * major (first) translational motion vector \f$\vec{v_1}\f$
 */
enum ParticleHelicity : int
{
    _HelicityInvalid   = 0,                                     //!< Invalid helicity
    _HelicityPositive  = (0b00000000000000000000000000000001),  //!< Positive helicity \f$\angle (\vec{N_1}, \vec{v_1}) < \frac{\pi}{2}\f$
    _HelicityNegative  = (0b00000000000000000000000000000010),  //!< Negative helicity \f$\angle (\vec{N_1}, \vec{v_1}) > \frac{\pi}{2}\f$
    _HelicityBoth      = (0b00000000000000000000000000000011),  //!< Dual, positive and negative helicity (only W and Z bosons)
};
Q_ENUM_NS(ParticleHelicity)

/*!
 * \brief Red normal helicity names = Red wave charges (red wave magnitudes)
 * \details The helicity is established by an angle between red normal \f$\vec{N_R}\f$ and 
 * major (first) translational motion vector \f$\vec{v_1}\f$
 */
enum ParticleChargeR : int
{
    _ChargeRNull      = 0,                                     //!< Null red charge - \f$\vec{N_R} \bot \vec{v_1}\f$
    _ChargeRPositive  = (0b00000000000000000000000000000100),  //!< Positive red charge - positive helicity \f$\angle (\vec{N_R}, \vec{v_1}) < \frac{\pi}{2}\f$
    _ChargeRNegative  = (0b00000000000000000000000000001000),  //!< Negative red charge - negative helicity \f$\angle (\vec{N_R}, \vec{v_1}) > \frac{\pi}{2}\f$
    _ChargeRBosonZ    = (0b00000000000000000000000000001100),  //!< Null red charge - Two red normals active (only Z bosons)
};
Q_ENUM_NS(ParticleChargeR)

/*!
 * \brief Green normal helicity names = Green wave charges (green wave magnitudes)
 * \details The helicity is established by an angle between green normal \f$\vec{N_G}\f$ and 
 * major (first) translational motion vector \f$\vec{v_1}\f$
 */
enum ParticleChargeG : int
{
    _ChargeGNull      = 0,                                     //!< Null green charge - \f$\vec{N_G} \bot \vec{v_1}\f$
    _ChargeGPositive  = (0b00000000000000000000000000010000),  //!< Positive green charge - positive helicity \f$\angle (\vec{N_G}, \vec{v_1}) < \frac{\pi}{2}\f$
    _ChargeGNegative  = (0b00000000000000000000000000100000),  //!< Negative green charge - negative helicity \f$\angle (\vec{N_G}, \vec{v_1}) > \frac{\pi}{2}\f$
    _ChargeGBosonZ    = (0b00000000000000000000000000110000),  //!< Null green charge - Two green normals active (only Z bosons)
};
Q_ENUM_NS(ParticleChargeG)

/*!
 * \brief Blue normal helicity names = Blue wave charges (blue wave magnitudes)
 * \details The helicity is established by an angle between blue normal \f$\vec{N_B}\f$ and 
 * major (first) translational motion vector \f$\vec{v_1}\f$
 */
enum ParticleChargeB : int
{
    _ChargeBNull      = 0,                                     //!< Null blue charge - \f$\vec{N_B} \bot \vec{v_1}\f$
    _ChargeBPositive  = (0b00000000000000000000000001000000),  //!< Positive blue charge - positive helicity \f$\angle (\vec{N_B}, \vec{v_1}) < \frac{\pi}{2}\f$
    _ChargeBNegative  = (0b00000000000000000000000010000000),  //!< Negative blue charge - negative helicity \f$\angle (\vec{N_B}, \vec{v_1}) > \frac{\pi}{2}\f$
    _ChargeBBosonZ    = (0b00000000000000000000000011000000),  //!< Null blue charge - Two blue normals active (only Z bosons)
};
Q_ENUM_NS(ParticleChargeB)

/*! \brief Fermion particle generation names */
enum ParticleGeneration : int
{
    _GenerationBoson   = 0,                                     //!< Boson
    _Generation1       = (0b00000000000000000000000100000000),  //!< 1. generation fermion
    _Generation2       = (0b00000000000000000000001000000000),  //!< 2. generation fermion
    _Generation3       = (0b00000000000000000000001100000000),  //!< 3. generation fermion
};
Q_ENUM_NS(ParticleGeneration)

/*! \brief Supported particle classes */
enum ParticleClass : int
{
    _ClassInvalid      = 0,                                     //!< Invalid particle class
    _ClassNeutrino     = (0b00000000000000000000010000000000),  //!< Neutrino and Anti-neutrino 
    _ClassElectron     = (0b00000000000000000000100000000000),  //!< Electron and Positron
    _ClassQuarkUpRG    = (0b00000000000000000000110000000000),  //!< Up quark and Up anti-quark - red+green
    _ClassQuarkUpGB    = (0b00000000000000000001000000000000),  //!< Up quark and Up anti-quark - green+blue
    _ClassQuarkUpBR    = (0b00000000000000000001010000000000),  //!< Up quark and Up anti-quark - blue+red
    _ClassQuarkDownR   = (0b00000000000000000001100000000000),  //!< Down quark and Down anti-quark - red
    _ClassQuarkDownG   = (0b00000000000000000001110000000000),  //!< Down quark and Down anti-quark - green
    _ClassQuarkDownB   = (0b00000000000000000010000000000000),  //!< Down quark and Down anti-quark - blue
    _ClassPhoton       = (0b00000000000000000010010000000000),  //!< Photon
    _ClassGluonRG      = (0b00000000000000000010110000000000),  //!< Gluon - red+anti-green
    _ClassGluonRB      = (0b00000000000000000011000000000000),  //!< Gluon - red+anti-blue
    _ClassGluonGR      = (0b00000000000000000011100000000000),  //!< Gluon - green+anti-red 
    _ClassGluonGB      = (0b00000000000000000011110000000000),  //!< Gluon - green+anti-blue 
    _ClassGluonBR      = (0b00000000000000000100000000000000),  //!< Gluon - blue+anti-red 
    _ClassGluonBG      = (0b00000000000000000100010000000000),  //!< Gluon - blue+anti-green 
    _ClassWBoson       = (0b00000000000000000100100000000000),  //!< W+ and W- Boson 
    _ClassZBoson       = (0b00000000000000000100110000000000),  //!< Z Boson
};

// clang-format on

/*! \brief Particle calculation states */
enum ParticleState : int
{
    _StateInvalid = 0,          //!< Invalid particle state
    _StateHistoryIntitial = 1,  //!< Initial historical state of a particle (Initial conditions of a simulation)
    _StateHistory = 2,          //!< Calculated historical state of a particle
    _StateCurrentInit = 3,      //!< Current state of a particle - without calculated interactions
    _StateCurrentReady = 4      //!< Current state of a particle - with calculated interactions, ready to move
};
Q_ENUM_NS(ParticleState)

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Particle transformation or collision structure
 * \tparam T Template floating point type
 * \details Singular moment in absolute time when a particle (or more particles) transforms into another particle
 * (or particles). The structure is composed from two collections of particle states (\a parents and \a children)
 * that are recorded at exactly the same time-step.
 *
 * In this system we use special transformation that is used only for the initialization of particles and holds
 * the very first state of particles that are defined by an user within the initial conditions.
 *
 * For all other types of particle transformation, there must be at least one particle state in both \a parents
 * and \a children collections and the waves generated by a \a parents particle states must be exactly the same
 * as the waves generated by \a children particle states.
 *
 * Transformation types:
 * | Type                      | Example                                          | parents | children |
 * | :------------------------ | :----------------------------------------------- | :------ | :------- |
 * | Particle initialization   | First particle state (initial conditions)        | 0       | 1        |
 * | Generation transformation | Neutrino swap to next (or previous) generation   | 1       | 1        |
 * | Single particle decay     | Electron loses energy in the form of photon      | 1       | 2        |
 * | Two particles fusion      | Electron absorbs a photon                        | 2       | 1        |
 * | Two particles collision   | Two photons transforms to electron-positron pair | 2       | 2        |
 * | Many particles collision  | Collisions in the nucleus                        | N >= 2  | M >= 2   |
 */
template <typename T>
struct ParticleTransformation
{
    /*! \brief Collection of particle states that represents the last moment of existence of transforming particles */
    std::vector<const Particle<T> *> parents = {};

    /*! \brief Collection of particle states that represents the first moment of existence of new particles */
    std::vector<const Particle<T> *> children = {};
};

/*!
 * \brief Single state of a particle at a specific time-step
 * \tparam T Template floating point type
 */
template <typename T>
struct Particle
{
    /*!
     * \brief Particle index
     * \details All the following particle states that represents a single particle shares the same unique index value
     */
    size_t ParticleID = 0UL;

    /*!
     * \brief Particle type
     * \note Particle type caries information about particle type name, generation, major and color helicity
     * \sa U1::Math::Universe1::ParticleType
     */
    ParticleType type = _ParticleInvalid;

    /*!
     * \brief Calculation state
     * \sa U1::Math::Universe1::ParticleState
     */
    ParticleState state = _StateInvalid;

    /*!
     * \brief Previous position of this particle in abs. spacetime
     * \details Pointer to previous stored state of this particle.
     * If the value of this pointer is \b NULL, then it means that this particle was created at this time-step
     * (so the pointer to this particle state is stored in \a born -> \a children).
     */
    const Particle<T> *prev = nullptr;

    /*!
     * \brief Next position of this particle in abs. spacetime
     * \details Pointer to next stored state of this particle.
     * If the value of this pointer is \b NULL, then it means that this particle state is the currently calculating
     * time-step of a simulation OR this state is the last stored state of particle (so the pointer to this particle
     * state is stored in \a born -> \a children).
     */
    const Particle<T> *next = nullptr;

    /*!
     * \brief The transformation (or collision) where this particle was created
     * \note This pointer should never by \b NULL
     */
    const ParticleTransformation<T> *born = nullptr;

    /*!
     * \brief The transformation (or collision) where this particle will disappear
     * \details This pointer has \b NULL value through whole lifetime of the particle and when there is a moment
     * in the simulation when the particle will cease to exist, then all the states on the trajectory of a particle
     * take the value of actual terminating transformation
     */
    const ParticleTransformation<T> *dead = nullptr;

    /*!
     * \brief Exact time-step in abs. spacetime for this particle state
     * \note <i>Physical unit</i>: quantity for measuring the duration of time \f$[\mbox{s}]\f$ (<b>second</b>)
     * \details In this system, the <b>absolute spacetime</b> (Euclidean space and the flow of time) is scaled
     * by two main system constants:
     * - <b>particle radius</b> \f$\hat{r}_1 = 1 \mbox{m}\f$
     * - <b>universal speed</b> \f$c_1 = 1 \frac{\mbox{m}}{\mbox{s}}\f$
     *
     * In this system <b>one second</b> \f$1 \mbox{s}\f$ is:
     * - the time duration, that every particles (its central point only) travels the distance of one
     *   <b>particle radius</b> \f$\hat{r}_1\f$ along its trajectory
     * - the time duration, during which every wave grows its radius by a length equal to one
     *   <b>particle radius</b> \f$\hat{r}_1\f$
     */
    T time = T(0);

    /*!
     * \brief The central position of a particle in the abs. spacetime
     * \note <i>Physical unit</i>: quantity for measuring the distance \f$[\mbox{m}]\f$ (<b>meter</b>).
     * In this system <b>one meter</b> \f$1 \mbox{m}\f$ is equal to the length of every <b>particle radius</b>
     * \f$\hat{r}_1\f$ \details Positional vector of a singular point at the center of spherical body of a particle. All
     * particles defined in the system always have exactly the same perfect spherical body with constant radius,
     * universal system constant, the <b>particle radius</b> \f$\hat{r}_1\f$.
     *
     * - The central position of a particle is a singular point where at this time-step (at this particle state)
     *   particle produces a wave with some "amplitude". The "amplitude" is derived from information about the current
     *   state and other objects penetrating the body of this particle at this state). Every wave always appears
     *   as a singular point and then it spreads into the abs. spacetime evenly in every direction as
     *   an inflating balloon (perfect spherical \b surface shape) with the velocity of inflation equal to
     *   the <b>universal speed</b> \f$c_1\f$ (the wave radius is growing at \f$c_1\f$). The wave produced at central
     *   position of a particle is called the <b>1. generation wave</b>
     *
     * - The central position of a particle is the only singular point that always propose through abs. spacetime
     *   at universal constant magnitude of velocity \f$c_1\f$. It is as if currently created wave explodes in this
     *   singular point "at the speed \f$c_1\f$" and kicked away "at the speed \f$c_1\f$"
     *
     * <b>the wave source position</b> for all particles defined
     * - For all particles, its central points must always propose through abs. spacetime at universal constant
     *   magnitude of velocity while the direction of translational motion is changing as reaction to penetrating waves
     *   and cross-section
     */
    Vec3<T> center1 = {};

    /*!
     * \brief The major translation motion vector of a particle \f$\vec{v_1}\f$ (in meters per second)
     * \note Applies to the central position of a particle
     * \note The orientation of this vector can only be within the major axis (\f$\vec{N_1}\f$ or \f$-\vec{N_1}\f$)
     * \note For all boson and 1. generation fermion particles the magnitude is equal to the constant \f$c_1\f$
     * \note For all 2. and 3. generation fermion particles the magnitude is always lower then \f$c_1\f$
     * \note 2. generation fermion particles: \f$|\vec{v_1}|^2 + |\vec{v_2}|^2 = c_1^2\f$
     * \note 3. generation fermion particles: \f$|\vec{v_1}|^2 + |\vec{v_2}|^2 + |\vec{v_3}|^2 = c_1^2\f$
     */
    Vec3<T> velocity1 = {};

    /*!
     * \brief The major orientated axis of a particle \f$\vec{N_1}\f$ (unit vector)
     */
    Vec3<T> normal1 = {};

    //!< The orientated axis for color vectors of a particle (unit vector)
    // Vec3<T> arm1 = {};     //!< The secondary direction perpendicular to a major normal (unit vector)

    Vec3<T> boson1R = {};  //!< Primary boson red matter orientation (unit vector)
    Vec3<T> boson1G = {};  //!< Primary boson green matter orientation (unit vector)
    Vec3<T> boson1B = {};  //!< Primary boson blue matter orientation (unit vector)

    /*! \brief The anonymous union for secondary red normal */
    union
    {
        Vec3<T> fermionR = {};  //!< Primary fermion red matter orientation (unit vector)
        Vec3<T> boson2R;        //!< Secondary boson red matter orientation (unit vector)
    };

    /*! \brief The anonymous union for secondary green normal */
    union
    {
        Vec3<T> fermionG = {};  //!< Primary fermion green matter orientation (unit vector)
        Vec3<T> boson2G;        //!< Secondary boson green matter orientation (unit vector)
    };

    /*! \brief The anonymous union for secondary blue normal */
    union
    {
        Vec3<T> fermionB = {};  //!< Primary fermion blue matter orientation (unit vector)
        Vec3<T> boson2B;        //!< Secondary boson blue matter orientation (unit vector)
    };

    T angle = T(0);  //!< Angle between boson color normals with the major normal, with the value between 0 to π/2
                     //!< (in radians)

    T phase = T(0);  //!< Inner phase, rotational shift between boson and fermion normals (in radians)

    T rotation = T(0);  //!< Inner rotation angular velocity  of boson normals within the fermion normals
                        //!< (in radians per second)

    T charge1 = T(0);  //!< 1. generation wave charge

    Vec3<T> avgWaveR = {};  //!< Avg. red wave vector from all red waves penetrating the major body
    Vec3<T> avgWaveG = {};  //!< Avg. green wave vector from all green waves penetrating the major body
    Vec3<T> avgWaveB = {};  //!< Avg. blue wave vector from all blue waves penetrating the major body
    Vec3<T> avgWave1 = {};  //!< Avg. major wave vector from all major waves penetrating the major body

    Vec3<T> avgBodyR = {};  //!< Avg. red body vector from red vectors of colliding particles with major body
    Vec3<T> avgBodyG = {};  //!< Avg. green body vector from green vectors of colliding particles with major body
    Vec3<T> avgBodyB = {};  //!< Avg. blue body vector from blue vectors of colliding particles with major body
    Vec3<T> avgBody1 = {};  //!< Avg. major body vector from major vectors of colliding particles with major body

    Vec3<T> bodySpin1 = {};  //!< Current outer body major rotation (in radian per second)

    // 2. Generation properties

    //  Vec3<T> center2 = {};  //!< 2. generation sub-particle center (2. generation wave source position)

    //  Vec3<T> normal2 = {};  //!< Current normal - the major direction of translational motion (unit vector)
    //  Vec3<T> normal3 = {};  //!< Current normal - the major direction of translational motion (unit vector)

    //  // T charge1 = T(0);  //!< Charge amplitude of a major wave generated at a major particle position
    //  // T charge2 = T(0);  //!< Charge amplitude of a 2. generation wave generated at a \a position2
    //  // T charge3 = T(0);  //!< Charge amplitude of a 3. generation wave generated at a \a position3

    //  Vec3<T> position3 = {};  //!< 3. generation sub-particle center (3. generation wave source position)

    //  Vec3<T> normal1R = {};  //!< Major (boson) red color vector
    //  Vec3<T> normal1G = {};  //!< Major (boson) green color vector
    //  Vec3<T> normal1B = {};  //!< Major (boson) blue color vector

    //  Vec3<T> normal2R = {};  //!< Secondary (fermion) red color vector
    //  Vec3<T> normal2G = {};  //!< Secondary (fermion) green color vector
    //  Vec3<T> normal2B = {};  //!< Secondary (fermion) blue color vector

    //  Vec3<T> bodySpin1 = {};  //!< Current outer body major rotation (in radian per second)
    //  Vec3<T> bodySpin2 = {};  //!< Current generation 2 body rotation (in radian per second)

    //  Vec3<T> avgWaveR = {};  //!< Avg. red wave vector from all red waves penetrating major body
    //  Vec3<T> avgWaveG = {};  //!< Avg. green wave vector from all green waves penetrating major body
    //  Vec3<T> avgWaveB = {};  //!< Avg. blue wave vector from all blue waves penetrating major body
    //  Vec3<T> avgWave1 = {};  //!< Avg. major wave vector from all major waves penetrating major body
    //  Vec3<T> avgWave2 = {};  //!< Avg. major wave vector from all major waves penetrating 2. generation body

    //  Vec3<T> avgBodyR = {};  //!< Avg. red body vector from red vectors colliding particles with major body
    //  Vec3<T> avgBodyG = {};  //!< Avg. green body vector from green vectors colliding particles with major body
    //  Vec3<T> avgBodyB = {};  //!< Avg. blue body vector from blue vectors colliding particles with major body
    //  Vec3<T> avgBody1 = {};  //!< Avg. major body vector from major vectors colliding particles with major body
    //  Vec3<T> avgBody2 = {};  //!< Avg. 2. gen. body vector from major vectors colliding particles with 2. gen.
    //  body

    inline ParticleGeneration generation() const;
    Particle<T> moved(const T _timeDelta) const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Particle generation
 * \tparam T Template floating point type
 * \return Particle generation
 */
template <typename T>
inline ParticleGeneration Particle<T>::generation() const
{
    switch ((static_cast<int>(type) & (0b00000000000000000000001100000000)))
    {
    case (0b00000000000000000000000000000000): return _GenerationBoson;
    case (0b00000000000000000000000100000000): return _Generation1;
    case (0b00000000000000000000001000000000): return _Generation2;
    case (0b00000000000000000000001100000000): return _Generation3;
    default: break;
    }
    return _GenerationBoson;
}

/*!
 * \brief Particle moved by a given time-delta
 * \tparam T Template floating point type
 * \param _timeDelta Time delta to move
 * \return This particle moved by a given time-delta
 */
template <typename T>
Particle<T> Particle<T>::moved(const T _timeDelta) const
{
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \namespace U1::Math::Universe1::Calculus
 * \brief The Universe1 physics calculus tools
 */
namespace Calculus {

/*!
 * \brief Tool function for failing build method
 * \tparam T Template floating point type
 * \param _dbSize Particle database size
 * \param _particles Number of initial particles
 * \param _timeEnd Final time in calculation
 * \param _timeDelta General time-step duration
 * \param _msg Error message
 * \return Always \c false
 */
template <typename T>
inline static bool
failBuild(const size_t _dbSize, const size_t _particles, const T _timeEnd, const T _timeDelta, const std::string &_msg)
{
    std::cerr << "Error: PhysicsUniverse1::build(" << _dbSize << ", " << _particles << ", " << _timeEnd << ", "
              << _timeDelta << "): " << _msg;
    return false;
}

/*!
 * \brief Test if initial particle is valid
 * \param _particle Particle to test
 * \return \c true if major particle parameters are valid
 */
template <typename T>
static bool testInitParticle(const Particle<T> &_particle)
{
    if (_particle.type == _ParticleInvalid || !isBetween0_PI2(_particle.chargeAngle) ||
        !isPositive(_particle.charge1) || !_particle.normal.isNormalized() || !_particle.arm.isNormalized() ||
        !_particle.normal.isPerpendicular(_particle.arm))
        return false;

    const int t = static_cast<int>(_particle.type);
    // clang-format off
    switch (t & (0b00000000000000000000000000001100)) {
    case (0b00000000000000000000000000000100): if (_particle.chargeR !=  1) return false; break;
    case (0b00000000000000000000000000001000): if (_particle.chargeR != -1) return false; break;
    default:                                   if (_particle.chargeR !=  0) return false; break;
    }

    switch (t & (0b00000000000000000000000000110000)) {
    case (0b00000000000000000000000000010000): if (_particle.chargeG !=  1) return false; break;
    case (0b00000000000000000000000000100000): if (_particle.chargeG != -1) return false; break;
    default:                                   if (_particle.chargeG !=  0) return false; break;
    }

    switch (t & (0b00000000000000000000000011000000)) {
    case (0b00000000000000000000000001000000): if (_particle.chargeB !=  1) return false; break;
    case (0b00000000000000000000000010000000): if (_particle.chargeB != -1) return false; break;
    default:                                   if (_particle.chargeB !=  0) return false; break;
    }

    switch (_particle.generation()) {
    case _GenerationBoson: break;
    case _Generation1: break;
    case _Generation2:
        if (!isPositive(_particle.charge2)) return false;
        if (!isBetween0_1(_particle.position.distanceToPoint(_particle.position2))) return false;
        break;
    case _Generation3:
        if (!isPositive(_particle.charge2) || !isPositive(_particle.charge3)) return false;
        if (!isBetween0_1(_particle.position.distanceToPoint(_particle.position2))) return false;
        if (!isBetween0_1(_particle.position.distanceToPoint(_particle.position3))) return false;
        if (!isBetween0_1(_particle.position2.distanceToPoint(_particle.position3))) return false;
        break;
    }
    // clang-format on

    return true;
}

/*!
 * \brief Test validity of initial following particles
 * \param _p1 Particle 1
 * \param _p2 Particle 2
 * \return \c true if particles are valid and particle 2 is properly following particle 1
 */
template <typename T>
inline static bool testInitParticles(const Particle<T> &_p1, const Particle<T> &_p2)
{
    if (_p1.type != _p2.type || _p1.chargeR != _p2.chargeR || _p1.chargeG != _p2.chargeG ||
        _p1.chargeB != _p2.chargeB || !equals(_p1.chargeAngle, _p2.chargeAngle) || isMoreOrEqual(_p1.time, _p2.time))
        return false;

    const ParticleGeneration g = _p1.generation();
    switch (g)
    {
    case _GenerationBoson:
    case _Generation1:
        if (!equals(_p1.charge1, _p2.charge1))
            return false;
        break;
    case _Generation2:
        if (!equals(std::sqrt(_p1.charge1 * _p1.charge1 + _p1.charge2 * _p1.charge2),
                    std::sqrt(_p2.charge1 * _p2.charge1 + _p2.charge2 * _p2.charge2)))
            return false;
        break;

    case _Generation3:
        if (!equals(std::sqrt(_p1.charge1 * _p1.charge1 + _p1.charge2 * _p1.charge2 + _p1.charge3 * _p1.charge3),
                    std::sqrt(_p2.charge1 * _p2.charge1 + _p2.charge2 * _p2.charge2 + _p2.charge3 * _p2.charge3)))
            return false;
        break;
    }

    const T dt = _p2.time - _p1.time;

    // if (!equals(_p1.charge1, _p2.charge1))
    //     return false;
}

/*!
 * \brief Calculate the "energy" of a photon
 * \tparam T Template floating point type
 * \param _angleBoson Color vector normals angle (in radians)
 * \return Energy of a photon
 */
template <typename T>
inline static T energyPhoton(const T _angleBoson)
{
    return T(6) * std::cos(_angleBoson) / std::sin(_angleBoson);
}

/*!
 * \brief Calculate the "energy" of a gluon
 * \tparam T Template floating point type
 * \param _angleBoson Color vector normals angle (in radians)
 * \return Energy of a gluon
 */
template <typename T>
inline static T energyGluon(const T _angleBoson)
{
    return T(2) * std::cos(_angleBoson) / std::sin(_angleBoson);
}

/*!
 * \brief Calculate the "energy" of a fermion
 * \tparam T Template floating point type
 * \param _angleBoson Boson color vector normals angle (in radians)
 * \param _angleFermion Fermion color vector normals angle (in radians)
 * \param _cntActive No of active spins
 * \return Energy of a fermion
 */
template <typename T>
inline static T energyFermion(const T _angleBoson, const T _angleFermion, const uint8_t _cntActive)
{
    if (_cntActive == 0U)  // Neutrino
    {
        // return energyPhoton(_angleBoson) * (T(2) / T(3));
        // return T(6) * std::cos(_angleBoson) / std::sin(_angleBoson) * T(4) / T(6);
        return T(4) * std::cos(_angleBoson) / std::sin(_angleBoson);
    }
    else if (_cntActive <= 3U)  // Charged fermion
    {
        // const T tanFermion = T(1) / std::tan(_angleFermion);
        // T result = T(0);
        // for (uint8_t n = 0U; n < _cntActive; ++n)
        //     result += tanFermion;
        // return (energyPhoton(_angleBoson) - result) * T(4U - _cntActive) / T(_cntActive + 6U);

        return (T(6) * std::cos(_angleBoson) / std::sin(_angleBoson) -
                T(_cntActive) * std::cos(_angleFermion) / std::sin(_angleFermion)) *
            T(4U - _cntActive) / T(_cntActive + 6U);
    }
    return T(-1.0f);
}

}  // namespace Calculus

}  // namespace Universe1
}  // namespace Math
}  // namespace U1

#endif  // MATH_PHYSICSUNIVERSE1CALCULUS_H
