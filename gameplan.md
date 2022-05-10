Object:
- A base class that allows a class to be added to the scene graph

Component:
- A base class that signifies that a class can be added as a component
- 

Shader:
- holds methods to activate shader program
- holds a list of uniforms and methods to set those uniforms
- will take a texture object as a paremeter

Material:
- A material class holds:
	- Inherit from shader:
		- a shader reference
		- uniform setters for shader properties (float, vec3, mat4, etc.)
	- one or more textures

Renderer:
- an ECS component base class
- it holds:
	- shared materials
	- whether or not an object is visible to any camera
- Has a virtual draw() method that will be overriden by different renderer types.

MeshRenderer:
- Inherits the Renderer base class
- also holds vertex buffer, index buffer.
- Overrides the draw() method using glDrawElements and all that.
