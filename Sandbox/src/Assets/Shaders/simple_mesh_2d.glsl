#type vertex
#version 430 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coord;

//uniform variables
uniform mat4 uniform_viewprojection;
uniform mat4 uniform_transform;

//output variables
out vec2 texture_coord;


void main()
{	
	gl_Position 	= uniform_viewprojection * uniform_transform * vec4(a_position, 1.0f);
	texture_coord 	= a_texture_coord;
}

#type fragment
#version  430 core

in vec2 texture_coord;

//uniform variables
uniform sampler2D 	uniform_texture;
uniform vec4 		uniform_tex_tint_color;
uniform float 		uniform_tex_tiling_factor;

// output variables
out vec4 output_color;

void main()
{
	output_color = texture(uniform_texture, texture_coord * uniform_tex_tiling_factor) * uniform_tex_tint_color;
}



