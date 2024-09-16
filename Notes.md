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
