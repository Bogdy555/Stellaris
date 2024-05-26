#version 330 core



struct CameraStruct
{
	vec2 Position;
	float Angle;
	float Fov;
	float ZNear;
	float ZFar;
};

struct MeshWorldDataStruct
{
	vec3 Position;
	float Angle;
	vec2 Scale;
};

struct MaterialStruct
{
	sampler2D TextureAlbedo;
	vec4 Color;
	vec2 Start;
	vec2 Size;
};



layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec4 v_Color;
layout (location = 2) in vec2 v_TextureCoords;



uniform CameraStruct u_Camera;
uniform MeshWorldDataStruct u_WorldData;
uniform MaterialStruct u_Material;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_MVP;



out vec3 vf_Position;
out vec4 vf_Color;
out vec2 vf_TextureCoords;



void main()
{
	vf_Position = v_Position;
	vf_Color = v_Color;
	vf_TextureCoords = v_TextureCoords;

	gl_Position = u_MVP * vec4(v_Position, 1.0f);
}
