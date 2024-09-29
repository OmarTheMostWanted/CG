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

  $$
   \begin{bmatrix}
   x' \\
   y'
   \end{bmatrix}
   =
   \begin{bmatrix}
   x \\
   y
   \end{bmatrix}
    +
   \begin{bmatrix}
   t_x \\
   t_y
   \end{bmatrix}
   $$

2. **Rotation**: Rotate the translated point by an angle $\theta$:
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

## Third Idea: Non-Linear Interpolation

