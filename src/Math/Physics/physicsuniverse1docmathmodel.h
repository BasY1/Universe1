/*!
 * \file src/Math/Physics/physicsuniverse1docmathmodel.h
 * \brief Doxygen-only documentation for the pure mathematical model and calculus in the "Universe 1" project
 * \note This page is derived from an iterative model-definition dialogue conducted with ChatGPT.
 */

/*! \page U1page0 0. TODO: Metaframework, notation conventions, and short explanations */

/*! \page U1page0_1 0.1 Purpose and scope of the model (what the model does and does not solve)
 * \tableofcontents
 *
 * \section U1page0_1_sec1 Purpose
 * The model defines a closed, explicitly constructed kinematic/dynamic system in an absolute space-time using only a
 * minimal unit set (length, time, and three color-analog unit labels).
 *
 * \section U1page0_1_sec2 Out of scope
 * The model does <i>not</i> use mass, electric current, thermodynamic units, or an energy-conservation law expressed
 * via \f$kg\f$-based quantities. Any “conservation” statements refer to model-specific conserved scalars (e.g.,
 * information injected at wave-birth singularities), not Newtonian energy.
 *
 * \section U1page0_1_sec3 Interpretation policy
 * Unless explicitly stated otherwise, every rule is to be treated as an axiom of this model, not as a claim about
 * real-world physics. When two statements conflict, the most recently agreed correction is the authoritative one for
 * this chat’s model state.
 */

/*! \page U1page0_2 0.2 Absolute space-time (3D Euclidean space + global time)
 * \tableofcontents
 *
 * \section U1page0_2_sec1 Space domain (3D Euclidean space, Cartesian coordinates)
 * The model uses an <b>absolute</b> space-time:
 * - Space is \f$\mathbb{R}^3\f$ with a Cartesian coordinate system and standard Euclidean geometry.
 * - Time is a single global scalar \f$t\f$ shared by all objects (no local clocks, no relativity).
 *
 * Positions are expressed as vectors \f$\vec{P}(t)\in\mathbb{R}^3\f$. When needed, distances are Euclidean norms
 * \f$\|\vec{P}_a-\vec{P}_b\|\f$.
 *
 * \section U1page0_2_sec2 Calibration conventions
 * The particle radius \f$R_1\f$ is both (i) the constant geometric radius of every type-1 object and (ii) the reference
 * length scale such that \f$R_1 = 1\,m\f$ in the model’s calibrated regime.
 *
 * The <b>Unit propagation speed</b> \f$C_1\f$ is a global constant in \f$m/s\f$ and is calibrated as \f$C_1 = 1\,m/s\f$
 * in the same regime.
 *
 * \section U1page0_2_sec3 Right-handedness, rotations, and sign conventions
 * The model is strictly <b>right-handed</b>:
 * - The Cartesian axes follow a right-handed coordinate system.
 * - The cross product \f$\vec{a}\times\vec{b}\f$ uses the right-hand rule.
 * - Angular-velocity vectors represent right-handed (positive) rotations about their direction.
 *
 * Whenever helicity or “alignment” is referenced, the sign conventions follow right-handed rotation and standard
 * dot/cross product orientation.
 */

/*! \page U1page0_3 0.3 Base units and calibration (m, s; ℝ₁ = 1 m, ℂ₁ = 1 m/s)
 * \tableofcontents
 *
 * \section U1page0_3_sec1 Allowed unit set
 * The model uses only:
 * - meter [m] for length,
 * - second [s] for time,
 * - three color-unit labels: [r], [g], [b].
 *
 * No other SI base units are used (e.g., kg, A), and therefore no SI energy concept or SI energy conservation law is
 * part of the model.
 *
 * \section U1page0_3_sec2 Primary geometric calibration (unit particle radius)
 * All type-1 objects (particles) are perfect spheres with a constant radius \f$\mathbb{R}_1\f$  (“unit particle
 * radius”). The model calibrates distance by fixing \f$\mathbb{R}_1 = 1\,m\f$. Consequently, spatial distances can be
 * expressed as multiples of \f$\mathbb{R}_1\f$ without introducing any additional length scale.
 *
 * \section U1page0_3_sec3 Primary kinematic calibration (unit propagation speed)
 * The model defines a global constant \f$\mathbb{C}_1\f$ in m/s (“unit propagation speed”) and calibrates
 * \f$\mathbb{C}_1 = 1\,m/s\f$. Translational motion of type-1 objects and inflation of type-2 objects (waves) are both
 * locked to \f$\mathbb{C}_1\f$.
 *
 * \section U1page0_3_sec4 Explicit non-Newtonian stance (no acceleration primitive)
 * The model does not use translational acceleration as a fundamental variable. Objects translate at the locked speed
 * \f$\mathbb{C}_1\f$, while changes of direction are handled via rotational rules (external body rotations) defined
 * elsewhere in the model.
 */

/*! \page U1page0_4 0.4 Color units [r], [g], [b] (unit labels for pointers and wave channels)
 * \tableofcontents
 *
 * \section U1page0_4_sec1 Meaning of color units
 * The model uses three color-unit labels: [r], [g], [b]. These labels represent three symmetric “channels” used to tag
 * specific vectors and wave fields. They are not complex numbers and do not imply any algebra beyond standard
 * real-vector operations in 3D space.
 *
 * \section U1page0_4_sec2 Where color units appear in the model
 * Color units appear only in two places:
 * - Color pointer vectors of type-1 objects: \f$\vec{I}_r\f$ carries [r], \f$\vec{I}_g\f$ carries [g], and
 *   \f$\vec{I}_b\f$ carries [b]. Each of these is always a unit vector in its own color unit.
 * - Color wave-channel fields of type-2 objects: \f$\vec{W}_r\f$, \f$\vec{W}_g\f$, \f$\vec{W}_b\f$, defined on the wave
 *   surface only, with magnitudes that scale as an areal density in the corresponding color unit.
 *
 * \section U1page0_4_sec3 Cancellation and dimensional consistency
 * Whenever an expression contains the same color unit in both numerator and denominator (e.g., via \f$|\vec{I}_r|^2\f$
 * in a normalization term), the color unit cancels. The result is interpreted as a purely geometric/kinematic quantity
 * (e.g., an angular-velocity contribution) with no residual color unit attached.
 *
 * \section U1page0_4_sec4 Symmetry across [r], [g], [b]
 * All rules and constants are assumed to be color-symmetric: any statement made for [r] applies identically to [g] and
 * [b] after renaming the channel.
 */

/*! \page U1page0_5 0.5 Naming conventions for indices
 *
 * Indexed variables use a compact, uniform pattern for both scalars and vectors:
 *
 * \f$\vec{X}_{\left[n\right]\left(m\right)|t|MAIN:qualifier}\f$
 *
 * - "[n]" (square brackets): optional particle id; omit when a single particle is implied.
 * - "(m)" (round brackets): optional particle block id
 * - "|t|" (vertical bars): optional time tag; omit when evaluated at \f$t_{now}\f$.
 * - "MAIN" mandatory main index when needed (e.g., r/g/b or I/II/III).
 * - ":qualifier" optional semantic suffix (e.g., :turn, :twist).
 */

/*! \page U1page0_6 0.6 TODO: Global constants (ℝ₁, ℂ₁ and user calibration constants)
 * \tableofcontents
 *
 * \section U1page0_6_sec1 Unit particle radius ℝ₁
 * \section U1page0_6_sec2 Unit propagation speed ℂ₁
 * \section U1page0_6_sec3 Calibration constants particle-wave
 * \subsection U1page0_6_sec3_1 Particle-wave interaction constant for color channel
 * \subsection U1page0_6_sec3_2 Particle-wave interaction constant for main channel
 * \section U1page0_6_sec4 Calibration constants particle-particle
 * \subsection U1page0_6_sec4_1 Particle-particle collision constant for color channel
 * \subsection U1page0_6_sec4_2 Particle-particle collision constant for main channel
 */

/*! \page U1page0_7 0.7 Particle unit vectors ψ and color channels
 * \tableofcontents
 *
 * This page defines the particle-attached unit-direction vectors (\f$\vec{ψ}\f$ vectors) used as canonical directions
 * for a type-1 object (particle).
 *
 * A \f$\vec{ψ}\f$ vector is a pure direction (unit length). It is evaluated in the global 3D Euclidean frame, but it is
 * conceptually attached to the particle body and therefore co-rotates with the body under any external body rotation.
 *
 * The model treats particle-attached directions as spatially homogeneous: at any singular point inside the particle
 * body (including the center and the surface), the same set of ψ directions is considered to apply.
 *
 * \section U1page0_7_sec1 ψ for color channels
 * The model uses three symmetric color channels, labelled [r], [g], [b]. Each channel has one corresponding particle
 * pointer direction:
 * - \f$\vec{ψ}_r\f$: unit direction of the red pointer (channel [r])
 * - \f$\vec{ψ}_g\f$: unit direction of the green pointer (channel [g])
 * - \f$\vec{ψ}_b\f$: unit direction of the blue pointer (channel [b])
 *
 * Canonical identification:
 * - \f$\vec{ψ}_r\f$ corresponds to the direction of vector \f$\vec{Ξ}_r\f$
 * - \f$\vec{ψ}_g\f$ corresponds to the direction of vector \f$\vec{Ξ}_g\f$
 * - \f$\vec{ψ}_b\f$ corresponds to the direction of vector \f$\vec{Ξ}_b\f$
 *
 * Scope note:
 * - The model assumes color symmetry: any statement about [r] applies identically to [g] and [b]
 *
 * \section U1page0_7_sec2 ψ for main channel
 * The main channel defines the canonical orthonormal motion basis used to express generation structure in the
 * particle's translational kinematics.
 *
 * \subsection U1page0_7_sec2_1 ψ_I. (I-generation kick direction)
 * \f$\vec{ψ}_{I.}\f$ is a unit vector oriented along the particle's main axis of symmetry. It represents the
 * translational “kick” direction caused by the explosion of the I-generation wave at the particle's central point.
 *
 * By convention, for bosons and I-generation fermions, the particle translates in direction \f$\vec{ψ}_{I.}\f$ with the
 * locked speed \f$\mathbb{C}_1\f$.
 *
 * \subsection U1page0_7_sec2_2 ψ_II. (II-generation kick direction)
 * \f$\vec{ψ}_{II.}\f$ is a unit vector representing the kick direction caused by the explosion of the II-generation
 * wave. The II-generation wave is born at a point inside the particle body that is not the central point.
 *
 * The direction \f$\vec{ψ}_{II.}\f$ is always orthogonal to \f$\vec{ψ}_{I.}\f$.
 *
 * \subsection U1page0_7_sec2_3 ψ_III. (III-generation kick direction)
 * \f$\vec{ψ}_{III.}\f$ is a unit vector representing the kick direction caused by the explosion of the III-generation
 * wave. The III-generation wave is born at a point inside the particle body that is not the central point, and it is
 * also not the II-generation wave-birth point (i.e., the II. and III. waves are born at two distinct non-central
 * locations).
 *
 * The direction \f$\vec{ψ}_{III.}\f$ is always orthogonal to both \f$\vec{ψ}_{I.}\f$ and \f$\vec{ψ}_{II.}\f$.
 *
 * \subsection U1page0_7_sec2_4 Translational speed composition by generation
 * For bosons and I-generation fermions:
 * - the particle translates along \f$\vec{ψ}_{I.}\f$ with speed \f$\mathbb{C}_1\f$.
 *
 * For II-generation fermions:
 * - the particle translates along \f$\vec{ψ}_{I.}\f$ with speed \f$V_{I.}\f$,
 * - and along \f$\vec{ψ}_{II.}\f$ with speed \f$V_{II.}\f$,
 * - the composed constraint holds: \f$V_{I.}^2 + V_{II.}^2 = \mathbb{C}_1^2\f$.
 *
 * Interpreting wave-birth-point motion in II-generation:
 * - the II-generation wave birth point is translated along \f$\vec{ψ}_{II.}\f$ with speed \f$V_{II.}\f$.
 *
 * For III-generation fermions:
 * - the particle translates along \f$\vec{ψ}_{I.}\f$ with speed \f$V_{I.}\f$,
 * - along \f$\vec{ψ}_{II.}\f$ with speed \f$V_{II.}\f$,
 * - and along \f$\vec{ψ}_{III.}\f$ with speed \f$V_{III.}\f$,
 * - the composed constraint holds: \f$V_{I.}^2 + V_{II.}^2 + V_{III.}^2 = \mathbb{C}_1^2\f$.
 *
 * Interpreting wave-birth-point motion in III-generation:
 * - the II-generation wave birth point translates with components \f$V_{II.}\f$ along \f$\vec{ψ}_{II.}\f$ and
 *   \f$V_{III.}\f$ along \f$\vec{ψ}_{III.}\f$,
 * - the III-generation wave birth point translates along \f$\vec{ψ}_{III.}\f$ with speed \f$V_{III.}\f$.
 *
 * \subsection U1page0_7_sec2_5 Neutral plane
 * The vector \f$\vec{ψ}_{I.}\f$ defines the particle's main symmetry axis and determines the particle's neutral plane:
 * the plane whose normal is \f$\vec{ψ}_{I.}\f$. Statements such as “a pointer is in the neutral plane” are always
 * evaluated with respect to this
 * \f$\vec{ψ}_{I.}\f$.
 */

/*! \page U1page0_8 0.8 Wave unit vector χ
 * \tableofcontents
 *
 * This page defines the wave-attached unit-direction vector (the “χ vector”) used to express the geometric direction of
 * a type-2 object (wave) at the particle–wave interaction site.
 *
 * In this model, a wave is a planar object: it exists only as the surface of an expanding sphere. Any wave-direction
 * vector is therefore defined only on the wave surface (never in the wave interior volume).
 *
 * \section U1page0_8_sec1 Definition of χ at evaluation time
 * Let:
 * - \f$t_{born}\f$ be the wave birth time,
 * - \f$t_{now}\f$ be the evaluation time,
 * - \f$\vec{P}_{born}\f$ be the wave birth position,
 * - \f$\vec{P}_{now}\f$ be the particle center position at \f$t_{now}\f$,
 * - \f$\mathbb{C}_1\f$ be the calibrated propagation speed.
 *
 * The wave radius at \f$t_{now}\f$ is:
 * \f[
 *   R_{wave}(t_{now}) = (t_{now} - t_{born})\,\mathbb{C}_1
 * \f]
 *
 * The wave unit direction χ used by the particle–wave calculus is defined as the axis direction pointing from the
 * particle center toward the wave birth point:
 * \f[
 *   \vec{χ}(t_{now}) = \frac{\vec{P}_{born} - \vec{P}_{now}}
 *                          {\left\lVert \vec{P}_{born} - \vec{P}_{now} \right\rVert}
 * \f]
 *
 * Interpretation:
 * - \f$\vec{χ}\f$ is the “collision axis” between the particle center and the wave birth point.
 * - \f$\vec{χ}\f$ is a unit vector and carries no color unit.
 *
 * \section U1page0_8_sec2 Domain of definition (when χ is valid)
 * The χ vector is evaluated only when the wave is relevant for interaction, i.e. only in the particle–wave
 * cross-section states:
 * - TOUCH_BEFORE (single-point contact): The wave sphere is externally tangent to the particle sphere. Their surfaces
 *   touch in exactly one point, and the intersection region has zero area. This state is the first boundary event when
 *   a previously missing wave begins to interact.
 *
 * - CROSSES (finite-area intersection): The wave sphere intersects the particle sphere such that their surfaces cross
 *   along a closed curve. The intersection region corresponds to a non-zero spherical-cap area of the wave surface
 *   lying inside the particle volume; this is the only state that produces a non-zero volumetric contribution when
 *   integrating over wave segments.
 *
 * - TOUCH_AFTER (single-point contact): The wave sphere is externally tangent to the particle sphere again (on the
 *   “exit” side). Their surfaces touch in exactly one point, and the intersection region again has zero area. This
 *   state is the last boundary event before the wave becomes a pure MISS_AFTER case for all older history.
 *
 * If the wave does not intersect the particle body (MISS_BEFORE or MISS_AFTER), χ is not evaluated (it is outside the
 * domain of the particle–wave interaction rules).
 *
 * \section U1page0_8_sec3 Relation to Ζ and ζ channel vectors
 * The wave carries channel magnitudes (main channel Ζ and color channels ζ_r, ζ_g, ζ_b) that are
 * distributed uniformly over the wave surface as areal densities. The directional part is encoded
 * by χ as follows:
 *
 * - Main (rotational) wave direction uses χ as the geometric axis toward the wave birth point.
 * - Color wave directions also use the same χ axis geometrically; the sign/orientation convention of a color channel is
 * handled by the channel scalar sign (ζ = +1 / -1 / 0) in the channel rules.
 *
 * In particular:
 * - if a color channel is inactive (ζ = 0), its vector contribution is treated as the zero vector, regardless of χ,
 * - otherwise χ provides the canonical direction used by the per-point angular response formulae.
 *
 * \section U1page0_8_sec4 Cancellation symmetry note
 * When wave contributions are integrated as vectors over the full wave surface, the net result is the zero vector due
 * to antipodal cancellation. Therefore, χ is used only in cross-section restricted calculations (the
 * intersecting/touching region), where the symmetry is broken by the particle body and the chosen interaction rule.
 */

/*! \page U1page0_9 0.9 Particle pointers Ξ
 * \tableofcontents
 *
 * This page defines the particle "pointer" vectors, denoted \f$\vec{Ξ}\f$. These are the canonical, body-fixed
 * directions that encode the internal RGB structure of a type-1 object (particle).
 *
 * A pointer \f$\vec{Ξ}\f$ is always a unit vector (a pure direction) evaluated in the global 3D Euclidean frame, but
 * conceptually attached to the particle body and therefore co-rotating with the body under any external body rotation.
 * The pointer field is treated as spatially homogeneous: at any singular point inside the particle body (including the
 * center and the surface), the same set of \f$\vec{Ξ}\f$ vectors applies.
 *
 * Constraints:
 * - No two pointers \f$\vec{Ξ}\f$ in one particle may be collinear.
 *
 * \section U1page0_9_sec1 Color pointers and per-block notation
 * Each tricolor block (3F block) carries three color pointers:
 * - \f$\vec{Ξ}_r\f$: red pointer vector (unit direction with unit label [r])
 * - \f$\vec{Ξ}_g\f$: green pointer vector (unit direction with unit label [g])
 * - \f$\vec{Ξ}_b\f$: blue pointer vector (unit direction with unit label [b])
 *
 * Unlike the corresponding ψ directions (\f$\vec{ψ}_r\f$, \f$\vec{ψ}_g\f$, \f$\vec{ψ}_b\f$), which are treated as
 * dimensionless unit directions, the pointer vectors \f$\vec{Ξ}_r\f$, \f$\vec{Ξ}_g\f$, \f$\vec{Ξ}_b\f$ explicitly carry
 * the model's color-unit labels [r], [g], [b]. This means:
 *
 * - \f$\|\vec{Ξ}_r\| = 1\, [r]\f$, \f$\|\vec{Ξ}_g\| = 1\, [g]\f$, \f$\|\vec{Ξ}_b\| = 1\, [b]\f$
 * - ψ vectors are the corresponding unit directions obtained by dropping the unit labels:
 *   \f$\vec{ψ}_r = \vec{Ξ}_r / \|\vec{Ξ}_r\|\f$, \f$\vec{ψ}_g = \vec{Ξ}_g / \|\vec{Ξ}_g\|\f$,
 *   \f$\vec{ψ}_b = \vec{Ξ}_b / \|\vec{Ξ}_b\|\f$
 *
 * If a particle consists of multiple tricolor blocks, pointers are indexed by the block id:
 * - \f$\vec{Ξ}_{(1)r}\f$, \f$\vec{Ξ}_{(1)g}\f$, \f$\vec{Ξ}_{(1)b}\f$ for block (1)
 * - \f$\vec{Ξ}_{(2)r}\f$, \f$\vec{Ξ}_{(2)g}\f$, \f$\vec{Ξ}_{(2)b}\f$ for block (2)
 * - \f$\vec{Ξ}_{(3)r}\f$, \f$\vec{Ξ}_{(3)g}\f$, \f$\vec{Ξ}_{(3)b}\f$ for block (3)
 *
 * All color pointer vectors are unit length in their own color unit by construction; the model never assigns magnitudes
 * different from 1 to \vec{Ξ}_{r} pointers.
 *
 * \subsection U1page0_9_sec1_1 Locked internal angles (alpha, beta, gamma)
 * The model uses three classes of angles to describe pointer geometry. These angles are locked (time-invariant) over
 * the lifetime of the particle, except during discrete transformation events (transformations are defined elsewhere).
 *
 * \subsubsection U1page0_9_sec1_1_1 Intra-block angles alpha
 * - \f$\alpha_{(n)r g}\f$ is the angle between \f$\vec{Ξ}_{(n)r}\f$ and \f$\vec{Ξ}_{(n)g}\f$
 * - \f$\alpha_{(n)g b}\f$ is the angle between \f$\vec{Ξ}_{(n)g}\f$ and \f$\vec{Ξ}_{(n)b}\f$
 * - \f$\alpha_{(n)b r}\f$ is the angle between \f$\vec{Ξ}_{(n)b}\f$ and \f$\vec{Ξ}_{(n)r}\f$
 *
 * Constraints:
 * - No alpha angle may be 0 (no two color pointers in one block may be collinear).
 *
 * \subsubsection U1page0_9_sec1_1_2 Angles beta to the main direction
 * - \f$\beta_{(n)r}\f$ is the angle between \f$\vec{Ξ}_{(n)r}\f$ and \f$\vec{ψ}_{I.}\f$
 * - \f$\beta_{(n)g}\f$ is the angle between \f$\vec{Ξ}_{(n)g}\f$ and \f$\vec{ψ}_{I.}\f$
 * - \f$\beta_{(n)b}\f$ is the angle between \f$\vec{Ξ}_{(n)b}\f$ and \f$\vec{ψ}_{I.}\f$
 *
 * Constraints:
 * - No beta angle may be 0 or pi (no color pointer may lie exactly on the \f$\vec{ψ}_{I.}\f$ axis).
 *
 * \subsubsection U1page0_9_sec1_1_3 Inter-block angles gamma
 * - \f$\gamma_{(n,m)r}\f$ is the angle between \f$\vec{Ξ}_{(n)r}\f$ and \f$\vec{Ξ}_{(m)r}\f$
 * - \f$\gamma_{(n,m)g}\f$ is the angle between \f$\vec{Ξ}_{(n)g}\f$ and \f$\vec{Ξ}_{(m)g}\f$
 * - \f$\gamma_{(n,m)b}\f$ is the angle between \f$\vec{Ξ}_{(n)b}\f$ and \f$\vec{Ξ}_{(m)b}\f$
 *
 * These are used primarily to describe "mixing" constraints between blocks (see below).
 *
 * \subsection U1page0_9_sec1_2 Pointer activity types (mixing, inactive, active)
 * Each color pointer in each block is assigned exactly one of the following types, and the type is invariant over the
 * particle lifetime (except during discrete transformation events):
 *
 * \subsubsection U1page0_9_sec1_2_1 Mixing pointer
 * - A mixing pointer exists as one of a same-color pair across two blocks that are locked as anti-parallel:
 *   \f$\gamma_{(1,2)color} = \pi\f$ for that color.
 * - Mixing pointers are never allowed to be exactly orthogonal to \f$\vec{ψ}_{I.}\f$ (\f$\beta_{(n)color} \ne
 *   \frac{\pi}{2}\f$), and are never allowed to lie on the \f$\vec{ψ}_{I.}\f$ axis (\f$\beta_{(n)color} \ne 0\f$ and
 *   \f$\beta_{(n)color} \ne \pi\f$).
 * - For a mixing pair, one is designated "front" and the other "back" relative to \f$\vec{ψ}_{I.}\f$, based on which
 *   one has smaller beta with \f$\vec{ψ}_{I.}\f$. The back pointer is the exact opposite direction of the front
 *   pointer.
 *
 * Additional locked alpha-equality constraint (for a fully mixing two-block pair):
 * - If blocks (1) and (2) form a fully mixing pair (i.e., all three colors are mixing across the pair), then all
 * intra-block alpha angles in both blocks are identical and locked:
 * \f[
 *  \alpha_{(1)r g} = \alpha_{(1)g b} = \alpha_{(1)b r} = \alpha_{(2)r g} = \alpha_{(2)g b} = \alpha_{(2)b r}
 * \f].
 *
 * \subsubsection U1page0_9_sec1_2_2 Inactive pointer
 * - An inactive pointer lies in the neutral plane: \f$\beta_{(n)color} = \frac{\pi}{2}\f$.
 * - Inactivity is defined by a cancellation rule in the neutral-plane projections: the projected contributions of all
 *   same-color pointers (across all blocks of the particle) cancel to zero in the sense specified by the model's
 *   pointer-sum convention.
 *
 * \subsubsection U1page0_9_sec1_2_3 Active pointer
 * - An active pointer is never orthogonal to \f$\vec{ψ}_{I.}\f$ (\f$\beta_{(n)color} \ne \frac{\pi}{2}\f$), and never
 *   lies on the \f$\vec{ψ}_{I.}\f$ axis (\f$\beta_{(n)color} \ne 0\f$ and \f$\beta_{(n)color} \ne \pi\f$).
 * - Activity is defined by a non-cancellation rule in the neutral-plane projections: the projected contributions of all
 *   same-color pointers (across all blocks of the particle) cancel in such a way that the net result equals the tracked
 *   pointer direction, as specified by the model's pointer-sum convention.
 *
 * Additional locked constraints used in the fermion spectrum:
 * - All active pointers in a 3F block share the same β to \f$\vec{ψ}_{I.}\f$.
 * - In configurations with multiple mixing pairs (e.g., three mixing pairs), all mixing pairs share the same beta to
 *   \f$\vec{ψ}_{I.}\f$
 *
 * \subsubsection U1page0_9_sec1_2_4 Per-particle uniqueness constraint for active/inactive pointers (per color)
 * For each color channel (r, g, b), a single particle may contain at most one <i>active</i> pointer of that color and
 * at most one <i>inactive</i> pointer of that color (counted across <u>all</u> tricolor blocks that form the particle).
 *
 * Allowed per-color occupancy patterns are therefore:
 * - exactly one active and zero inactive,
 * - exactly zero active and one inactive,
 * - exactly one active and one inactive,
 * - exactly zero active and zero inactive.
 *
 * Any additional pointer(s) of the same color, if present in the particle, must be of the <i>mixing</i> type (i.e.,
 * part of a locked anti-parallel mixing pair across the designated mixing blocks), or the configuration is invalid.
 *
 * \subsection U1page0_9_sec1_3 Wave information magnitude in color channels
 * This subsection defines the scalar “information magnitude” carried by the wave color channels and the corresponding
 * particle-level discrete labels used to describe those channels at wave birth.
 *
 * \paragraph Naming
 * The three color-channel information magnitudes are:
 * - \f$\zeta_r\f$ (red channel),
 * - \f$\zeta_g\f$ (green channel),
 * - \f$\zeta_b\f$ (blue channel).
 *
 * \paragraph Allowed values and interpretation
 * Each \f$\zeta\_{color}\f$ is a discrete scalar taking only one of the values:
 * - \f$+1\f$: outward-oriented color contribution,
 * - \f$-1\f$: inward-oriented color contribution,
 * - \f$0\f$: no color contribution (the channel is inactive).
 *
 * The \f$\zeta\_{color}\f$ value is attached at wave birth and remains constant for that wave for all future times
 * \f$t_{now} > t_{born}\f$.
 *
 * \paragraph Uniform areal distribution onz
 * Consider a type-2 wave (spherical surface) born at time \f$t_{born}\f$ and evaluated at time \f$t_{now}\f). Its
 * radius is:
 * \f[
 *   R_{wave}(t_{now}) = (t_{now} - t_{born})\,\mathbb{C}_1
 * \f]
 *
 * The model assumes the color information \f$\zeta\_{color}\f$ is distributed uniformly over the wave surface as an
 * areal density (defined only on the wave surface, not in any volume):
 * \f[
 *   \rho_{\zeta\_{color}}(t_{now})
 *   =
 *   \frac{\zeta\_{color}}{4\pi\,R_{wave}(t_{now})^2}
 * \f]
 *
 * Units:
 * - \f$\zeta\_{color}\f$ is dimensionless,
 * - \f$\rho_{\zeta\_{color}}\f$ has units \f$m^{-2}\f$.
 *
 * \paragraph Vector form for interaction (direction carried by the wave)
 * In the interaction calculus, the scalar surface density is paired with a unit direction on the wave surface (defined
 * elsewhere, via \f$\vec{\chi}\f$). The resulting color-channel wave field is treated as a vector surface density whose
 * direction depends on the sign of \f$\zeta\_{color}\f$:
 * - if \f$\zeta\_{color} = +1\f$, the vector points outward from the wave-birth point,
 * - if \f$\zeta\_{color} = -1\f$, the vector points toward the wave-birth point,
 * - if \f$\zeta\_{color} = 0\f$, the vector is the zero vector everywhere on the wave surface.
 *
 * This convention is designed so that:
 * - the surface integral of the scalar density over the wave surface equals \f$\zeta\_{color}\f$,
 * - the surface integral of the vector field over the full wave surface is the zero vector (antipodal cancellation),
 *   and only cross-section-restricted regions can yield a non-zero net vector contribution in subsequent calculations.
 *
 *
 * \section U1page0_9_sec2 Main pointer Ξ shared by all blocks
 * The main pointer \f$\vec{Ξ}_{I.}\f$ is a particle-level unit direction that is shared by all tricolor blocks forming
 * a single type-1 object (particle). In other words, while each block has its own color pointers \f$\vec{Ξ}_r(m)\f$,
 * \f$\vec{Ξ}_g(m)\f$, \f$\vec{Ξ}_b(m)\f$, there is exactly one \f$\vec{Ξ}_{I.}\f$ per particle, and every block
 * references the same \f$\vec{Ξ}_{I.}\f$.
 *
 * The direction of \f$\vec{Ξ}_{I.}\f$ is always aligned with the particle's I-generation unit motion direction
 * \f$\vec{ψ}_{I.}\f$:
 * \f[
 *   \frac{\vec{Ξ}_{I.}}{\left\lVert \vec{Ξ}_{I.} \right\rVert} = \vec{ψ}_{I.}
 * \f]
 *
 * \subsection U1page0_9_sec2_1 Magnitude and physical unit
 * This subsection specifies how the main-pointer magnitude is parameterized and how its unit convention remains
 * dimensionless.
 *
 * \paragraph 1) Geometry-driven factor from the particle's color-pointer layout
 * The scalar \f$X\f$ represents the <u>pointer-geometry coupling factor</u> induced by:
 * - the number of mixing pointers in the locked mixing blocks, and
 * - the number of active pointers in the non-mixing block (if present),
 * with both effects mediated by the locked angles \f$\beta_{12}\f$ and \f$\beta_3\f$.
 *
 * We use the following rule for \f$X\f$ pointer-geometry coupling factor:
 * \f[
 *   X
 *   =
 *   \sqrt{
 *     \frac{
 *       \left(
 *         N_m \,\cot(\beta_{12})
 *         -
 *         N_a \,\cot(\beta_3)
 *       \right)
 *       \left(4 - N_a\right)
 *     }{
 *       N_a + N_m
 *     }
 *   }
 * \f]
 *
 * Term meaning:
 * - \f$N_m\f$: the number of mixing pointers present in the particle (e.g., 2 for gluon, 6 for
 *   fully-mixing two-block objects and for fermions whose first two blocks are fully mixing).
 * - \f$N_a\f$: the number of active pointers in the non-mixing block (for fermions: the 3rd block;
 *   for objects without a 3rd block: \f$N_a = 0\f$).
 * - \f$\beta_{12}\f$: the locked angle used for mixing pointers in the first two (mixing) blocks.
 *   Conventionally \f$\beta_{12} \in (0,\pi/2)\f$ for the chosen reference block.
 * - \f$\beta_3\f$: the locked beta angle(s) of the active pointers in the non-mixing block
 *   (\f$\beta_3\ne\pi/2\f$ when active pointers exist).
 *
 * The factor \f$N_m\cot(\beta_{12})\f$ acts as a "drive" term, while \f$N_a\cot(\beta_3)\f$ acts as a
 * "brake" term. The multiplier \f$(4-N_a)\f$ and the denominator \f$(N_a+N_m)\f$ normalize how strongly
 * the active-pointer presence suppresses the resulting magnitude.
 *
 * \paragraph 2) Velocity-driven factor from the component along \f$\vec{ψ}_{I.}\f$
 * The central point of a particle moves with total speed \f$\mathbb{C}_1\f$:
 * \f[
 *   \left\lVert \vec{V}_{I.} \right\rVert = \mathbb{C}_1
 * \f]
 *
 * For higher generations, the total velocity is decomposed into orthogonal components along the
 * particle-attached unit directions:
 * \f[
 *   \vec{V}_{I.} = \vec{V}_{I.I.} + \vec{V}_{I.II.} + \vec{V}_{I.III.}
 * \f]
 *
 * The only factor relevant here is the normalized projection onto \f$\vec{ψ}_{I.}\f$:
 * \f[
 *   \frac{\vec{V}_{I.}\cdot \vec{ψ}_{I.}}{\mathbb{C}_1}
 *   =
 *   \frac{\left\lVert \vec{V}_{I.I.} \right\rVert}{\mathbb{C}_1}
 *   =
 *   \frac{V_1}{\mathbb{C}_1}
 * \f]
 *
 * \paragraph 3) Resulting magnitude convention for the main pointer
 * The magnitude convention used for the main pointer is dimensionless and is defined as:
 * \f[
 *   \left\lVert \vec{Ξ}_{I.} \right\rVert
 *   =
 *   X \cdot \frac{V_1}{\mathbb{C}_1}
 * \f]
 *
 * By convention, the unit of \f$\left\lVert \vec{Ξ}_{I.} \right\rVert\f$ is:
 * - \f$[1]\f$ (dimensionless).
 *
 * Note:
 * - If a separate symbol \f$V_2\f$ is used elsewhere to denote a different generation component,
 *   it must not replace \f$V_1\f$ in the expression above: this magnitude uses the component aligned
 *   with \f$\vec{ψ}_{I.}\f$, i.e. \f$V_1\f$.
 *
 * \subsection U1page0_9_sec2_2 Wave information magnitude in main channel
 * This subsection defines the scalar wave-information magnitude of the <b>main</b> (non-color) channel.
 *
 * \paragraph 1) Definition at particle level
 * The main-channel scalar carried by waves born from a given particle is denoted \f$\Zeta_{I.}\f$ and is defined
 * directly from the particle main pointer magnitude:
 * \f[
 *   \Zeta_{I.} \;\equiv\; \left\lVert \vec{Ξ}_{I.} \right\rVert^2
 * \f]
 * By construction, \f$\Zeta_{I.}\f$ is dimensionless. The model assumes \f$\Zeta_{I.} \gt 0\f$ for all valid particles
 * (a vanishing \f$\Zeta_{I.}\f$ is treated as an invalid/degenerate configuration).
 *
 * \paragraph 2) Attachment to the born wave
 * Whenever a type-2 wave is born at time \f$t_{born}\f$ and birth position \f$\vec{P}_{born}\f$, the scalar
 * \f$\Zeta_{I.}\f$ is assigned to that wave at birth and remains constant for all \f$t_{now} > t_{born}\f$.
 *
 * \paragraph 3) Uniform areal distribution on the wave surface
 * At evaluation time \f$t_{now}\f$, the wave radius is
 * \f[
 *    R_{wave}(t_{now}) = (t_{now} - t_{born})\,\mathbb{C}_1
 * \f]
 * The main-channel information is distributed uniformly over the wave surface as an areal density:
 * \f[
 *   \rho_{\Zeta I.}(t_{now}) = \frac{\Zeta_{I.}}{4\pi\,R_{wave}(t_{now})^2}
 * \f]
 * Units:
 * - \f$\Zeta_{I.}\f$ is dimensionless \f$[1]\f$,
 * - \f$\rho_{\Zeta I.}\f$ has units \f$m^{-2}\f$.
 *
 * \paragraph 4) Vector form for interaction (direction carried by the wave)
 * In particle–wave interaction rules, the scalar density \f$\rho_{\Zeta I.}\f$ is paired with the wave unit direction
 * \f$\vec{\chi}(t_{now})\f$ (defined in \ref U1page0_3_4_sec3) to form a directional surface density used by the
 * per-point response calculus. The geometric direction is always taken along the axis from the particle center toward
 * the wave birth point (i.e., \f$\vec{\chi}\f$ provides direction; the scalar \f$\Zeta_{I.}\f$ provides magnitude via
 * \f$\rho_{\Zeta I.}\f$).
 *
 * Consistency notes:
 * - The surface integral of the scalar density over the full wave surface equals \f$\Zeta_{I.}\f$.
 * - The surface integral of the corresponding <i>vector</i> field over the full wave surface is the zero vector
 * (antipodal cancellation); only cross-section-restricted regions can yield a non-zero net vector contribution.
 *
 * \subsection U1page0_9_sec2_3 Main pointer Ξ and wave information magnitude for II. generation
 * This subsection extends the main-channel wave information magnitude from I-generation to II-generation fermions.
 *
 * In II-generation, the particle has two orthogonal translational components:
 * - along \f$\vec{ψ}_{I.}\f$ with speed \f$V_1\f$,
 * - along \f$\vec{ψ}_{II.}\f$ with speed \f$V_2\f$,
 * and the locked constraint holds:
 * \f[
 *   V_1^2 + V_2^2 = \mathbb{C}_1^2
 * \f]
 *
 * The same particle-geometry coupling factor \f$X\f$ (defined in
 * \ref U1page0_3_4_sec4_2_1) is reused for all generations of the same fermion configuration.
 *
 * \paragraph 1) II-generation main pointers
 * The model associates two main pointers with the two kick directions:
 * - \f$\vec{Ξ}_{I.}\f$ aligned with \f$\vec{ψ}_{I.}\f$,
 * - \f$\vec{Ξ}_{II.}\f$ aligned with \f$\vec{ψ}_{II.}\f$.
 *
 * Their magnitudes are defined by the same functional form, differing only in the velocity projection used:
 * \f[
 *   \left\lVert \vec{Ξ}_{I.} \right\rVert = X \cdot \frac{V_1}{\mathbb{C}_1},
 *   \qquad
 *   \left\lVert \vec{Ξ}_{II.} \right\rVert = X \cdot \frac{V_2}{\mathbb{C}_1}
 * \f]
 *
 * \paragraph 2) II-generation wave information magnitudes
 * The corresponding main-channel scalar magnitudes carried by the born waves are:
 * \f[
 *   \Zeta_{I.} \equiv \left\lVert \vec{Ξ}_{I.} \right\rVert^2,
 *   \qquad
 *   \Zeta_{II.} \equiv \left\lVert \vec{Ξ}_{II.} \right\rVert^2
 * \f]
 * Both \f$\Zeta_{I.}\f$ and \f$\Zeta_{II.}\f$ are dimensionless and non-negative.
 *
 * \paragraph 3) Example statement and its proof
 * Consider a fixed fermion configuration (same \f$X\f$ in all cases).
 *
 * - In I-generation, the particle translates purely along \f$\vec{ψ}_{I.}\f$ with
 *   \f$V_1 = \mathbb{C}_1\f$ and \f$V_2 = 0\f$. The single born wave has magnitude:
 *   \f[
 *     \Zeta_{\text{(I-gen total)}} = \Zeta_{I.}
 *     = \left(X \cdot \frac{\mathbb{C}_1}{\mathbb{C}_1}\right)^2
 *     = X^2
 *   \f]
 *   Let this reference total be denoted by \f$\mathrm{XXX}\f$, i.e. \f$\mathrm{XXX} \equiv X^2\f$.
 *
 * - In II-generation, two waves are born (one associated with \f$\vec{ψ}_{I.}\f$, one with
 *   \f$\vec{ψ}_{II.}\f$). Their total main-channel magnitude is:
 *   \f[
 *     \Zeta_{\text{(II-gen total)}} = \Zeta_{I.} + \Zeta_{II.}
 *     = \left(X \cdot \frac{V_1}{\mathbb{C}_1}\right)^2
 *       + \left(X \cdot \frac{V_2}{\mathbb{C}_1}\right)^2
 *     = X^2 \cdot \frac{V_1^2 + V_2^2}{\mathbb{C}_1^2}
 *   \f]
 *   Using the locked constraint \f$V_1^2 + V_2^2 = \mathbb{C}_1^2\f$, we obtain:
 *   \f[
 *     \Zeta_{\text{(II-gen total)}} = X^2 = \mathrm{XXX}
 *   \f]
 *
 * Therefore, for the same fermion configuration (same \f$X\f$), the model guarantees that the sum of II-generation
 * main-channel wave magnitudes equals the I-generation reference magnitude.
 *
 * \paragraph 4) Uniform distribution on each wave surface (per wave)
 * For each born wave with scalar magnitude \f$\Zeta\f$ (either \f$\Zeta_{I.}\f$ or \f$\Zeta_{II.}\f$), evaluated at
 * time \f$t_{now}\f$ with birth time \f$t_{born}\f$:
 * \f[
 *   R_{wave}(t_{now}) = (t_{now} - t_{born})\,\mathbb{C}_1,
 *   \qquad
 *   \rho_{\Zeta}(t_{now}) = \frac{\Zeta}{4\pi\,R_{wave}(t_{now})^2}
 * \f]
 *
 * \paragraph Color-channel note (generations II and III)
 * For any particle in a generation higher than I (i.e., generation II or III), all color-channel wave information
 * magnitudes are defined to be identically zero:
 * \f[
 *   \zeta_r = 0,\qquad \zeta_g = 0,\qquad \zeta_b = 0.
 * \f]
 * Equivalently: II- and III-generation waves carry <u>only</u> the main-channel magnitude (\f$\Zeta_{I.}\f$,
 * \f$\Zeta_{II.}\f$, \f$\Zeta_{III.}\f$ as applicable), while color channels are inactive.
 *
 *
 * \subsection U1page0_9_sec2_4 Main pointer Ξ and wave information magnitude for III. generation
 *
 * This subsection extends the main-channel wave information magnitude from I- and II-generation to III-generation
 * fermions.
 *
 * In III-generation, the particle has three mutually orthogonal translational components:
 * - along \f$\vec{ψ}_{I.}\f$ with speed \f$V_1\f$,
 * - along \f$\vec{ψ}_{II.}\f$ with speed \f$V_2\f$,
 * - along \f$\vec{ψ}_{III.}\f$ with speed \f$V_3\f$,
 * and the locked constraint holds:
 * \f[
 *   V_1^2 + V_2^2 + V_3^2 = \mathbb{C}_1^2
 * \f]
 *
 * The same particle-geometry coupling factor \f$X\f$ (defined in
 * \ref U1page0_3_4_sec4_2_1) is reused for all generations of the same fermion configuration.
 *
 * \paragraph 1) III-generation main pointers
 * The model associates three main pointers with the three kick directions:
 * - \f$\vec{Ξ}_{I.}\f$ aligned with \f$\vec{ψ}_{I.}\f$,
 * - \f$\vec{Ξ}_{II.}\f$ aligned with \f$\vec{ψ}_{II.}\f$,
 * - \f$\vec{Ξ}_{III.}\f$ aligned with \f$\vec{ψ}_{III.}\f$.
 *
 * Their magnitudes are defined by the same functional form, differing only in the velocity projection used:
 * \f[
 *   \left\lVert \vec{Ξ}_{I.} \right\rVert   = X \cdot \frac{V_1}{\mathbb{C}_1}, \qquad
 *   \left\lVert \vec{Ξ}_{II.} \right\rVert  = X \cdot \frac{V_2}{\mathbb{C}_1}, \qquad
 *   \left\lVert \vec{Ξ}_{III.} \right\rVert = X \cdot \frac{V_3}{\mathbb{C}_1}
 * \f]
 *
 * \paragraph 2) III-generation wave information magnitudes
 * The corresponding main-channel scalar magnitudes carried by the born waves are:
 * \f[
 *   \Zeta_{I.}   \equiv \left\lVert \vec{Ξ}_{I.} \right\rVert^2, \qquad
 *   \Zeta_{II.}  \equiv \left\lVert \vec{Ξ}_{II.} \right\rVert^2, \qquad
 *   \Zeta_{III.} \equiv \left\lVert \vec{Ξ}_{III.} \right\rVert^2
 * \f]
 * All of \f$\Zeta_{I.}\f$, \f$\Zeta_{II.}\f$, \f$\Zeta_{III.}\f$ are dimensionless and non-negative.
 *
 * \paragraph 3) Consistency statement and its proof (III-generation total equals I-generation total)
 * Consider a fixed fermion configuration (same \f$X\f$ in all cases).
 *
 * - In I-generation, the particle translates purely along \f$\vec{ψ}_{I.}\f$ with
 *   \f$V_1 = \mathbb{C}_1\f$, \f$V_2 = 0\f$, \f$V_3 = 0\f$. The single born wave has magnitude:
 *   \f[
 *     \Zeta_{\text{(I-gen total)}} = \Zeta_{I.}
 *     = \left(X \cdot \frac{\mathbb{C}_1}{\mathbb{C}_1}\right)^2
 *     = X^2
 *   \f]
 *
 * - In III-generation, three waves are born (one associated with each of \f$\vec{ψ}_{I.}\f$,
 *   \f$\vec{ψ}_{II.}\f$, \f$\vec{ψ}_{III.}\f$). Their total main-channel magnitude is:
 *   \f[
 *     \Zeta_{\text{(III-gen total)}} = \Zeta_{I.} + \Zeta_{II.} + \Zeta_{III.}
 *     = \left(X \cdot \frac{V_1}{\mathbb{C}_1}\right)^2
 *       + \left(X \cdot \frac{V_2}{\mathbb{C}_1}\right)^2
 *       + \left(X \cdot \frac{V_3}{\mathbb{C}_1}\right)^2
 *     = X^2 \cdot \frac{V_1^2 + V_2^2 + V_3^2}{\mathbb{C}_1^2}
 *   \f]
 *   Using the locked constraint \f$V_1^2 + V_2^2 + V_3^2 = \mathbb{C}_1^2\f$, we obtain:
 *   \f[
 *     \Zeta_{\text{(III-gen total)}} = X^2
 *   \f]
 *
 * Therefore, for the same fermion configuration (same \f$X\f$), the model guarantees that the sum of III-generation
 * main-channel wave magnitudes equals the I-generation reference magnitude.
 *
 * \paragraph 4) Uniform distribution on each wave surface (per wave)
 * For each born wave with scalar magnitude \f$\Zeta\f$ (one of \f$\Zeta_{I.}\f$, \f$\Zeta_{II.}\f$,
 * \f$\Zeta_{III.}\f$), evaluated at time \f$t_{now}\f$ with birth time \f$t_{born}\f$:
 * \f[
 *   R_{wave}(t_{now}) = (t_{now} - t_{born})\,\mathbb{C}_1, \qquad
 *   \rho_{\Zeta}(t_{now}) = \frac{\Zeta}{4\pi\,R_{wave}(t_{now})^2}
 * \f]
 * The surface density is defined only on the wave surface (the wave is planar in this model).
 *
 * \paragraph Color-channel note (generations II and III)
 * For any particle in a generation higher than I (i.e., generation II or III), all color-channel wave information
 * magnitudes are defined to be identically zero:
 * \f[
 *   \zeta_r = 0,\qquad \zeta_g = 0,\qquad \zeta_b = 0.
 * \f]
 * Equivalently: II- and III-generation waves carry <u>only</u> the main-channel magnitude (\f$\Zeta_{I.}\f$,
 * \f$\Zeta_{II.}\f$, \f$\Zeta_{III.}\f$ as applicable), while color channels are inactive.
 */

#ifndef PHYSICS_PHYSICSUNIVERSE1DOCMATHMODEL_H
#define PHYSICS_PHYSICSUNIVERSE1DOCMATHMODEL_H
#ifdef __NEVER_DEFINE_THIS___THIS_FILE_IS_FOR_DOCS_ONLY__
#define __DUMMY_NOTHING 0  //!< No purpose
#endif
#endif  // PHYSICS_PHYSICSUNIVERSE1DOCMATHMODEL_H

/*!
 *
 *
 *
 *
 *
 *
 * \section U1page0_3_4_sec5 Wave vectors ξ
 *
 * \section U1page0_3_4_sec6 Positional vectors
 * \todo
 *
 * \subsection U1page0_3_4_sec6_1 Particle center position
 * \todo
 *
 * \subsection U1page0_3_4_sec6_2 Particle II. generation center position
 * \todo
 *
 * \subsection U1page0_3_4_sec6_3 Particle III. generation center position
 * \todo
 *
 *
 * \section U1page0_3_4_sec7 Velocity vectors
 * \todo
 *
 * \subsection U1page0_3_4_sec7_1 Bosons and I. generation fermions translational motion vectors
 * \todo
 *
 * \subsection U1page0_3_4_sec7_2 II. generation fermions translational motion vectors
 * \todo
 *
 * \subsection U1page0_3_4_sec7_3 III. generation fermions translational motion vectors
 * \todo
 *
 *
 * \section U1page0_3_4_sec8 Angular velocity vectors
 * \todo
 *
 * \subsection U1page0_3_4_sec8_1 Bosons and I. generation fermions body rotation vector
 * \todo
 *
 * \subsection U1page0_3_4_sec8_2 II. generation fermions body rotation vector
 * \todo
 */
