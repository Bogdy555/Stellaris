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



in vec3 vf_Position;
in vec4 vf_Color;
in vec2 vf_TextureCoords;



uniform CameraStruct u_Camera;
uniform MeshWorldDataStruct u_WorldData;
uniform MaterialStruct u_Material;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_MVP;



out vec4 f_Color;



void main()
{
	f_Color = vf_Color * texture(u_Material.TextureAlbedo, vf_TextureCoords * u_Material.Size + u_Material.Start) * u_Material.Color;
}
