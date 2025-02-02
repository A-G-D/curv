Boolean (Set Theoretic) Operations
==================================

``complement shape``
  Reverses inside and outside, so that all points inside the argument
  shape are outside the result shape, and vice versa.
  But the boundary doesn't change.
  If the input is a finite shape, the output will be infinite.

``union [shape1, shape2, ...]``
  Construct the set union of a list of zero or more shapes.
  
  The colours of shapes later in the list
  take precedence over shapes earlier in the list.
  This follows the metaphor of ``union`` as an additive operation
  where later shapes are "painted on top of" earlier shapes.

  ``union`` is an associative operation with ``nothing``
  as the identity element, meaning it is a monoid.
  The empty list is mapped to ``nothing``.
  If all of the shapes have the same colour, then
  ``union`` is commutative.

``intersection [shape1, shape2, ...]``
  Construct the set intersection of zero or more shapes.
  
  The colour of the first shape takes precedence.
  This is the opposite of the ``union`` convention.
  It follows the metaphor of ``intersection`` as a subtractive operation
  where the first shape is primary, and subsequent shapes indicate which parts of
  the primary shape not to remove.
  It is consistent with the traditional definition
  of ``difference[s1,s2]`` as ``intersection[s1,complement s2]``.

  ``intersection`` is an associative operation.
  The empty list is mapped to ``everything``.
  If all of the shape arguments have the default colour,
  then ``everything`` is the identity element,
  and ``intersection`` is commutative and a monoid.
  
``difference [shape1, shape2]``
  A binary operation that subtracts shape2 from shape1,
  preserving the colour of shape1.

``symmetric_difference [shape1, shape2, ...]``
  The result contains all of the points that belong to exactly one shape in the list.
  
  This is an associative, commutative operation with ``nothing`` as its identity element.

``row d shapes``
  Move each shape in ``shapes`` along the X axis
  so they are lined up in a row, separated by gaps of distance ``d``.
  The group is centred on the origin along the X axis.

``row shapes``
  Same as ``row d shapes`` except that the gap distance is provided for you.

Distance Field Behaviour
------------------------
The boolean shape operations create shapes where the distance field class of the outside of the shape
can be different from the distance field class of the inside of the shape.

``complement s``
  * The outside distance field of the result has the same class (exact, mitred, approximate, etc)
    as the inside of ``s``.
  * The inside distance field of the result has the same class
    as the outside of ``s``.

``union``
  If the input shapes have exact distance fields,
  then the outside of the result is exact, and the inside is approximate.

``intersection``
  If the input shapes have exact distance fields,
  then the outside of the result is mitred, and the inside is exact.

``difference[s1,s2]``
  ``difference [s1, s2] = intersection [s1, complement s2]``. As a consequence of this,
  
  * The outside distance field of the result is mitred if the outside of ``s1`` is exact and the inside of ``s2`` is exact.
  * The inside distance field of the result is exact if the inside of ``s1`` is exact and the outside of ``s2`` is exact.
