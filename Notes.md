# Computer Graphics

## Types of Computer Graphics
- Modeling: Creating 3D models of objects
- Rendering: Creating 2D images from 3D models
- Animation: Creating motion from 3D models

## Check if a ray intersects a triangle in 3D space
Consider ray with origin `E`, direction `D` and scalar `t`: $ E + tD $
Triangle with vertices `a`, `b`, `c`.
Point `P` on the plane of the triangle: $ E + tD = \alpha + + \beta (b - a) + \gamma (c - a) $
where $\alpha, \beta, \gamma$ are scalars and $a, b, c$ are the vertices of the triangle.

We have three equations:
1. $ E_x + tD_x = \alpha_x + \beta (b_x - a_x) + \gamma (c_x - a_x) $
2. $ E_y + tD_y = \alpha_y + \beta (b_y - a_y) + \gamma (c_y - a_y) $
3. $ E_z + tD_z = \alpha_z + \beta (b_z - a_z) + \gamma (c_z - a_z) $

We can solve these equations to find the intersection point.

This can be represented as matrix equation: $ A \cdot X = B $

where:
$ A = \begin{bmatrix} b_x - a_x & c_x - a_x & -D_x \\ b_y - a_y & c_y - a_y & -D_y \\ b_z - a_z & c_z - a_z & -D_z \end{bmatrix} $
$ X = \begin{bmatrix} \beta \\ \gamma \\ t \end{bmatrix} $
$ B = \begin{bmatrix} a_x - E_x \\ a_y - E_y \\ a_z - E_z \end{bmatrix} $

$ A $ stands for the coefficients of the unknowns, $ X $ is the unknowns and $ B $ is the constants.

If $ \beta, \gamma, t $ are all positive, then the ray intersects the triangle.

## Geometry Pipeline

### Linear Perspective

Linear perspective is a technique used in art and computer graphics to create the illusion of depth and space on a flat surface. This method was developed during the Renaissance by artists like Filippo Brunelleschi and later documented by Leon Battista Alberti.

#### Key Components of Linear Perspective

1. **Horizon Line**: This is the distant line where the sky appears to meet the ground. It represents the viewer's eye level.
2. **Vanishing Point**: All parallel lines (orthogonals) converge at this point on the horizon line. It is the point where objects appear to disappear into the distance.
3. **Orthogonals**: These are the parallel lines that recede into the distance and converge at the vanishing point.

#### How It Works

- Objects closer to the viewer appear larger, while objects further away appear smaller.
- By arranging objects along orthogonals that converge at the vanishing point, artists can create a realistic sense of depth.

#### Example

Consider a road that seems to narrow as it stretches into the distance. The sides of the road are orthogonals that converge at a vanishing point on the horizon line.

### Projective Geometry and Homogeneous Coordinates

#### Why Everything is Linear in Projective Geometry

Projective geometry extends Euclidean geometry by adding points at infinity where parallel lines intersect. This approach simplifies many geometric transformations and makes them linear.

#### Homogeneous Coordinates

In projective geometry, points are represented using homogeneous coordinates. A point in the Euclidean plane $(x, y)$ is represented in homogeneous coordinates as $(X, Y, Z)$, where $X = xZ$ and $Y = yZ$.

#### Benefits of Homogeneous Coordinates

1. **Simplification of Transformations**: Many transformations that are non-linear in Cartesian coordinates become linear in homogeneous coordinates. For example, perspective projection can be represented as a linear transformation.
2. **Representation of Points at Infinity**: Homogeneous coordinates allow for the representation of points at infinity, which are essential in projective geometry.

#### Example

A point $(x, y)$ in Cartesian coordinates can be represented as $(x, y, 1)$ in homogeneous coordinates. If we multiply all coordinates by a non-zero scalar $k$, the point remains the same: $(kx, ky, k)$.

#### Perspective Projection

The perspective projection of a point $(X, Y, Z)$ onto the image plane $Z = 1$ is given by:

$$
(x, y) = \left( \frac{X}{Z}, \frac{Y}{Z} \right)
$$

This transformation is linear in homogeneous coordinates:

$$ 
\begin{bmatrix}
x \\
y \\
1
\end{bmatrix}
=
\begin{bmatrix}
\frac{X}{Z} \\
\frac{Y}{Z} \\
1
\end{bmatrix}
=
\begin{bmatrix}
X \\
Y \\
Z
\end{bmatrix}
\cdot
\begin{bmatrix}
\frac{1}{Z} \\
\frac{1}{Z} \\
\frac{1}{Z}
\end{bmatrix}
$$

---

# Movement and Orientation in 2D and 3D

## Scaling

Scaling is a transformation that changes the size of an object without changing its shape. It is a fundamental operation in computer graphics for resizing objects.

### 2D Scaling

In 2D, scaling transforms a point $(x, y)$ to a new position $(x', y')$ by multiplying the coordinates by scaling factors $s_x$ and $s_y$.

#### Formula

The scaling transformation can be represented as:
$$
\begin{bmatrix}
x' \\
y'
\end{bmatrix}
=
\begin{bmatrix}
s_x & 0 \\
0 & s_y
\end{bmatrix}
\begin{bmatrix}
x \\
y
\end{bmatrix}
$$

#### Intuition

- **Scaling Factors**: $s_x$ and $s_y$ determine how much the object is scaled along the x and y axes, respectively.
    - If $s_x > 1$ and $s_y > 1$, the object enlarges.
    - If $0 < s_x < 1$ and $0 < s_y < 1$, the object shrinks.
    - If $s_x = 1$ and $s_y = 1$, the object remains the same size.

#### Example

If we have a point at $(2, 3)$ and apply scaling factors $s_x = 2$ and $s_y = 3$, the new position of the point will be:
$$
\begin{bmatrix}
x' \\
y'
\end{bmatrix}
=
\begin{bmatrix}
2 & 0 \\
0 & 3
\end{bmatrix}
\begin{bmatrix}
2 \\
3
\end{bmatrix}
=
\begin{bmatrix}
4 \\
9
\end{bmatrix}
$$

#### Homogeneous Coordinates

In homogeneous coordinates, a point $(x, y)$ is represented as $(x, y, 1)$. The scaling matrix is:
$$
\begin{bmatrix}
s_x & 0 & 0 \\
0 & s_y & 0 \\
0 & 0 & 1
\end{bmatrix}
$$

The new position is obtained by multiplying the scaling matrix with the point:

$$ \begin{bmatrix} x' \\ y' \\ 1 \end{bmatrix} = \begin{bmatrix} s_x & 0 & 0 \\ 0 & s_y & 0 \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} x \\ y \\ 1 \end{bmatrix} $$

## 3D Scaling

In 3D, scaling transforms a point $(x, y, z)$ to a new position $(x', y', z')$ by multiplying the coordinates by scaling factors $s_x$, $s_y$, and $s_z$.

### Formula

The scaling transformation can be represented as:
$$
\begin{bmatrix}
x' \\
y' \\
z'
\end{bmatrix}
=
\begin{bmatrix}
s_x & 0 & 0 \\
0 & s_y & 0 \\
0 & 0 & s_z
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z
\end{bmatrix}
$$

### Intuition

- **Scaling Factors**: $s_x$, $s_y$, and $s_z$ determine how much the object is scaled along the x, y, and z axes, respectively.
    - If $s_x > 1$, $s_y > 1$, and $s_z > 1$, the object enlarges.
    - If $0 < s_x < 1$, $0 < s_y < 1$, and $0 < s_z < 1$, the object shrinks.
    - If $s_x = 1$, $s_y = 1$, and $s_z = 1$, the object remains the same size.

### Example

If we have a point at $(2, 3, 4)$ and apply scaling factors $s_x = 2$, $s_y = 3$, and $s_z = 4$, the new position of the point will be:
$$
\begin{bmatrix}
x' \\
y' \\
z'
\end{bmatrix}
=
\begin{bmatrix}
2 & 0 & 0 \\
0 & 3 & 0 \\
0 & 0 & 4
\end{bmatrix}
\begin{bmatrix}
2 \\
3 \\
4
\end{bmatrix}
=
\begin{bmatrix}
4 \\
9 \\
16
\end{bmatrix}
$$

### Homogeneous Coordinates

In homogeneous coordinates, a point $(x, y, z)$ is represented as $(x, y, z, 1)$. The scaling matrix is:
$$
\begin{bmatrix}
s_x & 0 & 0 & 0 \\
0 & s_y & 0 & 0 \\
0 & 0 & s_z & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

The new position is obtained by multiplying the scaling matrix with the point:
$$
\begin{bmatrix}
x' \\
y' \\
z' \\
1
\end{bmatrix}
=
\begin{bmatrix}
s_x & 0 & 0 & 0 \\
0 & s_y & 0 & 0 \\
0 & 0 & s_z & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z \\
1
\end{bmatrix}
$$

## Translations

Translation is a type of transformation that shifts every point of an object by the same distance in a given direction. It is one of the simplest forms of transformation and is used extensively in computer graphics to move objects around the scene.

### 2D Translations

In 2D, a translation moves a point $(x, y)$ to a new position $(x', y')$ by adding a translation vector $(t_x, t_y)$.

#### Formula

The translation can be represented as:

$$ \begin{bmatrix} x' \\ y' \end{bmatrix} = \begin{bmatrix} x \\ y \end{bmatrix} + \begin{bmatrix} t_x \\ t_y \end{bmatrix} $$

#### Intuition

- **Translation Vector**: The vector $(t_x, t_y)$ specifies how far and in which direction to move the point.
- **Uniform Movement**: Every point in the object moves the same distance in the same direction, preserving the shape and orientation of the object.

#### Example

If we have a point at $(2, 3)$ and we apply a translation vector $(1, -2)$, the new position of the point will be:
$$ \begin{bmatrix} 2 \\ 3 \end{bmatrix} + \begin{bmatrix} 1 \\ -2 \end{bmatrix} = \begin{bmatrix} 3 \\ 1 \end{bmatrix} $$

### 3D Translations

In 3D, a translation moves a point $(x, y, z)$ to a new position $(x', y', z')$ by adding a translation vector $(t_x, t_y, t_z)$.

#### Formula

The translation can be represented as:
$$ \begin{bmatrix} x' \\ y' \\ z' \end{bmatrix} = \begin{bmatrix} x \\ y \\ z \end{bmatrix} + \begin{bmatrix} t_x \\ t_y \\ t_z \end{bmatrix} $$

#### Intuition

- **Translation Vector**: The vector $(t_x, t_y, t_z)$ specifies how far and in which direction to move the point in 3D space.
- **Uniform Movement**: Every point in the object moves the same distance in the same direction, preserving the shape and orientation of the object.

#### Example

If we have a point at $(2, 3, 4)$ and we apply a translation vector $(1, -2, 3)$, the new position of the point will be:
$$ \begin{bmatrix} 2 \\ 3 \\ 4 \end{bmatrix} + \begin{bmatrix} 1 \\ -2 \\ 3 \end{bmatrix} = \begin{bmatrix} 3 \\ 1 \\ 7 \end{bmatrix} $$

### Homogeneous Coordinates

Translations can also be represented using homogeneous coordinates, which allow for the use of matrix multiplication to perform the translation.

#### 2D Translation Matrix

In homogeneous coordinates, a point $(x, y)$ is represented as $(x, y, 1)$. The translation matrix for a vector $(t_x, t_y)$ is:
$$
\begin{bmatrix}
1 & 0 & t_x \\
0 & 1 & t_y \\
0 & 0 & 1
\end{bmatrix}
$$

The new position is obtained by multiplying the translation matrix with the point:
$$
\begin{bmatrix}
x' \\
y' \\
1
\end{bmatrix}
=
\begin{bmatrix}
1 & 0 & t_x \\
0 & 1 & t_y \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
1
\end{bmatrix}
$$

#### 3D Translation Matrix

In homogeneous coordinates, a point $(x, y, z)$ is represented as $(x, y, z, 1)$. The translation matrix for a vector $(t_x, t_y, t_z)$ is:
$$
\begin{bmatrix}
1 & 0 & 0 & t_x \\
0 & 1 & 0 & t_y \\
0 & 0 & 1 & t_z \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

The new position is obtained by multiplying the translation matrix with the point:
$$
\begin{bmatrix}
x' \\
y' \\
z' \\
1
\end{bmatrix}
=
\begin{bmatrix}
1 & 0 & 0 & t_x \\
0 & 1 & 0 & t_y \\
0 & 0 & 1 & t_z \\
0 & 0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z \\
1
\end{bmatrix}
$$

## Rotations

Rotation is a transformation that turns every point of an object around a fixed point, known as the pivot point, by a certain angle. This transformation is crucial in computer graphics for changing the orientation of objects.

### 2D Rotations

In 2D, rotation moves a point $(x, y)$ to a new position $(x', y')$ by rotating it around the origin or a specified pivot point.

#### Rotation Around the Origin

To rotate a point $(x, y)$ around the origin by an angle $\theta$, we use the following formulas:

$$
\begin{bmatrix}
x' \\
y'
\end{bmatrix}
=
\begin{bmatrix}
\cos \theta & -\sin \theta \\
\sin \theta & \cos \theta
\end{bmatrix}
\begin{bmatrix}
x \\
y
\end{bmatrix}
$$

#### Intuition

- **Angle $\theta$**: The angle of rotation, measured in degrees or radians.
- **Counterclockwise Rotation**: Positive values of $\theta$ result in counterclockwise rotation.
- **Clockwise Rotation**: Negative values of $\theta$ result in clockwise rotation.

#### Example

If we rotate a point $(1, 0)$ by 90 degrees counterclockwise, the new position is:

$$
\begin{bmatrix}
x' \\
y'
\end{bmatrix}
=
\begin{bmatrix}
\cos 90^\circ & -\sin 90^\circ \\
\sin 90^\circ & \cos 90^\circ
\end{bmatrix}
\begin{bmatrix}
1 \\
0
\end{bmatrix}
=
\begin{bmatrix}
0 \\
1
\end{bmatrix}
$$

#### Rotation Around a Pivot Point

To rotate a point $(x, y)$ around a pivot point $(p_x, p_y)$, we first translate the point to the origin, perform the rotation, and then translate it back.

1. **Translate** the point to the origin:
   $$
   x' = x - p_x \\
   y' = y - p_y
   $$

2. **Rotate** the point around the origin:
   $$
   \begin{bmatrix}
   x'' \\
   y''
   \end{bmatrix}
   =
   \begin{bmatrix}
   \cos \theta & -\sin \theta \\
   \sin \theta & \cos \theta
   \end{bmatrix}
   \begin{bmatrix}
   x' \\
   y'
   \end{bmatrix}
   $$

3. **Translate** the point back:
   $$
   x''' = x'' + p_x \\
   y''' = y'' + p_y
   $$

### 3D Rotations

In 3D, rotation is more complex as it involves rotating around an axis (x, y, or z).

#### Rotation Around the X-Axis

To rotate a point $(x, y, z)$ around the x-axis by an angle $\theta$:

$$
\begin{bmatrix}
x' \\
y' \\
z'
\end{bmatrix}
=
\begin{bmatrix}
1 & 0 & 0 \\
0 & \cos \theta & -\sin \theta \\
0 & \sin \theta & \cos \theta
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z
\end{bmatrix}
$$

#### Rotation Around the Y-Axis

To rotate a point $(x, y, z)$ around the y-axis by an angle $\theta$:

$$
\begin{bmatrix}
x' \\
y' \\
z'
\end{bmatrix}
=
\begin{bmatrix}
\cos \theta & 0 & \sin \theta \\
0 & 1 & 0 \\
-\sin \theta & 0 & \cos \theta
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z
\end{bmatrix}
$$

#### Rotation Around the Z-Axis

To rotate a point $(x, y, z)$ around the z-axis by an angle $\theta$:

$$
\begin{bmatrix}
x' \\
y' \\
z'
\end{bmatrix}
=
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 \\
\sin \theta & \cos \theta & 0 \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z
\end{bmatrix}
$$

### Intuition Behind 3D Rotations

- **Axis of Rotation**: The line around which the rotation occurs.
- **Angle $\theta$**: The angle of rotation, which determines how far the point is rotated around the axis.
- **Right-Hand Rule**: If you point the thumb of your right hand along the axis of rotation, your fingers curl in the direction of positive rotation.

### Homogeneous Coordinates

Rotations can also be represented using homogeneous coordinates, which allow for the use of matrix multiplication to perform the rotation.

#### 2D Rotation Matrix

In homogeneous coordinates, a point $(x, y)$ is represented as $(x, y, 1)$. The rotation matrix for an angle $\theta$ is:

$$
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 \\
\sin \theta & \cos \theta & 0 \\
0 & 0 & 1
\end{bmatrix}
$$

The new position is obtained by multiplying the rotation matrix with the point:

$$
\begin{bmatrix}
x' \\
y' \\
1
\end{bmatrix}
=
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 \\
\sin \theta & \cos \theta & 0 \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
1
\end{bmatrix}
$$

#### 3D Rotation Matrices

In homogeneous coordinates, a point $(x, y, z)$ is represented as $(x, y, z, 1)$ - The rotation matrices for the x, y, and z axes are:

- **X-Axis**:
  $$
  \begin{bmatrix}
  1 & 0 & 0 & 0 \\
  0 & \cos \theta & -\sin \theta & 0 \\
  0 & \sin \theta & \cos \theta & 0 \\
  0 & 0 & 0 & 1
  \end{bmatrix}
  $$

- **Y-Axis**:
  $$
  \begin{bmatrix}
  \cos \theta & 0 & \sin \theta & 0 \\
  0 & 1 & 0 & 0 \\
  -\sin \theta & 0 & \cos \theta & 0 \\
  0 & 0 & 0 & 1
  \end{bmatrix}
  $$

- **Z-Axis**:
  $$
  \begin{bmatrix}
  \cos \theta & -\sin \theta & 0 & 0 \\
  \sin \theta & \cos \theta & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & 0 & 0 & 1
  \end{bmatrix}
  $$


### Combined Transformation Matrix


To rotate an object around a pivot point $(p_x, p_y)$ in 2D, you can combine the translation and rotation into a single matrix.

#### Steps

1. **Translate** the object so that the pivot point moves to the origin.
2. **Rotate** the object around the origin.
3. **Translate** the object back to the original pivot point.

The combined transformation matrix $T$ is obtained by multiplying the individual matrices for translation and rotation.

#### Translation to Origin

The translation matrix to move the pivot point $(p_x, p_y)$ to the origin is:
$$
T_{\text{to origin}} =
\begin{bmatrix}
1 & 0 & -p_x \\
0 & 1 & -p_y \\
0 & 0 & 1
\end{bmatrix}
$$

#### Rotation Around Origin

The rotation matrix for an angle $\theta$ is:
$$
R =
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 \\
\sin \theta & \cos \theta & 0 \\
0 & 0 & 1
\end{bmatrix}
$$

#### Translation Back

The translation matrix to move the pivot point back to its original position is:
$$
T_{\text{back}} =
\begin{bmatrix}
1 & 0 & p_x \\
0 & 1 & p_y \\
0 & 0 & 1
\end{bmatrix}
$$

### Combined Matrix 2D

The combined transformation matrix $T$ is:
$$
T = T_{\text{back}} \cdot R \cdot T_{\text{to origin}}
$$

Substituting the matrices, we get:
$$
T =
\begin{bmatrix}
1 & 0 & p_x \\
0 & 1 & p_y \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 \\
\sin \theta & \cos \theta & 0 \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & -p_x \\
0 & 1 & -p_y \\
0 & 0 & 1
\end{bmatrix}
$$

Multiplying these matrices together, we get:
$$
T =
\begin{bmatrix}
\cos \theta & -\sin \theta & p_x (1 - \cos \theta) + p_y \sin \theta \\
\sin \theta & \cos \theta & p_y (1 - \cos \theta) - p_x \sin \theta \\
0 & 0 & 1
\end{bmatrix}
$$

### Applying the Combined Matrix

To apply the combined transformation matrix $T$ to a point $(x, y)$, we use:
$$
\begin{bmatrix}
x' \\
y' \\
1
\end{bmatrix}
=
T
\begin{bmatrix}
x \\
y \\
1
\end{bmatrix}
$$


### Combined Transformation Matrix 3D

The combined transformation matrix $T$ is obtained by multiplying the individual matrices for translation and rotation.

#### Translation to Origin

The translation matrix to move the pivot point $(p_x, p_y, p_z)$ to the origin is:
$$
T_{\text{to origin}} =
\begin{bmatrix}
1 & 0 & 0 & -p_x \\
0 & 1 & 0 & -p_y \\
0 & 0 & 1 & -p_z \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

#### Rotation Around the Origin

The rotation matrix depends on the axis of rotation. For simplicity, let's consider rotation around the z-axis by an angle $\theta$:

$$
R_z =
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 & 0 \\
\sin \theta & \cos \theta & 0 & 0 \\
0 & 0 & 1 & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

#### Translation Back

The translation matrix to move the pivot point back to its original position is:
$$
T_{\text{back}} =
\begin{bmatrix}
1 & 0 & 0 & p_x \\
0 & 1 & 0 & p_y \\
0 & 0 & 1 & p_z \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

### Combined Matrix

The combined transformation matrix $T$ is:
$$
T = T_{\text{back}} \cdot R_z \cdot T_{\text{to origin}}
$$

Substituting the matrices, we get:
$$
T =
\begin{bmatrix}
1 & 0 & 0 & p_x \\
0 & 1 & 0 & p_y \\
0 & 0 & 1 & p_z \\
0 & 0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 & 0 \\
\sin \theta & \cos \theta & 0 & 0 \\
0 & 0 & 1 & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 & -p_x \\
0 & 1 & 0 & -p_y \\
0 & 0 & 1 & -p_z \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

Multiplying these matrices together, we get:
$$
T =
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 & p_x (1 - \cos \theta) + p_y \sin \theta \\
\sin \theta & \cos \theta & 0 & p_y (1 - \cos \theta) - p_x \sin \theta \\
0 & 0 & 1 & p_z \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

### Applying the Combined Matrix

To apply the combined transformation matrix $T$ to a point $(x, y, z)$, we use:
$$
\begin{bmatrix}
x' \\
y' \\
z' \\
1
\end{bmatrix}
=
T
\begin{bmatrix}
x \\
y \\
z \\
1
\end{bmatrix}
$$

This single matrix multiplication performs the entire sequence of translating to the origin, rotating, and translating back in one step.


## Rotation Around an Arbitrary Axis $(k_x, k_y, k_z)$

Rotating around an arbitrary axis in 3D space is more complex than rotating around the principal axes (x, y, z). However, it can be achieved using a combination of translations and rotations.

### Steps to Rotate Around an Arbitrary Axis

1. **Translate** the object so that the arbitrary axis passes through the origin.
2. **Align** the arbitrary axis with one of the principal axes (e.g., the z-axis).
3. **Perform** the rotation around the aligned axis.
4. **Reverse** the alignment transformation.
5. **Translate** the object back to its original position.

#### Combined Transformation Matrix

To rotate a point $(x, y, z)$ around an arbitrary axis $(k_x, k_y, k_z)$ by an angle $\theta$, we use the following steps:

##### 1. Translate to Origin

Translate the object so that the arbitrary axis passes through the origin. The translation matrix is:
$$
T_{\text{to origin}} =
\begin{bmatrix}
1 & 0 & 0 & -k_x \\
0 & 1 & 0 & -k_y \\
0 & 0 & 1 & -k_z \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

##### 2. Align with Principal Axis

Align the arbitrary axis with the z-axis. This involves two rotations:
- **Rotate** around the y-axis to align the projection of the axis onto the xz-plane.
- **Rotate** around the x-axis to align the axis with the z-axis.

Let $\alpha$ be the angle to rotate around the y-axis, and $\beta$ be the angle to rotate around the x-axis.

The rotation matrices are:
$$
R_y(\alpha) =
\begin{bmatrix}
\cos \alpha & 0 & \sin \alpha & 0 \\
0 & 1 & 0 & 0 \\
-\sin \alpha & 0 & \cos \alpha & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

$$
R_x(\beta) =
\begin{bmatrix}
1 & 0 & 0 & 0 \\
0 & \cos \beta & -\sin \beta & 0 \\
0 & \sin \beta & \cos \beta & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

##### 3. Rotate Around the Z-Axis

Perform the rotation around the z-axis by an angle $\theta$:
$$
R_z(\theta) =
\begin{bmatrix}
\cos \theta & -\sin \theta & 0 & 0 \\
\sin \theta & \cos \theta & 0 & 0 \\
0 & 0 & 1 & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

##### 4. Reverse Alignment

Reverse the alignment transformations:
$$
R_x(-\beta) =
\begin{bmatrix}
1 & 0 & 0 & 0 \\
0 & \cos (-\beta) & -\sin (-\beta) & 0 \\
0 & \sin (-\beta) & \cos (-\beta) & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

$$
R_y(-\alpha) =
\begin{bmatrix}
\cos (-\alpha) & 0 & \sin (-\alpha) & 0 \\
0 & 1 & 0 & 0 \\
-\sin (-\alpha) & 0 & \cos (-\alpha) & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

##### 5. Translate Back

Translate the object back to its original position:
$$
T_{\text{back}} =
\begin{bmatrix}
1 & 0 & 0 & k_x \\
0 & 1 & 0 & k_y \\
0 & 0 & 1 & k_z \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

#### Combined Matrix

The combined transformation matrix $T$ is:
$$
T = T_{\text{back}} \cdot R_y(-\alpha) \cdot R_x(-\beta) \cdot R_z(\theta) \cdot R_x(\beta) \cdot R_y(\alpha) \cdot T_{\text{to origin}}
$$

#### Applying the Combined Matrix

To apply the combined transformation matrix $T$ to a point $(x, y, z)$, we use:
$$
\begin{bmatrix}
x' \\
y' \\
z' \\
1
\end{bmatrix}
=
T
\begin{bmatrix}
x \\
y \\
z \\
1
\end{bmatrix}
$$

This single matrix multiplication performs the entire sequence of translating to the origin, aligning with the principal axis, rotating, reversing the alignment, and translating back in one step.

## Non-Commutativity of Transformations

In computer graphics, transformations such as translation, rotation, and scaling are generally not commutative. This means that the order in which you apply these transformations matters. Applying transformation A followed by transformation B usually yields a different result than applying transformation B followed by transformation A.

### Example in 2D

Let's consider a point $(x, y)$ and apply a translation followed by a rotation, and then a rotation followed by a translation.

#### Translation Followed by Rotation

1. **Translation**: Translate the point by $(t_x, t_y)$:
$  \begin{bmatrix}   x' \\   y'   \end{bmatrix}   =   \begin{bmatrix}   x \\   y   \end{bmatrix}     +   \begin{bmatrix}   t_x \\   t_y   end{bmatrix}   $

2. **Rotation**: Rotate the translated point by an angle $\theta$:
$   \begin{bmatrix}   x'' \\   y''   \end{bmatrix}   =   \begin{bmatrix}   \cos \theta & -\sin \theta \\   \sin \theta & \cos \theta   end{bmatrix}   \begin{bmatrix}   x' \\   y'   \end{bmatrix}   $

#### Rotation Followed by Translation

1. **Rotation**: Rotate the point by an angle $\theta$:
   $$
   \begin{bmatrix}
   x' \\
   y'
   \end{bmatrix}
   =
   \begin{bmatrix}
   \cos \theta & -\sin \theta \\
   \sin \theta & \cos \theta
   \end{bmatrix}
   \begin{bmatrix}
   x \\
   y
   \end{bmatrix}
   $$

2. **Translation**: Translate the rotated point by $(t_x, t_y)$:

$$
   \begin{bmatrix}
   x'' \\
   y'' \\
   \end{bmatrix}
   =
   \begin{bmatrix}
   x' \\
   y'
   \end{bmatrix}
    +
   \begin{bmatrix}
   t_x \\
   t_y
   \end{bmatrix}
   $$

#### Comparison

The final positions $(x'', y'')$ obtained from the two sequences of transformations will generally be different, demonstrating that translation and rotation are not commutative.

### Example in 3D

Let's consider a point $(x, y, z)$ and apply a scaling followed by a rotation, and then a rotation followed by a scaling.

#### Scaling Followed by Rotation

1. **Scaling**: Scale the point by factors $(s_x, s_y, s_z)$:
   $$
   \begin{bmatrix}
   x' \\
   y' \\
   z'
   \end{bmatrix}
   =
   \begin{bmatrix}
   s_x & 0 & 0 \\
   0 & s_y & 0 \\
   0 & 0 & s_z
   \end{bmatrix}
   \begin{bmatrix}
   x \\
   y \\
   z
   \end{bmatrix}
   $$

2. **Rotation**: Rotate the scaled point around the z-axis by an angle $\theta$:
   $$
   \begin{bmatrix}
   x'' \\
   y'' \\
   z''
   \end{bmatrix}
   =
   \begin{bmatrix}
   \cos \theta & -\sin \theta & 0 \\
   \sin \theta & \cos \theta & 0 \\
   0 & 0 & 1
   \end{bmatrix}
   \begin{bmatrix}
   x' \\
   y' \\
   z'
   \end{bmatrix}
   $$

#### Rotation Followed by Scaling

1. **Rotation**: Rotate the point around the z-axis by an angle $\theta$:
   $$
   \begin{bmatrix}
   x' \\
   y' \\
   z'
   \end{bmatrix}
   =
   \begin{bmatrix}
   \cos \theta & -\sin \theta & 0 \\
   \sin \theta & \cos \theta & 0 \\
   0 & 0 & 1
   \end{bmatrix}
   \begin{bmatrix}
   x \\
   y \\
   z
   \end{bmatrix}
   $$

2. **Scaling**: Scale the rotated point by factors $(s_x, s_y, s_z)$:
   $$
   \begin{bmatrix}
   x'' \\
   y'' \\
   z''
   \end{bmatrix}
   =
   \begin{bmatrix}
   s_x & 0 & 0 \\
   0 & s_y & 0 \\
   0 & 0 & s_z
   \end{bmatrix}
   \begin{bmatrix}
   x' \\
   y' \\
   z'
   \end{bmatrix}
   $$

#### Comparison

The final positions $(x'', y'', z'')$ obtained from the two sequences of transformations will generally be different, demonstrating that scaling and rotation are not commutative.

### Conclusion

The non-commutativity of transformations means that the order in which you apply transformations matters. This property is crucial in computer graphics, as it affects how objects are manipulated and displayed in a scene.

# Local vs. Global Interpretation

In computer graphics, transformations can be interpreted in two different ways: globally and locally. These interpretations affect how we understand the transformation of points and coordinate systems.

## Global Interpretation

### Points Multiply from the Right

When we multiply points by transformation matrices from the right, we are transforming the points with respect to a **global coordinate system**. This means that the transformations are applied to the points as if they are in a fixed, universal coordinate system.

#### Example

Consider a point $(x, y, z)$ and a transformation matrix $T$. The global interpretation is:
$$
\begin{bmatrix}
x' \\
y' \\
z' \\
1
\end{bmatrix}
=
T
\begin{bmatrix}
x \\
y \\
z \\
1
\end{bmatrix}
$$

Here, $T$ could be a translation, rotation, or scaling matrix. The point $(x, y, z)$ is transformed with respect to the global coordinate system.

### Intuition

- **Global Coordinate System**: The transformations are applied as if the points are in a fixed, universal coordinate system.
- **Consistency**: This approach ensures that all points are transformed consistently with respect to the same reference frame.

## Local Interpretation

### Matrices from the Left

When we look at the matrices from the left, we interpret these transformations as a change of the origin or coordinate system. This establishes a **local coordinate system**. In this interpretation, the transformations are applied as if the coordinate system itself is being transformed.

#### Example

Consider the same point $(x, y, z)$ and transformation matrix $T$. The local interpretation is:
$$
\begin{bmatrix}
x' \\
y' \\
z' \\
1
\end{bmatrix}
=
\begin{bmatrix}
x \\
y \\
z \\
1
\end{bmatrix}
T
$$

Here, the transformation matrix $T$ is applied as if the coordinate system is being transformed, rather than the points themselves.

### Intuition

- **Local Coordinate System**: The transformations are applied as if the coordinate system itself is being transformed.
- **Relative Transformations**: This approach is useful for understanding how objects move relative to their own local coordinate systems.

## Comparison

### Global Interpretation

- **Transforms Points**: Points are transformed with respect to a fixed, global coordinate system.
- **Consistency**: Ensures consistent transformation of all points in the scene.

### Local Interpretation

- **Transforms Coordinate System**: The coordinate system itself is transformed, affecting how points are interpreted.
- **Relative Movement**: Useful for understanding relative movements and transformations within a local frame of reference.

### Practical Example

Consider a robot arm with multiple joints. Using the global interpretation, each joint's position is calculated with respect to a fixed, global coordinate system. Using the local interpretation, each joint's position is calculated relative to the previous joint, establishing a local coordinate system for each segment of the arm.

Understanding these two interpretations helps in designing and implementing complex transformations in computer graphics, ensuring that objects are manipulated correctly within their respective coordinate systems.


## Perspective Projection

Perspective projection is a technique used to project 3D points onto a 2D plane, mimicking how the human eye perceives the world. This is achieved using the **pinhole camera model**.

### Pinhole Camera Model

In the pinhole camera model, a 3D point $(X, Y, Z)$ is projected onto a 2D image plane at $(x, y)$ using the following equations:
$$
x = \frac{fX}{Z}, \quad y = \frac{fY}{Z}
$$
where $f$ is the focal length of the camera.

### Deriving the Projection Matrix

To derive the projection matrix, we use homogeneous coordinates. A 3D point $(X, Y, Z)$ in homogeneous coordinates is represented as $(X, Y, Z, 1)$. The projection matrix $P$ transforms this point to the 2D image plane:
$$
\begin{bmatrix}
x \\
y \\
w
\end{bmatrix}
=
\begin{bmatrix}
f & 0 & 0 & 0 \\
0 & f & 0 & 0 \\
0 & 0 & 1 & 0
\end{bmatrix}
\begin{bmatrix}
X \\
Y \\
Z \\
1
\end{bmatrix}
$$
After dividing by $w$, we get the 2D coordinates $(x, y)$.

### Virtual Camera Model

The virtual camera model includes the intrinsic and extrinsic parameters of the camera.

- **Intrinsic Parameters**: These define the camera's internal characteristics, such as focal length and principal point. The intrinsic matrix $K$ is:
  $$
  K =
  \begin{bmatrix}
  f_x & 0 & c_x \\
  0 & f_y & c_y \\
  0 & 0 & 1
  \end{bmatrix}
  $$
  where $f_x$ and $f_y$ are the focal lengths in the x and y directions, and $(c_x, c_y)$ is the principal point.

- **Extrinsic Parameters**: These define the camera's position and orientation in the world. The extrinsic matrix $ [R|t] $ combines rotation $R$ and translation $t$.

The complete projection matrix $P$ is:
$$
P = K [R|t]
$$

## Mapping to Pixels: Viewport Transformation

After projecting the 3D points onto the 2D image plane, we need to map these coordinates to the pixel coordinates on the screen. This is done using the viewport transformation.

### Viewport Transformation

The viewport transformation maps the normalized device coordinates (NDC) to screen coordinates (pixels). The transformation involves scaling and translating the coordinates to fit the viewport.

#### Steps

1. **Normalize** the coordinates to the range $[-1, 1]$.
2. **Scale** the normalized coordinates to the viewport size.
3. **Translate** the scaled coordinates to the viewport position.

The transformation can be represented as:
$$
x_{viewport} = \frac{(x_{ndc} + 1)}{2} \cdot width + x_{min}
$$
$$
y_{viewport} = \frac{(y_{ndc} + 1)}{2} \cdot height + y_{min}
$$

## Complete Camera Model

The complete camera model combines the projection matrix, camera matrix, and viewport transformation to map 3D world coordinates to 2D pixel coordinates.

### Components

1. **Camera Matrix**: Combines intrinsic and extrinsic parameters.
2. **Projection Matrix**: Projects 3D points onto the 2D image plane.
3. **Viewport Transformation**: Maps the 2D image plane coordinates to pixel coordinates.

### Final Transformation

The final transformation can be represented as:
$$
\text{Pixel Coordinates} = \text{Viewport Transformation} \times \text{Projection Matrix} \times \text{Camera Matrix} \times \text{World Coordinates}
$$

This complete model ensures that 3D points in the world are accurately projected onto the 2D image plane and mapped to the correct pixel coordinates on the screen.

# Near and Far Clipping Planes

## Explanation

### Near Clipping Plane

The near clipping plane is an imaginary plane located at a certain distance from the camera along its sight line. It defines the closest point to the camera that will be rendered. Any object closer to the camera than this plane will not be visible.

### Far Clipping Plane

The far clipping plane is another imaginary plane located at a certain distance from the camera along its sight line. It defines the farthest point from the camera that will be rendered. Any object farther from the camera than this plane will not be visible.

### Why We Need Clipping Planes

1. **Preventing Artifacts**: Without a near clipping plane, objects very close to the camera could cause rendering artifacts due to precision issues.
2. **Performance Optimization**: Clipping planes help in culling objects that are too close or too far from the camera, reducing the number of objects that need to be processed and rendered.
3. **Depth Buffer Precision**: The range between the near and far clipping planes affects the precision of the depth buffer. A smaller range improves depth precision, reducing z-fighting issues.

## Deriving the New Projection Matrix

To include the near and far clipping planes in the projection matrix, we need to modify the standard perspective projection matrix. Let's derive the new projection matrix step by step.

### Standard Perspective Projection Matrix

The standard perspective projection matrix without clipping planes is:
$$
P =
\begin{bmatrix}
f & 0 & 0 & 0 \\
0 & f & 0 & 0 \\
0 & 0 & 1 & 0 \\
0 & 0 & 1 & 0
\end{bmatrix}
$$
where $f$ is the focal length.

### Including Near and Far Clipping Planes

To include the near ($n$) and far ($f$) clipping planes, we modify the projection matrix as follows:
$$
P =
\begin{bmatrix}
\frac{2n}{r-l} & 0 & \frac{r+l}{r-l} & 0 \\
0 & \frac{2n}{t-b} & \frac{t+b}{t-b} & 0 \\
0 & 0 & -\frac{f+n}{f-n} & -\frac{2fn}{f-n} \\
0 & 0 & -1 & 0
\end{bmatrix}
$$
where:
- $r$ and $l$ are the right and left extents of the view frustum.
- $t$ and $b$ are the top and bottom extents of the view frustum.
- $n$ and $f$ are the near and far clipping planes.

### Final Projection Matrix

The final projection matrix, including the near and far clipping planes, ensures that objects outside the defined range are not rendered, optimizing performance and improving depth precision.

## Complete Camera Model

The complete camera model combines the projection matrix, camera matrix, and viewport transformation to map 3D world coordinates to 2D pixel coordinates.

### Components

1. **Camera Matrix**: Combines intrinsic and extrinsic parameters.
2. **Projection Matrix**: Projects 3D points onto the 2D image plane, including near and far clipping planes.
3. **Viewport Transformation**: Maps the 2D image plane coordinates to pixel coordinates.

### Final Transformation

The final transformation can be represented as:
$$
\text{Pixel Coordinates} = \text{Viewport Transformation} \times \text{Projection Matrix} \times \text{Camera Matrix} \times \text{World Coordinates}
$$

This complete model ensures that 3D points in the world are accurately projected onto the 2D image plane and mapped to the correct pixel coordinates on the screen.

---

# Graphics Pipeline

## Rasterization

Rasterization is the process of converting vector graphics into raster images. It involves determining which pixels to fill in to represent the shapes and colors of the objects in the scene.

### Depth Test

The depth test is a crucial step in the rasterization process. It determines whether a pixel should be drawn based on its depth value compared to the existing depth value in the depth buffer.

### Virtual Camera Model

Projecting a scene point with the camera:
- Apply camera position (adding an offset)
- Apply rotation (matrix multiplication)
- Apply projection (non-linear scaling)

#### Projection Matrix

The projection matrix transforms 3D points to 2D screen coordinates. It includes the near and far clipping planes to optimize rendering and depth precision.

$$
\begin{bmatrix}
\frac{f}{aspect} & 0 & 0 & 0 \\
0 & f & 0 & 0 \\
0 & 0 & \frac{near + far}{near - far} & \frac{2near \dot far }{near - far} \\
0 & 0 & -1 & 0
\end{bmatrix}
$$

Where:
- $f$ is the focal length:
  - The focal length determines the field of view of the camera. A shorter focal length results in a wider field of view, capturing more of the scene, while a longer focal length narrows the field of view, focusing on a smaller portion of the scene.
- $aspect$ is the aspect ratio of the screen:
  - The aspect ratio is the ratio of the width to the height of the screen. It ensures that the scene is displayed correctly without distortion.
- $near$ and $far$ are the near and far clipping planes:
  - The near and far clipping planes define the range of distances from the camera that will be rendered. Objects outside this range are not rendered, optimizing performance and depth precision.

##### Z-Buffer
As we go futher from the camera, the depth value increases. The Z-buffer stores the depth value of each pixel in the frame buffer. When a new pixel is drawn, the Z-buffer is checked to determine if the new pixel is closer to the camera than the existing pixel. If it is, the new pixel is drawn and its depth value is updated in the Z-buffer.
However in the Z-buffer, the depth value is stored in a non-linear way. The Z-buffer is not linearly distributed, which can cause precision issues when rendering objects at different depths.

#### Clip Space

Check if the` whole triangle is inside the view frustum. If not, clip the triangle to the view frustum.
To clip a triangle, we can split it into smaller triangles that fit within the view frustum.

## Standard Graphics Pipeline
1. **Object Transformation**: Transform the object's vertices from object space to world space.
2. **View Transformation**: Transform the vertices from world space to camera space.
3. **Clipping**: Clip the vertices that are outside the view frustum.
4. Scan Conversion:
   - **Rasterization**: Convert the primitives into fragments.
   - **Fragment Processing**: Determine the color of each fragment.
5. **Depth Test**: Determine which fragments are visible based on their depth values.
6. **Blend**: Combine the color of the fragments with the color of the frame buffer.

## Graphics Pipeline in OpenGL
1. **Vertex Shader**: Transform the vertices from object space to clip space. (Computation on each vertex)
2. **Geometry Shader**: Process the primitives (points, lines, triangles). (Compute on each primitive)
3. **Rasterization**: Convert the primitives into fragments.
4. **Fragment Shader**: Determine the color of each fragment. (Computations on pixels)
5. **Blend + Depth Test**: Combine the color of the fragments with the color of the frame buffer and determine which fragments are visible based on their depth values.


## What makes a GPU fast?
- Very high parallel throughput
- The data typically resides on the GPU and is streamed through specialized programs
- To illustrate parallel processing:
   - imagine a stream of vertices, groups of vertices are processed in parallel (e.g., each vertex is multiplied by a  atrix) result is put back into a stream.

## Flat Mesh represnation (Most basic)

Simply store the vertix in order:
- Vertix Positions $ [x_0 , y_0, z_0 , x_1 , y_1, z_1 , ...  x_n , y_n, z_n] $
- Colors $ [r_0 , g_0, b_0 , r_1 , g_1, b_1 , ...  r_n , g_n, b_n] $

The drawback of this is that for objects that share vertices, the same vertex is stored multiple times. This is inefficient in terms of memory usage and can lead to inconsistencies in the mesh.

## Indexed Mesh Representation (Indexed Face Set)
Instead of a seperate list of vertices for each mesh, we can use a single list of vertices and an index list that specifies for each triangle which vertices to use.

- This saves memory and allows for more efficient rendering because shared vertices are only stored once.

## Mesh with attributes GPU Ready:
- Data is stored in arrays containing all vertices and attributes.
- Triangles are defined by indices into the vertex array.
   - Consecutive indices define faces

## Vertex Shader
Input: Vertecies with attributes
Output: Vertecies with attributes

What operations can be done in the vertex shader?
- Object transformation (position, rotation, scale)
- View transformation (camera position, orientation)

### Vertex Shader Example (GLSL 4.3)
```glsl
#version 430 # version of GLSL
layout(location = 0) uniform mat4 ModelViewMatrix;
# layout means that the variable is bound to a specific location
# location = 0 means that the variable is bound to location 0
# uniform means that the variable is constant for all vertices 
# mat4 is a 4x4 matrix
layout(location = 1) in vec4 pos; // world space position
# in means that the variable is an input to the vertex shader
# vec4 is a 4D vector
layout(location = 2) in vec3 normal; // world space normal
# normal is a 3D vector

//Data to be passed to geometry shader
out vec3 gColor;
# out means that the variable is an output from the vertex shader

void main() {
    gl_Position = ModelViewMatrix * pos;  # gl_Position is a built-in variable that stores the position of the vertex
    gColor = vec3(normal.x , 0 , 0); // normal.x used as color
}
```

## Geometry Shader
Input:Vertex/Attribute array of current primitive (e.g., triangle or its immediate neighborhood)
Output: Several primitives (vertices and attributes)

### Primitives
Primitives are specified by vertices (These are the traditional OpenGL primitives – some  can be considered outdated)

#### Examples in OpenGL
- GL_POINTS: Draws a point for each vertex.
- GL_LINES: Draws a line between each pair of vertices.
- GL_LINE_STRIP: Draws a series of connected lines.
- GL_TRIANGLES: Draws a triangle for each set of three vertices.
- GL_TRIANGLE_STRIP: Draws a series of connected triangles.


### Input
- The input to the geometry shader is a single primitive (e.g., a triangle) and its immediate neighborhood.
- Points, lines, lines with adjacency, triangles or triangles with adjacency

### Output
- The geometry shader can output multiple primitives.
- Geometry shader supports points, line_strip and triangle_strip as output


```glsl
#version 430
layout (triangles) in; # input is a triangle
layout (triangle_strips, max_vertices=3) out; # output is a triangle strip with a maximum of 3 vertices
in vec3 gColor[3]; # input color for each vertex
out vec3 fColor; # output color for each vertex
void main(void){
   for (int i=0;i<3;++i) { # loop over the vertices of the input triangle
      gl_Position=gl_in[i].gl_position; # set the position of the output vertex
      fColor=gColor[i]; # set the color of the output vertex
      EmitVertex(); # emit the vertex ie output the vertex (creates a new vertex in the output primitive)
   }
   EndPrimitive(); # build the triangle from the 3 vertices
}

```

## Rasterization
- Convert primitives into fragments (pixels + attributes)
- Fragment the data determined by interpolation of vertex attributes
- Values are extract from the center pixels


### Interpolation

Interpolation is a method used to estimate values between known data points. When it comes to determining colors at a point within a triangle formed by three vertices, we often use **barycentric interpolation**. This method is particularly useful in computer graphics for shading and texture mapping.

### Barycentric Coordinates

Given a triangle with vertices $ V_1, V_2, V_3 $ and their corresponding colors $ C_1, C_2, C_3 $, we can determine the color at any point $ P $ inside the triangle using barycentric coordinates.

The barycentric coordinates $ (\lambda_1, \lambda_2, \lambda_3) $ of point $ P $ are calculated as follows:

1. **Calculate the areas of sub-triangles:**

   - $ A $ is the area of the entire triangle $ V_1V_2V_3 $.
   - $ A_1 $ is the area of the triangle $ PV_2V_3 $.
   - $ A_2 $ is the area of the triangle $ PV_1V_3 $.
   - $ A_3 $ is the area of the triangle $ PV_1V_2 $.

2. **Compute the barycentric coordinates:**

   $
   \lambda_1 = \frac{A_1}{A}, \quad \lambda_2 = \frac{A_2}{A}, \quad \lambda_3 = \frac{A_3}{A}
   $

   These coordinates satisfy the condition $ \lambda_1 + \lambda_2 + \lambda_3 = 1 $.

### Interpolating the Color

Once we have the barycentric coordinates, we can interpolate the color $ C_P $ at point $ P $ using the colors at the vertices:

$
C_P = \lambda_1 C_1 + \lambda_2 C_2 + \lambda_3 C_3
$

### Example

Let's say we have a triangle with vertices and colors as follows:

- $ V_1 = (x_1, y_1) $ with color $ C_1 = (R_1, G_1, B_1) $
- $ V_2 = (x_2, y_2) $ with color $ C_2 = (R_2, G_2, B_2) $
- $ V_3 = (x_3, y_3) $ with color $ C_3 = (R_3, G_3, B_3) $

To find the color at point $ P = (x, y) $:

1. Calculate the areas $ A, A_1, A_2, A_3 $.
2. Compute the barycentric coordinates $ \lambda_1, \lambda_2, \lambda_3 $.
3. Interpolate the color:

$
C_P = \lambda_1 (R_1, G_1, B_1) + \lambda_2 (R_2, G_2, B_2) + \lambda_3 (R_3, G_3, B_3)
$

This method ensures that the color at any point inside the triangle is a smooth blend of the colors at the vertices.

## Fragment Shader
Input: Pixels with interpolatised attributes/verties
Output:New Fragment for this position (Tipically new color for pixel)  

- Fragment = colors + depth at a pixel location
- Two fragments can fall in the same pixel (e.g., two  overlapping triangles)
- Fragments cannot be moved in the Fragment shader, their location on the screen is fixed

### Fragment Shader Example
``` glsl
#version 430
in vec3 fColor; #Interpolated attributes (was specified on primitive vertices in the geometry shader)
layout(location=0) out vec4 outColor;
void main()
{
   outColor = vec4(fColor,1.0);
}
```

## Blending
- Combining the color of the fragments with the color of the frame buffer

- Blending stage cannot be programmed.
- It takes the produced fragment and combines it with the current image.

## Summary (Vertex Shader VS Geometry Shader VS Fragment Shader)
Input:
- Vertex Shader: Vertices with attributes
- Geometry Shader: Vertex/Attribute array of current primitive
- Fragment Shader: Pixels with interpolated attributes/vertices

Output:
- Vertex Shader: Vertices with attributes
- Geometry Shader: Several primitives (vertices and attributes)
- Fragment Shader: New fragment for this position (typically new color for pixel)

Operations:
- Vertex Shader: Object transformation, view transformation
- Geometry Shader: Process the primitives
- Fragment Shader: Determine the color of each fragment



### Vertex Shader
- **Input**: Vertex attributes (position, color, texture coordinates, normals, etc.)
- **Output**: Transformed vertex position, possibly additional data like color or texture coordinates
- **Operations**:
  - Transform vertex positions from object space to screen space
  - Perform lighting calculations
  - Pass data to the next stage (Geometry Shader or Fragment Shader)

### Geometry Shader
- **Input**: Primitives (points, lines, triangles) assembled from vertices
- **Output**: Zero or more primitives (points, lines, triangles)
- **Operations**:
  - Generate new geometry (e.g., tessellation, extrusion)
  - Modify existing geometry
  - Pass data to the next stage (Fragment Shader)

### Fragment Shader
- **Input**: Fragments (potential pixels) with interpolated data from previous stages
- **Output**: Color and depth values for each fragment
- **Operations**:
  - Compute final color of a pixel
  - Apply textures and lighting
  - Perform per-pixel operations like fog, shadow mapping, etc.


# Computer Animation
## animation is about movement
- objects
- light
- texture
- camera

Animation is not about moving objects in a random manner, the frames per second matter as well as the animation speed.

Anmations could be done in 2D or 3D. Operations such as translation, rotation, scaling, and shearing are used to animate objects.

Animation is a story:
- actions
- gaols
- expressions

## Keyframe Animation
Keyframes describe important monents in the animation. 
The keyframes can be very fine or very coarse depending on the animation.
Keyframes are marked by time and the object's state at that time.

## Inbetweening
Inbetweening is the process of generating intermediate frames between two keyframes to create smooth motion.

### First Idea: Linear Interpolation
Interpolating between two keyframes using linear interpolation:

#### Animation is about timing
- from X to Y in t seconds

## Second Idea: Use Physics
- Use physics to animate objects using physical laws such as acceleration, velocity, and force.
- Not Everything is easily described by physics though.



## Third Idea: Non-Linear Interpolation

### Bezier curves
Bezier curves are used to create smooth animations. They are defined by control points that influence the shape of the curve.
Using control points, we can create curves that are not linear but smooth.

#### Binomial Coefficients Reminder
The binomial coefficient $ \binom{n}{k} $ represents the number of ways to choose $ k $ elements from a set of $ n $ elements. It is calculated as:
$$ \binom{n}{k} = \frac{n!}{k!(n-k)!} $$

### Bezier Curves Formula
$ B(t) = \sum_{i=0}^{n} \binom{n}{i} (1-t)^{n-i} t^i P_i $

Where:
- $ B(t) $ is the Bezier curve at time $ t $
- $ n $ is the degree of the curve (number of control points - 1)
- $ P_i $ are the control points
- $ t $ is the time parameter (0 <= t <= 1)

#### Bezier Curves Example (Linear)
For a linear Bezier curve with control points $ P_0, P_1 $:
$$ B(t) = \binom{1}{0} (1-t)^1 t^0 P_0 + \binom{1}{1} (1-t)^0 t^1 P_1 $$
$$ B(t) = (1-t) P_0 + t P_1 $$

#### Bezier Curves Example (Quadratic)
For a quadratic Bezier curve with control points $ P_0, P_1, P_2 $:
$$ B(t) = \binom{2}{0} (1-t)^2 P_0 + \binom{2}{1} (1-t) t P_1 + \binom{2}{2} t^2 P_2 $$
$$ B(t) = (1-t)^2 P_0 + 2(1-t) t P_1 + t^2 P_2 $$

### Composite Bezier Curves
Composite Bezier curves are created by chaining multiple Bezier curves together. The end point of one curve becomes the start point of the next curve.
 But constricting the last point of the first curve to the first point of the second curve to be of equal distance of the line you get a smooth transition 

## Orientation  Interpolation

### Invalid Approach: Linear Interpolation
Lets try to interpolate between two orientations in a similar way to how we interpolate between two positions.

Linear interpolation  between two points (LERP)
- $ P(t) = (1-t) P_0 + t P_1 $

Linear interpolation between two rotation matrices?
- $ R(t) = (1-t) R_0 + t R_1 $

Take two matrices:
$$ R_x(\theta) = \begin{bmatrix} 1 & 0 & 0 \\ 0 & \cos \theta & -\sin \theta \\ 0 & \sin \theta & \cos \theta \end{bmatrix} $$
$$ R_z(\theta) = \begin{bmatrix} \cos \theta & -\sin \theta & 0 \\ \sin \theta & \cos \theta & 0 \\ 0 & 0 & 1 \end{bmatrix} $$

Take $ R_0 = R_x(\pi) $ and $ R_1 = R_z(\pi) $.
$ R(t) = (1-t) R_0(\pi) + t R_1(\pi) $
Take t = 0.5 and plug it in the equation

We get an invalid rotation matrix:

$$ R(0.5) = 0.5 \begin{bmatrix} 1 & 0 & 0 \\ 0 & 0 & -1 \\ 0 & 1 & 0 \end{bmatrix} + 0.5 \begin{bmatrix} 0 & -1 & 0 \\ 1 & 0 & 0 \\ 0 & 0 & 1 \end{bmatrix} $$

$$ = \begin{bmatrix} 0.5 & -0.5 & 0 \\ 0.5 & 0 & -0.5 \\ 0 & 0.5 & 0.5 \end{bmatrix} $$

This matrix is not a valid rotation matrix, as it does not have an orthonormal basis (the columns are not orthogonal to each other).

### Interpolate The Angles
Instead of interpolating the rotation matrices directly, we can interpolate the angles (e.g., Euler angles) and then construct the rotation matrix from the interpolated angles.

#### Euler Angles
Euler angles are a set of three angles that represent the orientation of an object in 3D space. The most common representation is the XYZ rotation sequence, where the object is rotated around the X, Y, and Z axes in that order.

$ R(\alpha, \beta, \gamma) = R_z(\gamma) R_y(\beta) R_x(\alpha) $
$ \alpha(t) = (1-t) \alpha_0 + t \alpha_1 $
$ \beta(t) = (1-t) \beta_0 + t \beta_1 $
$ \gamma(t) = (1-t) \gamma_0 + t \gamma_1 $

But this approach has a problem as the **order** of rotation matters.
Also its **ambiguous** as the same orientation can be represented in different ways.

##### Gimbal Lock
Gimbal lock is a phenomenon that occurs when two of the three axes of rotation become aligned, leading to a loss of one degree of freedom and potential problems in representing orientations.

### Quaternion Interpolation
Quaternions are defined as four-dimensional complex numbers:
$$ q_0 + q_1 i + q_2 j + q_3 k $$
where $ i, j, k $ are the quaternion units and $ q_0, q_1, q_2, q_3 $ are real numbers.
$$ i^2 = j^2 = k^2 = ijk = -1 $$

Scalar and vector parts of a quaternion:
$$ q = q_0 + q_1 i + q_2 j + q_3 k = (q_0, q_1, q_2, q_3) = (s, v) $$
where $ s = q_0 $ is the scalar part and $ v = (q_1, q_2, q_3) $ is the vector part.

all operations are defined: addition, subtraction, multiplication ...

#### Unit Quaternions
- Unit quaternion q:
   - represents a rotation in $ \theta $ around an axis $ a $
$$ q = [q_0, q_1, q_2, q_3] = \langle s, V \rangle $$
$$ q = \langle \cos \frac{\theta}{2}, a \sin \frac{\theta}{2} \rangle $$

Properties of unit quaternions:
- it's possible to concatenate rotations
- it's possible to interpolate between two rotations

#### Linear Interpolation of Quaternions (LERP)
LERP is a method for interpolating between two quaternions. The path between the two quaternions is a straight line on the unit quaternion sphere.
This is not smooth at control points ("hiccups")

#### Spherical Linear Interpolation (SLERP)
SLERP is a method for interpolating between two unit quaternions. It ensures that the interpolated quaternions lie on the unit sphere and the shortest path between the two quaternions is taken.

$$ SLERP(t , q_1 , q_2) = q_1 (q_1^* q_2)^t $$
where:
- $ q_1^* $ is the conjugate of $ q_1 $
- $ t $ is the interpolation parameter (0 <= t <= 1)


### Squad Spherical Interpolation
Squad interpolation is a method for interpolating between two unit quaternions using spherical interpolation (SLERP) and tangents to create a smooth curve.


## Speed Along Curve

### Curve Parameterization
When an object moves along a Bézier curve, its speed is not constant. This is because the parameter $ t $ does not vary linearly with respect to the arc length of the curve. In other words, equal increments in $ t $ do not correspond to equal distances traveled along the curve.

### Re-parameterization
To control the speed of an object along the curve, we need to re-parameterize the curve so that the parameter varies linearly with respect to the arc length. Here's how we can do it:

1. **Divide the curve into equal $ t $ segments**:
   - Start by dividing the parameter $ t $ into equal segments. For example, if $ t $ ranges from 0 to 1, you might divide it into 100 equal segments.

2. **Approximate each arc-segment by a line**:
   - For each segment of $ t $, approximate the corresponding segment of the curve by a straight line. This can be done by evaluating the Bézier curve at the endpoints of each $ t $ segment and connecting these points with straight lines.

3. **Make a look-up table for arc-length**:
   - Calculate the length of each line segment and accumulate these lengths to create a look-up table that maps $ t $ values to arc lengths. This table will help us convert $ t $ to arc length.

4. **Convert $ t $ to arc-length**:
   - To move an object along the curve at a constant speed, use the look-up table to find the corresponding $ t $ value for a given arc length. This allows you to re-parameterize the curve so that the object moves at a constant speed.

### Intuition
The key idea is to ensure that the parameter $ t $ varies in such a way that equal increments in $ t $ correspond to equal distances traveled along the curve. By re-parameterizing the curve based on arc length, we can achieve a constant speed for the object moving along the curve.

In summary, the process involves:
- Dividing the curve into equal $ t $ segments.
- Approximating each segment by a line.
- Creating a look-up table for arc length.
- Using the look-up table to convert $ t $ to arc length, ensuring constant speed.

This approach allows for smooth and consistent motion along the curve, providing better control over the speed of the object.


## Forward Kinematics (FK)
Forward Kinematics involves calculating the position of each joint in a kinematic chain by operating on each joint individually. Given the angles of the joints, we can determine the position of the **end effector** (the final point of the chain or arm).

### Intuition
Imagine you have a robotic arm with several segments connected by joints. By specifying the angles of each joint, you can determine the position of the end effector. This is like moving your arm by controlling the angles of your shoulder, elbow, and wrist.

## Inverse Kinematics (IK)
Inverse Kinematics involves calculating the joint angles required to place the end effector at a desired position. Instead of operating on each joint individually, we operate on the end effector and work backward to find the joint angles.

### Intuition
Imagine you want to reach a specific point with your hand. Instead of thinking about the angles of your shoulder, elbow, and wrist, you focus on the position of your hand and let your brain figure out the necessary joint angles. This is the essence of IK.

## IK Analytical
In analytical IK, we use mathematical equations to find the joint angles. Let's consider a simple 2D example with three joints (a, b, and c) and their corresponding transformation matrices.

### Transformation Matrices
The transformation matrices for joints a, b, and c are given by:

$$ M_a = \begin{bmatrix} 1 & 0 & a_x \\ 0 & 1 & a_y \\ 0 & 0 & 1 \end{bmatrix} $$
$$ M_b = M_a \begin{bmatrix} 1 & 0 & d_0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix} $$
$$ M_c = M_b \begin{bmatrix} 1 & 0 & d_1 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix} $$

Where:
- $ a_x $ and $ a_y $ are the coordinates of joint a.
- $ d_0 $ is the distance between joints a and b.
- $ d_1 $ is the distance between joints b and c.

### Calculating Positions
To find the positions of points a, b, and c, we use the transformation matrices:

$$ a = M_a \begin{bmatrix} 0 \\ 0 \\ 1 \end{bmatrix} $$
$$ b = M_b \begin{bmatrix} 0 \\ 0 \\ 1 \end{bmatrix} $$
$$ c = M_c \begin{bmatrix} 0 \\ 0 \\ 1 \end{bmatrix} $$

### Detailed Explanation of Matrices
1. **Matrix $ M_a $**:
   - Represents the initial position of joint a.
   - $ a_x $ and $ a_y $ are the coordinates of joint a.

2. **Matrix $ M_b $**:
   - Represents the position of joint b after applying the transformation from joint a.
   - $ d_0 $ is the distance between joints a and b.

3. **Matrix $ M_c $**:
   - Represents the position of joint c after applying the transformations from joints a and b.
   - $ d_1 $ is the distance between joints b and c.

### Combining Rotations and Translations
To account for rotations, we modify the transformation matrices:

$$ M_b = M_a \begin{bmatrix} \cos \theta_0 & -\sin \theta_0 & 0 \\ \sin \theta_0 & \cos \theta_0 & 0 \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 & d_0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix} = M_a \begin{bmatrix} \cos \theta_0 & -\sin \theta_0 & d_0 \cos \theta_0 \\ \sin \theta_0 & \cos \theta_0 & d_0 \sin \theta_0 \\ 0 & 0 & 1 \end{bmatrix} $$

$$ M_c = M_b \begin{bmatrix} \cos \theta_1 & -\sin \theta_1 & 0 \\ \sin \theta_1 & \cos \theta_1 & 0 \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 & d_1 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix} = M_b \begin{bmatrix} \cos \theta_1 & -\sin \theta_1 & d_1 \cos \theta_1 \\ \sin \theta_1 & \cos \theta_1 & d_1 \sin \theta_1 \\ 0 & 0 & 1 \end{bmatrix} $$

### Finding Joint Angles
Given the position of point c, we can find the joint angles $ \theta_0 $ and $ \theta_1 $:

$$ \begin{bmatrix} c_x \\ c_y \\ 1 \end{bmatrix} = \begin{bmatrix} d_0 \cos \theta_0 + d_1 \cos {(\theta_0 + \theta_1)} \\ d_0 \sin \theta_0 + d_1 \sin {(\theta_0 + \theta_1)} \\ 1 \end{bmatrix} $$

To solve for $ \theta_0 $ and $ \theta_1 $:

$$ \theta_1 = \cos^{-1} \left( \frac{c_x^2 + c_y^2 - d_0^2 - d_1^2}{2d_0d_1} \right) $$

$$ \theta_0 = \tan^{-1} \left( \frac{c_y}{c_x} \right) - \tan^{-1} \left( \frac{d_1 \sin \theta_1}{d_0 + d_1 \cos \theta_1} \right) $$

### Considerations
- $ a $, $ d_0 $, and $ d_1 $ are constants.
- We do not need to worry about $ b $ or $ M_a $ directly, as they are intermediate steps in the calculation.

By understanding these concepts and equations, you can solve for the joint angles required to position the end effector at a desired location using Inverse Kinematics.



## Rigging

Rigging is the process of creating a skeleton for a 3D model to enable animation. The skeleton consists of bones and joints that define the structure of the model and how it can move.

It's very difficult to operate on the vertices of a 3D model directly. Instead, we can use a skeleton to control the movement of the model.

### Bones and Joints
- **Bones**: The rigid segments of the skeleton that define the structure of the model.
   - Each vertex of the 3D model is associated with one or more bones.
   - When a bone moves, the vertices associated with it move with the same transformation, ensuring that the model deforms in a controlled manner.
- **Joints**: The connections between bones that allow movement.
   - Joints define how bones can rotate and translate relative to each other, enabling complex movements like bending and twisting.

However, using rigid body transformations can lead to sharp edges at the joints or discontinuities in the lines. This is because the vertices move rigidly with the bones, resulting in unnatural deformations.

To achieve smooth transitions at the mesh level, we need to use a technique called skinning.

## Skinning

Skinning is the process of deforming a 3D model based on the movement of the skeleton. The skin of the model is attached to the bones, and as the bones move, the skin deforms accordingly.

### Linear Blend Skinning (LBS)
Linear Blend Skinning (LBS) is a popular technique used to achieve smooth deformations. The key idea is to blend the influence of multiple bones on each vertex, allowing for smooth transitions between different parts of the skeleton.

In the transition region between two bones, the vertices are influenced by both bones. The influence of each bone is determined by weights assigned to the vertices (in the blend region).

The formula for LBS is:

$$ v_j = \sum_{i=1}^{n} w_{ij} T_i(v) $$

Where:
- $ v_j $ is the deformed vertex position.
- $ w_{ij} $ is the weight of bone $ i $ on vertex $ j $. The sum of weights for each vertex must be 1 (normalized).
- $ T_i(v) $ is the transformation of bone $ i $ on vertex $ v $.

### Intuition Behind LBS
Imagine you have a piece of cloth attached to two sticks. If you move one stick, the cloth will deform, but the deformation will be influenced by the position of both sticks. The closer a point on the cloth is to a stick, the more influence that stick has on the point's movement.

In LBS, each vertex of the 3D model is like a point on the cloth, and the bones are like the sticks. The weights $ w_{ij} $ determine how much influence each bone has on each vertex. By blending the transformations of multiple bones, we achieve smooth and natural deformations.

### Interpolating the Normal Vectors
To ensure that the lighting and shading of the model remain consistent, we also need to interpolate the normal vectors. The formula for interpolating the normal vectors is:

$$ n_j = \sum_{i=1}^{n} w_{ij} T_i^{-T}(n_j) $$

Where:
- $ n_j $ is the deformed normal vector.
- $ T_i^{-T}(n_j) $ is the inverse transpose of the transformation matrix of bone $ i $ on normal $ n_j $.

By interpolating the normal vectors, we ensure that the surface normals are correctly transformed, resulting in smooth shading and realistic lighting.

In summary, Linear Blend Skinning (LBS) allows us to achieve smooth and natural deformations by blending the influence of multiple bones on each vertex. This technique ensures that the model deforms in a controlled and realistic manner, providing better control over the animation.


## Motion Capture
Motion capture is the process of recording the movement of objects or people. It is commonly used in animation, sports, and medicine to capture realistic movements.

## Blend Shapes
Create a set of target shapes and interpolate between them to create a smooth transition between different facial expressions.

Starting with a neutral face, we can create target shapes for different expressions (e.g., smile, frown, surprise). By interpolating between these target shapes, we can create a wide range of facial expressions.

Express all other faces as differences from the neutral face.

$$ \triangle P_i = P_i - P_{neutral} $$ 

This gives a vector representation of the face expressions.

$$ P_{new} = P_{neutral} + \sum_{i=1}^{n} w_i \triangle P_i $$

Where:
- $ P_{new} $ is the new vertex position.
- $ P_{neutral} $ is the neutral vertex position.
- $ w_i $ is the weight of the $ i $-th expression.

You can transition between different expressions by changing the weights gradually.

You express this in matrix notation:

$$ P_{new} = P_{neutral} + [ \triangle P_1, \triangle P_2, ... \triangle P_n ] \begin{bmatrix} w_1 \\ w_2 \\ ... \\ w_n \end{bmatrix} $$

Each column of the matrix is a target shape and the weights are the coefficients of the linear combination.

### How to set the weights?
- Manually: An artist can set the weights based on the desired expression.
Sometimes the face is split into regions and the weights are set for each region.


# Materials & Shading
## Standard Blending
Color can be a vec4 with the first three values being the RGB values and the last value being the alpha value.
The alpha value determines the transparency of the color; 0 means fully transparent, and 1 means fully opaque.

In general, incoming fragment (R,G,B,A) and current pixel color is  $ R_BG_BB_B $ (background) then the new pixel color is: $ A * RGB+ (1-A) * R_BG_BB_B $

Explanation: The new color is a combination of the incoming fragment color and the current pixel color based on the alpha value of the fragment.

Order is important when blending colors. The order of the fragments determines the final color.

Why this formula?
Imagine if the object have tiny holes with probabilty alpha,  with 0.5 the object with represtn a checkerboard pattern with the background

A light ray hits with probability A and passes with probability (1-A), hence, $ A * color + (1-A) * Background $

- If you have several transparent objects, it might be needed to sort the triangles.
- Be aware that when drawing transparent objects you should draw them last and deactivate the depth buffer because the depth buffer will not work correctly with transparent objects.

## Shading
Given a surface point (postion, normal and potential attributes) and a light source, we need to determine the color of the surface point.

### Reflection
Mirror: The angle of incidence is equal to the angle of reflection.
Perfectly defused: The light is reflected in all directions.


### How materials are represented? BRDF
BRDF (Bidirectional Reflectance Distribution Function) is a function that describes how light is reflected at an opaque surface. It takes the incoming light direction and the outgoing light direction as input and returns the ratio of the outgoing radiance to the incoming irradiance.

Function from $ IR^5 $ (incoming light direction, outgoing light direction, normal, incoming light, outgoing light) into $ IR $ (ratio between in- and outgoing energy) indication how much incident (incoming) light is reflected in a point.

$ f_x(\theta_i , \theta_o , \lambda) $ where:
- $ \theta_i $ is the incoming light direction
- $ \theta_o $ is the outgoing light direction
- $ \lambda $ is the wavelength of the light

### Acquired Materials
Big database of materials with their BRDFs. The BRDFs are measured in a lab and stored in a database. The BRDFs are used to render the materials in a realistic way.

This is useful for rendering realistic materials like metals, plastics, and fabrics but it is computationally expensive and not flexible for digital artists.

#### Material Acquisition
Using a gonioreflectometer to measure the BRDF of a material. The gonioreflectometer measures the reflection of light at different angles and wavelengths.


### Mathematical Models
Describe light interaction as a function (Mathematically describe Material Properties)
- Usually more lightweight
- Has parameters to control appearance
- Acquired materials can be approximated


#### Phong Model: Sum of 3 terms
- Ambient: Constant color for all surfaces
- Diffuse: Light that is scattered in all directions
- Specular: Light that is reflected in a specific direction

Visual system uses 3 cone types for color. In our model, we will treat wavelengths separately (in practice: Red, Green, Blue).
In the following, we usually describe the model for a single wavelength/color channel (do it 3 times for red, green, blue...)

##### Ambient Term
Is supposed to represent the light that is scattered in the environment. It is a constant color for all surfaces.

$$ A = k_a I_a $$

Where:
- $ A $ is the ambient light intensity
- $ k_a $ is the ambient reflection coefficient (Surface property) (Incriesing this value will make the object brighter)
- $ I_a $ is the ambient light intensity (Light property)

Used often in practice as a strong approximation of indirect light, but does't show the shape of the object.


##### Diffuse Term
Represents the light that is scattered (Uniformly) in all directions. It depends on the angle between the light source and the normal of the surface.

$$ D = k_d I_d \max(0, \vec{n} \cdot \vec{l}) $$

Where:
- $ D $ is the diffuse light intensity
- $ k_d $ is the diffuse reflection coefficient (Surface property)
- $ I_d $ is the diffuse light intensity (Light property)
- $ \vec{n} $ is the normal vector of the surface
- $ \vec{l} $ is the light direction vector

Shading varies along surface and Gives information about shape, doesn't depend on the viewer position.

The light should always come from above the surface, otherwise, it should stay black.

What does this mean for the angle $ \theta $ between the normal and the light direction?
- If $ \theta = 0 $, the light is perpendicular to the surface and the intensity is maximal.
- If $ \theta = 90 $, the light is parallel to the surface and the intensity is zero.


##### Specular Term

Represents the light that is reflected in a specific direction. It depends on the angle between the viewer and the reflection of the light source.

$$ S(\phi) = k_s I_s \cos^n(\phi) $$

Where:
- $ S(\phi) $ is the specular light intensity
- $ k_s $ is the specular reflection coefficient (Surface property)
- $ I_s $ is the specular light intensity (Light property)
- $ \phi $ is the angle between the reflection of the light source and the viewer
- $ n $ is the shininess coefficient (Surface property)

##### Emissive Term (Extention)
Represents the light that is emitted by the surface itself. It is a constant color for all surfaces, it's Ambient light with Light set to 1.

### Computatinon
- Early days - compute color per face: Flat shading produces “facets”
- Later – compute color per vertex: produces Gouraud Shading produces a smooth look

There are more advanced shading techniques but you trade off between quality and performance.

### Normals on Meshes
- Face normals (normal of the plane containing triangle)
- Vertex normals (average of face normals of adjacent faces)
- Interpolated normals (interpolated vertex normals over the triangle)


### Gouraud Shading (Per Vertex)
Computes the color at the vertices and interpolates the color across the triangle.

### Phong Shading (Per Pixel)
Computes the color at each pixel by interpolating the normals and then computing the color.
More expensive than Gouraud shading but produces better results (because there are usually more pixels than vertices).


### How are the three different types computed?
- Flat shading
   - Applies Phong Model to produce a color per **face**
- Gouraud shading
   - Applies Phong to produce a color per **vertex**
   - Interpolate color from vertices over triangle
- Phong shading
   - Interpolate parameters of **Phong model**
   - Applies Phong to produce a color per **pixel**


## Textures
Images that are mapped to the surface of a 3D object to add detail, color, or other properties.
Could be used to map properties like color, roughness, or transparency to the surface of an object.

Specified at each vertex and interpolated over the triangle.

``` glsl
glTexCoord{123}{fi}
```

### How to define Texture Coordinates?
#### Mesh Unwrapping
Unwrap the 3D model to a 2D plane using special software and draw the texture on the 2D plane.


# Advanced Material

## Color (Radiometry)
Color comes from light interaction
Pixel color represents the result from the light interaction with the environment
It depends on:
- Light sources
- Surface reflection properties
- Sensor properties
- Processor (How the light is interpreted)

Perfect Mirror: Reflects light in a single direction at the same angle as the incoming light
Perfect Diffuse: Reflects light in all directions uniformly (intentisy may change)
Glossy: Reflects light in a specific direction (like a mirror) but with a spread

## Reflectance Function BRDF
Input:
- Point on the surface
- Incoming light direction
- Outgoing light direction
- Wave length of the light

Output:
- Ratio of the outgoing radiance to the incoming irradiance


Phong model is not physically possible as the light is not conserved (light is created)

## Mathematical Formulation

Let's say we know the reflectance function \( f_r(p, v, l) \). But what about other incoming directions?
- We need to integrate over the hemisphere (all incoming directions).
- Note: Here we assume rays, but really we are dealing with differential quantities.

$$ L_o(p, v) = \int_{H} f_r(p, v, l) L_i(p, l) (n \cdot \theta) \, dl $$

Where:
- \( L_o(p, v) \) is the outgoing radiance.
- \( f_r(p, v, l) \) is the reflectance function.
- \( L_i(p, l) \) is the incoming radiance.
- \( n \cdot \theta \) is the cosine term of the angle between the normal and the incoming light direction.
- \( p \) is the point on the surface.
- \( v \) is the outgoing light direction.
- \( l \) is the incoming light direction.

### Intuition Behind the Integration
Imagine a point on a surface illuminated by light from all directions. To determine the total light leaving this point in a specific direction, we need to consider the contribution of light from every incoming direction. The reflectance function tells us how much of the incoming light is reflected towards the outgoing direction. By integrating over the hemisphere, we sum up the contributions from all incoming directions, weighted by the cosine term to account for the angle of incidence.

### Normalization with \( \pi \)
The integral is normalized by dividing by \( \pi \) to ensure that the total energy is conserved. This normalization factor accounts for the solid angle of the hemisphere and ensures that the radiance values are within a physically meaningful range.

Why \( \pi \)?
- The integral over the hemisphere covers a solid angle of \( 2\pi \) steradians.
- Dividing by \( \pi \) ensures that the total energy is conserved and the radiance values are normalized.

### Normalized Diffuse Term:
\[ \text{Diffuse} = \frac{1}{\pi} k_d I \max(0, n \cdot l) \]
   - where \( k_d \) is the diffuse reflection coefficient.
   - \( I \) is the light intensity.
   - \( n \) is the normal vector.
   - \( l \) is the light direction vector.

### Normalized Specular Term:
\[ \text{Specular} = \frac{1}{\pi} k_s I \cos^n(\theta) \]
   - where \( k_s \) is the specular reflection coefficient.
   - \( I \) is the light intensity.
   - \( n \) is the normal vector.
   - \( \theta \) is the angle between the reflection of the light source and the viewer.
   - \( n \) is the shininess coefficient.

Without normalization, the light will be amplified, and the object will appear brighter than it should be.

## Scattering - Geometry (Zooming into the Surface)
- **Surface roughness at micro-geometry scale**: When we zoom into a surface, we see that it is not perfectly smooth but has tiny irregularities. These irregularities affect how light interacts with the surface.
- **Statistical modeling**: We use statistical methods to model how light is scattered due to these irregularities, both for reflection and refraction.
- **Two types of materials**:
  - **Dielectric (Non-metallic)**: These materials can reflect, refract, and absorb light. Examples include water, glass, and plastic.
  - **Conductor (Metallic)**: These materials primarily reflect and absorb light but do not refract it. Examples include metals like gold, silver, and copper.

## Fresnel
The Fresnel equations describe how light is reflected and transmitted at an interface between two different media. The Fresnel term \( F(n,l) \) represents the ratio of reflected light to incident light and depends on the angle of incidence and the refractive indices of the materials.

### Schlick's Approximation
Schlick's approximation provides a simplified way to calculate the Fresnel term:
$$ F(n,l) \approx F_0 + (1 - F_0)(1 - (n \cdot l))^5 $$

Where:
- \( F(n,l) \) is the Fresnel term.
- \( F_0 \) is the reflectance at normal incidence (when the light hits the surface perpendicularly).
- \( n \) is the normal vector (perpendicular to the surface).
- \( l \) is the light direction vector.

### Specular Color from Index of Refraction (IOR)
The reflectance at normal incidence \( F_0 \) can be calculated using the refractive indices of the two media:
$$ F_0 = \left( \frac{n_1 - n_2}{n_1 + n_2} \right)^2 $$

Where:
- \( n_1 \) is the refractive index of the first medium.
- \( n_2 \) is the refractive index of the second medium.

### Table of IOR Values for Different Materials
#### Metal Table
| Material | $ f_0 $ in sRGB | Hex | Color |
|----------|-----------------|-----|-------|
| Silver   | 0.97, 0.96, 0.91 | #F7F6E8 | !Silver |
| Aluminum | 0.91, 0.92, 0.92 | #E9EBEB | !Aluminum |
| Titanium | 0.54, 0.57, 0.58 | #8A9294 | !Titanium |
| Iron     | 0.56, 0.57, 0.58 | #8F9294 | !Iron |
| Platinum | 0.67, 0.61, 0.58 | #AB9D94 | !Platinum |
| Gold     | 1.00, 0.71, 0.29 | #FFB548 | !Gold |
| Brass    | 0.71, 0.65, 0.26 | #B5A73A | !Brass |
| Copper   | 0.95, 0.64, 0.54 | #F3A47A | !Copper |

#### Dielectric Table
| Material | Refractance | IOR | 
|----------|------------|-----|
| Water    | 2%        | 1.33 |
| Fabrics  | 4% to 5.6% | 1.5 to 1.62 |
| Common Liquids | 2% to 4% | 1.33 to 1.5 |
| Plastic, Glass | 4% to 5% | 1.5 to 1.58 |
| Eyes     | 2.5%  | 1.38 |

In this table, "Refractance" refers to the amount of light that is refracted (bent) and not reflected. The IOR (Index of Refraction) is used to calculate \( F_0 \) for dielectric materials.

## Microfacet Model (Modeling Micro-Geometry Statistically)
The microfacet model uses statistical methods to represent the small-scale surface roughness and its effect on light scattering.

- **Normal Distribution Function (NDF)**: Describes the distribution of microfacet orientations.
- **Masking**: Parts of the surface block the view of other parts.
- **Shadowing**: Parts of the surface cast a shadow on other parts.
- **Inter-reflection**: Light bounces between different parts of the surface.

## Visibility
### Masking
Masking occurs when one part of the surface blocks the view of another part.
$$ G_1(m , v) $$

Where:
- \( G_1(m , v) \) is the masking function.
- \( m \) is the normal vector.
- \( v \) is the visibility vector.

### Shadowing
Shadowing occurs when one part of the surface casts a shadow on another part.
$$ G_1(m , l) $$

Where:
- \( m \) is the normal vector.
- \( l \) is the light direction vector.

### Combining Both: Masking-Shadowing Function
$$ G_2(m , l, v) $$

Where:
- \( G_2(m , l, v) \) combines the effects of masking and shadowing.

## Putting Everything Together
To model the interaction of light with a rough surface, we combine the Fresnel term, the Normal Distribution Function (NDF), and the visibility function.

## Microfacets - Specular Reflection
Each microfacet acts as a tiny mirror, reflecting light according to the Fresnel equations.

$$ f_r(l ,v) = \frac{(F(h, l) G_2(l, v, h) D(h))}{4 \abs{n \cdot l} \abs{n \cdot v}} $$

Where:
- \( f_r(l ,v) \) is the specular reflection.
- \( F(h, l) \) is the Fresnel term.
- \( G_2(l, v, h) \) is the masking-shadowing function.
- \( D(h) \) is the normal distribution function.
- \( 4 \abs{n \cdot l} \abs{n \cdot v} \) is the normalization factor.

## Roughness Parameter
The roughness parameter \( \alpha \) controls the spread of the microfacets. A higher \( \alpha \) value indicates a rougher surface, leading to more diffuse reflection, while a lower \( \alpha \) value indicates a smoother surface, leading to more specular reflection.


# Advanced Textures
Map properties like color, roughness, or transparency to the surface of an object.
- Specify texture coordinates at each vertex
- Vertex texture coordinates are interpolated over the triangle

## How to define Texture Coordinates?
### Mesh Unwrapping
Unwrap the 3D model to a 2D plane using special software and draw the texture on the 2D plane. (Can be drawn directly on the 3D model after unwrapping)

### In Between Suerfaces
Map the texture on an object that is easily discribable and then associate that object with the actual mesh.

For example define the texture on a sphere/cilender and then map the texture to the mesh.

With a sphere texture, at the poles the texture will be stretched and at the equator it will be compressed.

#### Cube Map
Map the texture to a cube and then map the cube to the mesh. This solves the problem of stretching and compression.

### Use Screen Space
Use the screen space to map the texture to the mesh. This leads to differenct textures for different views.

### What happens outside the texture?
We can use differnt modes per axes
- Border: Use a constant color
- Clamp: Use the color of the nearest pixel
- Repeat: Repeat the texture at the border

## Alpha Blending
Alpha blending is a technique used to combine the colors of two objects with transparency.
Stack textred polygons and blend the colors based on the alpha value. Create trees with leaves that have transparency.

## Sprites
Sprites are 2D images that are rendered in a 3D scene. 

## Water Particals
Similuate water particiale as a quad with water texture

## Affine Texture Mapping
Interpolate texture in screen-space.
Cheaper than perspective texture mapping.
   -  No Z-value needed
   -  No division needed by Z


## Aliasing
Aliasing is the jagged or stair-stepped appearance of in objects.
This comes from the fact that the screen is made of pixels and the object is not aligned with the pixels. (Not one-to-one pixel mapping with tecture and screen)

If the surface is far away many of the texture pixels will be mapped to the same screen pixel.
if the surface is close, many screen pixels will be mapped to the same texture pixel.

### Oversampling
This comes from the texcels bing too big for the screen pixels. This leads to the same texcel being used for multiple screen pixels. (The texture doesn't have enough resolution)
(Pixels smaller than texcel)

#### Nearest Neighbor
The color of the nearest texel is used for the screen pixel. (Causes blocky artifacts)


#### Linear Interpolation
$$ \alpha * C_1 + (1 - \alpha) * C_2 $$

#### Biliniear Interpolation
Interpolate between the 4 nearest texels to get the color of the pixel.
Start by interpolating in the x-direction and then in the y-direction.
##### Example
For texcels $ (x_1 , y_1) $, $ (x_2 , y_1) $, $ (x_1 , y_2) $, $ (x_2 , y_2) $ and screen pixel $ (x, y) $:

Create rectangles with the texcels and the screen pixel.
This gives 4 rectangles with the screen pixel in the middle.
Use the raltive size of those rectangles to interpolate the color of the screen pixel. (use the relative size as the weight)

Inorder to get the color of the screen pixel, interpolate the color of the 4 texcels by applying the linear interpolation formula once in the x-direction and once in the y-direction then combine the results.

### Undersampling
This comes from the texcels being too small for the screen pixels. This leads to the same screen pixel being mapped to multiple texels. (The texture has too much resolution)
This leads to random colors for the screen pixel. (noise)

Naive solution is to average the colors of the texels. (Causes blurring) or Render at a higher resolution and then downsample (Expensive)

### Mipmapping
Computue a filtered texture beforehand for each level.
Stating with level 0 (original texture) and then half the resolution for each level by combining each 2x2 texels into one texel. 
Choose the correct level based on the distance to the camera.

How to choose the correct level?
In Texture space, find the region that the screen pixel is in, approxiamte a square of size $ 2^k $ and then choose the level $ k $.

The extra memeory usage is one third of the original texture.

$$ MemoeryCostAllLevels = \sum_{i=0}^{n} \left( \frac{1}{4^i} \right) = \frac{4}{3} * \left( 1 - \frac{1}{4^{n+1}} \right) $$
In the limit the cost is $ \frac{4}{3} $ ie one third more of the original texture.

This approach of using the nearest level causes discontinuities at the borders of the levels since mipmans only grow by a factor of 2.


### Interpolation between Mipmaps (Trilinear Filtering)
Interpolate between the two nearest levels of the mipmaps.

### Anisotropic Filtering
In Mipmapping, the texels are combined in a square. This leads to blurring in when the z direction is strecthed differently than the x and y directions. But we approxiamte the pixel mapping as a square.


Inspread of at each mipmap level to reduce both x and y by 2, at each level create two levels one with x reduced by 2 and the other with y reduced by 2. This leads to a rectangular texel at each level.

This leads to a better approximation of the pixel mapping but costs 4 times more memory than the original texture.